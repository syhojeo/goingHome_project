#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import Bool
import roslaunch
import sys
from os.path import *
import os

sw =False
bar=False

def listener():
        print('camera_node start')
        rospy.init_node('camera_sw',anonymous=True)
        rospy.Subscriber('sw_pub',Bool,camera_sw)
       

def camera_sw(data):
        global sw
        global bar
        print('camera_node callback')
        print(data)
        sw=data.data
        bar=True

def file_path ():
        file_path=os.path.split(os.path.realpath(__file__)) #file`s dir path
        file_path=os.path.split(file_path[0])
        launch_path=os.path.join(file_path[0],'launch','fake_node.launch')
        return launch_path

if __name__=='__main__':
        print('camera_node start')
        rospy.init_node('camera_sw',anonymous=True)
        rospy.Subscriber('sw_pub',Bool,camera_sw)
        uuid = roslaunch.rlutil.get_or_generate_uuid(None, False)
        roslaunch.configure_logging(uuid)
        path=file_path()
        print(path)
        launch = roslaunch.parent.ROSLaunchParent(uuid,path)
        global sw
        global bar
        while True:    
                if bar:
                        if sw:
                                launch.start()
                                bar =False  
                        else:
                                launch.shutdown()
                                bar =False