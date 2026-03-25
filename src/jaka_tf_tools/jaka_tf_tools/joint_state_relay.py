from __future__ import annotations

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState


class JointStateRelay(Node):
    def __init__(self) -> None:
        super().__init__('joint_state_relay')

        self.declare_parameter('input_topic', '/jaka_driver/joint_position')
        self.declare_parameter('output_topic', '/joint_states')
        self.declare_parameter('clear_frame_id', True)

        self.input_topic = str(self.get_parameter('input_topic').value)
        self.output_topic = str(self.get_parameter('output_topic').value)
        self.clear_frame_id = bool(self.get_parameter('clear_frame_id').value)

        self.pub = self.create_publisher(JointState, self.output_topic, 20)
        self.sub = self.create_subscription(JointState, self.input_topic, self._cb, 20)

        self.get_logger().info(f'Relaying {self.input_topic} -> {self.output_topic}')

    def _cb(self, msg: JointState) -> None:
        out = JointState()
        out.header = msg.header
        if self.clear_frame_id:
            out.header.frame_id = ''
        out.name = list(msg.name)
        out.position = list(msg.position)
        out.velocity = list(msg.velocity)
        out.effort = list(msg.effort)
        self.pub.publish(out)


def main(args=None) -> None:
    rclpy.init(args=args)
    node = JointStateRelay()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()
