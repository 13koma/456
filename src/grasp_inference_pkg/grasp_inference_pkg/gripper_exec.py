from __future__ import annotations
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseStamped
from std_msgs.msg import String, Float32
from std_srvs.srv import Trigger
import time
import math
import threading


class GripperExecNode(Node):
    def __init__(self):
        super().__init__("gripper_exec_node")
        # ===== параметры =====
        self.declare_parameter("grasp_pose_topic", "/model_forward/grasp_pose_gripper")
        self.declare_parameter("tcp_pose_topic", "/ur5_/tcp_pose_broadcaster/pose")
        self.declare_parameter("urscript_topic", "/ur5_/urscript_interface/script_command")
        self.declare_parameter("gripper_target_topic", "/gripper/target_position")
        self.declare_parameter("gripper_current_topic", "/gripper/current_position")
        self.declare_parameter("move_acceleration", 0.05)
        self.declare_parameter("move_velocity", 0.05)
        self.declare_parameter("move_radius", 0.0)
        self.declare_parameter("gripper_close_position", 100.0)
        self.declare_parameter("gripper_open_position", 0.0)
        self.declare_parameter("auto_execute", True)
        self.declare_parameter("wait_after_move", 2.0)
        self.declare_parameter("wait_after_grip", 1.5)
        self.declare_parameter("pre_grasp_offset_y", 0.05)
        self.declare_parameter("lift_height", 0.05)

        # home_position: [x, y, z, rx, ry, rz] в координатах base (для movep)
        self.declare_parameter("home_position", [0.0, 0.0, 0.0, 0.0, 0.0, 0.0])
        self.declare_parameter("above_home_height", 0.15)

        # ===== dynamic pregrasp params =====
        self.declare_parameter("pregrasp_mode", "fixed")  # "fixed" or "dynamic"
        self.declare_parameter("pregrasp_settle_distance", 0.30)
        self.declare_parameter("pregrasp_z_offset", 0.04)  # pre-grasp Z = home_z + this
        self.declare_parameter("fresh_pose_timeout", 30.0)
        self.declare_parameter("object_center_topic", "/grasp_inference_node/object_center_base")
        self.declare_parameter("accumulator_reset_service", "/heightmap_node/reset_accumulator")

        # читаем параметры
        grasp_topic = self.get_parameter("grasp_pose_topic").value
        tcp_topic = self.get_parameter("tcp_pose_topic").value
        self.urscript_topic = self.get_parameter("urscript_topic").value
        gripper_target_topic = self.get_parameter("gripper_target_topic").value
        gripper_current_topic = self.get_parameter("gripper_current_topic").value

        self.move_accel = float(self.get_parameter("move_acceleration").value)
        self.move_vel = float(self.get_parameter("move_velocity").value)
        self.move_radius = float(self.get_parameter("move_radius").value)

        self.gripper_close = float(self.get_parameter("gripper_close_position").value)
        self.gripper_open = float(self.get_parameter("gripper_open_position").value)

        self.auto_execute = bool(self.get_parameter("auto_execute").value)
        self.wait_move = float(self.get_parameter("wait_after_move").value)
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

        # ===== Состояние =====
        self.latest_grasp_pose: PoseStamped | None = None
        self.current_tcp_pose: PoseStamped | None = None
        self.current_gripper_pos: float | None = None
        self.is_executing = False
        self.one_shot_done = False

        # ===== Threading sync for dynamic mode =====
        self._object_center_pose: PoseStamped | None = None
        self._object_center_event = threading.Event()
        self._fresh_grasp_pose: PoseStamped | None = None
        self._fresh_grasp_event = threading.Event()

        # ===== Подписчики =====
        self.sub_tcp = self.create_subscription(
            PoseStamped, tcp_topic, self._on_tcp_pose, 10
        )
        self.sub_gripper_current = self.create_subscription(
            Float32, gripper_current_topic, self._on_gripper_current, 10
        )

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

        # ===== Паблишеры =====
        self.pub_urscript = self.create_publisher(String, self.urscript_topic, 10)
        self.pub_gripper = self.create_publisher(Float32, gripper_target_topic, 10)

        self.get_logger().info("=" * 60)
        self.get_logger().info("GripperExecNode initialized")
        self.get_logger().info(f"  pregrasp_mode: {self.pregrasp_mode}")
        self.get_logger().info(
            f"  home_position: [{', '.join(f'{v:.3f}' for v in self.home_pos)}]"
        )
        self.get_logger().info(f"  lift_height: {self.lift_height} m")
        self.get_logger().info(f"  above_home_height: {self.above_home_height} m")
        self.get_logger().info(f"  pre_grasp_offset_y: {self.pre_grasp_y}")
        if self.pregrasp_mode == "dynamic":
            self.get_logger().info(f"  pregrasp_settle_distance: {self.pregrasp_settle_dist} m")
            self.get_logger().info(f"  pregrasp_z_offset: {self.pregrasp_z_offset} m (Z = home_z + this)")
            self.get_logger().info(f"  fresh_pose_timeout: {self.fresh_pose_timeout} s")
            self.get_logger().info(f"  object_center_topic: {object_center_topic}")
            self.get_logger().info(f"  accumulator_reset_service: {accumulator_reset_srv}")
            self.get_logger().info("Waiting for object center (dynamic mode)...")
        else:
            self.get_logger().info("Waiting for grasp pose (fixed mode)...")

    # ===== callbacks =====

    def _on_tcp_pose(self, msg: PoseStamped):
        self.current_tcp_pose = msg

    def _on_gripper_current(self, msg: Float32):
        self.current_gripper_pos = msg.data

    # --- fixed mode callback ---
    def _on_grasp_pose(self, msg: PoseStamped):
        if self.one_shot_done:
            return

        self.latest_grasp_pose = msg
        self.get_logger().info("GRASP POSE RECEIVED — starting sequence (fixed mode)")

        self.one_shot_done = True
        try:
            self.destroy_subscription(self.sub_grasp)
        except Exception:
            pass

        thread = threading.Thread(target=self.execute_grasp_sequence, daemon=True)
        thread.start()

    # --- dynamic mode callbacks ---
    def _on_object_center(self, msg: PoseStamped):
        self._object_center_pose = msg
        self._object_center_event.set()

    def _on_grasp_pose_dynamic(self, msg: PoseStamped):
        self._fresh_grasp_pose = msg
        self._fresh_grasp_event.set()

    # ===== main sequence: fixed mode (unchanged) =====

    def execute_grasp_sequence(self):
        if self.current_tcp_pose is None:
            self.get_logger().info("Waiting for first TCP message...")
        while self.current_tcp_pose is None and rclpy.ok():
            time.sleep(0.01)

        gx = self.latest_grasp_pose.pose.position.x
        gy = self.latest_grasp_pose.pose.position.y
        gz = self.latest_grasp_pose.pose.position.z

        hx, hy, hz = self.home_pos[0], self.home_pos[1], self.home_pos[2]
        hrx, hry, hrz = self.home_pos[3], self.home_pos[4], self.home_pos[5]

        self.is_executing = True
        t_start = time.perf_counter()

        self.get_logger().info("")
        self.get_logger().info(f"  Grasp target: x={gx:.3f}, y={gy:.3f}, z={gz:.3f}")
        self.get_logger().info(f"  Home:         x={hx:.3f}, y={hy:.3f}, z={hz:.3f}")
        self.get_logger().info("")

        try:
            # === 1. Move to home ===
            self.get_logger().info("[1/8] Moving to home_position...")
            self._move_to_xyzrpy(self.home_pos, "home")
            self._wait_until_reached_xyz(hx, hy, hz)
            self.get_logger().info("[1/8] Reached home_position")

            # === 2. Open gripper ===
            self.get_logger().info("[2/8] Opening gripper...")
            self._open_gripper()
            time.sleep(self.wait_grip)

            # === 3. Pre-grasp (always) ===
            pre_y = gy + self.pre_grasp_y
            pre = [gx, pre_y, gz, hrx, hry, hrz]
            self.get_logger().info(
                f"[3/8] Moving to PRE-GRASP: x={gx:.3f}, y={pre_y:.3f}, z={gz:.3f}"
            )
            self._move_to_xyzrpy(pre, "pre-grasp")
            self._wait_until_reached_xyz(gx, pre_y, gz)
            self.get_logger().info("[3/8] Reached pre-grasp")

            # === 4. Move to grasp ===
            grasp = [gx, gy, gz, hrx, hry, hrz]
            self.get_logger().info(
                f"[4/8] Moving to GRASP: x={gx:.3f}, y={gy:.3f}, z={gz:.3f}"
            )
            self._move_to_xyzrpy(grasp, "grasp")
            self._wait_until_reached_xyz(gx, gy, gz)
            self.get_logger().info("[4/8] Reached grasp position")

            # === 5. Close gripper ===
            self.get_logger().info("[5/8] Closing gripper...")
            self._close_gripper()
            time.sleep(3.0)
            self.get_logger().info("[5/8] Gripper closed")

            # === 6. Lift ===
            lift_z = gz + self.lift_height
            lift = [gx, gy, lift_z, hrx, hry, hrz]
            self.get_logger().info(f"[6/8] Lifting to z={lift_z:.3f}...")
            self._move_to_xyzrpy(lift, "lift")
            self._wait_until_reached_xyz(gx, gy, lift_z)
            self.get_logger().info("[6/8] Lifted")

            # === 7. Above home ===
            above_z = hz + self.above_home_height
            above = [hx, hy, above_z, hrx, hry, hrz]
            self.get_logger().info(f"[7/8] Moving above home: z={above_z:.3f}...")
            self._move_to_xyzrpy(above, "above-home")
            self._wait_until_reached_xyz(hx, hy, above_z)
            self.get_logger().info("[7/8] Reached above-home")

            # === 8. Return to home ===
            self.get_logger().info("[8/8] Returning to home_position...")
            self._move_to_xyzrpy(self.home_pos, "home-return")
            self._wait_until_reached_xyz(hx, hy, hz)
            self.get_logger().info("[8/8] Reached home")

            elapsed = time.perf_counter() - t_start
            self.get_logger().info("")
            self.get_logger().info(f"GRASP SEQUENCE COMPLETED in {elapsed:.2f} s")
            self.get_logger().info("")

        except Exception as e:
            elapsed = time.perf_counter() - t_start
            self.get_logger().error(f"EXECUTION FAILED after {elapsed:.2f} s: {e}")

        finally:
            self.is_executing = False
            elapsed_total = time.perf_counter() - t_start
            self.get_logger().info(f"State unlocked (one-shot finished, total {elapsed_total:.2f} s)")

    # ===== main sequence: dynamic mode =====

    def _start_dynamic_sequence(self):
        if self.one_shot_done:
            return
        self.one_shot_done = True
        thread = threading.Thread(target=self._execute_dynamic_sequence, daemon=True)
        thread.start()

    def _execute_dynamic_sequence(self):
        self.get_logger().info("DYNAMIC GRASP SEQUENCE — waiting for object center...")

        # --- wait for TCP ---
        if self.current_tcp_pose is None:
            self.get_logger().info("Waiting for first TCP message...")
        while self.current_tcp_pose is None and rclpy.ok():
            time.sleep(0.01)
        if not rclpy.ok():
            return

        # --- Phase 1: get object center and move to pre-grasp ---
        self._object_center_event.clear()

        self.get_logger().info("Waiting for object_center_base topic...")
        if not self._object_center_event.wait(timeout=self.fresh_pose_timeout):
            self.get_logger().error(
                f"Timeout ({self.fresh_pose_timeout}s) waiting for object center — aborting"
            )
            return
        if not rclpy.ok():
            return

        center = self._object_center_pose
        try:
            self.destroy_subscription(self.sub_object_center)
        except Exception:
            pass
        self.get_logger().info("Unsubscribed from object_center topic")

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
            f"  Object center: x={cx:.3f}, y={cy:.3f} | "
            f"dist_to_obj={dist_to_obj:.3f} m"
        )
        self.get_logger().info(
            f"  Pre-grasp [{pregrasp_mode_label}]: x={pre_x:.3f}, y={pre_y:.3f}, z={pre_z:.3f}"
        )

        self.is_executing = True
        t_start = time.perf_counter()

        try:
            # === 1. Move to home ===
            self.get_logger().info("[DYN 1/10] Moving to home_position...")
            self._move_to_xyzrpy(self.home_pos, "home")
            self._wait_until_reached_xyz(hx, hy, hz)
            self.get_logger().info("[DYN 1/10] Reached home_position")

            # === 2. Open gripper ===
            self.get_logger().info("[DYN 2/10] Opening gripper...")
            self._open_gripper()
            time.sleep(self.wait_grip)

            # === 3. Move to pre-grasp (X=center, Y=center+settle, Z=home+4cm) ===
            pre = [pre_x, pre_y, pre_z, hrx, hry, hrz]
            self.get_logger().info(
                f"[DYN 3/10] Moving to PRE-GRASP: x={pre_x:.3f}, y={pre_y:.3f}, z={pre_z:.3f}"
            )
            self._move_to_xyzrpy(pre, "dynamic-pre-grasp")
            self._wait_until_reached_xyz(pre_x, pre_y, pre_z)
            self.get_logger().info("[DYN 3/10] Reached pre-grasp")

            # === 4. Prepare for fresh data: clear event BEFORE reset ===
            self._fresh_grasp_event.clear()

            # === 5. Reset accumulator for fresh heightmap data ===
            self.get_logger().info("[DYN 4-5/10] Resetting accumulator, waiting for fresh RL pose...")
            reset_ok = self._call_reset_accumulator(timeout=10.0)
            if not reset_ok:
                self.get_logger().warn("Accumulator reset failed or timed out, continuing anyway")

            if not self._fresh_grasp_event.wait(timeout=self.fresh_pose_timeout):
                self.get_logger().error(
                    f"Timeout ({self.fresh_pose_timeout}s) waiting for fresh grasp pose — aborting"
                )
                return
            if not rclpy.ok():
                return

            fresh = self._fresh_grasp_pose
            try:
                self.destroy_subscription(self.sub_grasp)
            except Exception:
                pass
            self.get_logger().info("Unsubscribed from grasp_pose topic")
            gx = fresh.pose.position.x
            gy = fresh.pose.position.y
            gz = fresh.pose.position.z
            self.get_logger().info(
                f"[DYN 5/10] Fresh grasp pose: x={gx:.3f}, y={gy:.3f}, z={gz:.3f}"
            )

            # === 6. Move to grasp ===
            grasp = [gx, gy, gz, hrx, hry, hrz]
            self.get_logger().info(
                f"[DYN 6/10] Moving to GRASP: x={gx:.3f}, y={gy:.3f}, z={gz:.3f}"
            )
            self._move_to_xyzrpy(grasp, "grasp")
            self._wait_until_reached_xyz(gx, gy, gz)
            self.get_logger().info("[DYN 6/10] Reached grasp position")

            # === 7. Close gripper ===
            self.get_logger().info("[DYN 7/10] Closing gripper...")
            self._close_gripper()
            time.sleep(3.0)
            self.get_logger().info("[DYN 7/10] Gripper closed")

            # === 8. Lift ===
            lift_z = gz + self.lift_height
            lift = [gx, gy, lift_z, hrx, hry, hrz]
            self.get_logger().info(f"[DYN 8/10] Lifting to z={lift_z:.3f}...")
            self._move_to_xyzrpy(lift, "lift")
            self._wait_until_reached_xyz(gx, gy, lift_z)
            self.get_logger().info("[DYN 8/10] Lifted")

            # === 9. Above home + return ===
            above_z = hz + self.above_home_height
            above = [hx, hy, above_z, hrx, hry, hrz]
            self.get_logger().info(f"[DYN 9/10] Moving above home: z={above_z:.3f}...")
            self._move_to_xyzrpy(above, "above-home")
            self._wait_until_reached_xyz(hx, hy, above_z)

            self.get_logger().info("[DYN 9/10] Returning to home_position...")
            self._move_to_xyzrpy(self.home_pos, "home-return")
            self._wait_until_reached_xyz(hx, hy, hz)
            self.get_logger().info("[DYN 9/10] Reached home")

            # === 10. Done ===
            elapsed = time.perf_counter() - t_start
            self.get_logger().info("")
            self.get_logger().info(f"[DYN 10/10] DYNAMIC GRASP SEQUENCE COMPLETED in {elapsed:.2f} s")
            self.get_logger().info("")

        except Exception as e:
            elapsed = time.perf_counter() - t_start
            self.get_logger().error(f"DYNAMIC EXECUTION FAILED after {elapsed:.2f} s: {e}")

        finally:
            self.is_executing = False
            elapsed_total = time.perf_counter() - t_start
            self.get_logger().info(f"State unlocked (dynamic one-shot finished, total {elapsed_total:.2f} s)")

    def _call_reset_accumulator(self, timeout: float = 10.0) -> bool:
        if not self._reset_acc_client.wait_for_service(timeout_sec=5.0):
            self.get_logger().error("reset_accumulator service not available")
            return False

        request = Trigger.Request()
        future = self._reset_acc_client.call_async(request)

        deadline = time.monotonic() + timeout
        while not future.done() and rclpy.ok():
            if time.monotonic() > deadline:
                self.get_logger().error("reset_accumulator call timed out")
                future.cancel()
                return False
            time.sleep(0.05)

        if not rclpy.ok():
            return False

        try:
            result = future.result()
            self.get_logger().info(f"Accumulator reset: success={result.success} msg='{result.message}'")
            return result.success
        except Exception as e:
            self.get_logger().error(f"reset_accumulator call exception: {e}")
            return False

    # ===== movement helpers =====

    def _move_to_xyzrpy(self, pose6: list[float], label: str = "target"):
        x, y, z, rx, ry, rz = pose6
        urscript = (
            f"def my_prog():\n"
            f"  set_digital_out(1, True)\n"
            f"  movep(p[{x:.6f}, {y:.6f}, {z:.6f}, {rx:.6f}, {ry:.6f}, {rz:.6f}], "
            f"a={self.move_accel}, v={self.move_vel}, r={self.move_radius})\n"
            f'  textmsg("motion finished: {label}")\n'
            f"end"
        )
        msg = String()
        msg.data = urscript
        self.pub_urscript.publish(msg)
        self.get_logger().info(
            f"  URScript sent: p[{x:.3f}, {y:.3f}, {z:.3f}, {rx:.3f}, {ry:.3f}, {rz:.3f}] ({label})"
        )

    def _wait_until_reached_xyz(self, tx: float, ty: float, tz: float, pos_tol: float = 0.001):
        log_counter = 0
        while rclpy.ok():
            if self.current_tcp_pose is None:
                time.sleep(0.01)
                continue
            dx = self.current_tcp_pose.pose.position.x - tx
            dy = self.current_tcp_pose.pose.position.y - ty
            dz = self.current_tcp_pose.pose.position.z - tz
            dist = math.sqrt(dx * dx + dy * dy + dz * dz)
            if dist <= pos_tol:
                return
            if log_counter % 100 == 0:
                self.get_logger().info(f"  waiting... dist={dist:.4f} m")
            log_counter += 1
            time.sleep(0.02)

    # ===== gripper =====

    def _close_gripper(self):
        msg = Float32()
        msg.data = self.gripper_close
        self.pub_gripper.publish(msg)
        self.get_logger().info(f"  Gripper CLOSE ({self.gripper_close})")

    def _open_gripper(self):
        msg = Float32()
        msg.data = self.gripper_open
        self.pub_gripper.publish(msg)
        self.get_logger().info(f"  Gripper OPEN ({self.gripper_open})")

    # ===== utils =====

    @staticmethod
    def _quat_to_rotvec(qx: float, qy: float, qz: float, qw: float) -> tuple[float, float, float]:
        norm = math.sqrt(qx * qx + qy * qy + qz * qz + qw * qw)
        if norm < 1e-9:
            return 0.0, 0.0, 0.0
        qx, qy, qz, qw = qx / norm, qy / norm, qz / norm, qw / norm
        angle = 2.0 * math.acos(max(-1.0, min(1.0, qw)))
        sin_half = math.sin(angle / 2.0)
        if abs(sin_half) < 1e-9:
            return 0.0, 0.0, 0.0
        rx = qx / sin_half * angle
        ry = qy / sin_half * angle
        rz = qz / sin_half * angle
        return rx, ry, rz


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
