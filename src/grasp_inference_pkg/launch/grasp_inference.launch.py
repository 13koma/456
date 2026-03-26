# grasp_base.launch.py
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    pkg_share = get_package_share_directory("grasp_inference_pkg")

    # 1) ЧЕКПОИНТ: имя файла я не могу знать заранее, поэтому тут дефолт.
    # Поменяйте "checkpoint_base.pt" на ваше реальное имя.
    model_path = os.path.join(pkg_share, "models", "model_6600.pth")

    seg_model_path = os.path.join(pkg_share, "models", "best_yolo_s.pt")

    # heightmap строится в camera_link; model_forward переводит позу в base_link через TF
    heightmap_target_frame = "camera_link"
    inference_target_frame = "base_link"

    # --- значения из вашего Isaac-конфига ---
    hm_size = 224
    # 224 * 0.002 ~= 0.448 m => окно ~44.8 x 44.8 см
    # Должно быть согласовано с plane_min/plane_max
    hm_resolution = 0.002
    plane_min = [-0.224, -0.224]
    plane_max = [0.224, 0.224]
    grasp_depth_offset = 0.00  # GRASP_DEPTH (base mode)

    return LaunchDescription([
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

                # YOLO
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

                # "q_blur_sigma": 3.0,
                # "pose_ema_alpha": 0.4,

                "target_frame": inference_target_frame,
                "transform_timeout": 1.0,
                "apply_model_to_camera_transform": False,
            }]
        ),

        #Node(
        #    package="grasp_inference_pkg",
        #    executable="gripper_exec",
        #    name="gripper_exec_node",
        #    output="screen",
        #    parameters=[{
        #        "pregrasp_mode": "dynamic",
        #        "grasp_pose_topic": "/grasp_inference_node/grasp_pose_gripper",
        #        "object_center_topic": "/grasp_inference_node/object_center_base",
        #        "accumulator_reset_service": "/heightmap_node/reset_accumulator",

        #        "tcp_pose_topic": "/ur5_/tcp_pose_broadcaster/pose",
        #        "urscript_topic": "/ur5_/urscript_interface/script_command",
        #        "gripper_target_topic": "/gripper/target_position",
        #        "gripper_current_topic": "/gripper/current_position",

        #        "pregrasp_settle_distance": 0.30,
        #        "pregrasp_z_offset": 0.04,
        #        "fresh_pose_timeout": 30.0,

        #        "move_acceleration": 0.05,
        #        "move_velocity": 0.05,
        #        "gripper_close_position": 100.0,
        #        "gripper_open_position": 0.0,
        #        "wait_after_grip": 1.5,
        #        "lift_height": 0.05,
        #        "above_home_height": 0.15,
        #        "home_position": [0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
        #    }]
        #),
    ])
