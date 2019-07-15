#!/usr/bin/env python

import sys
import rospy
from face_checking.srv import *

def add_two_ints_client(x):
    rospy.wait_for_service('test')
    try:
        add_two_ints = rospy.ServiceProxy('test', test)
        resp1 = add_two_ints(x)
        return resp1.id
    except rospy.ServiceException, e:
        print "Service call failed: %s"%e

def usage():
    return "%s [x]"%sys.argv[0]

if __name__ == "__main__":
    if len(sys.argv) == 2:
        x = int(sys.argv[1])
    else:
        print usage()
        sys.exit(1)
    #print "Requesting %d"%(x)
    print "Requesting {0}".format(x)
    #print "%d = %d"%(x, add_two_ints_client(x))
    print "{0} = {1}".format(x, add_two_ints_client(x))
    
