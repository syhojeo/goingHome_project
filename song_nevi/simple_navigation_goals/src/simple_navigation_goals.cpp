//move_base-->goal 
#include <stdio.h>
#include <stdlib.h>
#include <ros/ros.h> //ros 기본 헤더파일
#include <move_base_msgs/MoveBaseAction.h> //movebase 에 전송할 topic msg 형태 헤더 파일
#include <geometry_msgs/PoseStamped.h>
#include <actionlib/client/simple_action_client.h>  //action_client 구성 헤더 파일

//msg 를 받기 위한 subscriber 구성을 위함
#include <ros/node_handle.h>

//amcl-->initalpose
#include <geometry_msgs/PoseWithCovarianceStamped.h> //initalpose msg 형식

//debug 확인용
#define DEBUG

//move_base action_client 
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBase_Client; //actionlib::SimpleActionClient 에서 move_base_msgs::MoveBaseAction의 메세지 형태 전송

//amcl x,y 좌표
static double amcl_x,amcl_y;

//orientation
static double amcl_w;

static double arg_x,arg_y;

//msg 받기 위한 callback 함수
void callback(const geometry_msgs::PoseWithCovarianceStamped& msg){

ROS_INFO("%f:x %f:y\n",msg.pose.pose.position.x,msg.pose.pose.position.y);
amcl_x=msg.pose.pose.position.x;
amcl_y=msg.pose.pose.position.y;
}

int main(int argc, char* argv[]){
  
  //ros 초기화 
  ros::init(argc, argv, "simple_navigation_goals"); 
 
 //노드 관리를 위한 객체 생성
  ros::NodeHandle nh;
  
  ros::Subscriber amcl_sub=nh.subscribe("amcl_pose",100,callback);
  
  ROS_INFO("subscriber start and waiting");
  
  //topic 받는걸 한번만 하도록한다. amcl_x 와 amcl_y 값이 0 일경우에는 다시 토픽을 받도록함.
  while ((amcl_x==0)&&(amcl_y==0))
  ros::spinOnce();
  
  MoveBase_Client ac ("move_base", true); //action_clinet 객체 생성 "move_base"에게 요청을 보냄 true spin_thread 허용여부 (boost를 이용한)
  
  while(!ac.waitForServer(ros::Duration(5.0))){ //액션 서버(move_base가 작동할때까지 대기)
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal_msg; // 상대 좌표 메세지 객체
  
  // move_base_msgs::MoveBaseGoal
  //메세지 객체 header
  goal_msg.target_pose.header.frame_id = "map";
  goal_msg.target_pose.header.stamp = ros::Time::now();
  arg_x=atof(argv[1]);
  arg_y=atof(argv[2]);
  //메세지 객체 pose
  goal_msg.target_pose.pose.position.x = arg_x;
  goal_msg.target_pose.pose.position.y = arg_y;
  
  
  goal_msg.target_pose.pose.orientation.x =0.0;
  goal_msg.target_pose.pose.orientation.y =0.0;
  goal_msg.target_pose.pose.orientation.w =-0.71;
  goal_msg.target_pose.pose.orientation.z =0.70;


  #ifdef DEBUG
  //arg (x,y)
  ROS_INFO("argc : %d",argc);
  ROS_INFO("argv");
  for(int i=0;i<argc;i++)
  ROS_INFO("%d : %s\n",i,argv[i]);
//amcl topic 
  ROS_INFO("amcl: %f:x %f:y\n",amcl_x,amcl_y);
  ROS_INFO("arg: %f:x %f:y\n",arg_x,arg_y);

//변위값
  ROS_INFO("send pose.x %f",goal_msg.target_pose.pose.position.x);
  ROS_INFO("send pose.y %f",goal_msg.target_pose.pose.position.y);
 
  #endif
  
   ROS_INFO("Sending goal");
  //메세지 전송
  ac.sendGoal(goal_msg);
  
  //응답 대기
  ac.waitForResult();
  
  //응답 여부 판단
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) //ac.getState() 로 상태 리턴  move_base_msgs/MoveBaseActionResult.msg
    ROS_INFO("the base moved at x=%d y=%d!!",arg_x,arg_y);
  else
    ROS_INFO("The base failed to move forward");
   
    return 0;
   //상태값
    /* 
  enum StateEnum
    {
      PENDING,
      ACTIVE,
      RECALLED,
      REJECTED,
      PREEMPTED,
      ABORTED,
      SUCCEEDED,
      LOST
    };
 */
}