cmake_minimum_required(VERSION 2.8.3)
project(serial_send)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  serial
  )

catkin_package()

include_directories(

    include ${catkin_INCLUDE_DIRS}
    include /home/artinxbot/RM2019_ws/devel/include
    include /opt/ros/kinetic/include/serial

)

add_executable(serial_send_node serial_send_node.cpp)
target_link_libraries(serial_send_node ${catkin_LIBRARIES})

