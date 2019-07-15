#include "ros/ros.h"
#include "ros_tutorials_service/SrvTutorial.h"

bool calculation(ros_tutorials_service::SrvTutorial::Request &req, ros_tutorials_service::SrvTutorial::Response &res)
{
    res.result = req.a + req.b;

    ROS_INFO("request: x=%ld, y%ld", (long int)req.a, (long int)req.b);
    ROS_INFO("sending back response: %ld", (long int)res.result);

    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "service_client");

    if (argc != 3)
    {
        ROS_INFO("cmd: rosrun ros_tutorials_service service_client arg0 arg1");
        ROS_INFO("arg0: double number, arg1: double number");
        return 1;
    }

    ros::NodeHandle nh;
    ros::ServiceClient ros_tutorials_service_client = nh.serviceClient<ros_tutorials_service::SrvTutorial>("ros_tutorial_srv");

    ros_tutorials_service::SrvTutorial srv;
    srv.request.a = atoll(argv[1]);
    srv.request.b = atoll(argv[2]);

    if (ros_tutorials_service_client.call(srv))
    {
        ROS_INFO("send srv, srv.Request.a and b: %ld, %ld", (long int)srv.request.a, (long int)srv.request.b);
        ROS_INFO("receive srv, srv.Request.result: %ld", (long int)srv.response.result);
    }
    
    else
    {
        ROS_ERROR("Failed to call service ros_tutorial_srv");
        return 1;
    }

    return 0;
}