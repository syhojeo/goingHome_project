#include "ros/ros.h"
#include "ros/publisher.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include "goinghome_host_controller/navigation_order.h"
#include "goinghome_host_controller/infoRequest.h"

bool nav_progress = false;

typedef struct loc
{
    float px, py, ow;
    int req;
} Loc;

Loc destination_menu(ros::NodeHandle &nh);
Loc set_destination(ros::NodeHandle &nh, std::string &dest, std::string &mode);

int main(int argc, char **argv)
{
    ros::init(argc, argv, "main_controller");
    ros::NodeHandle nh;
    ros::Publisher navigation_order_pub = nh.advertise<goinghome_host_controller::navigation_order>("navigation_order", 10);
    ros::Rate loop_rate(1);

    goinghome_host_controller::navigation_order dummy;
    goinghome_host_controller::navigation_order msg;
    navigation_order_pub.publish(dummy);
    ros::spinOnce();
    loop_rate.sleep();

    ROS_INFO("main_controller initialized\n");

    do
    {
        printf("command: ");
        char menu;
        bool isExit = false;
        std::cin >> menu;

        if (menu >= '1' && menu <= '3')
        {
            switch(menu)
            {
                case '1':
                    printf("Set destination and command service\n");
                    Loc getLocation;
                    getLocation = destination_menu(nh);
                    if (getLocation.req == -1)
                    {
                        break;
                    }

                    msg.px = getLocation.px;
                    msg.py = getLocation.py;
                    msg.ow = getLocation.ow;
                    msg.mode = getLocation.req;
                    navigation_order_pub.publish(msg);
                    ros::spinOnce();
                    loop_rate.sleep();
                    break;

                case '2':
                    printf("Surveilance mode: Work in Progress\n");
                    // goSurveilancemode();
                    break;

                case '3':
                    printf("Exit\n");
                    isExit = true;
                    break;
            }

            if (isExit)
                break;
        }
    } while(true);

    return 0;
}

Loc destination_menu(ros::NodeHandle &nh)
{
    // // for debug process. comment here when debug is over
    nav_progress = false;

    if (nav_progress)
    {
        Loc dummy;
        dummy.req = -1;
        printf("Robot service in progress. control order rejected\n");
        ROS_INFO("Error: navigating in progress\n");
        return dummy;
    }

    // Go to dest, and find name
    std::string dest, mode;
    printf("select destination: ");
    std::cin >> dest;

    printf("MODE SELECT - 1(WAIT THERE) 0(RETURN TO BASE): ");
    std::cin >> mode;

    Loc target = set_destination(nh, dest, mode);

    return target;
}

Loc set_destination(ros::NodeHandle &nh, std::string &dest, std::string &mode)
{
    std::cout << "go to " << dest << '\n';

    Loc ret;
    int idx = atoi(dest.c_str());
    ros::ServiceClient location_req = nh.serviceClient<goinghome_host_controller::infoRequest>("request_location_info");
    goinghome_host_controller::infoRequest srv;
    ROS_INFO("requesting locationInfo: %d", idx);
    srv.request.id = idx;

    if (location_req.call(srv))
    {
        ROS_INFO("locationInfo received!");
    }

    else
    {
        ROS_ERROR("Failed to getlocationInfo.");
    }

    ret.px = srv.response.px;
    ret.py = srv.response.py;
    ret.ow = srv.response.ow;
    ret.req = atoi(mode.c_str());

    return ret;
}
