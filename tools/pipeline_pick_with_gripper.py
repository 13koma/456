#!/usr/bin/env python3
import math
import time

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseStamped, TwistStamped
from sensor_msgs.msg import JointState
from std_srvs.srv import Trigger
from jaka_msgs.srv import GetIK, Move


def clip(v, lo, hi):
    return max(lo, min(hi, v))


class PipelinePickWithGripper(Node):
    def __init__(self):
	
        super().__init__("pipeline_pick_with_gripper")
        self.declare_parameter("skip_initialize", True)
        self.declare_parameter("target_topic", "/grasp_inference_node/object_center_base")
        self.declare_parameter("tool_topic", "/jaka_driver/tool_position")
        self.declare_parameter("joint_topic", "/jaka_driver/joint_position")

        self.declare_parameter("target_x_offset_m", 0.0)
        self.declare_parameter("target_y_offset_m", 0.0)
        self.declare_parameter("target_z_offset_m", 0.0)

        self.declare_parameter("pregrasp_above_m", 0.12)
        self.declare_parameter("grasp_above_m", 0.05)
        self.declare_parameter("lift_up_m", 0.08)

        self.declare_parameter("max_xy_step_m", 0.06)
        self.declare_parameter("max_z_step_m", 0.06)

        self.declare_parameter("mvvelo", 0.2)
        self.declare_parameter("mvacc", 0.2)

        self.target = None
        self.tool = None
        self.joints = None

        self.create_subscription(
            PoseStamped,
            self.get_parameter("target_topic").value,
            self.target_cb,
            10
        )
        self.create_subscription(
            TwistStamped,
            self.get_parameter("tool_topic").value,
            self.tool_cb,
            10
        )
        self.create_subscription(
            JointState,
            self.get_parameter("joint_topic").value,
            self.joint_cb,
            10
        )

        self.ik_client = self.create_client(GetIK, "/jaka_driver/get_ik")
        self.move_client = self.create_client(Move, "/jaka_driver/joint_move")
        self.gripper_init_client = self.create_client(Trigger, "/dh_gripper_node/initialize")
        self.gripper_open_client = self.create_client(Trigger, "/dh_gripper_node/open")
        self.gripper_close_client = self.create_client(Trigger, "/dh_gripper_node/close")

    def target_cb(self, msg):
        self.target = (
            float(msg.pose.position.x),
            float(msg.pose.position.y),
            float(msg.pose.position.z),
        )

    def tool_cb(self, msg):
        # JAKA: xyz в мм, углы в градусах
        self.tool = (
            float(msg.twist.linear.x) * 0.001,
            float(msg.twist.linear.y) * 0.001,
            float(msg.twist.linear.z) * 0.001,
            math.radians(float(msg.twist.angular.x)),
            math.radians(float(msg.twist.angular.y)),
            math.radians(float(msg.twist.angular.z)),
        )

    def joint_cb(self, msg):
        if len(msg.position) >= 6:
            self.joints = [float(x) for x in msg.position[:6]]

    def ready(self):
        return self.target is not None and self.tool is not None and self.joints is not None

    def call_trigger(self, client, name):
        if not client.wait_for_service(timeout_sec=5.0):
            self.get_logger().error(f"Сервис недоступен: {name}")
            return False
        fut = client.call_async(Trigger.Request())
        rclpy.spin_until_future_complete(self, fut, timeout_sec=10.0)
        if not fut.done() or fut.result() is None:
            self.get_logger().error(f"{name}: нет ответа")
            return False
        res = fut.result()
        self.get_logger().info(f"{name}: success={res.success}, msg={res.message}")
        return bool(res.success)

    def move_to(self, goal_x, goal_y, goal_z):
        if not self.ik_client.wait_for_service(timeout_sec=5.0):
            self.get_logger().error("get_ik недоступен")
            return False
        if not self.move_client.wait_for_service(timeout_sec=5.0):
            self.get_logger().error("joint_move недоступен")
            return False

        cur_x, cur_y, cur_z, cur_rx, cur_ry, cur_rz = self.tool

        max_xy = float(self.get_parameter("max_xy_step_m").value)
        max_z = float(self.get_parameter("max_z_step_m").value)

        cmd_x = cur_x + clip(goal_x - cur_x, -max_xy, max_xy)
        cmd_y = cur_y + clip(goal_y - cur_y, -max_xy, max_xy)
        cmd_z = cur_z + clip(goal_z - cur_z, -max_z, max_z)

        self.get_logger().info(
            f"CURRENT=({cur_x:.3f},{cur_y:.3f},{cur_z:.3f}) "
            f"GOAL=({goal_x:.3f},{goal_y:.3f},{goal_z:.3f}) "
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
            self.get_logger().error("get_ik не вернул ответ")
            return False

        ik_res = fut.result()
        joints = list(ik_res.joint)
        self.get_logger().info(f"IK: {ik_res.message} | joints={joints[:6]}")

        if len(joints) < 6:
            self.get_logger().error("IK вернул меньше 6 суставов")
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

        mv_fut = self.move_client.call_async(mv_req)
        rclpy.spin_until_future_complete(self, mv_fut, timeout_sec=30.0)
        if not mv_fut.done() or mv_fut.result() is None:
            self.get_logger().error("joint_move не вернул ответ")
            return False

        mv_res = mv_fut.result()
        self.get_logger().info(f"joint_move: ret={mv_res.ret} msg={mv_res.message}")
        return mv_res.ret in (0, 1)

    def spin_brief(self, sec=0.5):
        end = time.time() + sec
        while rclpy.ok() and time.time() < end:
            rclpy.spin_once(self, timeout_sec=0.05)

    def run(self):
        skip_initialize = bool(self.get_parameter("skip_initialize").value)

        if not skip_initialize:
            self.get_logger().info("Инициализация грипера")
            init_ok = self.call_trigger(self.gripper_init_client, "initialize")
            if not init_ok:
                self.get_logger().warn("Initialize вернул ошибку, продолжаю дальше")
        else:
            self.get_logger().info("Пропускаю initialize грипера")

        self.get_logger().info("Открытие грипера")
        if not self.call_trigger(self.gripper_open_client, "open"):
            return False

        self.spin_brief(0.5)

        tx, ty, tz = self.target
        tx += float(self.get_parameter("target_x_offset_m").value)
        ty += float(self.get_parameter("target_y_offset_m").value)
        tz += float(self.get_parameter("target_z_offset_m").value)

        pre_z = tz + float(self.get_parameter("pregrasp_above_m").value)
        grasp_z = tz + float(self.get_parameter("grasp_above_m").value)
        lift_up = float(self.get_parameter("lift_up_m").value)

        self.get_logger().info(f"STAGE 1 pregrasp -> ({tx:.3f}, {ty:.3f}, {pre_z:.3f})")
        if not self.move_to(tx, ty, pre_z):
            return False
        time.sleep(1.0)
        self.spin_brief(0.5)

        self.get_logger().info(f"STAGE 2 descend -> ({tx:.3f}, {ty:.3f}, {grasp_z:.3f})")
        if not self.move_to(tx, ty, grasp_z):
            return False
        time.sleep(1.0)
        self.spin_brief(0.5)

        self.get_logger().info("STAGE 3 close gripper")
        if not self.call_trigger(self.gripper_close_client, "close"):
            return False
        time.sleep(1.0)
        self.spin_brief(0.5)

        cur_x, cur_y, cur_z, _, _, _ = self.tool
        lift_z = cur_z + lift_up
        self.get_logger().info(f"STAGE 4 lift -> ({cur_x:.3f}, {cur_y:.3f}, {lift_z:.3f})")
        if not self.move_to(cur_x, cur_y, lift_z):
            return False

        self.get_logger().info("Pick sequence finished")
        return True


def main():
    rclpy.init()
    node = PipelinePickWithGripper()
    try:
        node.get_logger().info("Жду target/tool/joints ...")
        while rclpy.ok() and not node.ready():
            rclpy.spin_once(node, timeout_sec=0.1)

        if rclpy.ok():
            ok = node.run()
            if not ok:
                node.get_logger().error("Pick failed")
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
