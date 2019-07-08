#include "eventhandler.h"

bool nav_progress = false;

void gobase(int mode = 0)
{
    if (nav_progress && mode == 0)
    {
        printf("Robot service in progress. control order rejected\n");
        ROS_ERROR("Error: navigating in progress\n");
    }

    printf("Return to base!\n");

    ros::NodeHandle nh;
    ros::ServiceClient navigation_service_client = nh.serviceClient<goinghome_host_eventhandler::nav_request>("navigation_request");
    
    goinghome_host_eventhandler::nav_request rq;

    rq.request.px = 0;
    rq.request.py = 0;
    rq.request.pz = 0;
    rq.request.ox = 0;
    rq.request.oy = 0;
    rq.request.oz = 0;
    rq.request.ow = 0;

    if (navigation_service_client.call(rq))
    {
        printf("request: (%f, %f, %f), (%f, %f, %f, %f)\n", (float)rq.request.px, (float)rq.request.py, (float)rq.request.pz, 
        (float)rq.request.ox, (float)rq.request.oy, (float)rq.request.oz, (float)rq.request.ow);

        if(rq.response.result)
        {
            printf("send success!\n");
            nav_progress = true;
        }

        else
        {
            printf("error while processing navigation_service_client\n");
        }

        printf("result: %d\n", rq.response.result);
    }

    else
    {
        ROS_ERROR("Failed to call service navigation_service_srv");
        nav_progress = false;
    }
}

void set_destination(std::string &dest, std::string &mode)
{
    // for debug process. comment here when debug is over
    nav_progress = false;

    if (nav_progress && mode == 0)
    {
        printf("Robot service in progress. control order rejected\n");
        ROS_ERROR("Error: navigating in progress\n");
    }

    std::cout << "go to " << dest << " and mode: " << mode '\n';

    ros::NodeHandle nh;
    ros::ServiceClient navigation_service_client = nh.serviceClient<goinghome_host_eventhandler::nav_request>("navigation_request");
    
    goinghome_host_eventhandler::nav_request rq;

    // when filesystem implementation is complete, then read coordinates from loaded location
    rq.request.px = 1;
    rq.request.py = 2;
    rq.request.pz = 0;
    rq.request.ox = 0;
    rq.request.oy = 0;
    rq.request.oz = 0;
    rq.request.ow = 5;

    if (navigation_service_client.call(rq))
    {
        printf("request: (%f, %f, %f), (%f, %f, %f, %f)\n", (float)rq.request.px, (float)rq.request.py, (float)rq.request.pz, 
        (float)rq.request.ox, (float)rq.request.oy, (float)rq.request.oz, (float)rq.request.ow);

        if(rq.response.result)
        {
            printf("send success!\n");
            nav_progress = true;
        }

        else
        {
            printf("error while processing navigation_service_client\n");
        }

        printf("result: %d\n", rq.response.result);
    }

    else
    {
        ROS_ERROR("Failed to call service navigation_service_srv");
        nav_progress = false;
    }

    return;
}

void destination_menu()
{
    if (nav_progress)
    {
        printf("Robot service in progress. control order rejected\n");
        ROS_INFO("Error: navigating in progress\n");
        return;
    }

    // Go to dest, and find name
    std::string dest, name;
    printf("select destination: ");
    std::cin >> dest;
    
    set_destination(dest);

    return;
}
