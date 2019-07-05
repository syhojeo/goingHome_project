#Publisher node
#----------------------------------------------------------------------------------------------------#
## python ROS관련 노드 선언
import rospy
from std_msgs.msg import String # std_msg/String의 message type


def talker():
    pub = rospy.Publisher('chatter', String, queue_size=10)
    # publisher 노드 선언, 'chatter'는 name이라 생각하면 됨
    rospy.init_node('talker', anonymous=True)
    #  rospy.init_node(name, anonymous=False, log_level=rospy.INFO, disable_signals=False)   
    #  rospy.init_node('노드 이름') or rospy.init_node('노드이름', anonymous=True)-> 자주사용하는 형태
    #  위 함수를 선언하지않으면 Master와 Communicating 불가
    #  노드 이름은 "/" 쓰면 안됨
    #  anonymous=True는 각각의 노드에 독특한 번호를 준다. 만약 같은 이름의 두개의 노드가 ROS Graph에서 탐지되었을 때, 오래된 노드는 종료된다.
    #  log_level=rospy.INFO -> 기본 log message를 rospy.INFO로 설정
    #  cf) log message는 node의 status를 알려줌. rospy.INFO와 같은 형태로 사용함
    #      1) INFO : user에게 간단한 정보 알려줌 ex) "Node initialize", "New subscriber to topic X:Y"
    #      2) DEBUG : System이 잘동작하는지 확인할 때 사용
    #      3) WARN : 시스템의 예상 작동 정보를 알려줄 때 사용, 한마디로 말하면 주의사항과 같은 용도 ex) "Could not load configuration file from <path>. Using defaults."
    #      4) ERROR : 문제 발생시 사용, 그러나 회복할 수 있음 ex) "camera node error!
    #      5) FATAL : ERROR와 비슷하지만 회복할 수 없다는 것이 차이점이다.
    #  disable_signals=False -> 기본적으로 rospy는 signalHandler가 등록되어 있어서 ctrl+C를 하면 종료하게 되어있다. 만약 이것을 diable하고 싶을 때 선언해주면 된다.  
    rate = rospy.Rate(10) 
    while not rospy.is_shutdown():
        hello_str = "hello world %s" % rospy.get_time()
        rospy.loginfo(hello_str)
        pub.publish(hello_str)
        #'chatter' topic의 메세지를 날리는 문장
        rate.sleep()
#------------------------------------------------------------------------------------------#
# rate = rospy.Rate(10) + rate.sleep() 코드는 밑의 time측정 및 delay하는 명령어와 같음 
# cf) rospy에서 time측정 코드
# rospy.get_rostime() -> get time as rospy.Time instance
# rospy.get_time() -> get time as float secs
# rospy.sleep(duration)
#------------------------------------------------------------------------------------------#


if __name__ == '__main__':
    try:
        talker() 
    except rospy.ROSInterruptException: # sleep관렴 함수나 강제 종료와 같은 경우는 예외처리로 적용됨, 그 이유는 sleep후 계속 실행되는 것을 방지하기 위함
        pass
