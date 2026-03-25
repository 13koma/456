#!/usr/bin/env python3
"""
DH Robotics AG-95 Gripper - ROS2 Node
======================================

Provides ROS2 interface to control the AG-95 gripper via Modbus RTU.

Topics Published:
    ~/state          (dh_gripper_driver/GripperState)  - Gripper status at configured rate
    ~/joint_states   (sensor_msgs/JointState)          - For MoveIt/URDF integration

Topics Subscribed:
    ~/command         (std_msgs/Float32MultiArray)      - [position_permille, force_percent]
    ~/position_cmd    (std_msgs/Float32)                - Position only (0-1000 permille)

Services:
    ~/initialize     (std_srvs/Trigger)                - Initialize gripper
    ~/open           (std_srvs/Trigger)                - Fully open
    ~/close          (std_srvs/Trigger)                - Fully close
    ~/set_force      (std_srvs/SetBool) [hack]         - Not ideal, use command topic

Parameters:
    port             (string)  - Serial port (default: /dev/ttyUSB0)
    slave_id         (int)     - Modbus slave ID (default: 1)
    baudrate         (int)     - Baud rate (default: 115200)
    publish_rate     (float)   - State publish rate Hz (default: 10.0)
    auto_initialize  (bool)    - Init on startup (default: false)
    default_force    (int)     - Default force % (default: 50)
    simulation_mode  (bool)    - Sim mode, no real hardware (default: false)
"""

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy

from std_msgs.msg import Float32, Float32MultiArray, String
from std_srvs.srv import Trigger
from sensor_msgs.msg import JointState

import time
import threading
import json

from dh_gripper_driver.ag95_modbus import (
    AG95ModbusDriver,
    GripperState as AG95State,
    InitState,
    GripperStatus,
)


