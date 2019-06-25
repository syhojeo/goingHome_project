cmake_minimum_required(VERSION 2.8.3)
project(ros_tutorials_action)
find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  message_generation
  roscpp
  std_msgs
)

find_package(Boost REQUIRED COMPONENTS system)

# Generate actions in the 'action' folder
add_action_files(FILES Fibonacci.action)

# Generate added messages and services with any dependencies listed here
generate_messages(DEPENDENCIES actionlib_msgs std_msgs)

catkin_package(LIBRARIES ros_tutorials_action CATKIN_DEPENDS actionlib actionlib_msgs roscpp std_msgs)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

add_executable(action_server src/action_server.cpp)
add_dependencies(action_server ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(action_server ${catkin_LIBRARIES})

add_executable(action_client src/action_client.cpp)
add_dependencies(action_client ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(action_client ${catkin_LIBRARIES})
