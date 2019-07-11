#include "ros/ros.h"
#include "ros/publisher.h"
#include <iostream>
#include <cstdio>
#include <string>
#include "goinghome_host_controller/navigation_order.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "main_controller");
    ros::NodeHandle nh;
    ros::Publisher navigation_order_pub = nh.advertise<goinghome_host_controller::navigation_order>("navigation_order", 10);
    ros::Rate loop_rate(1);

    int cnt = 1;
    goinghome_host_controller::navigation_order dummy;
    navigation_order_pub.publish(dummy);
    ros::spinOnce();
    loop_rate.sleep();

    ROS_INFO("cnt: %d", cnt);
    goinghome_host_controller::navigation_order msg;
    msg.px = cnt++;
    msg.py = 0;
    msg.ow = 0;
    msg.mode = 1;
    navigation_order_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();

    return 0;
}