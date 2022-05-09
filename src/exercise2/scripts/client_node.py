#!/usr/bin/env python

from __future__ import print_function

import sys
import rospy
from exercise2.srv import Movement

def move_client(move, duration):
    rospy.wait_for_service('movement')
    try:
        moveFunc = rospy.ServiceProxy('movement', Movement)
        res = moveFunc(duration, move)
        return res.lastMove

    except rospy.ServiceException as e:
        print("Service call failed: %s"%e)


if __name__ == "__main__":
	move = sys.argv[1]
	duration = int(sys.argv[2])
	print("Requesting %s,%d"%(move, duration))
	move_client(move, duration)
	