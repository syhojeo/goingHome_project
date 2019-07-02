#ifndef SIMPLE_NAVIGATION_GOALS
#define SIMPLE_NAVIGATION_GOALS
//move_base-->goal 
#include <stdio.h>
#include <stdlib.h>

#include <ros/ros.h> //ros 기본 헤더파일

#include <ros/service_server.h>
#include <ros/service.h>

#include <goinghome_command/command.h> //외부패키지 서비스 헤더 파일
#include <move_base_msgs/MoveBaseAction.h> //movebase 에 전송할 topic msg 형태 헤더 파일
#include <geometry_msgs/PoseStamped.h>
#include <actionlib/client/simple_action_client.h>  //action_client 구성 헤더 파일

//msg 를 받기 위한 subscriber 구성을 위함
#include <ros/node_handle.h>

//amcl-->initalpose
#include <geometry_msgs/PoseWithCovarianceStamped.h> //initalpose msg 형식


struct pointToSector {
    float px;
    float py;
    float pz;
    float ox;
    float oy;
    float oz;
    float ow;
};

#elif
#endif