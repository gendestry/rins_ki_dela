#!/usr/bin/env python

from __future__ import print_function

from exercise2.srv import Movement
from geometry_msgs.msg import Twist
import rospy
import random

def triangle_movement(step):
	twist = Twist()
	twist.linear.x = 0.5
	step = step % 20

	if step % 5 == 0:
		twist.linear.x = 0
		twist.angular.z = (1 / 3) * 2 * 3.1415

	return twist

def circular_movement(step):
	twist = Twist()
	twist.angular.z = 0.6
	twist.linear.x = 0.6
	return twist

def random_movement(step):
	twist = Twist()
	twist.linear.x = random.random()
	twist.angular.z = (random.random() - 0.5)
	return twist
  
def rectangle_movement(step):
	twist = Twist()
	twist.linear.x = 0.5
	step = step % 20

	if step % 5 == 0:
		twist.linear.x = 0
		twist.angular.z = 1.57 #(90 / 360) * 2 * 3.14

	return twist


def handle_movement(req):
	r = rospy.Rate(1)
	step = 0.0

	while req.duration - step > 0:
		if req.movement == "rectangle":
			twist = rectangle_movement(step)
		elif req.movement == "circle":
			twist = circular_movement(step)
		elif req.movement == "random":
			twist = random_movement(step)
		elif req.movement == "triangle":
			twist = triangle_movement(step)	

		pub.publish(twist)
		step = step + 1.0
		r.sleep()
	return req.movement

if __name__ == "__main__":
	global pub
	rospy.init_node('movement_server')
	pub = rospy.Publisher('turtle1/cmd_vel', Twist, queue_size = 1000)
	s = rospy.Service('movement', Movement, handle_movement)
	print("Ready to move.")
	rospy.spin()
