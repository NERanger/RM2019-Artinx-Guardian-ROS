#! /bin/bash
source /opt/ros/kinetic/setup.bash
export ROBORTS_PATH="/home/artinxbot/RM2019_ws/src/RoboRTS-ros"
source ~/RM2019_ws/devel/setup.bash
export ROS_PACKAGE_PATH=~/RM2019_ws/src:$ROS_PACKAGE_PATH
#gnome-terminal -x bash -c "ls; exec bash"
gnome-terminal -x bash -c "roscore; exec bash"
sleep 1s
cd /home/artinxbot/auto_start
gnome-terminal -x bash -c "echo artinx| sudo -S ./usb.sh; exec bash"
#cd /home/artinxbot/RoboRTS
#gnome-terminal -x ./build/modules/driver/serial/serial_com_node
#gnome-terminal -x rosrun communicate car_target_test.py
gnome-terminal -x bash -c "echo 1 | roslaunch roborts_bringup gimbal_vision.launch; exec bash"
gnome-terminal -x bash -c "rosrun serial_send serial_send_node; exec bash"
