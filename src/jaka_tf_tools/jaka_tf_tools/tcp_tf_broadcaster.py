from __future__ import annotations

import math

import rclpy
from geometry_msgs.msg import TransformStamped, TwistStamped
from rclpy.node import Node
from tf2_ros import TransformBroadcaster


def quaternion_from_euler(roll: float, pitch: float, yaw: float) -> tuple[float, float, float, float]:
    cr = math.cos(roll * 0.5)
    sr = math.sin(roll * 0.5)
    cp = math.cos(pitch * 0.5)
    sp = math.sin(pitch * 0.5)
    cy = math.cos(yaw * 0.5)
    sy = math.sin(yaw * 0.5)

    qw = cr * cp * cy + sr * sp * sy
    qx = sr * cp * cy - cr * sp * sy
    qy = cr * sp * cy + sr * cp * sy
    qz = cr * cp * sy - sr * sp * cy
    return qx, qy, qz, qw


class JakaTcpTfBroadcaster(Node):
    def __init__(self) -> None:
        super().__init__('tcp_tf_broadcaster')

        self.declare_parameter('input_topic', '/jaka_driver/tool_position')
        self.declare_parameter('parent_frame', 'base_link')
        self.declare_parameter('child_frame', 'jaka_tcp')
        self.declare_parameter('use_degrees', True)

        self.input_topic = str(self.get_parameter('input_topic').value)
        self.parent_frame = str(self.get_parameter('parent_frame').value)
        self.child_frame = str(self.get_parameter('child_frame').value)
        self.use_degrees = bool(self.get_parameter('use_degrees').value)

        self.tf_broadcaster = TransformBroadcaster(self)
        self.sub = self.create_subscription(TwistStamped, self.input_topic, self._cb, 20)

        self.get_logger().info(
            f'Publishing TF {self.parent_frame} -> {self.child_frame} from {self.input_topic} '
            f'(angles in {"deg" if self.use_degrees else "rad"})'
        )

    def _cb(self, msg: TwistStamped) -> None:
        roll = float(msg.twist.angular.x)
        pitch = float(msg.twist.angular.y)
        yaw = float(msg.twist.angular.z)

        if self.use_degrees:
            roll = math.radians(roll)
            pitch = math.radians(pitch)
            yaw = math.radians(yaw)

        qx, qy, qz, qw = quaternion_from_euler(roll, pitch, yaw)

        t = TransformStamped()
        t.header.stamp = msg.header.stamp if (msg.header.stamp.sec != 0 or msg.header.stamp.nanosec != 0) else self.get_clock().now().to_msg()
        t.header.frame_id = self.parent_frame
        t.child_frame_id = self.child_frame
        t.transform.translation.x = float(msg.twist.linear.x) * 0.001
        t.transform.translation.y = float(msg.twist.linear.y) * 0.001
        t.transform.translation.z = float(msg.twist.linear.z) * 0.001
        t.transform.rotation.x = qx
        t.transform.rotation.y = qy
        t.transform.rotation.z = qz
        t.transform.rotation.w = qw
        self.tf_broadcaster.sendTransform(t)


def main(args=None) -> None:
    rclpy.init(args=args)
    node = JakaTcpTfBroadcaster()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()
