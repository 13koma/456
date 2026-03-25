"""
DH Robotics AG-95 Gripper Launch File
======================================

Usage:
    # Real hardware:
    ros2 launch dh_gripper_driver gripper.launch.py

    # With custom port:
    ros2 launch dh_gripper_driver gripper.launch.py port:=/dev/ttyUSB1

    # Simulation:
    ros2 launch dh_gripper_driver gripper.launch.py simulation:=true

    # Auto-initialize on startup:
    ros2 launch dh_gripper_driver gripper.launch.py auto_init:=true
"""

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    pkg_dir = get_package_share_directory('dh_gripper_driver')

    # Arguments
    port_arg = DeclareLaunchArgument(
        'port', default_value='/dev/ttyUSB0',
        description='Serial port for USB-to-RS485 adapter'
    )
    sim_arg = DeclareLaunchArgument(
        'simulation', default_value='false',
        description='Run in simulation mode'
    )
    auto_init_arg = DeclareLaunchArgument(
        'auto_init', default_value='false',
        description='Auto-initialize gripper on startup'
    )
    force_arg = DeclareLaunchArgument(
        'default_force', default_value='50',
        description='Default gripping force (20-100%%)'
    )
    rate_arg = DeclareLaunchArgument(
        'publish_rate', default_value='10.0',
        description='State publish rate (Hz)'
    )

    gripper_node = Node(
        package='dh_gripper_driver',
        executable='gripper_node.py',
        name='dh_gripper_node',
        output='screen',
        parameters=[
            os.path.join(pkg_dir, 'config', 'gripper_params.yaml'),
            {
                'port': LaunchConfiguration('port'),
                'simulation_mode': LaunchConfiguration('simulation'),
                'auto_initialize': LaunchConfiguration('auto_init'),
                'default_force': LaunchConfiguration('default_force'),
                'publish_rate': LaunchConfiguration('publish_rate'),
            },
        ],
    )

    return LaunchDescription([
        port_arg,
        sim_arg,
        auto_init_arg,
        force_arg,
        rate_arg,
        gripper_node,
    ])
