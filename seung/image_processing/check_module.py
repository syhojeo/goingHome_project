#!/usr/bin/env python
# -*- coding: utf-8 -*-
## client 의 srv가 왔을때 부터 영상처리 시작

from __future__ import print_function
#python 2.7에서도 python3버전의 일부 함수들을 사용하게 함
import roslib
roslib.load_manifest('face_checking')
import sys
import rospy
import cv2
from std_msgs.msg import String
from sensor_msgs.msg import Image
from face_checking.srv import *
from cv_bridge import CvBridge, CvBridgeError
import face_recognition
import numpy as np
import time

#서비스를 ctrl node 로 보내기 위한 flag
flag =1
#영상처리 결과를 알려주는 전역변수 id
sid =2

#face recognition
# Load a sample picture and learn how to recognize it.
obama_image = face_recognition.load_image_file("/home/goinghome/git/face_recognition/examples/obama.jpg")
obama_face_encoding = face_recognition.face_encodings(obama_image)[0]

# Load a second sample picture and learn how to recognize it.
biden_image = face_recognition.load_image_file("/home/goinghome/git/face_recognition/examples/biden.jpg")
biden_face_encoding = face_recognition.face_encodings(biden_image)[0]

# Create arrays of known face encodings and their names
known_face_encodings = [
    obama_face_encoding,
    biden_face_encoding
]
known_face_names = [
    "Barack Obama",
    "Joe Biden"
]

# Initialize some variables
face_locations = []
face_encodings = []
face_names = []

class image_converter:

  def __init__(self):
    self.image_pub = rospy.Publisher("image_topic_2",Image)

    self.bridge = CvBridge()
    self.image_sub = rospy.Subscriber("/camera/image_raw",Image,self.callback)
    print('start callback')
  def callback(self,data):
    
    global face_names
    global sid
    global flag
    
   
    try:
      frame = self.bridge.imgmsg_to_cv2(data, "bgr8")
    except CvBridgeError as e:
      print(e)

  
    process_this_frame = True

   
  
    # Resize frame of video to 1/4 size for faster face recognition processing
    small_frame = cv2.resize(frame, (0, 0), fx=0.25, fy=0.25)

    # Convert the image from BGR color (which OpenCV uses) to RGB color (which face_recognition uses)
    rgb_small_frame = small_frame[:, :, ::-1]

    # Only process every other frame of video to save time
    if process_this_frame:
        # Find all the faces and face encodings in the current frame of video
        face_locations = face_recognition.face_locations(rgb_small_frame)
        face_encodings = face_recognition.face_encodings(rgb_small_frame, face_locations)

        face_names = []
        for face_encoding in face_encodings:
            # See if the face is a match for the known face(s)
            matches = face_recognition.compare_faces(known_face_encodings, face_encoding)
            name = "Unknown"

            # # If a match was found in known_face_encodings, just use the first one.
            # if True in matches:
            #     first_match_index = matches.index(True)
            #     name = known_face_names[first_match_index]

            # Or instead, use the known face with the smallest distance to the new face
            face_distances = face_recognition.face_distance(known_face_encodings, face_encoding)
            best_match_index = np.argmin(face_distances)
            if matches[best_match_index]:
                name = known_face_names[best_match_index]
            face_names.append(name)
    

            
          
    process_this_frame = not process_this_frame
  


        # Display the results
    for (top, right, bottom, left), name in zip(face_locations, face_names):
        # Scale back up face locations since the frame we detected in was scaled to 1/4 size
        top *= 4
        right *= 4
        bottom *= 4
        left *= 4

        # Draw a box around the face
        cv2.rectangle(frame, (left, top), (right, bottom), (0, 0, 255), 2)

        # Draw a label with a name below the face
        cv2.rectangle(frame, (left, bottom - 35), (right, bottom), (0, 0, 255), cv2.FILLED)
        font = cv2.FONT_HERSHEY_DUPLEX
        cv2.putText(frame, name, (left + 6, bottom - 6), font, 1.0, (255, 255, 255), 1)
            
        # Display the resulting image
    cv2.imshow('Video', frame)
    cv2.waitKey(3)
    try:
        self.image_pub.publish(self.bridge.cv2_to_imgmsg(frame, "bgr8"))
    except CvBridgeError as e:
        print(e)
    
    #searching result
    if 'Unknown' in face_names:
      sid = 0
      #flag =0 
      #self.image_pub.unregister()
      #self.image_sub.unregister()
      #cv2.destroyAllWindows()
   
      #time.sleep(100)
      
  

    elif 'Barack Obama' in face_names:
      print('obama')
      sid = 321
      flag =0 #break while (receive srv)
      self.image_pub.unregister()
      self.image_sub.unregister()
      cv2.destroyAllWindows()
     
      #time.sleep(100)
      
      
    else: #continue
      sid = 2



def main(args):
  #init node
  rospy.init_node('image_converter', anonymous=True)
  #s=rospy.Service('test',test,handle_test)
  print ("Ready to add id.")
  try:
    s=rospy.Service('image_srv',image,handle_test)
    rospy.spin()  
  except KeyboardInterrupt:
    print("Shutting down")
  




  #sevice call handler 
def handle_test(req):  
    #start image processing
  print('com_num = %d' % req.com_num)         
  global flag
  global sid
  ic = image_converter()
  #영상처리가 끝날때 까지 대기
  while True:
    print('in while')
    time.sleep(1)
    if flag == 0:
        break
  
  
  print('out of while')    

  return imageResponse(sid)


if __name__ == '__main__':
    main(sys.argv)
