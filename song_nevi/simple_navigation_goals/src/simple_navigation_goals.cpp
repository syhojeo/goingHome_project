//move_base-->goal 
#include <ros/ros.h> //ros 기본 헤더파일
#include <move_base_msgs/MoveBaseAction.h> //movebase 에 전송할 topic msg 형태 헤더 파일
#include <actionlib/client/simple_action_client.h>  //action_client 구성 헤더 파일

//amcl-->initalpose
#include <geometry_msgs/PoseWithCovarianceStamped.h> //initalpose msg 형식

//move_base action_client 
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBase_Client; //actionlib::SimpleActionClient 에서 move_base_msgs::MoveBaseAction의 메세지 형태 전송
//amcl action_client
typedef actionlib::SimpleActionClient<geometry_msgs::PoseWithCovarianceStamped> amcl_Client; //actionlib::SimpleActionClient 에서 move_base_msgs::MoveBaseAction의 메세지 형태 전송

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals"); //ros 환경 구축

  MoveBase_Client mc("move_base", true); //action_clinet 객체 생성 "move_base"에게 요청을 보냄 true spin_thread 허용여부 (boost를 이용한)
  amcl_Client ac("amcl",true);
  while(!ac.waitForServer(ros::Duration(5.0))){ //액션 서버(move_base가 작동할때까지 대기)
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal_msg; // 상대 좌표 메세지 객체
  geometry_msgs::PoseWithCovarianceStamped initstate_msg; // 위치 설정 메세지 객체
  //메세지 객체 header
  goal_msg.target_pose.header.frame_id = "base_link";
  goal_msg.target_pose.header.stamp = ros::Time::now();
  
  //메세지 객체 pose
  goal_msg.target_pose.pose.position.x = 1.0;
  goal_msg.target_pose.pose.orientation.w = 1.0;
  
  ROS_INFO("Sending goal");
  //메세지 전송
  ac.sendGoal(goal_msg);
  
  //응답 대기
  ac.waitForResult();
  
  //응답 여부 판단
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) //ac.getState() 로 상태 리턴  move_base_msgs/MoveBaseActionResult.msg
    ROS_INFO("Hooray, the base moved 1 meter forward");
  else
    ROS_INFO("The base failed to move forward 1 meter for some reason");
   
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