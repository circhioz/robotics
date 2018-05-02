cmake_minimum_required(VERSION 2.8.3)
project(first_project)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  gazebo_ros
  std_msgs
  gazebo_plugins
)

## System dependencies are found with CMake's conventions
find_package(gazebo REQUIRED)

################################################
## Declare ROS messages, services and actions ##
################################################

## Generate messages in the 'msg' folder
add_message_files(FILES
  WheelEncoder.msg
)

## Generate added messages and services with any dependencies listed here
generate_messages(DEPENDENCIES
  std_msgs
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS gazebo_ros roscpp std_msgs gazebo_plugins
)

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${GAZEBO_INCLUDE_DIRS}
)

##  C++ library
add_library(gazebo_wheel_encoder
   src/gazebo_wheel_encoder.cpp
)

add_dependencies(gazebo_wheel_encoder
  first_project_generate_messages_cpp
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)

target_link_libraries(gazebo_wheel_encoder
  ${catkin_LIBRARIES}
  ${GAZEBO_LIBRARIES}
)
