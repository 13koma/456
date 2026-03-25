from __future__ import annotations

import math

import rclpy
from geometry_msgs.msg import TransformStamped
from rclpy.node import Node
from tf2_ros.static_transform_broadcaster import StaticTransformBroadcaster


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


class StaticCameraTf(Node):
    def __init__(self) -> None:
        super().__init__('static_camera_tf')

        self.declare_parameter('parent_frame', 'jaka_tcp')
        self.declare_parameter('child_frame', 'camera_link')
        self.declare_parameter('xyz', [0.0, 0.0, 0.0])
        self.declare_parameter('rpy', [0.0, 0.0, 0.0])
        self.declare_parameter('degrees', False)

        parent_frame = str(self.get_parameter('parent_frame').value)
        child_frame = str(self.get_parameter('child_frame').value)
        xyz = list(self.get_parameter('xyz').value)
        rpy = list(self.get_parameter('rpy').value)
        degrees = bool(self.get_parameter('degrees').value)

        if len(xyz) != 3 or len(rpy) != 3:
            raise ValueError('xyz and rpy must have exactly 3 values each')

        x, y, z = [float(v) for v in xyz]
        roll, pitch, yaw = [float(v) for v in rpy]
        if degrees:
            roll = math.radians(roll)
            pitch = math.radians(pitch)
            yaw = math.radians(yaw)

        qx, qy, qz, qw = quaternion_from_euler(roll, pitch, yaw)

        self.broadcaster = StaticTransformBroadcaster(self)

        t = TransformStamped()
        t.header.stamp = self.get_clock().now().to_msg()
        t.header.frame_id = parent_frame
        t.child_frame_id = child_frame
        t.transform.translation.x = x
        t.transform.translation.y = y
        t.transform.translation.z = z
        t.transform.rotation.x = qx
        t.transform.rotation.y = qy
        t.transform.rotation.z = qz
        t.transform.rotation.w = qw
        self.broadcaster.sendTransform(t)

        self.get_logger().info(
            f'Publishing static TF {parent_frame} -> {child_frame}: '
            f'xyz=[{x:.4f}, {y:.4f}, {z:.4f}] '
            f'rpy=[{roll:.4f}, {pitch:.4f}, {yaw:.4f}] rad'
        )


def main(args=None) -> None:
    rclpy.init(args=args)
    node = StaticCameraTf()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()
