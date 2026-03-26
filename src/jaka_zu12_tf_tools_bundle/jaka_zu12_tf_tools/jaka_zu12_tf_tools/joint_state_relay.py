#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, DurabilityPolicy, HistoryPolicy
from sensor_msgs.msg import JointState


class JointStateRelay(Node):
    def __init__(self):
        super().__init__('joint_state_relay')

        self.declare_parameter('input_topic', '/jaka_driver/joint_position')
        self.declare_parameter('output_topic', '/joint_states')
        self.declare_parameter('stamp_now', True)
        self.declare_parameter('frame_id', '')

        input_topic = self.get_parameter('input_topic').get_parameter_value().string_value
        output_topic = self.get_parameter('output_topic').get_parameter_value().string_value
        self.stamp_now = self.get_parameter('stamp_now').get_parameter_value().bool_value
        self.frame_id_override = self.get_parameter('frame_id').get_parameter_value().string_value

        qos = QoSProfile(
            reliability=ReliabilityPolicy.RELIABLE,
            durability=DurabilityPolicy.VOLATILE,
            history=HistoryPolicy.KEEP_LAST,
            depth=10,
        )

        self.pub = self.create_publisher(JointState, output_topic, qos)
        self.sub = self.create_subscription(JointState, input_topic, self._cb, qos)

        self.get_logger().info(
            f'Relaying JointState: {input_topic} -> {output_topic} | stamp_now={self.stamp_now}'
        )

    def _cb(self, msg: JointState):
        out = JointState()
        out.header = msg.header
        if self.stamp_now:
            out.header.stamp = self.get_clock().now().to_msg()
        if self.frame_id_override:
            out.header.frame_id = self.frame_id_override
        out.name = list(msg.name)
        out.position = list(msg.position)
        out.velocity = list(msg.velocity)
        out.effort = list(msg.effort)
        self.pub.publish(out)


def main(args=None):
    rclpy.init(args=args)
    node = JointStateRelay()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
