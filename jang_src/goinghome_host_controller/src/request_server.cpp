#include "ros/ros.h"
#include <iostream>
#include <cstdio>
#include <string>
#include "goinghome_host_controller/navigation_order.h"
#include "goinghome_host_controller/goinghome_remote.h"
#include "goinghome_host_controller/infoRequest.h"

int postRequest = -1;   // 1: Wait, 0: Comeback
int currentMode = -1;

/*
    - 0: Comeback
    - 1: Move
    - 2: Wait
    - 3: Guide
    - 4: Camera (Challenge)
    - 5: Search (Challenge)
    - 999: INT
*/

typedef struct fb
{
    float px;
    float py;
    float ow;
} FB;

void received_navigation_order(const goinghome_host_controller::navigation_order::ConstPtr &msg)
{
    ROS_INFO("Received %lf %lf %lf %d", msg->px, msg->py, msg->ow, msg->mode);
    // 여기에 데이터 무결성 검사를 해서 제대로 된 값이 안 나왔을 경우 main_controller에 명령을 날려 제대로 보내라고 일갈해주자.
    ros::NodeHandle nh;
    ros::ServiceClient remote_control = nh.serviceClient<goinghome_host_controller::goinghome_remote>("gate_service");
    ros::ServiceClient personInfo_request = nh.serviceClient<goinghome_host_controller::infoRequest>("request_personal_info");

    goinghome_host_controller::goinghome_remote rq;
    goinghome_host_controller::infoRequest pid;

    rq.request.px = msg->px;
    rq.request.py = msg->py;
    rq.request.ow = msg->ow;
    rq.request.com_num = 1;
    currentMode = 1;

    if (remote_control.call(rq))
    {
        ROS_INFO("Received Result. Checking...");
        ROS_INFO("Result: %d, id: %d", rq.response.result, rq.response.id);
    }

    else
    {
        ROS_ERROR("Failed to execute order.");
        // make main_controller order-able status in here
        return;
    }

    if (rq.response.result)
    {
        ROS_INFO("Execute sendIDinfo()");
        pid.request.id = rq.response.id;
        ROS_INFO("requesting personInfo: %d", pid.request.id);

        if (personInfo_request.call(pid))
        {
            ROS_INFO("personData received!");
        }

        else
        {
            ROS_ERROR("Failed to getPersonalInfo.");
            // make main_controller order-able status in here
            return;
        }

    }

    else
    {
        ROS_INFO("Failed get personal infomation");
        // make main_controller order-able status in here
        return;
    }

    // Work in progress...
    return;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "request_server");
    ros::NodeHandle nh;

    ros::Subscriber navigation_order_sub = nh.subscribe("navigation_order", 10, received_navigation_order);
    ROS_INFO("Request server ready\n");
    ros::spin();

    return 0;
}