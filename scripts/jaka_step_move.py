#!/usr/bin/env python3
import math
import sys
import time

import cv2
import numpy as np
import rclpy
from geometry_msgs.msg import TwistStamped
from rclpy.node import Node

from jaka_msgs.srv import Move


def rpy_deg_to_angle_axis(rx_deg: float, ry_deg: float, rz_deg: float) -> tuple[float, float, float]:
    rx = math.radians(rx_deg)
    ry = math.radians(ry_deg)
    rz = math.radians(rz_deg)

    crx, srx = math.cos(rx), math.sin(rx)
    cry, sry = math.cos(ry), math.sin(ry)
    crz, srz = math.cos(rz), math.sin(rz)

    rot_x = np.array([[1.0, 0.0, 0.0], [0.0, crx, -srx], [0.0, srx, crx]], dtype=np.float64)
    rot_y = np.array([[cry, 0.0, sry], [0.0, 1.0, 0.0], [-sry, 0.0, cry]], dtype=np.float64)
    rot_z = np.array([[crz, -srz, 0.0], [srz, crz, 0.0], [0.0, 0.0, 1.0]], dtype=np.float64)
    rot = rot_z @ rot_y @ rot_x

    ang_axis, _ = cv2.Rodrigues(rot)
    return float(ang_axis[0, 0]), float(ang_axis[1, 0]), float(ang_axis[2, 0])


class StepMoveNode(Node):
    def __init__(self, dx_mm: float, dy_mm: float, dz_mm: float, vel: float, acc: float):
        super().__init__("jaka_step_move")
        self.dx_mm = dx_mm
        self.dy_mm = dy_mm
        self.dz_mm = dz_mm
        self.vel = vel
        self.acc = acc
        self.current = None

        self.sub = self.create_subscription(TwistStamped, "/jaka_driver/tool_position", self._on_pose, 10)
        self.cli = self.create_client(Move, "/jaka_driver/linear_move")

    def _on_pose(self, msg: TwistStamped):
        self.current = [
            float(msg.twist.linear.x),
            float(msg.twist.linear.y),
            float(msg.twist.linear.z),
            float(msg.twist.angular.x),
            float(msg.twist.angular.y),
            float(msg.twist.angular.z),
        ]

    def run(self) -> int:
        deadline = time.monotonic() + 3.0
        while self.current is None and time.monotonic() < deadline and rclpy.ok():
            rclpy.spin_once(self, timeout_sec=0.1)
        if self.current is None:
            self.get_logger().error("No /jaka_driver/tool_position received")
            return 1

        if not self.cli.wait_for_service(timeout_sec=3.0):
            self.get_logger().error("/jaka_driver/linear_move is not available")
            return 1

        x = self.current[0] + self.dx_mm
        y = self.current[1] + self.dy_mm
        z = self.current[2] + self.dz_mm
        ax, ay, az = rpy_deg_to_angle_axis(self.current[3], self.current[4], self.current[5])

        req = Move.Request()
        req.pose = [float(x), float(y), float(z), float(ax), float(ay), float(az)]
        req.has_ref = False
        req.ref_joint = [0.0]
        req.mvvelo = float(self.vel)
        req.mvacc = float(self.acc)
        req.mvtime = 0.0
        req.mvradii = 0.0
        req.coord_mode = 0
        req.index = 0

        self.get_logger().info(
            f"Current TCP mm/deg: {self.current}"
        )
        self.get_logger().info(
            f"Target TCP mm: [{x:.3f}, {y:.3f}, {z:.3f}] | delta=[{self.dx_mm:.3f}, {self.dy_mm:.3f}, {self.dz_mm:.3f}]"
        )

        future = self.cli.call_async(req)
        while not future.done() and rclpy.ok():
            rclpy.spin_once(self, timeout_sec=0.1)

        if not rclpy.ok():
            return 1

        res = future.result()
        if res is None:
            self.get_logger().error("linear_move returned no response")
            return 1

        self.get_logger().info(f"linear_move ret={res.ret} message={res.message}")
        return 0 if int(res.ret) in (0, 1) else 1


def main():
    if len(sys.argv) < 4:
        print("Usage: jaka_step_move.py DX_MM DY_MM DZ_MM [VEL_MM_S] [ACC_MM_S2]")
        print("Example: jaka_step_move.py 0 0 -50 20 20")
        raise SystemExit(2)

    dx_mm = float(sys.argv[1])
    dy_mm = float(sys.argv[2])
    dz_mm = float(sys.argv[3])
    vel = float(sys.argv[4]) if len(sys.argv) > 4 else 20.0
    acc = float(sys.argv[5]) if len(sys.argv) > 5 else 20.0

    rclpy.init()
    node = StepMoveNode(dx_mm, dy_mm, dz_mm, vel, acc)
    try:
        code = node.run()
    finally:
        node.destroy_node()
        rclpy.shutdown()
    raise SystemExit(code)


if __name__ == "__main__":
    main()
