#include "eventhandler.h"

bool navigation_request(goinghome_host_eventhandler::nav_request::Request &req, goinghome_host_eventhandler::nav_request::Response &res)
{
    ROS_INFO("received request: navigation\n");
    ROS_INFO("TODO: MOVE ROBOT TO (%f, %f, %f), (%f, %f, %f, %f)\n", (float)req.px, (float)req.py, (float)req.pz, 
        (float)req.ox, (float)req.oy, (float)req.oz, (float)req.ow);
    return true;
}

bool surveilance_request(goinghome_host_eventhandler::survail_request::Request &req, goinghome_host_eventhandler::survail_request::Response &res)
{
    ROS_INFO("received request: surveilance mode\n");
    ROS_INFO("TODO: Survailance mode\n");

    if ((bool)req.onoff == 1)
    {
        ROS_INFO("TURN ON THE CAMARA WITH SURVAILANCE MODE\n");
    }

    else
    {
        ROS_INFO("TURN OFF THE CAMARA\n");
    }

    return true;
}


// This node is actually sends coordinates to turtlebot.
int main(int argc, char **argv)
{
    ros::init(argc, argv, "request_service_server");
    ros::NodeHandle nh;

    ros::ServiceServer navigation_service_server = nh.advertiseService("navigation_request", navigation_request);
    ros::ServiceServer surveilance_service_server = nh.advertiseService("surveilance_request", surveilance_request);

    ROS_INFO("request server ready!\n");

    ros::spin();

    return 0;
}
