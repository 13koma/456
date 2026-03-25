#!/usr/bin/env python3
import math
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseStamped, TwistStamped
from sensor_msgs.msg import JointState
from jaka_msgs.srv import GetIK, Move


def clip(v: float, lo: float, hi: float) -> float:
    return max(lo, min(hi, v))


class PipelinePreviewExecutor(Node):
    def __init__(self):
        super().__init__("pipeline_preview_executor")

        self.declare_parameter("grasp_topic", "/grasp_inference_node/object_center_base")
        self.declare_parameter("tool_topic", "/jaka_driver/tool_position")
        self.declare_parameter("joint_topic", "/jaka_driver/joint_position")
        self.declare_parameter("get_ik_service", "/jaka_driver/get_ik")
        self.declare_parameter("joint_move_service", "/jaka_driver/joint_move")

        self.declare_parameter("max_dx_m", 0.03)   # первый шаг: 3 см
        self.declare_parameter("max_dy_m", 0.03)   # первый шаг: 3 см
        self.declare_parameter("use_target_z", False)
        self.declare_parameter("max_dz_m", 0.02)
        self.declare_parameter("z_bias_m", 0.0)
        self.declare_parameter("min_z_m", 0.20)

        self.declare_parameter("mvvelo", 0.2)
        self.declare_parameter("mvacc", 0.2)

        self.target = None   # (x,y,z) в метрах, base_link
        self.tool = None     # (x,y,z,rx,ry,rz), x/y/z в метрах, rpy в радианах
        self.joints = None   # 6 суставов, рад

        grasp_topic = self.get_parameter("grasp_topic").value
        tool_topic = self.get_parameter("tool_topic").value
        joint_topic = self.get_parameter("joint_topic").value

        self.create_subscription(PoseStamped, grasp_topic, self.target_cb, 10)
        self.create_subscription(TwistStamped, tool_topic, self.tool_cb, 10)
        self.create_subscription(JointState, joint_topic, self.joint_cb, 10)

        self.ik_client = self.create_client(GetIK, self.get_parameter("get_ik_service").value)
        self.move_client = self.create_client(Move, self.get_parameter("joint_move_service").value)

    def target_cb(self, msg: PoseStamped):
        self.target = (
            float(msg.pose.position.x),
            float(msg.pose.position.y),
            float(msg.pose.position.z),
        )

    def tool_cb(self, msg: TwistStamped):
        # tool_position приходит: xyz в мм, углы в градусах
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

    def execute_once(self) -> bool:
        if not self.ik_client.wait_for_service(timeout_sec=5.0):
            self.get_logger().error("Сервис get_ik недоступен")
            return False
        if not self.move_client.wait_for_service(timeout_sec=5.0):
            self.get_logger().error("Сервис joint_move недоступен")
            return False

        cur_x, cur_y, cur_z, cur_rx, cur_ry, cur_rz = self.tool
        tgt_x, tgt_y, tgt_z = self.target

        max_dx = float(self.get_parameter("max_dx_m").value)
        max_dy = float(self.get_parameter("max_dy_m").value)
        use_target_z = bool(self.get_parameter("use_target_z").value)
        max_dz = float(self.get_parameter("max_dz_m").value)
        z_bias = float(self.get_parameter("z_bias_m").value)
        min_z = float(self.get_parameter("min_z_m").value)

        dx = clip(tgt_x - cur_x, -max_dx, max_dx)
        dy = clip(tgt_y - cur_y, -max_dy, max_dy)

        goal_x = cur_x + dx
        goal_y = cur_y + dy

        if use_target_z:
            dz = clip(tgt_z - cur_z, -max_dz, max_dz)
            goal_z = cur_z + dz + z_bias
        else:
            goal_z = cur_z + z_bias

        goal_z = max(goal_z, min_z)

        self.get_logger().info(
            f"CURRENT tcp[m]: x={cur_x:.3f} y={cur_y:.3f} z={cur_z:.3f} | "
            f"TARGET[m]: x={tgt_x:.3f} y={tgt_y:.3f} z={tgt_z:.3f}"
        )
        self.get_logger().info(
            f"GOAL[m]: x={goal_x:.3f} y={goal_y:.3f} z={goal_z:.3f} | "
            f"RPY[rad]: rx={cur_rx:.3f} ry={cur_ry:.3f} rz={cur_rz:.3f}"
        )

        ik_req = GetIK.Request()
        ik_req.ref_joint = self.joints
        ik_req.cartesian_pose = [
            goal_x * 1000.0,  # get_ik ждёт мм
            goal_y * 1000.0,
            goal_z * 1000.0,
            cur_rx,           # и RPY в радианах
            cur_ry,
            cur_rz,
        ]

        ik_future = self.ik_client.call_async(ik_req)
        rclpy.spin_until_future_complete(self, ik_future, timeout_sec=5.0)
        if not ik_future.done() or ik_future.result() is None:
            self.get_logger().error("get_ik не вернул результат")
            return False

        ik_res = ik_future.result()
        joints = list(ik_res.joint)

        if len(joints) < 6 or any(abs(j) > 1000.0 for j in joints[:6]):
            self.get_logger().error(f"Плохой IK: {joints} | msg={ik_res.message}")
            return False

        self.get_logger().info(f"IK joints[rad]: {joints[:6]} | msg={ik_res.message}")

        move_req = Move.Request()
        move_req.pose = joints[:6]
        move_req.has_ref = False
        move_req.ref_joint = []
        move_req.mvvelo = float(self.get_parameter("mvvelo").value)
        move_req.mvacc = float(self.get_parameter("mvacc").value)
        move_req.mvtime = 0.0
        move_req.mvradii = 0.0
        move_req.coord_mode = 0
        move_req.index = 0

        move_future = self.move_client.call_async(move_req)
        rclpy.spin_until_future_complete(self, move_future, timeout_sec=30.0)
        if not move_future.done() or move_future.result() is None:
            self.get_logger().error("joint_move не вернул результат")
            return False

        move_res = move_future.result()
        self.get_logger().info(f"joint_move ret={move_res.ret} msg={move_res.message}")
        return bool(move_res.ret)


def main():
    rclpy.init()
    node = PipelinePreviewExecutor()

    try:
        node.get_logger().info("Жду target/tool/joints ...")
        while rclpy.ok() and not node.ready():
            rclpy.spin_once(node, timeout_sec=0.1)

        if not rclpy.ok():
            return

        ok = node.execute_once()
        if ok:
            node.get_logger().info("Готово: preview move выполнен")
        else:
            node.get_logger().error("Preview move не выполнен")
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
