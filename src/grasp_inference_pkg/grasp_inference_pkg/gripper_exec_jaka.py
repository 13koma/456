"""
gripper_exec_jaka.py — Grasp execution node for JAKA ZU12 + DH AG-95 gripper.
=================================================================================
Логика адаптирована под JAKA и синхронизирована с обновлённым dynamic pre-grasp:
- большие перемещения: IK + joint_move
- короткие точные перемещения: linear_move
- dynamic pre-grasp: X/Y от object_center_base, Z = home_z + pregrasp_z_offset
- pregrasp_settle_distance влияет только на Y
- перед reset_accumulator очищается событие и включается фильтр от «старой» grasp pose
"""

from __future__ import annotations

import time
import threading

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseStamped, TwistStamped
from std_srvs.srv import Trigger


class GripperExecNode(Node):
    def __init__(self):
        super().__init__("gripper_exec_node")

        self.declare_parameter("grasp_pose_topic", "/grasp_inference_node/grasp_pose_gripper")
        self.declare_parameter("tcp_pose_topic", "/jaka_driver/tool_position")
        self.declare_parameter("linear_move_service", "/jaka_driver/linear_move")
        self.declare_parameter("joint_move_service", "/jaka_driver/joint_move")
        self.declare_parameter("ik_service", "/jaka_driver/get_ik")
        self.declare_parameter("move_velocity_mm_s", 20.0)
        self.declare_parameter("move_acceleration_mm_s2", 20.0)
        self.declare_parameter("joint_velocity", 0.3)
        self.declare_parameter("joint_acceleration", 0.3)
        self.declare_parameter("gripper_open_service", "/dh_gripper_node/open")
        self.declare_parameter("gripper_close_service", "/dh_gripper_node/close")
        self.declare_parameter("auto_execute", True)
        self.declare_parameter("wait_after_grip", 1.5)
        self.declare_parameter("pre_grasp_offset_y", 0.05)
        self.declare_parameter("lift_height", 0.05)
        self.declare_parameter("home_position", [0.0, 0.0, 0.0, 0.0, 0.0, 0.0])
        self.declare_parameter("home_joints", [0.0, 0.0, 0.0, 0.0, 0.0, 0.0])
        self.declare_parameter("above_home_height", 0.15)

        # dynamic pregrasp params
        self.declare_parameter("pregrasp_mode", "fixed")
        self.declare_parameter("pregrasp_settle_distance", 0.30)
        self.declare_parameter("pregrasp_z_offset", 0.04)  # pre-grasp Z = home_z + this
        self.declare_parameter("fresh_pose_timeout", 30.0)
        self.declare_parameter("object_center_topic", "/grasp_inference_node/object_center_base")
        self.declare_parameter("accumulator_reset_service", "/heightmap_node/reset_accumulator")
        self.declare_parameter("settle_time", 0.3)
        self.declare_parameter("dry_run", False)
        self.declare_parameter("stop_after_pregrasp", False)

        grasp_topic = self.get_parameter("grasp_pose_topic").value
        tcp_topic = self.get_parameter("tcp_pose_topic").value
        self.move_vel = float(self.get_parameter("move_velocity_mm_s").value)
        self.move_acc = float(self.get_parameter("move_acceleration_mm_s2").value)
        self.joint_vel = float(self.get_parameter("joint_velocity").value)
        self.joint_acc = float(self.get_parameter("joint_acceleration").value)
        gripper_open_srv_name = self.get_parameter("gripper_open_service").value
        gripper_close_srv_name = self.get_parameter("gripper_close_service").value
        self.auto_execute = bool(self.get_parameter("auto_execute").value)
        self.wait_grip = float(self.get_parameter("wait_after_grip").value)
        self.pre_grasp_y = float(self.get_parameter("pre_grasp_offset_y").value)
        self.lift_height = float(self.get_parameter("lift_height").value)
        self.home_pos = [float(v) for v in self.get_parameter("home_position").value]
        self.home_joints = [float(v) for v in self.get_parameter("home_joints").value]
        self.above_home_height = float(self.get_parameter("above_home_height").value)
        self.pregrasp_mode = (self.get_parameter("pregrasp_mode").value or "fixed").strip().lower()
        self.pregrasp_settle_dist = float(self.get_parameter("pregrasp_settle_distance").value)
        self.pregrasp_z_offset = float(self.get_parameter("pregrasp_z_offset").value)
        self.fresh_pose_timeout = float(self.get_parameter("fresh_pose_timeout").value)
        object_center_topic = self.get_parameter("object_center_topic").value
        accumulator_reset_srv = self.get_parameter("accumulator_reset_service").value
        self.settle_time = float(self.get_parameter("settle_time").value)
        self.dry_run = bool(self.get_parameter("dry_run").value)
        self.stop_after_pregrasp = bool(self.get_parameter("stop_after_pregrasp").value)

        # last known joint positions (updated after each joint_move)
        self._last_joints = list(self.home_joints)

        self.latest_grasp_pose: PoseStamped | None = None
        self.current_tcp_mm: list[float] | None = None
        self.is_executing = False
        self.one_shot_done = False

        self._object_center_pose: PoseStamped | None = None
        self._object_center_event = threading.Event()
        self._fresh_grasp_pose: PoseStamped | None = None
        self._fresh_grasp_event = threading.Event()
        self._accept_fresh_after_ns = 0

        self.sub_tcp = self.create_subscription(TwistStamped, tcp_topic, self._on_tcp_pose, 10)

        if self.pregrasp_mode == "dynamic":
            self.sub_object_center = self.create_subscription(
                PoseStamped, object_center_topic, self._on_object_center, 10
            )
            self.sub_grasp = self.create_subscription(
                PoseStamped, grasp_topic, self._on_grasp_pose_dynamic, 10
            )
            self._reset_acc_client = self.create_client(Trigger, accumulator_reset_srv)
        else:
            self.sub_grasp = self.create_subscription(
                PoseStamped, grasp_topic, self._on_grasp_pose, 10
            )

        try:
            from jaka_msgs.srv import Move as JakaMove
            from jaka_msgs.srv import GetIK as JakaGetIK
            self._JakaMove = JakaMove
            self._JakaGetIK = JakaGetIK
        except ImportError:
            self.get_logger().error("jaka_msgs not found!")
            self._JakaMove = None
            self._JakaGetIK = None

        linear_move_srv_name = self.get_parameter("linear_move_service").value
        joint_move_srv_name = self.get_parameter("joint_move_service").value
        ik_srv_name = self.get_parameter("ik_service").value

        self._linear_move_client = self.create_client(self._JakaMove, linear_move_srv_name) if self._JakaMove else None
        self._joint_move_client = self.create_client(self._JakaMove, joint_move_srv_name) if self._JakaMove else None
        self._ik_client = self.create_client(self._JakaGetIK, ik_srv_name) if self._JakaGetIK else None
        self._gripper_open_client = self.create_client(Trigger, gripper_open_srv_name)
        self._gripper_close_client = self.create_client(Trigger, gripper_close_srv_name)

        self.get_logger().info("=" * 60)
        self.get_logger().info("GripperExecNode (JAKA ZU12 + DH AG-95) — IK mode")
        self.get_logger().info(f"  home (m): [{', '.join(f'{v:.4f}' for v in self.home_pos)}]")
        self.get_logger().info(f"  home_joints: [{', '.join(f'{v:.4f}' for v in self.home_joints)}]")
        self.get_logger().info(
            f"  mode: {self.pregrasp_mode} | joint_vel: {self.joint_vel} | dry_run: {self.dry_run}"
        )
        if self.pregrasp_mode == "dynamic":
            self.get_logger().info(
                f"  pregrasp_settle_distance: {self.pregrasp_settle_dist} m | "
                f"pregrasp_z_offset: {self.pregrasp_z_offset} m (Z = home_z + this)"
            )
            self.get_logger().info(f"  stop_after_pregrasp: {self.stop_after_pregrasp}")

    # ===== callbacks =====

    def _on_tcp_pose(self, msg: TwistStamped):
        # linear in mm, angular in degrees
        self.current_tcp_mm = [
            float(msg.twist.linear.x),
            float(msg.twist.linear.y),
            float(msg.twist.linear.z),
            float(msg.twist.angular.x),
            float(msg.twist.angular.y),
            float(msg.twist.angular.z),
        ]

    def _on_grasp_pose(self, msg: PoseStamped):
        if self.one_shot_done:
            return
        self.latest_grasp_pose = msg
        self.one_shot_done = True
        try:
            self.destroy_subscription(self.sub_grasp)
        except Exception:
            pass
        threading.Thread(target=self.execute_grasp_sequence, daemon=True).start()

    def _on_object_center(self, msg: PoseStamped):
        self._object_center_pose = msg
        self._object_center_event.set()

    def _on_grasp_pose_dynamic(self, msg: PoseStamped):
        stamp_ns = msg.header.stamp.sec * 1_000_000_000 + msg.header.stamp.nanosec
        if stamp_ns < self._accept_fresh_after_ns:
            return
        self._fresh_grasp_pose = msg
        self._fresh_grasp_event.set()

    # ===== fixed mode =====

    def execute_grasp_sequence(self):
        self._wait_for_jaka_ready()
        gx = self.latest_grasp_pose.pose.position.x
        gy = self.latest_grasp_pose.pose.position.y
        gz = self.latest_grasp_pose.pose.position.z
        hx, hy, hz = self.home_pos[0], self.home_pos[1], self.home_pos[2]
        hrx, hry, hrz = self.home_pos[3], self.home_pos[4], self.home_pos[5]

        self.is_executing = True
        t_start = time.perf_counter()
        try:
            self.get_logger().info("[1/8] → home")
            self._joint_move_home()

            self.get_logger().info("[2/8] gripper open")
            self._open_gripper()
            time.sleep(self.wait_grip)

            pre_z = gz + self.pregrasp_z_offset
            self.get_logger().info("[3/8] → pre-grasp")
            self._move_via_ik([gx, gy, pre_z, hrx, hry, hrz], "pre-grasp")

            self.get_logger().info("[4/8] → grasp (linear)")
            self._linear_move([gx, gy, gz, hrx, hry, hrz], "grasp")

            self.get_logger().info("[5/8] gripper close")
            self._close_gripper()
            time.sleep(3.0)

            lift_z = gz + self.lift_height
            self.get_logger().info("[6/8] → lift")
            self._linear_move([gx, gy, lift_z, hrx, hry, hrz], "lift")

            above_z = hz + self.above_home_height
            self.get_logger().info("[7/8] → above home")
            self._move_via_ik([hx, hy, above_z, hrx, hry, hrz], "above-home")

            self.get_logger().info("[8/8] → home")
            self._joint_move_home()
            self.get_logger().info(f"DONE in {time.perf_counter() - t_start:.2f}s")
        except Exception as e:
            self.get_logger().error(f"FAILED: {e}")
        finally:
            self.is_executing = False

    # ===== dynamic mode =====

    def _start_dynamic_sequence(self):
        if self.one_shot_done:
            return
        self.one_shot_done = True
        threading.Thread(target=self._execute_dynamic_sequence, daemon=True).start()

    def _execute_dynamic_sequence(self):
        self.get_logger().info("DYNAMIC GRASP — waiting for object center...")
        self._wait_for_jaka_ready()

        self._object_center_event.clear()
        if not self._object_center_event.wait(timeout=self.fresh_pose_timeout):
            self.get_logger().error("Timeout waiting for object center")
            return
        if not rclpy.ok():
            return

        center = self._object_center_pose
        try:
            self.destroy_subscription(self.sub_object_center)
        except Exception:
            pass

        cx = center.pose.position.x
        cy = center.pose.position.y

        hx, hy, hz = self.home_pos[0], self.home_pos[1], self.home_pos[2]
        hrx, hry, hrz = self.home_pos[3], self.home_pos[4], self.home_pos[5]

        dist_to_obj = hy - cy
        pre_x = cx
        pre_z = hz + self.pregrasp_z_offset
        if dist_to_obj > self.pregrasp_settle_dist:
            pre_y = cy + self.pregrasp_settle_dist
            pregrasp_mode_label = "APPROACH"
        else:
            pre_y = hy
            pregrasp_mode_label = "ALIGN-ONLY"

        self.get_logger().info(
            f"  Object center: x={cx:.3f}, y={cy:.3f} | dist_to_obj={dist_to_obj:.3f} m"
        )
        self.get_logger().info(
            f"  Pre-grasp [{pregrasp_mode_label}]: x={pre_x:.3f}, y={pre_y:.3f}, z={pre_z:.3f}"
        )

        self.is_executing = True
        t_start = time.perf_counter()
        try:
            self.get_logger().info("[DYN 1/10] → home")
            self._joint_move_home()

            self.get_logger().info("[DYN 2/10] gripper open")
            self._open_gripper()
            time.sleep(self.wait_grip)

            self.get_logger().info("[DYN 3/10] → pre-grasp (IK)")
            self._move_via_ik([pre_x, pre_y, pre_z, hrx, hry, hrz], "dynamic-pre-grasp")

            if self.stop_after_pregrasp:
                self.get_logger().warn("TEST MODE: stop after pre-grasp")
                return

            self._fresh_grasp_event.clear()
            self._fresh_grasp_pose = None
            now = self.get_clock().now().to_msg()
            self._accept_fresh_after_ns = now.sec * 1_000_000_000 + now.nanosec

            self.get_logger().info("[DYN 4-5/10] reset acc + wait fresh pose")
            reset_ok = self._call_reset_accumulator(timeout=10.0)
            if not reset_ok:
                self.get_logger().warn("Accumulator reset failed or timed out, continuing anyway")

            if not self._fresh_grasp_event.wait(timeout=self.fresh_pose_timeout):
                self.get_logger().error("Timeout waiting for fresh grasp pose")
                return
            if not rclpy.ok():
                return

            fresh = self._fresh_grasp_pose
            try:
                self.destroy_subscription(self.sub_grasp)
            except Exception:
                pass

            gx = fresh.pose.position.x
            gy = fresh.pose.position.y
            gz = fresh.pose.position.z
            self.get_logger().info(
                f"[DYN 6/10] fresh grasp pose: x={gx:.3f} y={gy:.3f} z={gz:.3f}"
            )

            self.get_logger().info("[DYN 6/10] → grasp (linear)")
            self._linear_move([gx, gy, gz, hrx, hry, hrz], "grasp")

            self.get_logger().info("[DYN 7/10] gripper close")
            self._close_gripper()
            time.sleep(3.0)

            lift_z = gz + self.lift_height
            self.get_logger().info("[DYN 8/10] → lift (linear)")
            self._linear_move([gx, gy, lift_z, hrx, hry, hrz], "lift")

            above_z = hz + self.above_home_height
            self.get_logger().info("[DYN 9/10] → above home (IK)")
            self._move_via_ik([hx, hy, above_z, hrx, hry, hrz], "above-home")

            self.get_logger().info("[DYN 9/10] → home")
            self._joint_move_home()

            self.get_logger().info(f"[DYN 10/10] DONE in {time.perf_counter() - t_start:.2f}s")
        except Exception as e:
            self.get_logger().error(f"DYNAMIC FAILED: {e}")
        finally:
            self.is_executing = False
            self._accept_fresh_after_ns = 0

    # ===== IK + joint_move (safe for large moves) =====

    def _get_ik(self, pose6_m):
        """Call JAKA IK service. pose6_m in meters/radians. Returns joint angles."""
        if self._ik_client is None:
            raise RuntimeError("IK service not available")

        x_mm = pose6_m[0] * 1000.0
        y_mm = pose6_m[1] * 1000.0
        z_mm = pose6_m[2] * 1000.0
        rx, ry, rz = pose6_m[3], pose6_m[4], pose6_m[5]

        request = self._JakaGetIK.Request()
        request.ref_joint = list(self._last_joints)
        request.cartesian_pose = [x_mm, y_mm, z_mm, rx, ry, rz]

        self.get_logger().info(
            f"  IK request: cart=[{x_mm:.1f}, {y_mm:.1f}, {z_mm:.1f}, {rx:.3f}, {ry:.3f}, {rz:.3f}]"
        )

        if not self._ik_client.wait_for_service(timeout_sec=5.0):
            raise RuntimeError("IK service not available")

        future = self._ik_client.call_async(request)
        while not future.done() and rclpy.ok():
            time.sleep(0.05)

        if not rclpy.ok():
            raise RuntimeError("ROS2 shutdown during IK")

        result = future.result()
        joints = list(result.joint)
        self.get_logger().info(f"  IK result: [{', '.join(f'{j:.3f}' for j in joints)}]")
        return joints

    def _move_via_ik(self, pose6_m, label="target"):
        joints = self._get_ik(pose6_m)
        if self.dry_run:
            self.get_logger().info(f"  [DRY RUN] skipped ({label})")
            return
        self._joint_move_to(joints, label)

    def _joint_move_to(self, joints, label="target"):
        if self._joint_move_client is None:
            raise RuntimeError("joint_move not available")
        request = self._JakaMove.Request()
        request.pose = list(joints)
        request.has_ref = False
        request.ref_joint = [0.0]
        request.mvvelo = self.joint_vel
        request.mvacc = self.joint_acc
        request.mvtime = 0.0
        request.mvradii = 0.0
        request.coord_mode = 0
        request.index = 0

        self.get_logger().info(
            f"  joint_move: [{', '.join(f'{j:.3f}' for j in joints)}] ({label})"
        )
        if not self._joint_move_client.wait_for_service(timeout_sec=5.0):
            raise RuntimeError("joint_move service not available")

        future = self._joint_move_client.call_async(request)
        while not future.done() and rclpy.ok():
            time.sleep(0.05)

        if not rclpy.ok():
            raise RuntimeError("ROS2 shutdown during joint_move")

        result = future.result()
        try:
            ret = int(result.ret)
        except Exception:
            ret = 0

        if ret not in (0, 1):
            raise RuntimeError(f"joint_move ret={ret} ({label})")
        if ret == 1:
            self.get_logger().warn(f"  joint_move ret=1 ({label})")

        self._last_joints = list(joints)
        if self.settle_time > 0:
            time.sleep(self.settle_time)

    def _joint_move_home(self):
        if self.dry_run:
            self.get_logger().info("  [DRY RUN] skipped (joint_move home)")
            return
        self._joint_move_to(self.home_joints, "home")

    # ===== linear_move (short precise moves only) =====

    def _linear_move(self, pose6_m, label="target"):
        if self._linear_move_client is None:
            raise RuntimeError("linear_move not available")

        x_mm = pose6_m[0] * 1000.0
        y_mm = pose6_m[1] * 1000.0
        z_mm = pose6_m[2] * 1000.0
        rx, ry, rz = pose6_m[3], pose6_m[4], pose6_m[5]

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

        self.get_logger().info(
            f"  linear_move: [{x_mm:.1f}, {y_mm:.1f}, {z_mm:.1f}, {rx:.3f}, {ry:.3f}, {rz:.3f}] ({label})"
        )
        if self.dry_run:
            self.get_logger().info(f"  [DRY RUN] skipped ({label})")
            return
        if not self._linear_move_client.wait_for_service(timeout_sec=5.0):
            raise RuntimeError("linear_move service not available")

        future = self._linear_move_client.call_async(request)
        while not future.done() and rclpy.ok():
            time.sleep(0.05)

        if not rclpy.ok():
            raise RuntimeError("ROS2 shutdown during linear_move")

        result = future.result()
        try:
            ret = int(result.ret)
        except Exception:
            ret = 0

        if ret not in (0, 1):
            raise RuntimeError(f"linear_move ret={ret} ({label})")
        if ret == 1:
            self.get_logger().warn(f"  linear_move ret=1 ({label})")

        if self.settle_time > 0:
            time.sleep(self.settle_time)

    # ===== readiness =====

    def _wait_for_jaka_ready(self):
        if self.current_tcp_mm is not None:
            return
        self.get_logger().info("Waiting for TCP from jaka_driver...")
        while self.current_tcp_mm is None and rclpy.ok():
            time.sleep(0.05)
        if self.current_tcp_mm:
            self.get_logger().info(
                f"TCP: x={self.current_tcp_mm[0]:.1f} y={self.current_tcp_mm[1]:.1f} z={self.current_tcp_mm[2]:.1f} mm"
            )

    # ===== gripper =====

    def _open_gripper(self):
        self._call_gripper_service(self._gripper_open_client, "open")

    def _close_gripper(self):
        self._call_gripper_service(self._gripper_close_client, "close")

    def _call_gripper_service(self, client, name, timeout=5.0):
        if self.dry_run:
            self.get_logger().info(f"  [DRY RUN] gripper {name} skipped")
            return
        if not client.wait_for_service(timeout_sec=3.0):
            self.get_logger().error(f"Gripper '{name}' not available")
            return
        future = client.call_async(Trigger.Request())
        deadline = time.monotonic() + timeout
        while not future.done() and rclpy.ok():
            if time.monotonic() > deadline:
                self.get_logger().error(f"Gripper {name} timed out")
                return
            time.sleep(0.05)
        try:
            result = future.result()
            self.get_logger().info(f"  Gripper {name}: ok={result.success} msg='{result.message}'")
        except Exception as e:
            self.get_logger().error(f"  Gripper {name} error: {e}")

    # ===== accumulator reset =====

    def _call_reset_accumulator(self, timeout=10.0):
        if not self._reset_acc_client.wait_for_service(timeout_sec=5.0):
            self.get_logger().error("reset_accumulator not available")
            return False
        future = self._reset_acc_client.call_async(Trigger.Request())
        deadline = time.monotonic() + timeout
        while not future.done() and rclpy.ok():
            if time.monotonic() > deadline:
                self.get_logger().error("reset_accumulator timed out")
                future.cancel()
                return False
            time.sleep(0.05)
        try:
            result = future.result()
            self.get_logger().info(
                f"Accumulator reset: success={result.success} msg='{result.message}'"
            )
            return bool(result.success)
        except Exception as e:
            self.get_logger().error(f"reset_accumulator error: {e}")
            return False



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