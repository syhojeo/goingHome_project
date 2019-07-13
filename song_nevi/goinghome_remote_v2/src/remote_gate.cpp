#include "goinghome_remote_v2.h"

bool navi(float x,float y,float w,ros::ServiceClient& srv_client){
    remote_srv msg;
    for(int count=0;!srv_client.exists();count++){
        ROS_INFO("nevi_node connecting....");
        sleep(1);
            if(count==5){
                ROS_ERROR("nevi_node connect FAIL");
                return false;
            }
    }
    if(srv_client.call(msg)){
            ROS_INFO("service call to\"remote_control\"");
            if(msg.response.result){
                ROS_INFO("service received from\"remote_control\"");
            }else{ 
                return false;
            }
        }else{ //control 노드가 작동하지 않을때
                ROS_ERROR("contorol node is fail");
                return false;
        }
    return msg.response.result;
}


bool camera(int sw,ros::ServiceClient& srv_client){

    remote_srv msg;
    for(int count=0;!srv_client.exists();count++){
        ROS_INFO("nevi_node connecting....");
        sleep(1);
            if(count==5){
                ROS_ERROR("nevi_node connect FAIL");
                return false;       
            }
    }
    
    if(srv_client.call(msg)){
            ROS_INFO("service call to\"remote_control\"");
            if(msg.response.result){
                ROS_INFO("service received from\"remote_control\"");
            }else{ 
                return false;    
            }    
        }else{ //control 노드가 작동하지 않을때
                ROS_ERROR("contorol node is fail");
                return false;    
        }

    return msg.response.result;

}
bool camera_sw(bool sw){
    ros::NodeHandle camera_sw_node;
    std_msgs::Bool sw_msg;
    ros::Publisher camera_sw_pub=camera_sw_node.advertise<std_msgs::Bool>("sw_pub",1);
    camera_sw_pub.publish(sw_msg);
     if(sw_msg.data)
            ROS_INFO("camera on");
        else
            ROS_INFO("camera off");
    return sw;
}

bool gate_srv_callback(remote_srv::Request &req ,remote_srv::Response &res){
    ROS_INFO("gate_callback");

    ros::NodeHandle camera_con_service;
    ros::ServiceClient camera_con_client =camera_con_service.serviceClient<remote_srv>("nevi_service");
    
    ros::NodeHandle nevi_con_service;
    ros::ServiceClient nevi_con_client =nevi_con_service.serviceClient<nevi_srv>("nevi_srv");
    
    int order=req.com_num;
    bool order_bool=true,nevi_bool , camerasw_bool=false,camera_bool;
    //remote_control node 가 서비스를 받을수 있는지 확인
    
    //while(control_client.exists());
    //control node의 서비스 형태
    //control node에 전송할 request
    
    switch (order)
    {
    case COMEBACK:
        nevi_bool=navi(req.px,req.py,req.ow,nevi_con_client);
        break;
    case MOVE:
        nevi_bool=navi(req.px,req.py,req.ow,nevi_con_client);
        break;
    case WAIT:
        return true;
        break;
    case GUIDE:
        if(!camerasw_bool)
            camerasw_bool= camera_sw(!camerasw_bool);
        nevi_bool=navi(req.px,req.py,req.ow,nevi_con_client);
        camera_bool= camera(GUIDE,camera_con_client);
        camerasw_bool= camera_sw(!camerasw_bool);
        break;
    case CAMERA:
        camerasw_bool=camera_sw(!camerasw_bool);
        break;
    case SEARCH:
        if(!camerasw_bool)
            camerasw_bool=camera_sw(!camerasw_bool);
        camerasw_bool= camera_sw(!camerasw_bool);
        break;
    
    default:
        break;
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
shell test
rosservice call /gate_service "px: 1.0
py: 1.0
ow: 0.4
com_num: 1" 




 */