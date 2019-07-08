import roslaunch
import rospy
from std_msgs import Bool

def callback(data):
        camera_sw(data.data)
    
def listener():
    rospy.init_node('camera_sw')
    rospy.Subscriber('sw_pub',Bool,callback)

def camera_sw(bool onoff)
    package = 'rqt_gui'
    executable = 'rqt_gui'
    node = roslaunch.core.Node(package, executable)
    if condition:
        launch = roslaunch.scriptapi.ROSLaunch()
        launch.start()
    else:
        process = launch.launch(node)
        print process.is_alive()
        process.stop()

if __name__=='__main__':
    listener()