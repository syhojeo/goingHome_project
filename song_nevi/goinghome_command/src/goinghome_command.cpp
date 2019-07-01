#include <ros/ros.h>
#include <ros/service_client.h>
#include <ros/service.h>
#include <std_msgs/UInt8.h>
#include<ros/node_handle.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

//srv 불러 오기
#include <goinghome_command/command.h>
#include <goinghome_command/gohome_nevi.h>


//command node 

//service node
/*
topic root
server    <-->    client
command node  <--> command service node
nevi_node     <--> command node

*/

ros::NodeHandle nh;
goinghome_command::command command_msg;
goinghome_command::command nevi_msg;
//ros::ServiceClient client_srv=nh.serviceClient("command_srv");


bool command_srv(command_msg::Request& req,command_msg::Response& res) //event command node from service request
{
  //result 가 잘들어 왔는지 확인
  switch (req.msg_num)
  {
//move
  case 1: 
    ROS_INFO("request \"move\"");
    
    //nevi node에게 topic을 보낼 수 있을때까지 대기
    ros::service::waitForService("nevi");
    //nevi node에게 topic 보내고 받기
    if(ros::service::call("nevi",nevi_msg::Request& req_nevi,nevi_msg::Response& res_nevi)){ //nevi to service request
      
      //nevi 에 보낼 정보 
      req_nevi.msg_point=req.msg_sector;
      req_nevi.msg_num=req.msg_num;

      //nevi node 에서 처리를 다할때 까지 대기 
      //네비를 사용할수 있으면 ture 네비가 사용중이므로 불가능하면 false
      while(!(ros::service::exists("nevi")));
      
      // nevi 측 result 확인
      if (res_nevi.result){
        ROS_INFO("nevi_node success");
        res.result=true;
        return true;
      }else{
        ROS_ERROR("nevi_node fail");
        res.result=false;
        return false;
        }  
    }else{
      ROS_ERROR("nevi(move) service conneting error");
      res.result=false;
      }
    break;

  //wait
  case 2:
  ROS_INFO("request \"wait\"");
    
    //nevi node에게 topic을 보낼 수 있을때까지 대기
    ros::service::waitForService("nevi");
    //nevi node에게 topic 보내고 받기
    if(ros::service::call("nevi",nevi_msg::Request& req_nevi,nevi_msg::Response& res_nevi)){ //nevi to service request
      
      //nevi 에 보낼 정보 
      req_nevi.msg_point=req.msg_point;
      req_nevi.msg_num=req.msg_num;

      //nevi node 에서 처리를 다할때 까지 대기 
      //네비를 사용할수 있으면 ture 네비가 사용중이므로 불가능하면 false
      while(!(ros::service::exists("nevi")));
      
      // nevi 측 result 확인
      if (res_nevi.result){
        ROS_INFO("nevi_node success");
        res.result=true;
        return true;
      }else{
        ROS_ERROR("nevi_node fail");
        res.result=false;
        return false;
        }  
    }else{
      ROS_ERROR("nevi(wait) service conneting error");
      res.result=false;
      }
    
    break;

  //comeback
  case 3:
  ROS_INFO("request \"comeback\"");
    
    //nevi node에게 topic을 보낼 수 있을때까지 대기
    ros::service::waitForService("nevi");
    //nevi node에게 topic 보내고 받기
    if(ros::service::call("nevi",nevi_msg::Request& req_nevi,nevi_msg::Response& res_nevi)){ //nevi to service request
      
      //nevi 에 보낼 정보 
      req_nevi.msg_point=req.msg_point;
      req_nevi.msg_num=req.msg_num;

      //nevi node 에서 처리를 다할때 까지 대기 
      //네비를 사용할수 있으면 ture 네비가 사용중이므로 불가능하면 false
      while(!(ros::service::exists("nevi")));
      
      // nevi 측 result 확인
      if (res_nevi.result){
        ROS_INFO("nevi_node success");
        res.result=true;
        return true;
      }else{
        ROS_ERROR("nevi_node fail");
        res.result=false;
        return false;
        }
    }else{
      ROS_ERROR("nevi(wait) service conneting error");
      res.result=false;
      }
    
    break;

  default:
  ROS_ERROR("odd arg !!");
    return false;
    break;
    }
    ROS_ERROR("switch exception error!!");
    return false;
}

int main(int argc, char* argv[]){
    //ros init  
    ros::init(argc,argv,"goinghome_command");

    //service node server init	req ,
    ros::serviceServer service=nh.advertiseService("command",command_srv);

    //request 가 들어올때까지 대기
    ros::spin();
  
    
    
    return 0;
}


