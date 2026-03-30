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
    plane_min = [0.018, 0.675]
    plane_max = [0.242, 0.899]
    grasp_depth_offset = 0.03

    # Home position in METERS + radians (from FK of your joint home)
    # FK returned (mm): [-130.355, -547.971, 93.684, -1.552, -0.787, 3.128]
    jaka_home_position = [-0.13036, -0.54797, 0.09368, -1.5521, -0.7865, 3.1284]

    return LaunchDescription([

        # 1) Heightmap node — UNCHANGED
        Node(
            package="grasp_inference_pkg",
            executable="grasp_node",
            name="heightmap_node",
            output="screen",
            parameters=[{
                "pcd_topic": "/camera/camera/depth/color/points",
                "target_frame": heightmap_target_frame,
                "pcd_mask_from_topic": "/camera/camera/color/image_raw",
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
                "move_velocity_mm_s": 50.0,
                "move_acceleration_mm_s2": 50.0,
                "gripper_open_service": "/dh_gripper_node/open",
                "gripper_close_service": "/dh_gripper_node/close",
                "pregrasp_settle_distance": 0.30,
                "pregrasp_z_offset": 0.04,
                "fresh_pose_timeout": 30.0,
                "wait_after_grip": 1.5,
                "lift_height": 0.05,
                "above_home_height": 0.15,
                "settle_time": 0.3,
                "dry_run": True,
                "home_position": jaka_home_position,
            }]
        ),
    ])