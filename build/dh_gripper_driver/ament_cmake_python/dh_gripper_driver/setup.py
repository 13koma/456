from setuptools import find_packages
from setuptools import setup

setup(
    name='dh_gripper_driver',
    version='0.1.0',
    packages=find_packages(
        include=('dh_gripper_driver', 'dh_gripper_driver.*')),
)
