FROM ubuntu:20.04


# copy files
COPY ./sources.list /etc/apt/sources.list
COPY ./ros_entrypoint.sh /
COPY ./.vimrc /root/.vimrc


# setup environment
ENV LANG C.UTF-8
ENV LC_ALL C.UTF-8
ENV EDITOR vim
ENV ROS_DISTRO noetic
ENV TZ=Asia/Shanghai


# install recommended packages
RUN apt-get update \
    # setup man pages
    && yes | unminimize \
    && apt-get install -q -y --no-install-recommends man-db less \
    # setup timezone
    && echo 'Etc/UTC' > /etc/timezone \
    && apt-get install -q -y --no-install-recommends tzdata \
    && ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone \
    # install packages
    && apt-get install -q -y --no-install-recommends \
    dirmngr gnupg2 \
    git tig build-essential clang gdb cmake ninja-build \
    zsh sudo tree htop autojump iotop wget apt-file \
    vim-nox \
    && rm -rf /var/lib/apt/lists/*


# install ros packages
RUN apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654 \
    && echo "deb https://mirrors.tuna.tsinghua.edu.cn/ros/ubuntu focal main" > /etc/apt/sources.list.d/ros1-latest.list \
    && apt-get update && apt-get install -y --no-install-recommends \
    ros-noetic-ros-core=1.5.0-1* \
    && rm -rf /var/lib/apt/lists/*


# configure
RUN : \
    # configure git
    && git config --global core.editor vim \
    && git config --global credential.helper store \
    # configure zsh
    && wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | zsh || true \
    && git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions \
    && sed -i 's/ZSH_THEME="robbyrussell"/ZSH_THEME="ys"/g' ~/.zshrc \
    && sed -i 's/plugins=(git)/plugins=(git autojump command-not-found zsh-autosuggestions)/g' ~/.zshrc \
    && echo 'ZSH_AUTOSUGGEST_HIGHLIGHT_STYLE="fg=#666666"' >> ~/.zshrc


# setup entrypoint
ENTRYPOINT ["/ros_entrypoint.sh"]
CMD ["zsh"]
