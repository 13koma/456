#!/usr/bin/env python3
"""
jaka_gripper_exec.py — Dynamic pick-and-place for JAKA Zu12 + DH AG-95 gripper.

Architecture mirrors gripper_exec.py (UR5 original) but replaces URScript movement
with JAKA get_ik + joint_move. Threading model is identical:
  - ROS spin runs in main thread
  - Grasp sequence runs in a daemon thread
  - Fresh pose is latched before Stage 2 motion begins

Sequence (dynamic mode):
  1. Return to home joints
  2. Open gripper
  3. Move to pre-grasp (above object_center + pregrasp_z_offset)
  4. Reset accumulator, wait for fresh grasp_pose
  5. Latch fresh pose → move to grasp XYZ (grasp_z_offset below object)
  6. Close gripper
  7. Lift
  8. Return to home joints

Parameters (ros2 run / --ros-args -p):
  object_center_topic   (str)   /grasp_inference_node/object_center_base
  grasp_pose_topic      (str)   /grasp_inference_node/grasp_pose_base
  reset_service         (str)   /heightmap_node/reset_accumulator
  tool_topic            (str)   /jaka_driver/tool_position
  joint_topic           (str)   /jaka_driver/joint_states

  home_joints           (list[float])  6 joint angles in radians
  pregrasp_z_offset     (float) meters above object for pre-grasp     default 0.10
  grasp_z_offset        (float) meters above object for grasp          default 0.02
  lift_height           (float) meters to lift after close             default 0.08

  x_offset_m            (float) calibration X offset                   default 0.0
  y_offset_m            (float) calibration Y offset                   default 0.0
  z_offset_m            (float) calibration Z offset                   default 0.0

  fresh_pose_timeout    (float) seconds to wait for fresh pose         default 15.0
  move_velocity         (float) joint move velocity 0..1               default 0.2
  move_acceleration     (float) joint move acceleration 0..1           default 0.2
  xy_tolerance          (float) meters tolerance for reached check     default 0.015
  z_tolerance           (float) meters tolerance for reached check     default 0.015

  stop_after_pregrasp   (bool)  stop after stage 3 (debug)             default false
  stop_after_grasp      (bool)  stop after stage 5, skip close (debug) default false
  dry_run               (bool)  skip all hardware commands             default false
  skip_initialize       (bool)  skip gripper initialize                default true
"""

from __future__ import annotations

import math
import threading
import time
from typing import Optional

import rclpy
from rclpy.node import Node
from rclpy.time import Time
from rclpy.duration import Duration

from geometry_msgs.msg import TwistStamped, PoseStamped
from sensor_msgs.msg import JointState
from std_srvs.srv import Trigger

from jaka_msgs.srv import GetIK, Move


# ---------------------------------------------------------------------------
# helpers
# ---------------------------------------------------------------------------

def clip(v: float, lo: float, hi: float) -> float:
    return max(lo, min(hi, v))


class Pose3:
    def __init__(self, x: float, y: float, z: float):
        self.x = x
        self.y = y
        self.z = z

    def __repr__(self) -> str:
        return f"({self.x:.3f}, {self.y:.3f}, {self.z:.3f})"


# ---------------------------------------------------------------------------
# Node
# ---------------------------------------------------------------------------

