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

#define DEBUG
//탐색 
bool command_srv_callback(goinghome_command::event_command::Request &req ,goinghome_command::event_command::Response &res){  //event command node from service request

  #ifdef DEBUG
  ROS_INFO("point: %f %f",req.px,req.py);
  ROS_INFO("num: %d",req.msg_num);
  #endif

  ros::NodeHandle nevi_nh;
  ros::ServiceClient nevi_service_client=nevi_nh.serviceClient<goinghome_command::command>("nevi_service_server");
  while(!nevi_service_client.exists());

  ROS_INFO("nevi start");
  goinghome_command::command rq_srv; //송신할 service 형태
  //rq_srv.request.msg_num=req.msg_num;
  
  //result 가 잘들어 왔는지 확인
  switch (req.msg_num)
  {
    //move
    case 1: 
      ROS_INFO("request \"move\"");
      rq_srv.request.px =req.px;
      rq_srv.request.py =req.py;
      rq_srv.request.ow =req.ow;
     
      if(nevi_service_client.call(rq_srv)){
        
        #ifdef DEBUG
        ROS_INFO("point px:%f \n py:%f \n ow:%f",rq_srv.request.px,rq_srv.request.py,rq_srv.request.ow);
        //ROS_INFO("num: %d",rq_srv.request.msg_num);
        ROS_INFO("name: %s",rq_srv.request.name);
        #endif
        //반환값 확인
        if(rq_srv.response.result){
          ROS_INFO("nevi command success");
          res.result=true;
          return true;
          break;
        }else
        {
          ROS_ERROR("nevi command fail");
          res.result=false;
          return false;
          break;
        }
      }
      else{
        ROS_ERROR("nevi service call fail");
        res.result=false;
        return false;
        break;
      }
        break;
    //wait
    case 2:
      ROS_INFO("request \"wait\"");
      if(nevi_service_client.call(rq_srv)){
        if(rq_srv.response.result){
          ROS_INFO("wait command success");
          res.result=true;
          return true;
          break;
        }else{
          ROS_ERROR("wait command fail");
          res.result=false;
          return false;
          break;
        }
    }
    else{
      ROS_ERROR("nevi service call fail");
      res.result=false;
      return false;
      break;
    }

    //comeback
    case 3:
      ROS_INFO("request \"comeback\"");
      rq_srv.request.px =0;
      rq_srv.request.py =0;
      rq_srv.request.ow =req.ow;

      #ifdef DEBUG
      ROS_INFO("point px:%f py:%f ow:%f",rq_srv.request.px,rq_srv.request.py,rq_srv.request.ow);
      //ROS_INFO("num: %d",rq_srv.request.msg_num);
      ROS_INFO("name: %s",rq_srv.request.name);
      #endif
      
      if(nevi_service_client.call(rq_srv)){
        if(rq_srv.response.result){
          ROS_INFO("comeback command success");
          res.result=true;
          return true;
          break;
        }else{
          ROS_ERROR("comeback command fail");
          res.result=false;
          return false;
          break;
        }
    }else{
      ROS_ERROR("nevi service  fail");
      res.result=false;
      return false;
      break;
    }
    return true;
      break;

    default:
      ROS_ERROR("odd arg !!");
      res.result=false;
      return false;
      break;
  }
}

int main(int argc, char* argv[]){
  
    //service node server init
    ros::init(argc,argv,"goinghome_command");
    ros::NodeHandle command_nh;
    ROS_INFO("service server start");
    ros::ServiceServer command_service=command_nh.advertiseService("goinghome_command",command_srv_callback);
    
    //request 가 들어올때까지 대기
    ros::spin();

    return 0;
}


