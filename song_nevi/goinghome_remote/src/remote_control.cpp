#include "remote_base.h"




bool control_server_callback(remote_srv::Request &req ,remote_srv::Response &res){
    ROS_INFO("control_callback");
    ros::NodeHandle control_service;
    ros::ServiceClient control_client=control_service.serviceClient<remote_srv>("nevi_service");
    nevi_srv rq;

    switch(req.com_num)
    {
        case WAIT : 
        std::cout<<"wait";
        res.result=true;
        return true;
        break;

        case GUIDE : 
        std::cout<<"guide ";
        
        case MOVE :
        std::cout<<"move ";
        rq.request.px=req.px;
        rq.request.py=req.py;
        rq.request.ow=req.ow;
        break;
    
    /*추후에 사용될지 모르는 것들
    case SEARCH : 

        break;
    
    case INT : 

        break;
     */

    default:
        ROS_ERROR("odd COMMAND");
        res.result=false;
        return false;
        break;
    }
    ROS_INFO("nevi connecting....");
    while(!control_client.exists());

    if(control_client.call(rq)){
        if(rq.response.result){ //nevi 성공 --> camera node 실행
            /* 
            Py_Initialize();

            PyRun_SimpleString("import roslaunch");
            PyRun_SimpleString("package = 'rqt_gui'");
            PyRun_SimpleString("executable = 'rqt_gui'");
            PyRun_SimpleString("node = roslaunch.core.Node(package, executable)");
            PyRun_SimpleString("launch = roslaunch.scriptapi.ROSLaunch()");
            PyRun_SimpleString("launch.start()");
            PyRun_SimpleString("process = launch.launch(node)");
            PyRun_SimpleString("print process.is_alive()");
            PyRun_SimpleString("process.stop()");
            Py_Finalize();
            */
            }else //nevi 실패
            {
             res.result=false;
             return false;   
            }
        
        }else
        {
            ROS_ERROR("\"remote_nevi\" node not connect");
            res.result=false;
            return false;
        }
        

}

int main (int argc,char* argv[] ){
    ros::init(argc,argv,"control_node");
    ros::NodeHandle control_server;
    ros::ServiceServer control_srv_server=control_server.advertiseService("control_service",control_server_callback);
    ROS_INFO("control service server start");
    ros::spin();
    return 0;
}