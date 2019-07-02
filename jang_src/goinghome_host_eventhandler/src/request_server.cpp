#include "eventhandler.h"

bool receive_request(goinghome_host_eventhandler::request::Request &req, goinghome_host_eventhandler::request::Response &res)
{
    ROS_INFO("receive_request: WORK IN PROGRESS\n");
    ROS_INFO("request: (%f, %f, %f), (%f, %f, %f, %f)\n", (float)req.px, (float)req.py, (float)req.pz, 
        (float)req.ox, (float)req.oy, (float)req.oz, (float)req.ow);
    return false;
}


// This node is actually sends coordinates to turtlebot.
int main(int argc, char **argv)
{
    ros::init(argc, argv, "navigation_service_srv");
    ros::NodeHandle nh;

    ros::ServiceServer navigation_service_server = nh.advertiseService("navigation_service_srv", receive_request);

    ROS_INFO("ready srv server!\n");

    ros::spin();

    return 0;
}
