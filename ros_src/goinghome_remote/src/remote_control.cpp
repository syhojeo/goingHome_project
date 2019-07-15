#include "goinghome_remote.h"


bool control_server_callback(remote_srv::Request &req ,remote_srv::Response &res){
    ROS_INFO("control_callback");
    bool comeback =false;
  
    //nevi service 
    ros::NodeHandle nevi_service;
    ros::ServiceClient nevi_client=nevi_service.serviceClient<nevi_srv>("nevi_service");
    nevi_srv rq;
    
    //camera topic
    ros::NodeHandle camera_topic;
    ros::Publisher camera_pub =camera_topic.advertise<std_msgs::Bool>("sw_pub",1);
    std_msgs::Bool camera_sw;

    //image processing node (slug)
    ros::NodeHandle image_service;
    ros::ServiceClient image_client=image_service.serviceClient<image_srv>("image_srv");
    ros::ServiceClient image_client=image_service.serviceClient<image_srv>("fake_service");
    image_srv iq;
    

    switch(req.com_num)
    {
        case WAIT : 
        std::cout<<"wait";
        res.result=true;
        return true;
        break;

        case GUIDE : 
        std::cout<<"guide ";
        rq.request.px=req.px;
        rq.request.py=req.py;
        rq.request.ow=req.ow;
        camera_sw.data=true;
        comeback=false;
        break;
        case COMEBACK:
        comeback=true;
        camera_sw.data=true;
        case COMEBACK:
        case MOVE :
        std::cout<<"move ";
        rq.request.px=req.px;
        rq.request.py=req.py;
        rq.request.ow=req.ow;
        break;
    
    /*추후에 사용될지 모르는 것들
    case CAMERA : 

        break;
    
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
    //nevi exists 
    for(int count=0;!nevi_client.exists();count++){
                ROS_INFO("nevi_node connecting....");
                sleep(1);
                if(count==5){
                    ROS_ERROR("nevi_node connect FAIL");
                    res.result=false;
                    return false;       
                }
    }

    if(nevi_client.call(rq)){
        ROS_INFO("service call to\"remote_nevi\"");
        if(rq.response.result){ //nevi 성공 --> camera node 실행
            camera_sw.data=true;
            //camera_pub.publish(camera_sw); 
            ROS_INFO("control_node send to\"camera_node\"");
                if(!comeback){

                    for(int count=0;!image_client.exists();count++){
                        ROS_INFO("image_node connecting....");
                        sleep(1);
                        if(count==100){
                            ROS_ERROR("image_node connect FAIL");
                            res.result=false;
                            return false;       
                        }
                    }
                iq.request.com_num=20;
                    if(image_client.call(iq)){
                        res.id=iq.response.id;
                    }else{ //image node search fail
                        ROS_ERROR("searching fail");   
                        res.result=false;
                        res.id=-1;
                        return false;      
                    }
                //camera node shutdown
                ROS_INFO("searching Success");
                ROS_INFO("id: %d",iq.response.id);
                res.id=iq.response.id;
                camera_sw.data=false;
                //camera_pub.publish(camera_sw);
            }
            res.result=true;
            return true;
        }else{ //nevi 실패
            camera_pub.publish(camera_sw); 
            ROS_INFO("control_node send to\"camera_node\"");
            
            for(int count=0;!image_client.exists();count++){
                ROS_INFO("image_node connecting....");
                sleep(1);
                if(count==5){
                    ROS_ERROR("image_node connect FAIL");
                    res.result=false;
                    return false;       
                }
            }
            iq.request.com_num=1;
            if(image_client.call(iq)){
                res.id=iq.response.id;
            }else{ //image node search fail
                ROS_ERROR("searching fail");   
                res.result=false;
                res.id=-1;
                return false;      
            }
            //camera node shutdown
            ROS_INFO("searching Success");
            ROS_INFO("id: %d",iq.response.id);
            
            sleep(3);
            camera_sw.data=false;
            camera_pub.publish(camera_sw);
            
            res.result=true;
            return true;

        }else{ //nevi 실패
             res.result=false;
            return false;   
        }
        }else{
            ROS_ERROR("\"remote_nevi\" node not connect");
            res.result=false;
            return false;
        }
}
//camera_node callback
bool cameracallback(){
return true;
}

int main (int argc,char* argv[] ){
    ros::init(argc,argv,"control_node");
    ros::NodeHandle control_server;
    ros::ServiceServer control_srv_server=control_server.advertiseService("control_service",control_server_callback);
    ROS_INFO("control service server start");
    ros::spin();
    return 0;
}