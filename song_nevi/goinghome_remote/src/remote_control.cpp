#include "remote_base.h"




bool control_server_callback(remote_srv::Request &req ,remote_srv::Response &res){
    ROS_INFO("control_callback");
    
    //nevi service 
    ros::NodeHandle control_service;
    ros::ServiceClient control_client=control_service.serviceClient<nevi_srv>("nevi_service");
    nevi_srv rq;
    
    //camera topic
    static bool camera_sw; //camera on/off
    ros::NodeHandle camera_topic;
    ros::Publisher camera_pub =camera_topic.advertise<std_msgs::Bool>("camera_pub",1);
    

    switch(req.com_num)
    {
        case WAIT : 
        std::cout<<"wait";
        res.result=true;
        return true;
        break;

        case GUIDE : 
        std::cout<<"guide ";
        camera_sw=true;
        case MOVE :
        std::cout<<"move ";
        rq.request.px=req.px;
        rq.request.py=req.py;
        rq.request.ow=req.ow;
        break;
    
    /*추후에 사용될지 모르는 것들
    case SEARCH : 

        break;
    
    case INT : 

        break;
     */

    default:
        ROS_ERROR("odd COMMAND");
        res.result=false;
        return false;
        break;
    }
    ROS_INFO("nevi connecting....");
    while(!control_client.exists());

    if(control_client.call(rq)){
        ROS_INFO("service call to\"remote_nevi\"");
        if(rq.response.result){ //nevi 성공 --> camera node 실행
            //camera on/off topic send to sub
            camera_pub.publish(camera_sw);
            
            res.result=true;
            return true;
            }else //nevi 실패
            {
             res.result=false;
             return false;   
            }
        
        }else
        {
            ROS_ERROR("\"remote_nevi\" node not connect");
            res.result=false;
            return false;
        }
        

}

int main (int argc,char* argv[] ){
    ros::init(argc,argv,"control_node");
    ros::NodeHandle control_server;
    ros::ServiceServer control_srv_server=control_server.advertiseService("control_service",control_server_callback);
    ROS_INFO("control service server start");
    ros::spin();
    return 0;
}