from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from pathlib import Path


def generate_launch_description():
    config = str(Path(get_package_share_directory('jaka_tf_tools')) / 'config' / 'jaka_tf_tools.yaml')

    return LaunchDescription([
        Node(
            package='jaka_tf_tools',
            executable='tcp_tf_broadcaster',
            name='tcp_tf_broadcaster',
            output='screen',
            parameters=[config],
        ),
        Node(
            package='jaka_tf_tools',
            executable='static_camera_tf',
            name='static_camera_tf',
            output='screen',
            parameters=[config],
        ),
        Node(
            package='jaka_tf_tools',
            executable='joint_state_relay',
            name='joint_state_relay',
            output='screen',
            parameters=[config],
        ),
    ])
