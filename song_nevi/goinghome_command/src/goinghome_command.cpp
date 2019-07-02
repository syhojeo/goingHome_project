#include <ros/ros.h>
#include <ros/service_client.h>
#include <ros/service.h>
#include <ros/service_server.h>
#include<ros/node_handle.h>

//srv 불러 오기
#include <goinghome_command/command.h>


#define DEBUG

//command node 

//service node
/*
topic root
server    <-->    client
command node  <--> command service node
nevi_node     <--> command node
*/


int pointtoSector(float px ,float py ,float pz,float ox,float oy,float oz,float ow){
//map server에서 맵정보를 받아와 9개의 구역으로 변환

  return ;
}

bool command_srv(goinghome_command::command::Request &req ,goinghome_command::command::Response &res)  //event command node from service request
{
  #ifdef DEBUG
  ROS_INFO("sector: %d",req.msg_sector);
  ROS_INFO("num: %d",req.msg_num);

  #endif
  ros::NodeHandle nevi_nh;
  ros::ServiceClient nevi_service_client=nevi_nh.serviceClient<goinghome_command::command>("req_nevi_service");

  goinghome_command::command rq;

  rq.request.msg_sector=req.msg_sector;
  rq.request.msg_num=req.msg_num;
  
  //result 가 잘들어 왔는지 확인
  switch (req.msg_num)
  {
    
//move
  case 1: 
    ROS_INFO("request \"move\"");
    if(nevi_service_client.call(rq)){
      
      ROS_INFO("sector: %d",rq.request.msg_sector);
      ROS_INFO("num: %d",rq.request.msg_num);

  }else{
    ROS_ERROR("nevi service fail");
    
  }
    return true;
    break;

  //wait
  case 2:
  ROS_INFO("request \"wait\"");
    if(nevi_service_client.call(rq)){
      
      ROS_INFO("sector: %d",rq.request.msg_sector);
      ROS_INFO("num: %d",rq.request.msg_num);

  }else{
    ROS_ERROR("nevi service fail");
    
  }
    return true;
    break;

  //comeback
  case 3:
  ROS_INFO("request \"comeback\"");
    if(nevi_service_client.call(rq)){
      
      ROS_INFO("sector: %d",rq.request.msg_sector);
      ROS_INFO("num: %d",rq.request.msg_num);

  }else{
    ROS_ERROR("nevi service  fail");
    
  }
  return true;
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
    ros::NodeHandle command_nh;
    //service node server init
    ROS_INFO("server start");
    ros::ServiceServer command_service=command_nh.advertiseService("goinghome_command",command_srv);
    
    //request 가 들어올때까지 대기
    ros::spin();

    return 0;
}


