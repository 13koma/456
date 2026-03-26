from setuptools import find_packages
from setuptools import setup

setup(
    name='jaka_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('jaka_msgs', 'jaka_msgs.*')),
)
