cmake_minimum_required(VERSION 2.8.3)
project(goinghome_host_eventhandler)
find_package(catkin REQUIRED COMPONENTS message_generation roscpp std_msgs)

add_service_files(FILES nav_request.srv)
add_service_files(FILES survail_request.srv)
generate_messages(DEPENDENCIES std_msgs)
# add_message_files(FILES default.msg)


catkin_package(LIBRARIES goinghome_host_eventhandler CATKIN_DEPENDS message_generation roscpp std_msgs)

include_directories(${catkin_INCLUDE_DIRS})

# main_control에 빌드 옵션
add_executable(main_control src/eventhandler.h src/main_control.cpp src/destination.cpp src/camera_control.cpp src/util.cpp)
add_dependencies(main_control ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(main_control ${catkin_LIBRARIES})

add_executable(request_server src/eventhandler.h src/request_server.cpp)
add_dependencies(request_server ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(request_server ${catkin_LIBRARIES})

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
install(TARGETS main_control
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(TARGETS request_server
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )