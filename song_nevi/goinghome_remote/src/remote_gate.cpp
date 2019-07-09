#include "remote_base.h"

bool gate_srv_callback(goinghome_remote::goinghome_remote::Request &req ,goinghome_remote::goinghome_remote::Response &res){
    ROS_INFO("gate_callback");
    ros::NodeHandle remote_gate_client;
    ros::ServiceClient gate_client =remote_gate_client.serviceClient<goinghome_remote::goinghome_remote>("control_service");
    
    //remote_control node 가 서비스를 받을수 있는지 확인
    
    //while(gate_client.exists());
    //control node의 서비스 형태
    goinghome_remote::goinghome_remote gc_srv;
    
    //control node에 전송할 request
    gc_srv.request.com_num=req.com_num;
    gc_srv.request.px=req.px;
    gc_srv.request.py=req.py;
    gc_srv.request.ow=req.ow;
    ROS_INFO("control connecting....");
    while(!gate_client.exists());

    if(gate_client.call(gc_srv)){
        ROS_INFO("service call to\"remote_control\"");
        if(gc_srv.response.result){
            res.result=true;
            gc_srv.response.id=res.id;
            ROS_INFO("service received from\"remote_control\"");
            return true;
        }else
        {   
            res.result=false;
            return false;    
        }    
    }else //control 노드가 작동하지 않을시
    {
            ROS_ERROR("\"remote_control\" node not connect");
            res.result=false;
            return false;    
    }
}
 
int main (int argc,char* argv[] ){
ros::init(argc,argv,"remote_gate");
    ros::NodeHandle remote_gate;
    ROS_INFO("service server start");
   ros::ServiceServer gate_srv_server=remote_gate.advertiseService("gate_service",gate_srv_callback);
    
    //request 가 들어올때까지 대기
    ros::spin();
    ROS_INFO("remote_gate_node exit");
    
    
    return 0;
}


/*
rosservice call /gate_service "px: 1.0
py: 1.0
ow: 0.4
com_num: 1" 




 */