class JakaGripperExec(Node):

    def __init__(self):
        super().__init__("jaka_gripper_exec")

        # --- topics / services ---
        self.declare_parameter("object_center_topic", "/grasp_inference_node/object_center_base")
        self.declare_parameter("grasp_pose_topic",    "/grasp_inference_node/grasp_pose_base")
        self.declare_parameter("reset_service",       "/heightmap_node/reset_accumulator")
        self.declare_parameter("tool_topic",          "/jaka_driver/tool_position")
        self.declare_parameter("joint_topic",         "/jaka_driver/joint_states")

        # --- home ---
        self.declare_parameter("home_joints", [1.57, 1.57, 1.9, 2.8, 1.57, 2.355])

        # --- motion geometry ---
        self.declare_parameter("pregrasp_z_offset",  0.10)
        self.declare_parameter("grasp_z_offset",     0.02)
        self.declare_parameter("lift_height",        0.08)

        # --- calibration offsets (applied to both pre-grasp and grasp targets) ---
        self.declare_parameter("x_offset_m", 0.0)
        self.declare_parameter("y_offset_m", 0.0)
        self.declare_parameter("z_offset_m", 0.0)

        # --- timing / tolerances ---
        self.declare_parameter("fresh_pose_timeout", 15.0)
        self.declare_parameter("move_velocity",      0.2)
        self.declare_parameter("move_acceleration",  0.2)
        self.declare_parameter("xy_tolerance",       0.015)
        self.declare_parameter("z_tolerance",        0.015)
        self.declare_parameter("wait_after_move_sec", 0.3)
        self.declare_parameter("wait_after_grip_sec", 1.0)

        # --- debug flags ---
        self.declare_parameter("stop_after_pregrasp", False)
        self.declare_parameter("stop_after_grasp",    False)
        self.declare_parameter("dry_run",             False)
        self.declare_parameter("skip_initialize",     True)

        # --- state ---
        self._tool:   Optional[tuple] = None   # (x,y,z, rx,ry,rz) in meters+radians
        self._joints: Optional[list]  = None   # 6 floats radians

        self._object_center: Optional[Pose3] = None
        self._object_center_event = threading.Event()

        self._fresh_grasp: Optional[Pose3] = None
        self._fresh_grasp_event = threading.Event()

        self._sequence_started = False

        # --- subscriptions ---
        self.create_subscription(
            PoseStamped,
            self.get_parameter("object_center_topic").value,
            self._on_object_center, 10,
        )
        self.create_subscription(
            PoseStamped,
            self.get_parameter("grasp_pose_topic").value,
            self._on_grasp_pose, 10,
        )
        self.create_subscription(
            TwistStamped,
            self.get_parameter("tool_topic").value,
            self._on_tool, 10,
        )
        self.create_subscription(
            JointState,
            self.get_parameter("joint_topic").value,
            self._on_joints, 10,
        )

        # --- service clients ---
        self._ik_client    = self.create_client(GetIK,  "/jaka_driver/get_ik")
        self._move_client  = self.create_client(Move,   "/jaka_driver/joint_move")
        self._reset_client = self.create_client(Trigger, self.get_parameter("reset_service").value)
        self._gripper_init  = self.create_client(Trigger, "/dh_gripper_node/initialize")
        self._gripper_open  = self.create_client(Trigger, "/dh_gripper_node/open")
        self._gripper_close = self.create_client(Trigger, "/dh_gripper_node/close")

        self.get_logger().info("JakaGripperExec ready — waiting for first object_center_base ...")

    # ------------------------------------------------------------------
    # callbacks
    # ------------------------------------------------------------------

    def _on_tool(self, msg: TwistStamped):
        # tool_position publishes mm + degrees → convert to m + radians
        lv = msg.twist.linear
        av = msg.twist.angular
        self._tool = (
            lv.x / 1000.0, lv.y / 1000.0, lv.z / 1000.0,
            math.radians(av.x), math.radians(av.y), math.radians(av.z),
        )

    def _on_joints(self, msg: JointState):
        self._joints = list(msg.position)

    def _on_object_center(self, msg: PoseStamped):
        p = msg.pose.position
        self._object_center = Pose3(p.x, p.y, p.z)
        self._object_center_event.set()

    def _on_grasp_pose(self, msg: PoseStamped):
        p = msg.pose.position
        self._fresh_grasp = Pose3(p.x, p.y, p.z)
        self._fresh_grasp_event.set()

    # ------------------------------------------------------------------
    # ready check
    # ------------------------------------------------------------------

    def ready(self) -> bool:
        return self._tool is not None and self._joints is not None

    # ------------------------------------------------------------------
    # movement primitives
    # ------------------------------------------------------------------

    def _with_offsets(self, pose: Pose3) -> Pose3:
        return Pose3(
            pose.x + float(self.get_parameter("x_offset_m").value),
            pose.y + float(self.get_parameter("y_offset_m").value),
            pose.z + float(self.get_parameter("z_offset_m").value),
        )

    def _move_to_xyz(self, target: Pose3, label: str) -> bool:
        """Send one IK + joint_move command to target XYZ, keeping current RPY."""
        if self._tool is None or self._joints is None:
            self.get_logger().error(f"{label}: tool/joints not ready")
            return False

        if not self._ik_client.wait_for_service(timeout_sec=5.0):
            self.get_logger().error(f"{label}: get_ik service unavailable")
            return False
        if not self._move_client.wait_for_service(timeout_sec=5.0):
            self.get_logger().error(f"{label}: joint_move service unavailable")
            return False

        cur_x, cur_y, cur_z, cur_rx, cur_ry, cur_rz = self._tool

        self.get_logger().info(
            f"{label}: current=({cur_x:.3f},{cur_y:.3f},{cur_z:.3f}) "
            f"target={target}"
        )

        if bool(self.get_parameter("dry_run").value):
            self.get_logger().warn(f"{label}: dry_run=true, skipping IK+move")
            return True

        ik_req = GetIK.Request()
        ik_req.ref_joint = self._joints
        ik_req.cartesian_pose = [
            target.x * 1000.0,
            target.y * 1000.0,
            target.z * 1000.0,
            cur_rx,   # keep current orientation
            cur_ry,
            cur_rz,
        ]

        fut = self._ik_client.call_async(ik_req)
        rclpy.spin_until_future_complete(self, fut, timeout_sec=5.0)
        if not fut.done() or fut.result() is None:
            self.get_logger().error(f"{label}: IK no response")
            return False

        res = fut.result()
        joints = list(res.joint)
        self.get_logger().info(f"{label}: IK {res.message} | joints={[f'{j:.3f}' for j in joints[:6]]}")
        if len(joints) < 6 or any(abs(j) > 9000 for j in joints[:6]):
            self.get_logger().error(f"{label}: IK invalid joints")
            return False

        mv_req = Move.Request()
        mv_req.pose      = joints[:6]
        mv_req.has_ref   = False
        mv_req.ref_joint = []
        mv_req.mvvelo    = float(self.get_parameter("move_velocity").value)
        mv_req.mvacc     = float(self.get_parameter("move_acceleration").value)
        mv_req.mvtime    = 0.0
        mv_req.mvradii   = 0.0
        mv_req.coord_mode = 0
        mv_req.index     = 0

        mv_fut = self._move_client.call_async(mv_req)
        rclpy.spin_until_future_complete(self, mv_fut, timeout_sec=30.0)
        if not mv_fut.done() or mv_fut.result() is None:
            self.get_logger().error(f"{label}: joint_move no response")
            return False

        mv_res = mv_fut.result()
        self.get_logger().info(f"{label}: joint_move ret={mv_res.ret} msg={mv_res.message}")
        return mv_res.ret in (0, 1)

    def _move_to_home_joints(self, label: str = "home") -> bool:
        """Move directly to home joint configuration."""
        home = list(self.get_parameter("home_joints").value)
        if len(home) < 6:
            self.get_logger().error("home_joints must have 6 values")
            return False

        if bool(self.get_parameter("dry_run").value):
            self.get_logger().warn(f"{label}: dry_run=true, skipping home move")
            return True

        if not self._move_client.wait_for_service(timeout_sec=5.0):
            self.get_logger().error(f"{label}: joint_move unavailable")
            return False

        mv_req = Move.Request()
        mv_req.pose      = home
        mv_req.has_ref   = False
        mv_req.ref_joint = []
        mv_req.mvvelo    = float(self.get_parameter("move_velocity").value)
        mv_req.mvacc     = float(self.get_parameter("move_acceleration").value)
        mv_req.mvtime    = 0.0
        mv_req.mvradii   = 0.0
        mv_req.coord_mode = 0
        mv_req.index     = 0

        self.get_logger().info(f"{label}: moving to home joints {home}")
        fut = self._move_client.call_async(mv_req)
        rclpy.spin_until_future_complete(self, fut, timeout_sec=30.0)
        if not fut.done() or fut.result() is None:
            self.get_logger().error(f"{label}: joint_move no response")
            return False

        res = fut.result()
        self.get_logger().info(f"{label}: joint_move ret={res.ret} msg={res.message}")
        return res.ret in (0, 1)

    def _within_tolerance(self, target: Pose3) -> bool:
        if self._tool is None:
            return False
        cx, cy, cz = self._tool[0], self._tool[1], self._tool[2]
        xy_err = math.sqrt((cx - target.x)**2 + (cy - target.y)**2)
        z_err  = abs(cz - target.z)
        return (xy_err <= float(self.get_parameter("xy_tolerance").value) and
                z_err  <= float(self.get_parameter("z_tolerance").value))

    def _wait_until_reached(self, target: Pose3, timeout_sec: float = 15.0) -> bool:
        deadline = time.monotonic() + timeout_sec
        while time.monotonic() < deadline:
            time.sleep(0.1)
            if self._within_tolerance(target):
                return True
        return self._within_tolerance(target)

    def _move_and_wait(self, target: Pose3, label: str, timeout: float = 15.0) -> bool:
        if not self._move_to_xyz(target, label):
            return False
        time.sleep(float(self.get_parameter("wait_after_move_sec").value))
        reached = self._wait_until_reached(target, timeout)
        if not reached:
            self.get_logger().warn(f"{label}: tolerance not reached, continuing anyway")
        return True
    
    def _call_trigger(self, client, label: str) -> bool:
        if bool(self.get_parameter("dry_run").value):
            self.get_logger().warn(f"{label}: dry_run=true, skipping")
            return True
        if not client.wait_for_service(timeout_sec=5.0):
            self.get_logger().error(f"{label}: service unavailable")
            return False
        fut = client.call_async(Trigger.Request())
        rclpy.spin_until_future_complete(self, fut, timeout_sec=10.0)
        if not fut.done() or fut.result() is None:
            self.get_logger().error(f"{label}: no response")
            return False
        res = fut.result()
        self.get_logger().info(f"{label}: success={res.success} msg={res.message}")
        return res.success

    # ------------------------------------------------------------------
    # main sequence (runs in thread)
    # ------------------------------------------------------------------

    def _run_sequence(self):
        t_start = time.perf_counter()
        self.get_logger().info("=" * 60)
        self.get_logger().info("DYNAMIC GRASP SEQUENCE START")
        self.get_logger().info("=" * 60)

        try:
            ok = self._execute()
            elapsed = time.perf_counter() - t_start
            if ok:
                self.get_logger().info(f"SEQUENCE COMPLETED in {elapsed:.1f}s")
            else:
                self.get_logger().error(f"SEQUENCE FAILED after {elapsed:.1f}s")
        except Exception as e:
            self.get_logger().error(f"SEQUENCE EXCEPTION: {e}")
            import traceback
            self.get_logger().error(traceback.format_exc())

    def _execute(self) -> bool:
        dry_run = bool(self.get_parameter("dry_run").value)

        # wait for tool/joints
        self.get_logger().info("[0] Waiting for tool + joint state ...")
        deadline = time.monotonic() + 10.0
        while time.monotonic() < deadline:
            time.sleep(0.1)
            if self.ready():
                break
        if not self.ready():
            self.get_logger().error("[0] tool/joints not ready — abort")
            return False
        # ----------------------------------------------------------------
        # 1. Return to home
        # ----------------------------------------------------------------
        #self.get_logger().info("[1/7] Moving to home joints ...")
        #if not self._move_to_home_joints("home"):
        #    return False
        #time.sleep(2.0)  # wait for motion to complete
        #self.get_logger().info("[1/7] Home reached")

        # ----------------------------------------------------------------
        # 2. Open gripper
        # ----------------------------------------------------------------
        if not dry_run:
            self.get_logger().info("[2/7] Initializing + opening gripper ...")
            if not bool(self.get_parameter("skip_initialize").value):
                self._call_trigger(self._gripper_init, "gripper_init")
            if not self._call_trigger(self._gripper_open, "gripper_open"):
                return False
            time.sleep(float(self.get_parameter("wait_after_grip_sec").value))
        self.get_logger().info("[2/7] Gripper open")

        # ----------------------------------------------------------------
        # 3. Pre-grasp: move above object_center
        # ----------------------------------------------------------------
        self.get_logger().info("[3/7] Waiting for object_center_base ...")
        self._object_center_event.wait(timeout=10.0)
        if self._object_center is None:
            self.get_logger().error("[3/7] No object_center — abort")
            return False

        center = self._with_offsets(self._object_center)
        pregrasp_target = Pose3(
            center.x,
            center.y,
            center.z + float(self.get_parameter("pregrasp_z_offset").value),
        )
        self.get_logger().info(
            f"[3/7] object_center={self._object_center} "
            f"→ pregrasp_target={pregrasp_target}"
        )
        if not self._move_and_wait(pregrasp_target, "pregrasp", timeout=20.0):
            return False
        self.get_logger().info("[3/7] Pre-grasp reached")

        if bool(self.get_parameter("stop_after_pregrasp").value):
            self.get_logger().warn("stop_after_pregrasp=true — stopping here")
            return True

        # ----------------------------------------------------------------
        # 4. Reset accumulator → wait for fresh grasp_pose
        # ----------------------------------------------------------------
        self.get_logger().info("[4/7] Resetting accumulator for fresh pose ...")
        self._fresh_grasp_event.clear()
        self._call_trigger(self._reset_client, "reset_accumulator")

        timeout = float(self.get_parameter("fresh_pose_timeout").value)
        self.get_logger().info(f"[4/7] Waiting for fresh grasp_pose (timeout={timeout}s) ...")

        deadline = time.monotonic() + timeout
        while time.monotonic() < deadline:
            time.sleep(0.1)
            if self._fresh_grasp_event.is_set():
                break
            
        if not self._fresh_grasp_event.is_set() or self._fresh_grasp is None:
            self.get_logger().error(f"[4/7] Timeout waiting for fresh grasp_pose — abort")
            return False

        # LATCH — freeze target for the rest of the sequence
        latched = self._with_offsets(self._fresh_grasp)
        self.get_logger().info(
            f"[4/7] Fresh grasp_pose={self._fresh_grasp} → latched={latched}"
        )

        # ----------------------------------------------------------------
        # 5. Move to grasp XYZ (above object by grasp_z_offset)
        # ----------------------------------------------------------------
        grasp_target = Pose3(
            latched.x,
            latched.y,
            latched.z + float(self.get_parameter("grasp_z_offset").value),
        )
        self.get_logger().info(f"[5/7] Moving to grasp target={grasp_target}")
        if not self._move_and_wait(grasp_target, "grasp_approach", timeout=20.0):
            return False
        self.get_logger().info("[5/7] Grasp position reached")

        if bool(self.get_parameter("stop_after_grasp").value):
            self.get_logger().warn("stop_after_grasp=true — stopping before close")
            return True

        # ----------------------------------------------------------------
        # 6. Close gripper
        # ----------------------------------------------------------------
        if not dry_run:
            self.get_logger().info("[6/7] Closing gripper ...")
            if not self._call_trigger(self._gripper_close, "gripper_close"):
                return False
            time.sleep(float(self.get_parameter("wait_after_grip_sec").value))
        self.get_logger().info("[6/7] Gripper closed")

        # ----------------------------------------------------------------
        # 7. Lift + return home
        # ----------------------------------------------------------------
        if self._tool is None:
            self.get_logger().error("[7/7] tool pose lost — can't lift")
            return False

        cx, cy, cz = self._tool[0], self._tool[1], self._tool[2]
        lift_target = Pose3(cx, cy, cz + float(self.get_parameter("lift_height").value))
        self.get_logger().info(f"[7/7] Lifting to {lift_target}")
        if not self._move_and_wait(lift_target, "lift", timeout=10.0):
            return False

        self.get_logger().info("[7/7] Lifted — returning to home")
        self._move_to_home_joints("home_return")

        return True


# ---------------------------------------------------------------------------
# main
# ---------------------------------------------------------------------------

def main(args=None):
    rclpy.init(args=args)
    node = JakaGripperExec()

    # wait until tool + joints + first object_center are ready
    node.get_logger().info("Waiting for tool / joints / object_center ...")
    while rclpy.ok():
        rclpy.spin_once(node, timeout_sec=0.1)
        if node.ready() and node._object_center is not None:
            break

    if not rclpy.ok():
        return

    node.get_logger().info("All data ready — starting sequence")
    t = threading.Thread(target=node._run_sequence, daemon=True)
    t.start()

    # spin while sequence runs
    while rclpy.ok() and t.is_alive():
        rclpy.spin_once(node, timeout_sec=0.1)

    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
