#!/bin/zsh
set -e

# setup ros environment
source "/opt/ros/$ROS_DISTRO/setup.zsh"
exec "$@"
