# grasp_inference_jaka.launch.py
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    pkg_share = get_package_share_directory("grasp_inference_pkg")

    model_path = os.path.join(pkg_share, "models", "model_6600.pth")
    seg_model_path = os.path.join(pkg_share, "models", "best_yolo_s.pt")

    heightmap_target_frame = "camera_link"
    inference_target_frame = "base_link"    # JAKA TF base frame (verified via view_frames)

    hm_size = 224
    hm_resolution = 0.001
    plane_min = [-0.186, -0.085]
    plane_max = [0.038, 0.139]
    grasp_depth_offset = 0.03

    # Home position
    # FK return: [-130.355, -547.971, 93.684, -1.552, -0.787, 3.128]
    jaka_home_position = [-0.13036, -0.54797, 0.09368, -1.5521, -0.7865, 3.1284]

    return LaunchDescription([

        # 1) Heightmap node — UNCHANGED
        Node(
            package="grasp_inference_pkg",
            executable="grasp_node",
            name="heightmap_node",
            output="screen",
            parameters=[{
                "stop_after_pregrasp": True,
                "pcd_topic": "/camera/camera/depth/color/points",
                "target_frame": heightmap_target_frame,
                "pcd_mask_from_topic": "/camera/camera/color/image_raw",
                "fallback_optical_to_link": False,
                "hm_size": hm_size,
                "hm_resolution": hm_resolution,
                "plane_min": plane_min,
                "plane_max": plane_max,
                "out_prefix": "heightmap",
                "seg_model_path": seg_model_path,
                "seg_imgsz": 640,
                "seg_conf": 0.25,
                "seg_iou": 0.7,
                "seg_force_cpu": False,
                "seg_mask_persist_frames": 5,
                "seg_mask_mode": "selected",
                "seg_selection_rule": "highest_conf",
                "seg_target_class": "green_peas_canned",
                "seg_selected_mask_dilate_px": 7,
                "accumulate_frames": 10,
                "min_coverage": 0.02,
            }]
        ),

        # 2) Model inference node — UNCHANGED except target_frame
        Node(
            package="grasp_inference_pkg",
            executable="model_forward",
            name="grasp_inference_node",
            output="screen",
            parameters=[{
                "color_topic": "/heightmap_node/heightmap/color",
                "height_topic": "/heightmap_node/heightmap/height",
                "mask_topic": "/heightmap_node/heightmap/mask",
                "model_path": model_path,
                "force_cpu": False,
                "hm_size": hm_size,
                "hm_resolution": hm_resolution,
                "plane_min": plane_min,
                "grasp_depth_offset": grasp_depth_offset,
                "object_depth_margin": 0.10,
                "sync_slop": 0.1,
                "q_blur_sigma": 3.0,
                "pose_ema_alpha": 0.4,
                "target_frame": inference_target_frame,
                "transform_timeout": 1.0,
                "apply_model_to_camera_transform": True,
                "apply_model_to_camera_rotation": False,
                "camera_target_offset_m": [0.0, -0.007, 0.0],
                "grasp_keep_top_fraction": 0.20,
                "grasp_depth_bias_m": -0.015,
            }]
        ),

        # 3) Gripper execution — JAKA ZU12 + DH AG-95
        Node(
            package="grasp_inference_pkg",
            executable="gripper_exec_jaka",
            name="gripper_exec_node",
            output="screen",
            parameters=[{
                "pregrasp_mode": "dynamic",
                "grasp_pose_topic": "/grasp_inference_node/grasp_pose_gripper",
                "object_center_topic": "/grasp_inference_node/object_center_base",
                "accumulator_reset_service": "/heightmap_node/reset_accumulator",
                "tcp_pose_topic": "/jaka_driver/tool_position",
                "linear_move_service": "/jaka_driver/linear_move",
                "move_velocity_mm_s": 70.0,
                "move_acceleration_mm_s2": 70.0,
                "gripper_open_service": "/dh_gripper_node/open",
                "gripper_close_service": "/dh_gripper_node/close",
                "auto_execute": False,
                "pregrasp_settle_distance": 0.30,
                "pregrasp_z_offset": 0.04,
                "fresh_pose_timeout": 30.0,
                "wait_after_grip": 1.5,
                "lift_height": 0.10,
                "above_home_height": 0.25,
                "tcp_to_tip_offset_m": [0.0, 0.0, 0.15],
                "settle_time": 0.3,
                "debug_publish_targets": True,
                "debug_frame_id": "base_link",
                "use_live_tcp_orientation": False,
                "use_linear_pregrasp": False,
                "use_joint_move_for_grasp_path": True,
                "release_at_above_home": True,
                "wait_after_release": 1.0,
                "dry_run": False,
                "home_position": jaka_home_position,
                "home_joints": [1.5698206424713135, 1.8715859651565552, 2.3616514205932617, 2.0367627143859863, 1.569820761680603, 2.3550024032592773],
                "joint_move_service": "/jaka_driver/joint_move",
                "ik_service": "/jaka_driver/get_ik",
                "joint_velocity": 1.0,
                "joint_acceleration": 1.0,
                "home_joint_velocity": 0.8,
                "home_joint_acceleration": 0.8,
            }]
        ),
    ])
