from setuptools import setup
from glob import glob
import os

package_name = "grasp_inference_pkg"

setup(
    name=package_name,
    version="0.0.1",
    packages=[package_name],
    data_files=[
        ("share/ament_index/resource_index/packages", ["resource/" + package_name]),
        (
            "share/" + package_name + "/launch",
            [
                "launch/grasp_inference.launch.py",
                "launch/grasp_inference_jaka.launch.py",
            ],
        ),
        (os.path.join("share", package_name, "models"), glob("models/*")),
        (os.path.join("share", package_name, "launch"), glob("launch/*.launch.py")),
    ],
    install_requires=["setuptools", "numpy", "opencv-python"],
    zip_safe=True,
    maintainer="you",
    maintainer_email="you@todo.todo",
    description="GraspNet inference node",
    license="Apache-2.0",
    tests_require=["pytest"],
    entry_points={
        "console_scripts": [
            "grasp_node = grasp_inference_pkg.grasp_node:main",
            "model_forward = grasp_inference_pkg.model_forward:main",
            "gripper_exec = grasp_inference_pkg.gripper_exec:main",
            "gripper_exec_jaka = grasp_inference_pkg.gripper_exec_jaka:main",
        ],
    },
)
