#include"goinghome_remote_v2.h"
#include<std_msgs/UInt16.h>


bool fake_sev_callback(goinghome_remote_v2::image::Request &req,goinghome_remote_v2::image::Response &res){

res.id =rand()%10;
return true;
}


int main (int argc ,char* argv[]){ 
  //ros 초기화 
  ros::init(argc, argv, "fake_node"); 

  ros::NodeHandle fake_node;
  ros::ServiceServer fake_sev_server=fake_node.advertiseService("fake_service",fake_sev_callback);
  ROS_INFO("fake service server start");
  ros::spin();
  return 0;


}