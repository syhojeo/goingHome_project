#Subscriber Node

import rospy
from std_msgs.msg import String
 
def callback(data):
    rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)
     
def listener():
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber("chatter", String, callback)
  # spin() simply keeps python from exiting until this node is stopped 
  # -> 노드가 종료되지 전까지 python main thread가 종료되는 것을 막음. 즉, rospy.is_shutdown()이 내려지기 전까지 python main 실행부가 종료되지 않는다.
  # python은 기본적으로 single Thread를 가지고 있다. 한문장씩 실행되고 종료되는 python의 동작을 생각하면 바로 이해할 수 있다. 
  # 따라서 cpp과 달리 rospy.spin()는 subscrieber callback 함수에 영향을 주지 않는다. 
    rospy.spin() 


if __name__ == '__main__':
     listener()