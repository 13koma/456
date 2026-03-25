#!/usr/bin/env python3
import math
import time
from dataclasses import dataclass
from typing import Optional

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseStamped, TwistStamped
from sensor_msgs.msg import JointState
from std_srvs.srv import Trigger
from jaka_msgs.srv import GetIK, Move


@dataclass
class Pose3:
    x: float
    y: float
    z: float


class JakaDynamicGripperExec(Node):
    def __init__(self) -> None:
        super().__init__("jaka_dynamic_gripper_exec")

        # Topics
        self.declare_parameter("object_center_topic", "/grasp_inference_node/object_center_base")
        self.declare_parameter("grasp_pose_topic", "/grasp_inference_node/grasp_pose_gripper")
        self.declare_parameter("tool_topic", "/jaka_driver/tool_position")
        self.declare_parameter("joint_topic", "/jaka_driver/joint_position")

        # Stage 1: coarse approach to object center
        self.declare_parameter("coarse_x_offset_m", 0.0)
        self.declare_parameter("coarse_y_offset_m", 0.0)
        self.declare_parameter("coarse_z_offset_m", 0.0)
        self.declare_parameter("pregrasp_above_m", 0.10)

        # Stage 2: fresh grasp pose after reset
        self.declare_parameter("fine_x_offset_m", 0.0)
        self.declare_parameter("fine_y_offset_m", 0.0)
        self.declare_parameter("fine_z_offset_m", 0.0)
        self.declare_parameter("grasp_above_m", 0.03)

        # Motion / timing
        self.declare_parameter("max_xy_step_m", 0.04)
        self.declare_parameter("max_z_step_m", 0.04)
        self.declare_parameter("xy_tol_m", 0.008)
        self.declare_parameter("z_tol_m", 0.008)
        self.declare_parameter("max_stage_iterations", 12)
        self.declare_parameter("wait_after_move_sec", 1.0)
        self.declare_parameter("wait_pose_timeout_sec", 6.0)
        self.declare_parameter("mvvelo", 0.2)
        self.declare_parameter("mvacc", 0.2)
        self.declare_parameter("lift_up_m", 0.08)
        self.declare_parameter("settle_after_pregrasp_sec", 0.5)
        self.declare_parameter("fresh_grasp_timeout_sec", 10.0)
        self.declare_parameter("reset_accumulator_service", "/heightmap_node/reset_accumulator")

        # IK orientation strategy
        self.declare_parameter("use_fixed_rpy_for_ik", False)
        self.declare_parameter("fixed_roll_deg", 0.0)
        self.declare_parameter("fixed_pitch_deg", 0.0)
        self.declare_parameter("fixed_yaw_deg", 0.0)

        # Behavior
        self.declare_parameter("skip_initialize", True)
        self.declare_parameter("dry_run", False)
        self.declare_parameter("preview_only", False)          # stop after stage 1
        self.declare_parameter("stop_after_stage2", False)     # stop after fresh grasp pose approach
        self.declare_parameter("preview_hold_sec", 5.0)
        self.declare_parameter("skip_gripper_open_in_preview", True)
        self.declare_parameter("return_to_start_on_preview", True)
        self.declare_parameter("return_to_start_on_failure", True)
        self.declare_parameter("return_to_start_on_success", False)

        # State
        self.object_center: Optional[Pose3] = None
        self.grasp_pose: Optional[Pose3] = None
        self.tool: Optional[tuple[float, float, float, float, float, float]] = None
        self.joints: Optional[list[float]] = None
        self.object_center_count = 0
        self.grasp_pose_count = 0

        # Subs
        self.create_subscription(
            PoseStamped,
            self.get_parameter("object_center_topic").value,
            self._on_object_center,
            10,
        )
        self.create_subscription(
            PoseStamped,
            self.get_parameter("grasp_pose_topic").value,
            self._on_grasp_pose,
            10,
        )
        self.create_subscription(
            TwistStamped,
            self.get_parameter("tool_topic").value,
            self._on_tool,
            10,
        )
        self.create_subscription(
            JointState,
            self.get_parameter("joint_topic").value,
            self._on_joint,
            10,
        )

        # Services
        self.ik_client = self.create_client(GetIK, "/jaka_driver/get_ik")
        self.move_client = self.create_client(Move, "/jaka_driver/joint_move")
        self.reset_client = self.create_client(
            Trigger, self.get_parameter("reset_accumulator_service").value
        )
        self.gripper_init_client = self.create_client(Trigger, "/dh_gripper_node/initialize")
        self.gripper_open_client = self.create_client(Trigger, "/dh_gripper_node/open")
        self.gripper_close_client = self.create_client(Trigger, "/dh_gripper_node/close")

    # ---------- callbacks ----------
    def _on_object_center(self, msg: PoseStamped) -> None:
        self.object_center = Pose3(
            float(msg.pose.position.x),
            float(msg.pose.position.y),
            float(msg.pose.position.z),
        )
        self.object_center_count += 1

    def _on_grasp_pose(self, msg: PoseStamped) -> None:
        self.grasp_pose = Pose3(
            float(msg.pose.position.x),
            float(msg.pose.position.y),
            float(msg.pose.position.z),
        )
        self.grasp_pose_count += 1

    def _on_tool(self, msg: TwistStamped) -> None:
        # xyz in mm, rpy in degrees
        self.tool = (
            float(msg.twist.linear.x) * 0.001,
            float(msg.twist.linear.y) * 0.001,
            float(msg.twist.linear.z) * 0.001,
            math.radians(float(msg.twist.angular.x)),
            math.radians(float(msg.twist.angular.y)),
            math.radians(float(msg.twist.angular.z)),
        )

    def _on_joint(self, msg: JointState) -> None:
        if len(msg.position) >= 6:
            self.joints = [float(x) for x in msg.position[:6]]

    # ---------- generic helpers ----------
    def spin_brief(self, sec: float = 0.2) -> None:
        end = time.time() + sec
        while rclpy.ok() and time.time() < end:
            rclpy.spin_once(self, timeout_sec=0.05)

    def ready(self) -> bool:
        return (
            self.object_center is not None
            and self.grasp_pose is not None
            and self.tool is not None
            and self.joints is not None
        )

    def current_pose3(self) -> Pose3:
        if self.tool is None:
            raise RuntimeError("tool pose is not available")
        return Pose3(self.tool[0], self.tool[1], self.tool[2])

    def current_rpy(self) -> tuple[float, float, float]:
        if self.tool is None:
            raise RuntimeError("tool pose is not available")
        return self.tool[3], self.tool[4], self.tool[5]

    @staticmethod
    def rpy_deg_str(rpy: tuple[float, float, float]) -> str:
        return "({:.1f}, {:.1f}, {:.1f}) deg".format(
            math.degrees(rpy[0]), math.degrees(rpy[1]), math.degrees(rpy[2])
        )

    def ik_rpy(self) -> tuple[float, float, float]:
        if bool(self.get_parameter("use_fixed_rpy_for_ik").value):
            return (
                math.radians(float(self.get_parameter("fixed_roll_deg").value)),
                math.radians(float(self.get_parameter("fixed_pitch_deg").value)),
                math.radians(float(self.get_parameter("fixed_yaw_deg").value)),
            )
        return self.current_rpy()

    def with_offsets(self, pose: Pose3, prefix: str) -> Pose3:
        return Pose3(
            pose.x + float(self.get_parameter(f"{prefix}_x_offset_m").value),
            pose.y + float(self.get_parameter(f"{prefix}_y_offset_m").value),
            pose.z + float(self.get_parameter(f"{prefix}_z_offset_m").value),
        )

    def maybe_return_to_start(self, start_pose: Pose3, reason: str) -> bool:
        should_return = bool(self.get_parameter(reason).value)
        if not should_return:
            self.get_logger().info(f"{reason}=false, keeping current pose")
            return True
        self.get_logger().warn(
            f"Returning to start pose because {reason}=true | "
            f"start=({start_pose.x:.3f}, {start_pose.y:.3f}, {start_pose.z:.3f})"
        )
        return self.move_until_reached(start_pose, "RETURN start")

    def call_trigger(self, client, name: str, timeout_sec: float = 10.0) -> bool:
        if not client.wait_for_service(timeout_sec=5.0):
            self.get_logger().error(f"Service unavailable: {name}")
            return False
        fut = client.call_async(Trigger.Request())
        rclpy.spin_until_future_complete(self, fut, timeout_sec=timeout_sec)
        if not fut.done() or fut.result() is None:
            self.get_logger().error(f"{name}: no response")
            return False
        res = fut.result()
        self.get_logger().info(f"{name}: success={res.success}, msg={res.message}")
        return bool(res.success)

    def within_tolerance(self, goal: Pose3) -> bool:
        if self.tool is None:
            return False
        cur_x, cur_y, cur_z, _, _, _ = self.tool
        xy_err = math.hypot(goal.x - cur_x, goal.y - cur_y)
        z_err = abs(goal.z - cur_z)
        return xy_err <= float(self.get_parameter("xy_tol_m").value) and z_err <= float(
            self.get_parameter("z_tol_m").value
        )

    def wait_until_tool_near(self, goal: Pose3, timeout_sec: float) -> bool:
        end = time.time() + timeout_sec
        while rclpy.ok() and time.time() < end:
            self.spin_brief(0.1)
            if self.within_tolerance(goal):
                return True
        return self.within_tolerance(goal)

    def move_one_step_towards(self, goal: Pose3) -> bool:
        if self.tool is None or self.joints is None:
            self.get_logger().error("tool/joints are not ready")
            return False
        if not self.ik_client.wait_for_service(timeout_sec=5.0):
            self.get_logger().error("get_ik unavailable")
            return False
        if not self.move_client.wait_for_service(timeout_sec=5.0):
            self.get_logger().error("joint_move unavailable")
            return False

        cur_x, cur_y, cur_z, cur_rx, cur_ry, cur_rz = self.tool
        cmd_rx, cmd_ry, cmd_rz = self.ik_rpy()
        max_xy = float(self.get_parameter("max_xy_step_m").value)
        max_z = float(self.get_parameter("max_z_step_m").value)

        def clip(v: float, lo: float, hi: float) -> float:
            return max(lo, min(hi, v))

        cmd_x = cur_x + clip(goal.x - cur_x, -max_xy, max_xy)
        cmd_y = cur_y + clip(goal.y - cur_y, -max_xy, max_xy)
        cmd_z = cur_z + clip(goal.z - cur_z, -max_z, max_z)

        self.get_logger().info(
            f"CURRENT=({cur_x:.3f},{cur_y:.3f},{cur_z:.3f}) "
            f"GOAL=({goal.x:.3f},{goal.y:.3f},{goal.z:.3f}) "
            f"CMD=({cmd_x:.3f},{cmd_y:.3f},{cmd_z:.3f})"
        )
        self.get_logger().info(
            f"IK RPY current={self.rpy_deg_str((cur_rx, cur_ry, cur_rz))} "
            f"cmd={self.rpy_deg_str((cmd_rx, cmd_ry, cmd_rz))} "
            f"use_fixed={bool(self.get_parameter('use_fixed_rpy_for_ik').value)}"
        )

        ik_req = GetIK.Request()
        ik_req.ref_joint = self.joints
        ik_req.cartesian_pose = [
            cmd_x * 1000.0,
            cmd_y * 1000.0,
            cmd_z * 1000.0,
            cmd_rx,
            cmd_ry,
            cmd_rz,
        ]
        fut = self.ik_client.call_async(ik_req)
        rclpy.spin_until_future_complete(self, fut, timeout_sec=5.0)
        if not fut.done() or fut.result() is None:
            self.get_logger().error("get_ik returned no response")
            return False

        ik_res = fut.result()
        joints = list(ik_res.joint)
        self.get_logger().info(f"IK: {ik_res.message} | joints={joints[:6]}")
        if len(joints) < 6 or any(abs(j) > 9000 for j in joints[:6]):
            self.get_logger().error("IK returned invalid joints")
            return False

        mv_req = Move.Request()
        mv_req.pose = joints[:6]
        mv_req.has_ref = False
        mv_req.ref_joint = []
        mv_req.mvvelo = float(self.get_parameter("mvvelo").value)
        mv_req.mvacc = float(self.get_parameter("mvacc").value)
        mv_req.mvtime = 0.0
        mv_req.mvradii = 0.0
        mv_req.coord_mode = 0
        mv_req.index = 0

        if bool(self.get_parameter("dry_run").value):
            self.get_logger().warn("dry_run=true, joint_move skipped")
            return True

        mv_fut = self.move_client.call_async(mv_req)
        rclpy.spin_until_future_complete(self, mv_fut, timeout_sec=30.0)
        if not mv_fut.done() or mv_fut.result() is None:
            self.get_logger().error("joint_move returned no response")
            return False

        mv_res = mv_fut.result()
        self.get_logger().info(f"joint_move: ret={mv_res.ret} msg={mv_res.message}")
        return mv_res.ret in (0, 1)

    def move_until_reached(self, goal: Pose3, stage_name: str) -> bool:
        max_iters = int(self.get_parameter("max_stage_iterations").value)
        wait_after = float(self.get_parameter("wait_after_move_sec").value)
        wait_pose_timeout = float(self.get_parameter("wait_pose_timeout_sec").value)

        self.get_logger().info(
            f"{stage_name}: target=({goal.x:.3f}, {goal.y:.3f}, {goal.z:.3f})"
        )
        for i in range(max_iters):
            self.spin_brief(0.2)
            if self.within_tolerance(goal):
                self.get_logger().info(f"{stage_name}: reached without extra move")
                return True

            if not self.move_one_step_towards(goal):
                self.get_logger().error(f"{stage_name}: step {i+1}/{max_iters} failed")
                return False

            time.sleep(wait_after)
            reached = self.wait_until_tool_near(goal, wait_pose_timeout)
            self.get_logger().info(
                f"{stage_name}: step {i+1}/{max_iters} done | reached={reached}"
            )
            if reached:
                return True

        self.get_logger().error(f"{stage_name}: max iterations exceeded")
        return False

    def wait_for_new_grasp_pose(self, old_count: int, timeout_sec: float) -> Optional[Pose3]:
        deadline = time.monotonic() + timeout_sec
        while rclpy.ok() and time.monotonic() < deadline:
            self.spin_brief(0.1)
            if self.grasp_pose is not None and self.grasp_pose_count > old_count:
                return self.grasp_pose
        return None

    # ---------- main sequence ----------
    def run(self) -> bool:
        dry_run = bool(self.get_parameter("dry_run").value)
        preview_only = bool(self.get_parameter("preview_only").value)
        stop_after_stage2 = bool(self.get_parameter("stop_after_stage2").value)
        skip_initialize = bool(self.get_parameter("skip_initialize").value)
        skip_open_in_preview = bool(self.get_parameter("skip_gripper_open_in_preview").value)

        start_pose = self.current_pose3()
        start_rpy = self.current_rpy()
        self.get_logger().info(
            f"Saved start pose=({start_pose.x:.3f}, {start_pose.y:.3f}, {start_pose.z:.3f})"
        )
        self.get_logger().info(
            f"Start tool RPY={self.rpy_deg_str(start_rpy)} | "
            f"fixed IK enabled={bool(self.get_parameter('use_fixed_rpy_for_ik').value)}"
        )

        if not skip_initialize and not dry_run:
            self.get_logger().info("Initializing gripper")
            init_ok = self.call_trigger(self.gripper_init_client, "initialize")
            if not init_ok:
                self.get_logger().warn("initialize failed, continuing")
        else:
            self.get_logger().info("Skipping gripper initialize")

        need_open = not dry_run and not (preview_only and skip_open_in_preview)
        if need_open:
            self.get_logger().info("Opening gripper")
            if not self.call_trigger(self.gripper_open_client, "open"):
                self.maybe_return_to_start(start_pose, "return_to_start_on_failure")
                return False
            self.spin_brief(0.5)
        else:
            self.get_logger().info("Skipping gripper open")

        # Stage 1: coarse center -> pregrasp
        if self.object_center is None:
            self.get_logger().error("object_center is not available")
            self.maybe_return_to_start(start_pose, "return_to_start_on_failure")
            return False

        coarse_target = self.with_offsets(self.object_center, "coarse")
        pre_goal = Pose3(
            coarse_target.x,
            coarse_target.y,
            coarse_target.z + float(self.get_parameter("pregrasp_above_m").value),
        )
        self.get_logger().info(
            f"STAGE 1 source object_center=({self.object_center.x:.3f}, {self.object_center.y:.3f}, {self.object_center.z:.3f})"
        )
        self.get_logger().info(
            f"STAGE 1 coarse target=({coarse_target.x:.3f}, {coarse_target.y:.3f}, {coarse_target.z:.3f})"
        )
        if not self.move_until_reached(pre_goal, "STAGE 1 pregrasp"):
            self.maybe_return_to_start(start_pose, "return_to_start_on_failure")
            return False

        if preview_only:
            hold = float(self.get_parameter("preview_hold_sec").value)
            self.get_logger().warn("preview_only=true, stopping after coarse pregrasp")
            if hold > 0.0:
                self.get_logger().info(f"Holding at preview pose for {hold:.1f}s")
                self.spin_brief(hold)
            self.maybe_return_to_start(start_pose, "return_to_start_on_preview")
            return True

        # Stage 2: reset and wait for fresh grasp pose
        settle = float(self.get_parameter("settle_after_pregrasp_sec").value)
        if settle > 0.0:
            self.get_logger().info(f"Settling after pregrasp for {settle:.2f}s")
            self.spin_brief(settle)

        grasp_count_before_reset = self.grasp_pose_count
        self.get_logger().info(
            f"Resetting accumulator before fine pose refresh | current grasp_count={grasp_count_before_reset}"
        )
        reset_ok = self.call_trigger(self.reset_client, "reset_accumulator")
        if not reset_ok:
            self.get_logger().warn("reset_accumulator failed, continuing anyway")

        fresh_timeout = float(self.get_parameter("fresh_grasp_timeout_sec").value)
        fresh_pose = self.wait_for_new_grasp_pose(grasp_count_before_reset, fresh_timeout)
        if fresh_pose is None:
            self.get_logger().error(
                f"Timeout waiting for fresh grasp pose after reset ({fresh_timeout:.1f}s)"
            )
            self.maybe_return_to_start(start_pose, "return_to_start_on_failure")
            return False

        fine_target = self.with_offsets(fresh_pose, "fine")
        grasp_goal = Pose3(
            fine_target.x,
            fine_target.y,
            fine_target.z + float(self.get_parameter("grasp_above_m").value),
        )
        self.get_logger().info(
            f"STAGE 2 fresh grasp_pose=({fresh_pose.x:.3f}, {fresh_pose.y:.3f}, {fresh_pose.z:.3f})"
        )
        self.get_logger().info(
            f"STAGE 2 fine target=({fine_target.x:.3f}, {fine_target.y:.3f}, {fine_target.z:.3f})"
        )

        if not self.move_until_reached(grasp_goal, "STAGE 2 fine approach"):
            self.maybe_return_to_start(start_pose, "return_to_start_on_failure")
            return False

        if stop_after_stage2:
            hold = float(self.get_parameter("preview_hold_sec").value)
            self.get_logger().warn("stop_after_stage2=true, stopping before gripper close")
            if hold > 0.0:
                self.get_logger().info(f"Holding at stage2 pose for {hold:.1f}s")
                self.spin_brief(hold)
            self.maybe_return_to_start(start_pose, "return_to_start_on_preview")
            return True

        # Stage 3: close gripper
        if not dry_run:
            self.get_logger().info("STAGE 3 close gripper")
            if not self.call_trigger(self.gripper_close_client, "close"):
                self.maybe_return_to_start(start_pose, "return_to_start_on_failure")
                return False
            self.spin_brief(1.0)
        else:
            self.get_logger().warn("dry_run=true, gripper close skipped")

        # Stage 4: lift straight up from current TCP
        if self.tool is None:
            self.get_logger().error("tool pose lost before lift")
            self.maybe_return_to_start(start_pose, "return_to_start_on_failure")
            return False

        cur_x, cur_y, cur_z, _, _, _ = self.tool
        lift_goal = Pose3(cur_x, cur_y, cur_z + float(self.get_parameter("lift_up_m").value))
        if not self.move_until_reached(lift_goal, "STAGE 4 lift"):
            self.maybe_return_to_start(start_pose, "return_to_start_on_failure")
            return False

        self.get_logger().info("Dynamic pick sequence finished")
        self.maybe_return_to_start(start_pose, "return_to_start_on_success")
        return True


def main() -> None:
    rclpy.init()
    node = JakaDynamicGripperExec()
    try:
        node.get_logger().info("Waiting for object_center / grasp_pose / tool / joints ...")
        while rclpy.ok() and not node.ready():
            rclpy.spin_once(node, timeout_sec=0.1)

        if not rclpy.ok():
            return

        ok = node.run()
        if ok:
            node.get_logger().info("Done")
        else:
            node.get_logger().error("Sequence failed")
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
