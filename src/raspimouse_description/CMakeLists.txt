cmake_minimum_required(VERSION 2.8.3)
project(raspimouse_description)

find_package(catkin REQUIRED COMPONENTS
  urdf controller_manager joint_state_controller robot_state_publisher control_msgs
)

catkin_package(
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)
