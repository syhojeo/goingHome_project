#include "goinghome_remote_v2.h"
#define MULTI
static bool camera_callback=false;
static int id=-1;

bool nevi_server_callback(remote_srv::Request &req ,remote_srv::Response &res){
    ROS_INFO("control_callback");
    
    camera_callback=true;
    while(camera_callback){
    }
    res.id=id;
    res.id=true;
    return true;
    }

bool camera_server_callback(remote_srv::Request &req ,remote_srv::Response &res){

    ROS_INFO("camera_callback");
    id=0;
    ROS_INFO("ID: %d",id);
    camera_callback=false;
    return true;

}
int main (int argc,char* argv[] ){
    ros::init(argc,argv,"control_node");
    
    ros::NodeHandle camerasw_con_service;
    ros::ServiceServer camerasw_con_server=camerasw_con_service.advertiseService("camerasw_con_srv",nevi_server_callback);
    //camera connect
    ros::NodeHandle camara_con_topic;
    ros::ServiceServer control_srv_server=camara_con_topic.advertiseService("control_service",camera_server_callback);
    ROS_INFO("control service server start");
#ifdef MULTI
    ros::MultiThreadedSpinner spinner(2);
    spinner.spin();
#else
{
    ros::spin();
}
#endif
    return 0;
}