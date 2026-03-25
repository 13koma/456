#!/usr/bin/env python3
import math
import time
from dataclasses import dataclass

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseStamped, TwistStamped
from sensor_msgs.msg import JointState
from std_srvs.srv import Trigger
from jaka_msgs.srv import GetIK, Move


def clip(v: float, lo: float, hi: float) -> float:
    return max(lo, min(hi, v))


@dataclass
class Pose3:
    x: float
    y: float
    z: float


class PipelinePickWithGripperV3(Node):
    def __init__(self):
        super().__init__("pipeline_pick_with_gripper_v3")

        # topics
        self.declare_parameter("target_topic", "/grasp_inference_node/object_center_base")
        self.declare_parameter("tool_topic", "/jaka_driver/tool_position")
        self.declare_parameter("joint_topic", "/jaka_driver/joint_position")

        # target compensation / grasp geometry
        self.declare_parameter("target_x_offset_m", 0.0)
        self.declare_parameter("target_y_offset_m", 0.0)
        self.declare_parameter("target_z_offset_m", 0.0)
        self.declare_parameter("pregrasp_above_m", 0.10)
        self.declare_parameter("grasp_above_m", 0.03)
        self.declare_parameter("lift_up_m", 0.08)
        self.declare_parameter("refresh_target_before_descend", True)
        self.declare_parameter("settle_before_refresh_sec", 0.5)

        # motion bounds
        self.declare_parameter("max_xy_step_m", 0.04)
        self.declare_parameter("max_z_step_m", 0.04)
        self.declare_parameter("xy_tol_m", 0.008)
        self.declare_parameter("z_tol_m", 0.008)
        self.declare_parameter("max_stage_iterations", 12)
        self.declare_parameter("wait_after_move_sec", 1.0)
        self.declare_parameter("wait_pose_timeout_sec", 6.0)

        # robot speeds
        self.declare_parameter("mvvelo", 0.2)
        self.declare_parameter("mvacc", 0.2)

        # return-to-start for repeatable experiments
        self.declare_parameter("return_to_start_on_preview", True)
        self.declare_parameter("return_to_start_on_failure", True)
        self.declare_parameter("return_to_start_on_success", False)

        # gripper
        self.declare_parameter("skip_initialize", True)
        self.declare_parameter("dry_run", False)
        self.declare_parameter("preview_only", False)
        self.declare_parameter("preview_hold_sec", 5.0)

        self.target: Pose3 | None = None
        self.tool: tuple[float, float, float, float, float, float] | None = None
        self.joints: list[float] | None = None

        self.create_subscription(
            PoseStamped,
            self.get_parameter("target_topic").value,
            self.target_cb,
            10,
        )
        self.create_subscription(
            TwistStamped,
            self.get_parameter("tool_topic").value,
            self.tool_cb,
            10,
        )
        self.create_subscription(
            JointState,
            self.get_parameter("joint_topic").value,
            self.joint_cb,
            10,
        )

        self.ik_client = self.create_client(GetIK, "/jaka_driver/get_ik")
        self.move_client = self.create_client(Move, "/jaka_driver/joint_move")
        self.gripper_init_client = self.create_client(Trigger, "/dh_gripper_node/initialize")
        self.gripper_open_client = self.create_client(Trigger, "/dh_gripper_node/open")
        self.gripper_close_client = self.create_client(Trigger, "/dh_gripper_node/close")

    # ---------- callbacks ----------
    def target_cb(self, msg: PoseStamped):
        self.target = Pose3(
            float(msg.pose.position.x),
            float(msg.pose.position.y),
            float(msg.pose.position.z),
        )

    def tool_cb(self, msg: TwistStamped):
        # xyz in mm, rpy in degrees
        self.tool = (
            float(msg.twist.linear.x) * 0.001,
            float(msg.twist.linear.y) * 0.001,
            float(msg.twist.linear.z) * 0.001,
            math.radians(float(msg.twist.angular.x)),
            math.radians(float(msg.twist.angular.y)),
            math.radians(float(msg.twist.angular.z)),
        )

    def joint_cb(self, msg: JointState):
        if len(msg.position) >= 6:
            self.joints = [float(x) for x in msg.position[:6]]

    def ready(self) -> bool:
        return self.target is not None and self.tool is not None and self.joints is not None

    # ---------- helpers ----------
    def spin_brief(self, sec: float = 0.3):
        end = time.time() + sec
        while rclpy.ok() and time.time() < end:
            rclpy.spin_once(self, timeout_sec=0.05)

    def current_target_with_offsets(self) -> Pose3:
        if self.target is None:
            raise RuntimeError("target is not available")
        return Pose3(
            self.target.x + float(self.get_parameter("target_x_offset_m").value),
            self.target.y + float(self.get_parameter("target_y_offset_m").value),
            self.target.z + float(self.get_parameter("target_z_offset_m").value),
        )


    def current_pose3(self) -> Pose3:
        if self.tool is None:
            raise RuntimeError("tool pose is not available")
        return Pose3(self.tool[0], self.tool[1], self.tool[2])

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

    def call_trigger(self, client, name: str) -> bool:
        if not client.wait_for_service(timeout_sec=5.0):
            self.get_logger().error(f"Service unavailable: {name}")
            return False
        fut = client.call_async(Trigger.Request())
        rclpy.spin_until_future_complete(self, fut, timeout_sec=10.0)
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
        max_xy = float(self.get_parameter("max_xy_step_m").value)
        max_z = float(self.get_parameter("max_z_step_m").value)

        cmd_x = cur_x + clip(goal.x - cur_x, -max_xy, max_xy)
        cmd_y = cur_y + clip(goal.y - cur_y, -max_xy, max_xy)
        cmd_z = cur_z + clip(goal.z - cur_z, -max_z, max_z)

        self.get_logger().info(
            f"CURRENT=({cur_x:.3f},{cur_y:.3f},{cur_z:.3f}) "
            f"GOAL=({goal.x:.3f},{goal.y:.3f},{goal.z:.3f}) "
            f"CMD=({cmd_x:.3f},{cmd_y:.3f},{cmd_z:.3f})"
        )

        ik_req = GetIK.Request()
        ik_req.ref_joint = self.joints
        ik_req.cartesian_pose = [
            cmd_x * 1000.0,
            cmd_y * 1000.0,
            cmd_z * 1000.0,
            cur_rx,
            cur_ry,
            cur_rz,
        ]
        fut = self.ik_client.call_async(ik_req)
        rclpy.spin_until_future_complete(self, fut, timeout_sec=5.0)
        if not fut.done() or fut.result() is None:
            self.get_logger().error("get_ik returned no response")
            return False

        ik_res = fut.result()
        joints = list(ik_res.joint)
        self.get_logger().info(f"IK: {ik_res.message} | joints={joints[:6]}")
        if len(joints) < 6:
            self.get_logger().error("IK returned fewer than 6 joints")
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

    # ---------- main sequence ----------
    def run(self) -> bool:
        skip_initialize = bool(self.get_parameter("skip_initialize").value)
        dry_run = bool(self.get_parameter("dry_run").value)

        start_pose = self.current_pose3()
        self.get_logger().info(
            f"Saved start pose=({start_pose.x:.3f}, {start_pose.y:.3f}, {start_pose.z:.3f})"
        )

        if not skip_initialize and not dry_run:
            self.get_logger().info("Initializing gripper")
            init_ok = self.call_trigger(self.gripper_init_client, "initialize")
            if not init_ok:
                self.get_logger().warn("initialize failed, continuing")
        else:
            self.get_logger().info("Skipping gripper initialize")

        if not dry_run:
            self.get_logger().info("Opening gripper")
            if not self.call_trigger(self.gripper_open_client, "open"):
                self.maybe_return_to_start(start_pose, "return_to_start_on_failure")
                return False
            self.spin_brief(0.5)
        else:
            self.get_logger().warn("dry_run=true, gripper open skipped")

        # freeze target for stage 1
        target_1 = self.current_target_with_offsets()
        pre_z = target_1.z + float(self.get_parameter("pregrasp_above_m").value)
        pre_goal = Pose3(target_1.x, target_1.y, pre_z)

        if not self.move_until_reached(pre_goal, "STAGE 1 pregrasp"):
            self.maybe_return_to_start(start_pose, "return_to_start_on_failure")
            return False

        if bool(self.get_parameter("preview_only").value):
            hold = float(self.get_parameter("preview_hold_sec").value)
            self.get_logger().warn("preview_only=true, stopping after safe pregrasp")
            if hold > 0.0:
                self.get_logger().info(f"Holding at preview pose for {hold:.1f}s")
                self.spin_brief(hold)
            self.maybe_return_to_start(start_pose, "return_to_start_on_preview")
            return True

        if bool(self.get_parameter("refresh_target_before_descend").value):
            settle = float(self.get_parameter("settle_before_refresh_sec").value)
            self.get_logger().info(f"Refreshing target before descend after {settle:.2f}s settle")
            self.spin_brief(settle)

        target_2 = self.current_target_with_offsets()
        grasp_z = target_2.z + float(self.get_parameter("grasp_above_m").value)
        grasp_goal = Pose3(target_2.x, target_2.y, grasp_z)

        if not self.move_until_reached(grasp_goal, "STAGE 2 descend"):
            self.maybe_return_to_start(start_pose, "return_to_start_on_failure")
            return False

        if not dry_run:
            self.get_logger().info("STAGE 3 close gripper")
            if not self.call_trigger(self.gripper_close_client, "close"):
                self.maybe_return_to_start(start_pose, "return_to_start_on_failure")
                return False
            self.spin_brief(1.0)
        else:
            self.get_logger().warn("dry_run=true, gripper close skipped")

        if self.tool is None:
            self.get_logger().error("tool pose lost before lift")
            self.maybe_return_to_start(start_pose, "return_to_start_on_failure")
            return False

        cur_x, cur_y, cur_z, _, _, _ = self.tool
        lift_z = cur_z + float(self.get_parameter("lift_up_m").value)
        lift_goal = Pose3(cur_x, cur_y, lift_z)

        if not self.move_until_reached(lift_goal, "STAGE 4 lift"):
            self.maybe_return_to_start(start_pose, "return_to_start_on_failure")
            return False

        self.get_logger().info("Pick sequence finished")
        self.maybe_return_to_start(start_pose, "return_to_start_on_success")
        return True


def main():
    rclpy.init()
    node = PipelinePickWithGripperV3()
    try:
        node.get_logger().info("Waiting for target/tool/joints ...")
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
