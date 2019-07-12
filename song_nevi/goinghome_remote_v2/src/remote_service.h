#ifndef REMOTE_SERVICE_H
#define REMOTE_SERVICE_H

#include <ros/service_server.h>
#include <ros/service.h>
#include <ros/service_client.h>

//msg

#include <std_msgs/Bool.h>
#include <goinghome_remote_v2/image.h>
#include <goinghome_remote_v2/goinghome_remote.h>
#include <goinghome_remote_v2/remote_point.h>
#include <goinghome_remote_v2/image.h>
#include <move_base_msgs/MoveBaseAction.h> //movebase 에 전송할 topic msg 형태 헤더 파일
//#include <geometry_msgs/PoseStamped.h>
#include <actionlib/client/simple_action_client.h>  //action_client 구성 헤더 파일

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBase_Client; //actionlib::SimpleActionClient 에서 move_base_msgs::MoveBaseAction의 메세지 형태 전송
typedef goinghome_remote_v2::goinghome_remote  remote_srv;
typedef goinghome_remote_v2::remote_point nevi_srv;
typedef goinghome_remote_v2::image image_srv;

//srvice error code
#define NOTCON          -1
#define NEVIFAIL        -2
#define SEARCHFAIL      -3



//msg_num 형태
#define COMEBACK        0
#define MOVE            1   //사용대상자 위치로 이동
#define WAIT            2   //대기
#define GUIDE           3   //사용대상자를 사용대상자의 집으로 안내
//추후에 사용할지도 모를 명령
#define CAMERA          4   //
#define SEARCH          5   //사용대상자를 찾으러 다님

#define INT             999 //인터럽트 (모든 작업 정지등....) 


#endif

