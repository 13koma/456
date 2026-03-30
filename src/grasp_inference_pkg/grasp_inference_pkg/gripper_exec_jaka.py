"""
gripper_exec_jaka.py — Grasp execution node for JAKA ZU12 + DH AG-95 gripper.
=================================================================================

Drop-in replacement for gripper_exec.py (UR5e version).
Changes vs original:
  1. Robot motion:  URScript (String topic)  →  /jaka_driver/linear_move (service call)
  2. Gripper:       Float32 topic            →  /dh_gripper_node/open & /close services
  3. TCP feedback:  PoseStamped topic        →  /jaka_driver/tool_position (TwistStamped)
  4. Units:         Internal meters (same as model_forward output) → mm at JAKA boundary

Prerequisites (must be running BEFORE this node):
  1. ros2 launch jaka_driver robot_start.launch.py ip:=<robot_ip>
  2. ros2 launch dh_gripper_driver gripper.launch.py port:=/dev/ttyUSB0 auto_init:=true
"""

from __future__ import annotations
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseStamped, TwistStamped
from std_srvs.srv import Trigger
import time
import math
import threading


class GripperExecNode(Node):
    def __init__(self):
        super().__init__("gripper_exec_node")

        self.declare_parameter("grasp_pose_topic", "/model_forward/grasp_pose_gripper")
        self.declare_parameter("tcp_pose_topic", "/jaka_driver/tool_position")
        self.declare_parameter("linear_move_service", "/jaka_driver/linear_move")
        self.declare_parameter("move_velocity_mm_s", 50.0)
        self.declare_parameter("move_acceleration_mm_s2", 50.0)
        self.declare_parameter("gripper_open_service", "/dh_gripper_node/open")
        self.declare_parameter("gripper_close_service", "/dh_gripper_node/close")
        self.declare_parameter("auto_execute", True)
        self.declare_parameter("wait_after_grip", 1.5)
        self.declare_parameter("pre_grasp_offset_y", 0.05)
        self.declare_parameter("lift_height", 0.05)
        self.declare_parameter("home_position", [0.0, 0.0, 0.0, 0.0, 0.0, 0.0])
        self.declare_parameter("above_home_height", 0.15)
        self.declare_parameter("pregrasp_mode", "fixed")
        self.declare_parameter("pregrasp_settle_distance", 0.30)
        self.declare_parameter("pregrasp_z_offset", 0.04)
        self.declare_parameter("fresh_pose_timeout", 30.0)
        self.declare_parameter("object_center_topic", "/grasp_inference_node/object_center_base")
        self.declare_parameter("accumulator_reset_service", "/heightmap_node/reset_accumulator")
        self.declare_parameter("settle_time", 0.3)
        self.declare_parameter("dry_run", False)

        grasp_topic = self.get_parameter("grasp_pose_topic").value
        tcp_topic = self.get_parameter("tcp_pose_topic").value
        linear_move_srv_name = self.get_parameter("linear_move_service").value
        self.move_vel = float(self.get_parameter("move_velocity_mm_s").value)
        self.move_acc = float(self.get_parameter("move_acceleration_mm_s2").value)
        gripper_open_srv_name = self.get_parameter("gripper_open_service").value
        gripper_close_srv_name = self.get_parameter("gripper_close_service").value
        self.auto_execute = bool(self.get_parameter("auto_execute").value)
        self.wait_grip = float(self.get_parameter("wait_after_grip").value)
        self.pre_grasp_y = float(self.get_parameter("pre_grasp_offset_y").value)
        self.lift_height = float(self.get_parameter("lift_height").value)
        home_raw = self.get_parameter("home_position").value
        self.home_pos = [float(v) for v in home_raw]
        self.above_home_height = float(self.get_parameter("above_home_height").value)
        self.pregrasp_mode = (self.get_parameter("pregrasp_mode").value or "fixed").strip().lower()
        self.pregrasp_settle_dist = float(self.get_parameter("pregrasp_settle_distance").value)
        self.pregrasp_z_offset = float(self.get_parameter("pregrasp_z_offset").value)
        self.fresh_pose_timeout = float(self.get_parameter("fresh_pose_timeout").value)
        object_center_topic = self.get_parameter("object_center_topic").value
        accumulator_reset_srv = self.get_parameter("accumulator_reset_service").value
        self.settle_time = float(self.get_parameter("settle_time").value)
        self.dry_run = bool(self.get_parameter("dry_run").value)

        self.latest_grasp_pose: PoseStamped | None = None
        self.current_tcp_mm: list[float] | None = None
        self.is_executing = False
        self.one_shot_done = False
        self._object_center_pose: PoseStamped | None = None
        self._object_center_event = threading.Event()
        self._fresh_grasp_pose: PoseStamped | None = None
        self._fresh_grasp_event = threading.Event()

        # TCP: TwistStamped (linear=xyz_mm, angular=rxryrz_rad)
        self.sub_tcp = self.create_subscription(TwistStamped, tcp_topic, self._on_tcp_pose, 10)

        if self.pregrasp_mode == "dynamic":
            self.sub_object_center = self.create_subscription(PoseStamped, object_center_topic, self._on_object_center, 10)
            self.sub_grasp = self.create_subscription(PoseStamped, grasp_topic, self._on_grasp_pose_dynamic, 10)
            self._reset_acc_client = self.create_client(Trigger, accumulator_reset_srv)
        else:
            self.sub_grasp = self.create_subscription(PoseStamped, grasp_topic, self._on_grasp_pose, 10)

        try:
            from jaka_msgs.srv import Move as JakaMove
            self._JakaMove = JakaMove
        except ImportError:
            self.get_logger().error("jaka_msgs not found!")
            self._JakaMove = None

        self._linear_move_client = self.create_client(self._JakaMove, linear_move_srv_name) if self._JakaMove else None
        self._gripper_open_client = self.create_client(Trigger, gripper_open_srv_name)
        self._gripper_close_client = self.create_client(Trigger, gripper_close_srv_name)

        self.get_logger().info("=" * 60)
        self.get_logger().info("GripperExecNode (JAKA ZU12 + DH AG-95)")
        self.get_logger().info(f"  home (m): [{', '.join(f'{v:.4f}' for v in self.home_pos)}]")
        self.get_logger().info(f"  mode: {self.pregrasp_mode} | vel: {self.move_vel} mm/s")
        self.get_logger().info(f"  tcp_topic: {tcp_topic} (TwistStamped)")

    def _on_tcp_pose(self, msg: TwistStamped):
        self.current_tcp_mm = [
            msg.twist.linear.x, msg.twist.linear.y, msg.twist.linear.z,
            msg.twist.angular.x, msg.twist.angular.y, msg.twist.angular.z,
        ]

    def _on_grasp_pose(self, msg: PoseStamped):
        if self.one_shot_done:
            return
        self.latest_grasp_pose = msg
        self.get_logger().info("GRASP POSE RECEIVED — starting sequence (fixed mode)")
        self.one_shot_done = True
        try: self.destroy_subscription(self.sub_grasp)
        except: pass
        threading.Thread(target=self.execute_grasp_sequence, daemon=True).start()

    def _on_object_center(self, msg: PoseStamped):
        self._object_center_pose = msg
        self._object_center_event.set()

    def _on_grasp_pose_dynamic(self, msg: PoseStamped):
        self._fresh_grasp_pose = msg
        self._fresh_grasp_event.set()

    def execute_grasp_sequence(self):
        self._wait_for_jaka_ready()
        gx = self.latest_grasp_pose.pose.position.x
        gy = self.latest_grasp_pose.pose.position.y
        gz = self.latest_grasp_pose.pose.position.z
        hx, hy, hz = self.home_pos[0], self.home_pos[1], self.home_pos[2]
        hrx, hry, hrz = self.home_pos[3], self.home_pos[4], self.home_pos[5]
        self.is_executing = True
        t_start = time.perf_counter()
        self.get_logger().info(f"  Grasp(m): x={gx:.3f} y={gy:.3f} z={gz:.3f}")
        self.get_logger().info(f"  Home(m):  x={hx:.3f} y={hy:.3f} z={hz:.3f}")
        try:
            self.get_logger().info("[1/8] → home"); self._move_to_xyzrpy(self.home_pos, "home")
            self.get_logger().info("[2/8] gripper open"); self._open_gripper(); time.sleep(self.wait_grip)
            pre_y = gy + self.pre_grasp_y
            self.get_logger().info(f"[3/8] → pre-grasp y={pre_y:.3f}"); self._move_to_xyzrpy([gx, pre_y, gz, hrx, hry, hrz], "pre-grasp")
            self.get_logger().info(f"[4/8] → grasp"); self._move_to_xyzrpy([gx, gy, gz, hrx, hry, hrz], "grasp")
            self.get_logger().info("[5/8] gripper close"); self._close_gripper(); time.sleep(3.0)
            lift_z = gz + self.lift_height
            self.get_logger().info(f"[6/8] → lift z={lift_z:.3f}"); self._move_to_xyzrpy([gx, gy, lift_z, hrx, hry, hrz], "lift")
            above_z = hz + self.above_home_height
            self.get_logger().info(f"[7/8] → above home z={above_z:.3f}"); self._move_to_xyzrpy([hx, hy, above_z, hrx, hry, hrz], "above-home")
            self.get_logger().info("[8/8] → home"); self._move_to_xyzrpy(self.home_pos, "home-return")
            self.get_logger().info(f"DONE in {time.perf_counter()-t_start:.2f}s")
        except Exception as e:
            self.get_logger().error(f"FAILED after {time.perf_counter()-t_start:.2f}s: {e}")
        finally:
            self.is_executing = False

    def _start_dynamic_sequence(self):
        if self.one_shot_done: return
        self.one_shot_done = True
        threading.Thread(target=self._execute_dynamic_sequence, daemon=True).start()

    def _execute_dynamic_sequence(self):
        self.get_logger().info("DYNAMIC GRASP — waiting for object center...")
        self._wait_for_jaka_ready()
        self._object_center_event.clear()
        if not self._object_center_event.wait(timeout=self.fresh_pose_timeout):
            self.get_logger().error("Timeout waiting for object center"); return
        if not rclpy.ok(): return
        center = self._object_center_pose
        try: self.destroy_subscription(self.sub_object_center)
        except: pass
        cx, cy = center.pose.position.x, center.pose.position.y
        hx, hy, hz = self.home_pos[0], self.home_pos[1], self.home_pos[2]
        hrx, hry, hrz = self.home_pos[3], self.home_pos[4], self.home_pos[5]
        dist_to_obj = hy - cy
        pre_x, pre_z = cx, hz + self.pregrasp_z_offset
        pre_y = (cy + self.pregrasp_settle_dist) if dist_to_obj > self.pregrasp_settle_dist else hy
        self.is_executing = True
        t_start = time.perf_counter()
        try:
            self.get_logger().info("[DYN 1/10] → home"); self._move_to_xyzrpy(self.home_pos, "home")
            self.get_logger().info("[DYN 2/10] gripper open"); self._open_gripper(); time.sleep(self.wait_grip)
            self.get_logger().info(f"[DYN 3/10] → pre-grasp"); self._move_to_xyzrpy([pre_x, pre_y, pre_z, hrx, hry, hrz], "pre-grasp")
            self._fresh_grasp_event.clear()
            self.get_logger().info("[DYN 4-5/10] reset acc + wait fresh pose")
            self._call_reset_accumulator(timeout=10.0)
            if not self._fresh_grasp_event.wait(timeout=self.fresh_pose_timeout):
                self.get_logger().error("Timeout waiting for fresh grasp pose"); return
            if not rclpy.ok(): return
            fresh = self._fresh_grasp_pose
            try: self.destroy_subscription(self.sub_grasp)
            except: pass
            gx, gy, gz = fresh.pose.position.x, fresh.pose.position.y, fresh.pose.position.z
            self.get_logger().info(f"[DYN 6/10] → grasp x={gx:.3f} y={gy:.3f} z={gz:.3f}")
            self._move_to_xyzrpy([gx, gy, gz, hrx, hry, hrz], "grasp")
            self.get_logger().info("[DYN 7/10] gripper close"); self._close_gripper(); time.sleep(3.0)
            lift_z = gz + self.lift_height
            self.get_logger().info(f"[DYN 8/10] → lift"); self._move_to_xyzrpy([gx, gy, lift_z, hrx, hry, hrz], "lift")
            above_z = hz + self.above_home_height
            self.get_logger().info(f"[DYN 9/10] → above home + return")
            self._move_to_xyzrpy([hx, hy, above_z, hrx, hry, hrz], "above-home")
            self._move_to_xyzrpy(self.home_pos, "home-return")
            self.get_logger().info(f"[DYN 10/10] DONE in {time.perf_counter()-t_start:.2f}s")
        except Exception as e:
            self.get_logger().error(f"DYNAMIC FAILED after {time.perf_counter()-t_start:.2f}s: {e}")
        finally:
            self.is_executing = False

    def _move_to_xyzrpy(self, pose6, label="target"):
        if self._linear_move_client is None:
            raise RuntimeError("jaka_msgs.srv.Move not available")
        x_m, y_m, z_m, rx, ry, rz = pose6
        x_mm, y_mm, z_mm = x_m * 1000.0, y_m * 1000.0, z_m * 1000.0
        request = self._JakaMove.Request()
        request.pose = [x_mm, y_mm, z_mm, rx, ry, rz]
        request.has_ref = False
        request.ref_joint = [0.0]
        request.mvvelo = self.move_vel
        request.mvacc = self.move_acc
        request.mvtime = 0.0
        request.mvradii = 0.0
        request.coord_mode = 0
        request.index = 0
        self.get_logger().info(f"  JAKA linear_move: [{x_mm:.1f}, {y_mm:.1f}, {z_mm:.1f}, {rx:.3f}, {ry:.3f}, {rz:.3f}] ({label})")
        if self.dry_run:
            self.get_logger().info(f"  [DRY RUN] skipped ({label})")
            return
        if self.dry_run:
            self.get_logger().info(f"  [DRY RUN] skipped ({label})")
            return
        if not self._linear_move_client.wait_for_service(timeout_sec=5.0):
            raise RuntimeError("JAKA linear_move service not available")
        future = self._linear_move_client.call_async(request)
        while not future.done() and rclpy.ok():
            time.sleep(0.05)
        if not rclpy.ok():
            raise RuntimeError("ROS2 shutdown during motion")
        try:
            result = future.result()
            if result.ret != 0:
                self.get_logger().warn(f"  linear_move ret={result.ret} ({label})")
        except Exception as e:
            self.get_logger().error(f"  linear_move exception: {e}"); raise
        if self.settle_time > 0:
            time.sleep(self.settle_time)

    def _wait_for_jaka_ready(self):
        if self.current_tcp_mm is not None: return
        self.get_logger().info("Waiting for TCP from jaka_driver...")
        while self.current_tcp_mm is None and rclpy.ok():
            time.sleep(0.05)
        if self.current_tcp_mm:
            self.get_logger().info(f"TCP: x={self.current_tcp_mm[0]:.1f} y={self.current_tcp_mm[1]:.1f} z={self.current_tcp_mm[2]:.1f} mm")

    def _open_gripper(self):
        self._call_gripper_service(self._gripper_open_client, "open")

    def _close_gripper(self):
        self._call_gripper_service(self._gripper_close_client, "close")

    def _call_gripper_service(self, client, name, timeout=5.0):
        if not client.wait_for_service(timeout_sec=3.0):
            self.get_logger().error(f"Gripper '{name}' not available"); return
        if self.dry_run:
            self.get_logger().info(f"  [DRY RUN] gripper {name} skipped")
            return
        future = client.call_async(Trigger.Request())
        deadline = time.monotonic() + timeout
        while not future.done() and rclpy.ok():
            if time.monotonic() > deadline:
                self.get_logger().error(f"Gripper {name} timed out"); return
            time.sleep(0.05)
        try:
            r = future.result()
            self.get_logger().info(f"  Gripper {name}: ok={r.success} msg='{r.message}'")
        except Exception as e:
            self.get_logger().error(f"  Gripper {name} error: {e}")

    def _call_reset_accumulator(self, timeout=10.0):
        if not self._reset_acc_client.wait_for_service(timeout_sec=5.0):
            self.get_logger().error("reset_accumulator not available"); return False
        future = self._reset_acc_client.call_async(Trigger.Request())
        deadline = time.monotonic() + timeout
        while not future.done() and rclpy.ok():
            if time.monotonic() > deadline:
                self.get_logger().error("reset_accumulator timed out"); return False
            time.sleep(0.05)
        try:
            r = future.result(); return r.success
        except Exception as e:
            self.get_logger().error(f"reset_accumulator error: {e}"); return False


def main(args=None):
    rclpy.init(args=args)
    node = GripperExecNode()
    if node.pregrasp_mode == "dynamic":
        node._start_dynamic_sequence()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info("Shutting down...")
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == "__main__":
    main()