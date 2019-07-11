#include "ros/ros.h"
#include <iostream>
#include <cstdio>
#include <string>
#include "goinghome_host_controller/infoRequest.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "file_server_Read");
    ros::NodeHandle nh("~");

    ros::ServiceClient personInfo_request = nh.serviceClient<goinghome_host_controller::infoRequest>("infoTest");
    goinghome_host_controller::infoRequest pid;

    for (int32_t i = 0; i < 8; i++)
    {
        pid.request.id = i;
        ROS_INFO("requesting personInfo: %d", pid.request.id);

        if (personInfo_request.call(pid))
        {
            ROS_INFO("personData received!");
        }

        else
        {
            ROS_ERROR("Failed to getPersonalInfo.");
        }
    }


    return 0;
}