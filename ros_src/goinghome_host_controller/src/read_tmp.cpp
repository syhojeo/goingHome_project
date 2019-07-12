#include "ros/ros.h"
#include <iostream>
#include <cstdio>
#include <string>
#include "goinghome_host_controller/infoRequest.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "file_server_Read");
    ros::NodeHandle nh;

    ros::ServiceClient person_req = nh.serviceClient<goinghome_host_controller::infoRequest>("request_personal_info");
    goinghome_host_controller::infoRequest srv;

    for (int i = 0; i < 9; i++)
    {
        srv.request.id = i;
        ROS_INFO("requesting personInfo: %d", srv.request.id);

        if (person_req.call(srv))
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