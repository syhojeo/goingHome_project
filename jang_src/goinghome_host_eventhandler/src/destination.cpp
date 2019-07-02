#include "eventhandler.h"

bool nav_progress = false;

void gobase()
{
    if (nav_progress)
    {
        printf("Robot service in progress. control order rejected\n");
        ROS_ERROR("Error: navigating in progress\n");
    }

    printf("Return to base!\n");
    nav_progress = true;

    ros::NodeHandle nh;
    ros::ServiceClient navigation_service_client = nh.serviceClient<goinghome_host_eventhandler::request>("navigation_service_srv");
    
    goinghome_host_eventhandler::request rq;

    rq.request.px = 0;
    rq.request.py = 0;
    rq.request.pz = 0;
    rq.request.ox = 0;
    rq.request.oy = 0;
    rq.request.oz = 0;
    rq.request.ow = 0;

    if (navigation_service_client.call(rq))
    {
        ROS_INFO("request: (%f, %f, %f), (%f, %f, %f, %f)\n", (float)rq.request.px, (float)rq.request.py, (float)rq.request.pz, 
        (float)rq.request.ox, (float)rq.request.oy, (float)rq.request.oz, (float)rq.request.ow);
        ROS_INFO("result: %d\n", rq.response.result);
    }

    else
    {
        ROS_ERROR("Failed to call service navigation_service_srv");
        nav_progress = false;
    }
}

void set_destination(std::string &dest, std::string &name)
{
    std::cout << "go to " << dest << " and find " << name << '\n';
    // 여기에 서비스/메시지 관련 내용 추가

    std::cout << "WORK IN PROGRESS" << '\n';
    // nav_progress = true;

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

    printf("find who: ");
    std::cin >> name;
    
    set_destination(dest, name);

    return;
}