class GripperNode(Node):
    """ROS2 node for DH Robotics AG-95 gripper control."""

    def __init__(self):
        super().__init__('dh_gripper_node')

        # ----- Parameters -----
        self.declare_parameter('port', '/dev/ttyUSB0')
        self.declare_parameter('slave_id', 1)
        self.declare_parameter('baudrate', 115200)
        self.declare_parameter('publish_rate', 10.0)
        self.declare_parameter('auto_initialize', False)
        self.declare_parameter('default_force', 50)
        self.declare_parameter('simulation_mode', False)
        self.declare_parameter('joint_name', 'gripper_joint')

        self.port = self.get_parameter('port').value
        self.slave_id = self.get_parameter('slave_id').value
        self.baudrate = self.get_parameter('baudrate').value
        self.publish_rate = self.get_parameter('publish_rate').value
        self.auto_init = self.get_parameter('auto_initialize').value
        self.default_force = self.get_parameter('default_force').value
        self.sim_mode = self.get_parameter('simulation_mode').value
        self.joint_name = self.get_parameter('joint_name').value

        # ----- Driver -----
        self.driver = None
        self._lock = threading.Lock()

        # Sim state
        self._sim_position = 1000  # Open
        self._sim_state = 1  # Reached
        self._sim_force = 50
        self._sim_initialized = False

        # ----- QoS Profiles -----
        qos_state = QoSProfile(
            reliability=ReliabilityPolicy.RELIABLE,
            history=HistoryPolicy.KEEP_LAST,
            depth=10,
        )
        qos_cmd = QoSProfile(
            reliability=ReliabilityPolicy.RELIABLE,
            history=HistoryPolicy.KEEP_LAST,
            depth=1,
        )

        # ----- Publishers -----
        # Gripper state as JSON (universal, no custom msg dependency)
        self.state_pub = self.create_publisher(
            String, '~/state', qos_state
        )
        # JointState for URDF/MoveIt
        self.joint_state_pub = self.create_publisher(
            JointState, '~/joint_states', qos_state
        )
        # Simple position feedback
        self.position_pub = self.create_publisher(
            Float32, '~/current_position', qos_state
        )

        # ----- Subscribers -----
        # Command: [position_permille, force_percent]
        self.create_subscription(
            Float32MultiArray, '~/command', self._command_cb, qos_cmd
        )
        # Simple position command
        self.create_subscription(
            Float32, '~/position_cmd', self._position_cmd_cb, qos_cmd
        )

        # ----- Services -----
        self.create_service(Trigger, '~/initialize', self._init_srv)
        self.create_service(Trigger, '~/open', self._open_srv)
        self.create_service(Trigger, '~/close', self._close_srv)

        # ----- Connect -----
        if not self.sim_mode:
            self._connect_driver()
        else:
            self.get_logger().info('Running in SIMULATION mode (no hardware)')

        # Auto-initialize
        if self.auto_init:
            self.get_logger().info('Auto-initializing gripper...')
            threading.Thread(target=self._auto_initialize, daemon=True).start()

        # ----- Timer for state publishing -----
        period = 1.0 / self.publish_rate
        self.create_timer(period, self._publish_state)

        self.get_logger().info(
            f'AG-95 Gripper Node started '
            f'(port={self.port}, sim={self.sim_mode}, rate={self.publish_rate}Hz)'
        )

    def _connect_driver(self):
        """Attempt to connect to the gripper hardware."""
        try:
            self.driver = AG95ModbusDriver(
                port=self.port,
                slave_id=self.slave_id,
                baudrate=self.baudrate,
            )
            self.driver.connect()
            self.get_logger().info(f'Connected to AG-95 on {self.port}')
        except Exception as e:
            self.get_logger().error(f'Failed to connect: {e}')
            self.driver = None

    def _auto_initialize(self):
        """Run initialization in a background thread."""
        time.sleep(1.0)  # Wait for node to fully start
        if self.sim_mode:
            self._sim_initialized = True
            self.get_logger().info('Simulation: gripper initialized')
            return

        if self.driver and self.driver.is_connected:
            success = self.driver.initialize(full=True, timeout=15.0)
            if success:
                self.get_logger().info('Gripper auto-initialization complete')
            else:
                self.get_logger().error('Gripper auto-initialization FAILED')

    # =====================================================================
    # Callbacks
    # =====================================================================

    def _command_cb(self, msg: Float32MultiArray):
        """Handle command: [position_permille, force_percent]."""
        if len(msg.data) < 1:
            return

        position = int(msg.data[0])
        force = int(msg.data[1]) if len(msg.data) > 1 else self.default_force

        self.get_logger().debug(f'Command: pos={position}, force={force}%')

        if self.sim_mode:
            self._sim_position = max(0, min(1000, position))
            self._sim_force = max(20, min(100, force))
            self._sim_state = 1  # Reached immediately in sim
            return

        with self._lock:
            if self.driver and self.driver.is_connected:
                self.driver.set_force(force)
                self.driver.set_position(position)

    def _position_cmd_cb(self, msg: Float32):
        """Handle simple position command (permille)."""
        position = int(msg.data)
        self.get_logger().debug(f'Position cmd: {position}')

        if self.sim_mode:
            self._sim_position = max(0, min(1000, position))
            self._sim_state = 1
            return

        with self._lock:
            if self.driver and self.driver.is_connected:
                self.driver.set_position(position)

    # =====================================================================
    # Services
    # =====================================================================

    def _init_srv(self, request, response):
        """Initialize gripper service."""
        self.get_logger().info('Initialize service called')

        if self.sim_mode:
            self._sim_initialized = True
            response.success = True
            response.message = 'Simulation: initialized'
            return response

        with self._lock:
            if not self.driver or not self.driver.is_connected:
                response.success = False
                response.message = 'Gripper not connected'
                return response

            try:
                success = self.driver.initialize(full=True, timeout=15.0)
                response.success = success
                response.message = 'Initialized' if success else 'Init failed/timeout'
            except Exception as e:
                response.success = False
                response.message = f'Error: {e}'

        return response

    def _open_srv(self, request, response):
        """Fully open gripper."""
        self.get_logger().info('Open service called')

        if self.sim_mode:
            self._sim_position = 1000
            self._sim_state = 1
            response.success = True
            response.message = 'Simulation: opened'
            return response

        with self._lock:
            if not self.driver or not self.driver.is_connected:
                response.success = False
                response.message = 'Gripper not connected'
                return response

            try:
                success = self.driver.open(self.default_force)
                response.success = success
                response.message = 'Opening' if success else 'Failed'
            except Exception as e:
                response.success = False
                response.message = f'Error: {e}'

        return response

    def _close_srv(self, request, response):
        """Fully close gripper."""
        self.get_logger().info('Close service called')

        if self.sim_mode:
            self._sim_position = 0
            self._sim_state = 2  # Object caught
            response.success = True
            response.message = 'Simulation: closed'
            return response

        with self._lock:
            if not self.driver or not self.driver.is_connected:
                response.success = False
                response.message = 'Gripper not connected'
                return response

            try:
                success = self.driver.close(self.default_force)
                response.success = success
                response.message = 'Closing' if success else 'Failed'
            except Exception as e:
                response.success = False
                response.message = f'Error: {e}'

        return response

    # =====================================================================
    # State Publishing
    # =====================================================================

    def _publish_state(self):
        """Periodic state publisher."""
        if self.sim_mode:
            self._publish_sim_state()
            return

        if not self.driver or not self.driver.is_connected:
            return

        with self._lock:
            try:
                status = self.driver.get_status()
            except Exception as e:
                self.get_logger().error(f'Status read error: {e}', throttle_duration_sec=5.0)
                return

        if status is None:
            return

        # Publish JSON state
        state_dict = {
            'initialized': status.is_initialized,
            'state': status.gripper_state.name,
            'state_code': int(status.gripper_state),
            'position_permille': status.current_position,
            'position_mm': round(status.current_position_mm, 2),
            'force_percent': status.force_setting,
            'target_permille': status.position_setting,
            'is_moving': status.is_moving,
            'object_caught': status.object_caught,
            'object_dropped': status.object_dropped,
        }
        state_msg = String()
        state_msg.data = json.dumps(state_dict)
        self.state_pub.publish(state_msg)

        # Publish simple position
        pos_msg = Float32()
        pos_msg.data = float(status.current_position)
        self.position_pub.publish(pos_msg)

        # Publish JointState
        self._publish_joint_state(status.current_position)

    def _publish_sim_state(self):
        """Publish simulated state."""
        state_dict = {
            'initialized': self._sim_initialized,
            'state': AG95State(self._sim_state).name if self._sim_initialized else 'NOT_INITIALIZED',
            'state_code': self._sim_state,
            'position_permille': self._sim_position,
            'position_mm': round((self._sim_position / 1000.0) * 98.0, 2),
            'force_percent': self._sim_force,
            'target_permille': self._sim_position,
            'is_moving': False,
            'object_caught': self._sim_state == 2,
            'object_dropped': self._sim_state == 3,
        }
        state_msg = String()
        state_msg.data = json.dumps(state_dict)
        self.state_pub.publish(state_msg)

        pos_msg = Float32()
        pos_msg.data = float(self._sim_position)
        self.position_pub.publish(pos_msg)

        self._publish_joint_state(self._sim_position)

    def _publish_joint_state(self, position_permille: int):
        """Publish JointState for URDF integration."""
        js = JointState()
        js.header.stamp = self.get_clock().now().to_msg()
        js.name = [self.joint_name]
        # Convert permille to meters for prismatic joint (0-0.049m per finger)
        js.position = [(position_permille / 1000.0) * 0.049]
        js.velocity = [0.0]
        js.effort = [0.0]
        self.joint_state_pub.publish(js)

    def destroy_node(self):
        """Clean shutdown."""
        if self.driver:
            self.driver.disconnect()
        super().destroy_node()


def main(args=None):
    rclpy.init(args=args)
    node = GripperNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
