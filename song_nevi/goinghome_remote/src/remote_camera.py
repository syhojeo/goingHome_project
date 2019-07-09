#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import Bool
import roslaunch

   
def listener():
    print('camera_node start')
    rospy.init_node('camera_sw')
    rospy.Subscriber('sw_pub',Bool,callback)
    rospy.spin()

def camera_sw(onoff):
    print('camera_node callback')
    package = ''
    executable = 'rqt_gui'
    node = roslaunch.core.Node(package, executable)
    launch = roslaunch.scriptapi.ROSLaunch()
    if onoff.data:
        launch.start()
    else:
        process = launch.launch(node)
        print process.is_alive()
        process.stop()

def callback (data):
        camera_sw(data)

if __name__=='__main__':
    listener()