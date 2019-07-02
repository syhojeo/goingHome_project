#include "eventhandler.h"

bool survail_mode = false;

void goSurveilancemode()
{
    printf("Surveilance mode: WORKING IN PROGRESS\n");
    ROS_INFO("Surveilance mode: WORKING IN PROGRESS\n");

    ros::NodeHandle nh;
    ros::ServiceClient surveilance_service_client = nh.serviceClient<goinghome_host_eventhandler::survail_request>("surveilance_request");

    goinghome_host_eventhandler::survail_request rq;

    if (!survail_mode)
    {
        survail_mode = true;
        rq.request.onoff = 1;
    }

    else
    {
        survail_mode = false;
        rq.request.onoff = 0;
    }

    if (surveilance_service_client.call(rq))
    {
        if (survail_mode)
        {
            printf("Surveilance Camera On\n");
        }

        else
        {
            printf("Surveilance Camera Off\n");
        }

        if(!rq.response.result)
        {
            printf("request send succees!\n");
        }

        else
        {
            printf("error while processing surveilance_service_client\n");
        }

        printf("result: %d\n", rq.response.result);
    }

    else
    {
        ROS_ERROR("Failed to call service: surveilance_service_client");
    }

    return;
}

// implement any camera related functions in here!
