#ifndef ROS_BASE_H
#define ROS_BASE_H
//C,C++ lib
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//ROS
#include<ros/ros.h>
#include<ros/node_handle.h>
#include<ros/callback_queue.h>

#include <ros/service_server.h>
#include <ros/service.h>
#include <ros/service_client.h>

//python
#include <python2.7/Python.h>

//msg
#include <std_msgs/Bool.h>
#include <goinghome_remote/goinghome_remote.h>
#include <goinghome_remote/remote_point.h>
#include <goinghome_remote/image.h>
#include <move_base_msgs/MoveBaseAction.h> //movebase 에 전송할 topic msg 형태 헤더 파일
//#include <geometry_msgs/PoseStamped.h>
#include <actionlib/client/simple_action_client.h>  //action_client 구성 헤더 파일

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBase_Client; //actionlib::SimpleActionClient 에서 move_base_msgs::MoveBaseAction의 메세지 형태 전송
typedef goinghome_remote::goinghome_remote remote_srv;
typedef goinghome_remote::remote_point nevi_srv;
typedef goinghome_remote::image image_srv;


//msg_num 형태
#define MOVE            1   //사용대상자 위치로 이동
#define WAIT            2   //대기
#define GUIDE           3   //사용대상자를 사용대상자의 집으로 안내

//추후에 사용할지도 모를 명령
#define SEARCH          4   //사용대상자를 찾으러 다님
#define INT             999 //인터럽트 (모든 작업 정지등....) 

#elif
#endif

