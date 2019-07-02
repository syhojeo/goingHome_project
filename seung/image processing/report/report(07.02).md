영상처리(카메라)  부분 진행 상황

#### 1.ROS에서 open CV를 이용한 영상처리를 위해서는 CV bridge 를 사용해야한다

ROS image/message -> CV bridge -> opencv (영상처리)

<http://wiki.ros.org/cv_bridge/Tutorials/UsingCvBridgeToConvertBetweenROSImagesAndOpenCVImages>



#### 2.카메라 영상을 ros에서 사용가능한 message (image/message) 로 만들 필요가 있다.

gscam 패키지를 사용

<http://wiki.ros.org/gscam>

gscam 은 여러 멀티 미디어를 모두 제어가능한 gstreamer를 사용한 패키지이기 때문에 csi camera 에서도 호환이 가능하다



#### 3.gscam 을 실행하면 될줄 알았으나 실패 -> ERROR message :  could not get gstreamer sample

=> 다른 패키지를 이용해보려 하였으나 인터넷상의 대부분의 패키지에 gscam 이 들어가는 것으로 보아 근본적인 문제를 해결해야할 필요성을 느낌



따라서 gscam 문제를 해결하려 방향을 잡게됨



could not get gstreamer sample

위의 에러메시지를 검색하였으나 에러내용이 다르거나 같더라도 camera를 uvc카메라로 변경하여 해결했다는 내용밖엔 확인하지 못함



gscam cpp 파일을 분석해본 결과 sample을 얻어오지 못하였고,

이 의미는 gstream이 play 상태가 아니거나 중간의 과정에서 데이터가 넘어오지 못하여 가져오지 못한다고 판단됨



gscam cpp 파일

<https://github.com/ros-drivers/gscam/blob/master/src/gscam.cpp>





#### 4.문제 원인

1) gscam 은 오래된 패키지인 만큼 gstreamer 의 버전이 맞지 않다라는 생각

gscam gstreamer 사용 버전  0.1 ,  현 jetson nano 버전 1.14

->  but cmakefile을 보면 gstreamer 1.0버전을 사용하는것 같다고 생각됨



2)gscam_config 파일

rosrun gscam gscam 을 하기전에 반드신 gscam_config 변수를 export 하여 지정해 주어야 노드실행이 정상적으로 가능하다



gscam_config 파일을 해결하기 위해 여러가지 사이트에서 정보를 모으고 해결하려 노력중 (현재상태)



gstreamer 개발자 가이드

<https://developer.download.nvidia.com/embedded/L4T/r32_Release_v1.0/Docs/Accelerated_GStreamer_User_Guide.pdf?pjhpOuGWPufu_AUQCs-PUuq_Z-gnC9-QmYaBmVcVSAz2vzh2Oz5ffNvjdGTb2C4cJfZJJCaNaHXci1zrEyPIhNalJe3q0jNf-x-JkASiBw2bpDESMnd2Sh3CDInbjgE6ZnGQvwh1ZVed1buKgRNNUCcbzm6kcaQ02uTnXAqpY2W-o5WfRsQ>



jetson hack의 gstream 실행 문서

<https://www.jetsonhacks.com/2019/04/02/jetson-nano-raspberry-pi-camera/>



gstreamer 프로그래밍 설명 블로그

<https://studyingdever.tistory.com/3?category=502391>