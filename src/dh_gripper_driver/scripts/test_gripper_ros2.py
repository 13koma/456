#!/usr/bin/env python3
"""
ROS2 Gripper Integration Test
===============================

Tests the gripper node via ROS2 topics and services.
Run after: ros2 launch dh_gripper_driver gripper.launch.py simulation:=true

Usage:
    ros2 run dh_gripper_driver test_gripper_ros2.py
"""

import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32, Float32MultiArray, String
from std_srvs.srv import Trigger
import json
import time


class GripperTestNode(Node):
    def __init__(self):
        super().__init__('gripper_test')

        self.last_state = None
        self.last_position = None

        # Subscribers
        self.create_subscription(
            String, '/dh_gripper_node/state', self._state_cb, 10
        )
        self.create_subscription(
            Float32, '/dh_gripper_node/current_position', self._pos_cb, 10
        )

        # Publishers
        self.cmd_pub = self.create_publisher(
            Float32MultiArray, '/dh_gripper_node/command', 10
        )
        self.pos_pub = self.create_publisher(
            Float32, '/dh_gripper_node/position_cmd', 10
        )

        # Service clients
        self.init_client = self.create_client(Trigger, '/dh_gripper_node/initialize')
        self.open_client = self.create_client(Trigger, '/dh_gripper_node/open')
        self.close_client = self.create_client(Trigger, '/dh_gripper_node/close')

        self.get_logger().info('Gripper test node started. Waiting 2s for connections...')
        time.sleep(2.0)

        # Run tests
        self.create_timer(0.5, self._run_tests_once)
        self._tests_done = False

    def _state_cb(self, msg):
        self.last_state = json.loads(msg.data)

    def _pos_cb(self, msg):
        self.last_position = msg.data

    def _call_service(self, client, name):
        if not client.wait_for_service(timeout_sec=3.0):
            self.get_logger().error(f'Service {name} not available')
            return None
        future = client.call_async(Trigger.Request())
        rclpy.spin_until_future_complete(self, future, timeout_sec=5.0)
        if future.result():
            self.get_logger().info(f'{name}: success={future.result().success}, msg={future.result().message}')
            return future.result()
        return None

    def _run_tests_once(self):
        if self._tests_done:
            return
        self._tests_done = True

        self.get_logger().info('=' * 50)
        self.get_logger().info('Starting gripper integration tests')
        self.get_logger().info('=' * 50)

        # Test 1: Check state is published
        self.get_logger().info('\n[Test 1] Checking state publication...')
        if self.last_state:
            self.get_logger().info(f'  State: {json.dumps(self.last_state, indent=2)}')
            self.get_logger().info('  ✅ State published')
        else:
            self.get_logger().warn('  ⚠️ No state received yet')

        # Test 2: Initialize
        self.get_logger().info('\n[Test 2] Initialize...')
        self._call_service(self.init_client, 'Initialize')
        time.sleep(0.5)

        # Test 3: Open
        self.get_logger().info('\n[Test 3] Open gripper...')
        self._call_service(self.open_client, 'Open')
        time.sleep(0.5)

        # Test 4: Close
        self.get_logger().info('\n[Test 4] Close gripper...')
        self._call_service(self.close_client, 'Close')
        time.sleep(0.5)

        # Test 5: Position command via topic
        self.get_logger().info('\n[Test 5] Position command (500‰)...')
        msg = Float32()
        msg.data = 500.0
        self.pos_pub.publish(msg)
        time.sleep(0.5)

        # Test 6: Full command via topic
        self.get_logger().info('\n[Test 6] Full command (300‰, 80% force)...')
        cmd = Float32MultiArray()
        cmd.data = [300.0, 80.0]
        self.cmd_pub.publish(cmd)
        time.sleep(0.5)

        # Final state
        self.get_logger().info('\n[Final] Current state:')
        if self.last_state:
            self.get_logger().info(f'  Position: {self.last_state.get("position_permille")}‰')
            self.get_logger().info(f'  State: {self.last_state.get("state")}')

        self.get_logger().info('\n' + '=' * 50)
        self.get_logger().info('Tests complete!')
        self.get_logger().info('=' * 50)


def main():
    rclpy.init()
    node = GripperTestNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
