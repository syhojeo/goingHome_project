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
    ros::ServiceClient location_request = nh.serviceClient<goinghome_host_controller::infoRequest>("request_location_info");
    ros::ServiceClient person_request = nh.serviceClient<goinghome_host_controller::infoRequest>("request_personal_info");

    goinghome_host_controller::goinghome_remote rq;
    goinghome_host_controller::infoRequest info_rq;
    goinghome_host_controller::infoRequest rtb_rq;

    rq.request.px = msg->px;
    rq.request.py = msg->py;
    rq.request.ow = msg->ow;
    postRequest = msg->mode;
    rq.request.com_num = 1;
    currentMode = 1;

    if (remote_control.call(rq))
    {
        ROS_INFO("Received Result. Checking...");
        ROS_INFO("Result: %d, id: %d", rq.response.result, (int)rq.response.id);
    }

    else
    {
        ROS_ERROR("Failed to execute order.");
        // make main_controller order-able status in here
        return;
    }

    if (rq.response.result)
    {
        ROS_INFO("Execute sendIDinfo(): requesting personInfo: %d", (int)rq.response.id);
        info_rq.request.id = (int)rq.response.id;

        if (person_request.call(info_rq))
        {
            ROS_INFO("personData received!");
            ROS_INFO("received: %lf %lf %lf", info_rq.response.px, info_rq.response.py, info_rq.response.ow);
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
        ROS_INFO("Failed get personal infomation from site");
        // make main_controller order-able status in here
        return;
    }

    rq.request.px = info_rq.response.px;
    rq.request.py = info_rq.response.py;
    rq.request.ow = info_rq.response.ow;
    rq.request.com_num = 3;
    currentMode = 3;

    if (remote_control.call(rq))
    {
        ROS_INFO("Received Result. Checking...");
        ROS_INFO("Result: %d, id: %d", rq.response.result, (int)rq.response.id);
    }

    else
    {
        ROS_ERROR("Failed to execute order.");
        // make main_controller order-able status in here
        return;
    }

    if (rq.response.result)
    {
        ROS_INFO("NAVIGATION SERVICE SUCCESS!");

        // Convert request signal to make sure 
        if(postRequest == 0)    // Return to base
        {
            rq.request.com_num = 0;
        }

        else if (postRequest == 1)  // Wait there.
        {
            rq.request.com_num = 2;
        }
    }

    else
    {
        ROS_ERROR("Failed to do NAVIGATION SERVICE. THERE IS SOME REASON");
        // make main_controller order-able status in here
        return;
    }

    if(postRequest == 0)    // Return to base
    {
        ROS_INFO("Execute sendIDinfo(): requesting location_info: %d", 0);
        rtb_rq.request.id = 0;

        if (location_request.call(rtb_rq))
        {
            ROS_INFO("personData received!");
            ROS_INFO("received: %lf %lf %lf", rtb_rq.response.px, rtb_rq.response.py, rtb_rq.response.ow);
        }

        else
        {
            ROS_ERROR("Failed to getLocation request.");
            return;
        }

        rq.request.px = rtb_rq.response.px;
        rq.request.py = rtb_rq.response.py;
        rq.request.ow = rtb_rq.response.ow;
        rq.request.com_num = 0;

        if (remote_control.call(rq))
        {
            ROS_INFO("Received Result. Checking...");
            ROS_INFO("Result: %d, id: %d", rq.response.result, (int)rq.response.id);
        }

        else
        {
            ROS_ERROR("Failed to execute order.");
            // make main_controller order-able status in here
            return;
        }
    }

    else
    {
        rq.request.px = -1;
        rq.request.py = -1;
        rq.request.ow = 0;
        rq.request.com_num = 2;

        if (remote_control.call(rq))
        {
            ROS_INFO("Received Result. Checking...");
            ROS_INFO("Result: %d, id: %d", rq.response.result, (int)rq.response.id);
        }

        else
        {
            ROS_ERROR("Failed to execute order.");
            // make main_controller order-able status in here
            return;
        }
    }

    ROS_INFO("SERVICE COMPLETE. EXIT PROCESS");
    currentMode = -1;

    // make main_controller order-able status in here
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