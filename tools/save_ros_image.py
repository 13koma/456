#!/usr/bin/env python3
import sys
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
import numpy as np
import cv2

TOPIC = sys.argv[1] if len(sys.argv) > 1 else '/camera/camera/color/image_raw'
OUT = sys.argv[2] if len(sys.argv) > 2 else '/tmp/ros_frame.png'

class Saver(Node):
    def __init__(self):
        super().__init__('save_ros_image')
        self.sub = self.create_subscription(Image, TOPIC, self.cb, 10)

    def cb(self, msg):
        if msg.encoding in ('rgb8', 'bgr8'):
            img = np.frombuffer(msg.data, dtype=np.uint8).reshape(msg.height, msg.width, 3)
            if msg.encoding == 'rgb8':
                img = cv2.cvtColor(img, cv2.COLOR_RGB2BGR)
        elif msg.encoding == 'mono8':
            img = np.frombuffer(msg.data, dtype=np.uint8).reshape(msg.height, msg.width)
        else:
            self.get_logger().error(f'Unsupported encoding: {msg.encoding}')
            rclpy.shutdown()
            return

        cv2.imwrite(OUT, img)
        self.get_logger().info(f'Saved {OUT}')
        rclpy.shutdown()

rclpy.init()
node = Saver()
rclpy.spin(node)
node.destroy_node()
