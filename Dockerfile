FROM osrf/ros:humble-desktop-full

ENV DEBIAN_FRONTEND=noninteractive \
    ROS_DISTRO=humble \
    ROS_WS=/workspaces/grasp_jaka_ws \
    LANG=C.UTF-8 \
    LC_ALL=C.UTF-8 \
    PYTHONUNBUFFERED=1 \
    PIP_NO_CACHE_DIR=1

ARG USERNAME=dev
ARG USER_UID=1000
ARG USER_GID=1000

SHELL ["/bin/bash", "-lc"]

RUN apt-get update && apt-get install -y --no-install-recommends \
    sudo \
    bash-completion \
    build-essential \
    cmake \
    gdb \
    git \
    curl \
    wget \
    unzip \
    less \
    vim \
    nano \
    tree \
    htop \
    tmux \
    iputils-ping \
    net-tools \
    usbutils \
    python3-serial \
    xauth \
    mesa-utils \
    udev \
    socat \
    x11-apps \
    python3-pip \
    python3-dev \
    python3-venv \
    python3-colcon-common-extensions \
    python3-vcstool \
    python3-rosdep \
    python3-argcomplete \
    python3-ament-package \
    libgl1-mesa-glx \
    libglib2.0-0 \
    libsm6 \
    libxext6 \
    libxrender1 \
    libgomp1 \
    && rm -rf /var/lib/apt/lists/*

RUN apt-get update && apt-get install -y --no-install-recommends \
    ros-${ROS_DISTRO}-cv-bridge \
    ros-${ROS_DISTRO}-image-transport \
    ros-${ROS_DISTRO}-image-transport-plugins \
    ros-${ROS_DISTRO}-compressed-image-transport \
    ros-${ROS_DISTRO}-vision-opencv \
    ros-${ROS_DISTRO}-message-filters \
    ros-${ROS_DISTRO}-tf2-ros \
    ros-${ROS_DISTRO}-tf2-tools \
    ros-${ROS_DISTRO}-tf2-geometry-msgs \
    ros-${ROS_DISTRO}-rviz2 \
    ros-${ROS_DISTRO}-xacro \
    ros-${ROS_DISTRO}-robot-state-publisher \
    ros-${ROS_DISTRO}-joint-state-publisher \
    ros-${ROS_DISTRO}-joint-state-publisher-gui \
    ros-${ROS_DISTRO}-moveit \
    ros-${ROS_DISTRO}-moveit-ros-planning-interface \
    ros-${ROS_DISTRO}-ros2-control \
    ros-${ROS_DISTRO}-ros2-controllers \
    ros-${ROS_DISTRO}-controller-manager \
    ros-${ROS_DISTRO}-realsense2-camera \
    ros-${ROS_DISTRO}-realsense2-description \
    && rm -rf /var/lib/apt/lists/*

RUN python3 -m pip install --upgrade pip wheel && \
    python3 -m pip install "setuptools<80"

COPY requirements.txt /tmp/requirements.txt

# CPU-only PyTorch for laptop/dev without NVIDIA
RUN python3 -m pip install \
    --index-url https://download.pytorch.org/whl/cpu \
    torch==2.1.0 torchvision==0.16.0

RUN python3 -m pip install -r /tmp/requirements.txt
RUN rosdep init 2>/dev/null || true && rosdep update

RUN groupadd --gid ${USER_GID} ${USERNAME} \
    && useradd --uid ${USER_UID} --gid ${USER_GID} -m ${USERNAME} -s /bin/bash \
    && usermod -aG sudo,dialout,video,plugdev ${USERNAME} \
    && echo "${USERNAME} ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/${USERNAME} \
    && chmod 0440 /etc/sudoers.d/${USERNAME}

RUN mkdir -p ${ROS_WS}/src /opt/devtools
COPY scripts/container_entrypoint.sh /opt/devtools/container_entrypoint.sh
RUN chmod +x /opt/devtools/container_entrypoint.sh \
    && chown -R ${USERNAME}:${USERNAME} ${ROS_WS}

USER ${USERNAME}
WORKDIR ${ROS_WS}

RUN echo "source /opt/ros/${ROS_DISTRO}/setup.bash" >> /home/${USERNAME}/.bashrc \
    && echo "if [ -f ${ROS_WS}/install/setup.bash ]; then source ${ROS_WS}/install/setup.bash; fi" >> /home/${USERNAME}/.bashrc \
    && echo "export ROS_WS=${ROS_WS}" >> /home/${USERNAME}/.bashrc \
    && echo "export PATH=\$HOME/.local/bin:\$PATH" >> /home/${USERNAME}/.bashrc \
    && echo "alias cw='cd ${ROS_WS}'" >> /home/${USERNAME}/.bashrc \
    && echo "alias cb='cd ${ROS_WS} && colcon build --symlink-install'" >> /home/${USERNAME}/.bashrc \
    && echo "alias cbs='cd ${ROS_WS} && colcon build --symlink-install --packages-select'" >> /home/${USERNAME}/.bashrc \
    && echo "alias sb='source ${ROS_WS}/install/setup.bash'" >> /home/${USERNAME}/.bashrc \
    && echo "alias ll='ls -lah'" >> /home/${USERNAME}/.bashrc

ENTRYPOINT ["/opt/devtools/container_entrypoint.sh"]
CMD ["bash"]
