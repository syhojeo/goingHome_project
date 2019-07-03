//c stdl
#include <stdio.h>

//ros
#include <ros/ros.h>
#include <ros/service_client.h>
#include <ros/service.h>
#include <ros/service_server.h>
#include <ros/node_handle.h>
#include <ros/subscriber.h>

//srv 불러 오기
#include <goinghome_command/command.h>
#include <goinghome_command/event_command.h>

//msg 불러 오기
#include <nav_msgs/MapMetaData.h>

#define DEBUG

//command node 

//service node
/*
topic root
server    <-->    client
command node  <--> command service node
nevi_node     <--> command node
*/

/*
  동적 맵 sector 변환  (미완성) 
  sector 하나의 크기를 1m*1m 로 정하여 map의 정보를 가져와(resolution,width,height) 필요한 sector의 갯수를구하고
  sector에 대한 구조체를 이용하여 필요한 갯수만큼의 배열을 할당하고 (동적 할당? 정적할당?)
  각 sector의 기본위치를 sector의 중심으로 잡는다.



int map_x,map_y;
float offset_map_x, offset_map_y;
//map server에서 맵정보를 받아와 n개의 구역으로 변환

void mapservertoSector(float resolution,int width,int height){
  int meterTocel=(int)1/resolution;
  
  int map_x= width/meterTocel; 
  if((width%meterTocel)>0)
    map_x++;
  
  int map_y=height/meterTocel;
  if((height%meterTocel)>0)
    map_y++;

    //각 섹터의 좌표를 어떻게 할것인가.
}

해당 좌표를 보내면 


void mapserver_Callback(nav_msgs::MapMetaData &msg){
mapservertoSector(msg.resolution,msg.width,msg.height);
offset_map_x=msg.origin.position.x;
offset_map_y=msg.origin.position.y;

}
*/
typedef struct Sector_xy{
  float sector_px;
  float sector_py;
  float sector_pz;
  float sector_ox;
  float sector_oy;
  float sector_oz;
  float sector_ow;
}Sector;

static Sector *link_Sector;

/* 
Sector pointtoSector(float px ,float py){
  return NULL;
}
*/
void setSector(int secNum){

}

void getSector(){

}
bool command_srv_callback(goinghome_command::event_command::Request &req ,goinghome_command::event_command::Response &res){  //event command node from service request

  #ifdef DEBUG
  ROS_INFO("point: %f %f",req.px,req.py);
  ROS_INFO("num: %d",req.msg_num);
  #endif

  ros::NodeHandle nevi_nh;
  ros::ServiceClient nevi_service_client=nevi_nh.serviceClient<goinghome_command::command>("nevi_service_server");
  while(!nevi_service_client.exists());

  ROS_INFO("nevi start");
  goinghome_command::command rq;
  rq.request.msg_num=req.msg_num;
  
  //result 가 잘들어 왔는지 확인
  switch (req.msg_num)
  {
    //move
    case 1: 
      ROS_INFO("request \"move\"");
      rq.request.px =req.px;
      rq.request.py =req.py;
      rq.request.pz =req.pz;
      rq.request.ox =req.px;
      rq.request.oy =req.oy;
      rq.request.oz =req.oz;
      rq.request.ow =req.ow;
     
      if(nevi_service_client.call(rq)){
        
        #ifdef DEBUG
        ROS_INFO("point px:%f \n py:%f \n pz:%f \n ox:%f \n oy:%f \n oz:%f \n ow:%f",rq.request.px,rq.request.py,rq.request.pz,rq.request.ox,rq.request.oy,rq.request.oz,rq.request.ow);
        ROS_INFO("num: %d",rq.request.msg_num);
        ROS_INFO("name: %s",rq.request.name);
        #endif
      }
      else{
        ROS_ERROR("nevi service fail");
      }
      return true;
      break;

    //wait
    case 2:
      ROS_INFO("request \"wait\"");
      if(nevi_service_client.call(rq)){
        
    }
    else{
      ROS_ERROR("nevi service fail");
      
    }
      return true;
      break;

    //comeback
    case 3:
    ROS_INFO("request \"comeback\"");
    rq.request.px =0;
      rq.request.py =0;
      rq.request.pz =req.pz;
      rq.request.ox =req.px;
      rq.request.oy =req.oy;
      rq.request.oz =req.oz;
      rq.request.ow =req.ow;
      #ifdef DEBUG
      ROS_INFO("point px:%f py:%f pz:%f ox:%f oy:%f oz:%f ow:%f",rq.request.px,rq.request.py,rq.request.pz,rq.request.ox,rq.request.oy,rq.request.oz,rq.request.ow);
      ROS_INFO("num: %d",rq.request.msg_num);
      ROS_INFO("name: %s",rq.request.name);
      #endif
      while(!nevi_service_client.waitForExistence());
      if(nevi_service_client.call(rq)){

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
}

int main(int argc, char* argv[]){
    
    /*
    read sector --> read file 
    
     */

    //ros init
    ros::init(argc,argv,"goinghome_command");
    ros::NodeHandle command_nh;
    
    //ros subscripter  mapserver(map_metadata) 맵정보를 받아 Sector로 나눔
    
    //ros::Subscriber map_sub=command_nh.subscribe("map_metadata",mapserver_Callback);
    // ROS_INFO("get map_metadata from map_server");
    
    //# 한번만 실행하도록 유도
    //ros::spinonce();
    
    //service node server init
    ROS_INFO("server start");
    ros::ServiceServer command_service=command_nh.advertiseService("goinghome_command",command_srv_callback);
    
    //request 가 들어올때까지 대기
    ros::spin();

    return 0;
}


