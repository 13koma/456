from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    pkg_share = get_package_share_directory("grasp_inference_pkg")

    model_path = os.path.join(pkg_share, "models", "model_6600.pth")
    seg_model_path = os.path.join(pkg_share, "models", "best_yolo_s.pt")

    heightmap_target_frame = "camera_link"
    inference_target_frame = "base_link"

    hm_size = 224
    # 224 * 0.002 ~= 0.448 m => окно ~44.8 x 44.8 см
    hm_resolution = 0.002
    plane_min = [-0.224, -0.224]
    plane_max = [0.224, 0.224]
    grasp_depth_offset = 0.00

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
                "seg_model_path": seg_model_path,
                "seg_imgsz": 640,
                "seg_conf": 0.25,
                "seg_iou": 0.7,
                "seg_force_cpu": False,
                "seg_mask_persist_frames": 1,
                "accumulate_frames": 3,
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
                "target_frame": inference_target_frame,
                "transform_timeout": 1.0,
                "apply_model_to_camera_transform": False,
            }]
        ),
    ])
