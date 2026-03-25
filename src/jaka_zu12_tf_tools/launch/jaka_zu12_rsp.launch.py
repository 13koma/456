#!/usr/bin/env python3
import os
import yaml
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.substitutions import Command
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory


def _vec_to_str(vec):
    return ' '.join(str(float(v)) for v in vec)


def _launch_setup(context, *args, **kwargs):
    from launch.substitutions import LaunchConfiguration

    config_file = LaunchConfiguration('config_file').perform(context)

    with open(config_file, 'r', encoding='utf-8') as f:
        cfg = yaml.safe_load(f)

    description_pkg = cfg.get('robot_description_package', 'jaka_zu12_tf_tools')
    description_file = cfg.get('robot_description_file', 'urdf/jaka_zu12_with_camera.urdf.xacro')
    xacro_path = os.path.join(get_package_share_directory(description_pkg), description_file)

    xacro_cmd = Command([
        'xacro ',
        xacro_path,
        ' base_frame:=', str(cfg.get('base_frame', 'base_link')),
        ' tool0_xyz:="', _vec_to_str(cfg.get('tool0_xyz', [0.0, 0.0, 0.0])), '"',
        ' tool0_rpy:="', _vec_to_str(cfg.get('tool0_rpy', [0.0, 0.0, 0.0])), '"',
        ' legacy_tcp_frame:=', str(cfg.get('legacy_tcp_frame', 'jaka_tcp')),

        ' camera_mount_parent:=', str(cfg.get('camera_mount_parent', 'Link_6')),
        ' camera_mount_frame:=', str(cfg.get('camera_mount_frame', 'camera_mount_link')),
        ' camera_mount_xyz:="', _vec_to_str(cfg.get('camera_mount_xyz', [0.0, 0.0, 0.0])), '"',
        ' camera_mount_rpy:="', _vec_to_str(cfg.get('camera_mount_rpy', [0.0, 0.0, 0.0])), '"',

        ' camera_parent:=', str(cfg.get('camera_parent', 'Link_6')),
        ' camera_frame:=', str(cfg.get('camera_frame', 'camera_link')),
        ' camera_xyz:="', _vec_to_str(cfg.get('camera_xyz', [0.0, 0.0, 0.0])), '"',
        ' camera_rpy:="', _vec_to_str(cfg.get('camera_rpy', [0.0, 0.0, 0.0])), '"',

        ' gripper_tip_parent:=', str(cfg.get('gripper_tip_parent', 'Link_6')),
        ' gripper_tip_frame:=', str(cfg.get('gripper_tip_frame', 'gripper_tip')),
        ' gripper_tip_xyz:="', _vec_to_str(cfg.get('gripper_tip_xyz', [0.0, 0.0, 0.0])), '"',
        ' gripper_tip_rpy:="', _vec_to_str(cfg.get('gripper_tip_rpy', [0.0, 0.0, 0.0])), '"',
    ])

    joint_state_relay = Node(
        package='jaka_zu12_tf_tools',
        executable='joint_state_relay',
        name='joint_state_relay',
        output='screen',
        parameters=[{
            'input_topic': cfg.get('joint_state_input_topic', '/jaka_driver/joint_position'),
            'output_topic': cfg.get('joint_state_output_topic', '/joint_states'),
            'frame_id': cfg.get('joint_state_frame_id', 'base_link'),
            'stamp_now': bool(cfg.get('joint_state_stamp_now', True)),
        }],
    )

    rsp = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[{
            'robot_description': xacro_cmd,
            'publish_frequency': float(cfg.get('publish_frequency', 125.0)),
        }],
    )

    return [joint_state_relay, rsp]


def generate_launch_description():
    default_cfg = os.path.join(
        get_package_share_directory('jaka_zu12_tf_tools'),
        'config',
        'jaka_zu12_tf.yaml',
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            'config_file',
            default_value=default_cfg,
            description='Path to TF/URDF config yaml',
        ),
        OpaqueFunction(function=_launch_setup),
    ])