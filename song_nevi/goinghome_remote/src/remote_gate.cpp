#include "remote_base.h"

bool remote_gate_srv_callback(goinghome_remote::goinghome_remote::Request &req ,goinghome_remote::goinghome_remote::Response &res){
    ros::NodeHandle remote_gate_client;

    ros::ServiceClient gate_client =remote_gate_client.serviceClient<goinghome_remote::goinghome_remote>("remote_gate_clinet");

    while(1);

return true;
}
 
int main (int argc,char* argv[] ){
ros::init(argc,argv,"goinghome_command");
    ros::NodeHandle remote_gate_server;
    ROS_INFO("service server start");
   ros::ServiceServer gate_server=remote_gate_server.advertiseService("remote_gate",remote_gate_srv_callback);
    
    //request 가 들어올때까지 대기
    ros::spin();

    return 0;
}


