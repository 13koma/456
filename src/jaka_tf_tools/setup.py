from setuptools import find_packages, setup

package_name = 'jaka_tf_tools'

setup(
    name=package_name,
    version='0.0.1',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/launch', ['launch/jaka_tf_minimal.launch.py']),
        ('share/' + package_name + '/config', ['config/jaka_tf_tools.yaml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='User',
    maintainer_email='user@example.com',
    description='Minimal TF bridge for JAKA',
    license='MIT',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'tcp_tf_broadcaster = jaka_tf_tools.tcp_tf_broadcaster:main',
            'static_camera_tf = jaka_tf_tools.static_camera_tf:main',
            'joint_state_relay = jaka_tf_tools.joint_state_relay:main',
        ],
    },
)
