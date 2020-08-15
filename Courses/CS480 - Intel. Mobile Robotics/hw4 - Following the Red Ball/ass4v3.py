#!/usr/bin/env python

'''
'''
import roslib
import rospy
import sys
import cv2
import numpy as np
import time
from cv_bridge import CvBridge,CvBridgeError

from geometry_msgs.msg import Twist, Point
from std_msgs.msg import String
from sensor_msgs.msg import Image

class ballFinder:

	def __init__(self):
		self.image_pub = rospy.Publisher("image_topic_2",Image)
		self.pub_vel = rospy.Publisher('cmd_vel_mux/input/navi', Twist, queue_size=1)
		
		self.bridge = CvBridge()
		self.image_sub = rospy.Subscriber("/camera/rgb/image_raw",Image,self.callback)
        	self.depth_sub = rospy.Subscriber("/camera/depth/image_raw", Image, self.depth_callback)
		self.img = np.zeros(shape=[512, 512, 3], dtype=np.uint8)
		self.x = 0
		self.y = 0

	def regions(self, x, y, w, h):
		width, height,_ = self.img.shape
		width = width/3
		x = (x+w/2)
		x = (y+h/2)
		vel = Twist()
		
		if(x<width):
			vel.angular.z = 0.5 #left
			print"left"
			self.pub_vel.publish(vel)
		elif(x<(2*width)):
			vel.angular.z = 0 #forward
			
			self.pub_vel.publish(vel)
		else:
			vel.angular.z = -0.5 #right
			print "right"
			self.pub_vel.publish(vel)
		self.x = x
		self.y = y
	
	def depth_callback(self,ros_data):
		vel = Twist()
		try:
			# The depth image is a single-channel float32 image
			depth_image = self.bridge.imgmsg_to_cv(ros_image, "32FC1")
		except CvBridgeError, e:
			print e

		z = depth_image[self.x][self.y]

		if(z>1000):
			vel.linear.x = 0.2
		else:
			vel.linear.x = 0

		self.pub_vel.publish(vel)
				

	def callback(self,ros_data):
		'''Callback function of subscribed topic. 
		Here images get converted and features detected'''
		print "a"
		global pub, bridge
		self.img = self.bridge.imgmsg_to_cv2(ros_data, "bgr8")

		
		hsv = cv2.cvtColor(self.img, cv2.COLOR_BGR2HSV) 
		lower_red = np.array([0,100,100]) 
		upper_red = np.array([10,255,255]) 
		  
		# Here we are defining range of bluecolor in HSV 
		# This creates a mask of blue coloured  
		# objects found in the frame. 
		mask = cv2.inRange(hsv, lower_red, upper_red) 
		  
		# The bitwise and of the frame and mask is done so  
		# that only the blue coloured objects are highlighted  
		# and stored in res 
		res = cv2.bitwise_and(self.img,self.img, mask= mask)

		#cv2.circle(img, (col, row), 2, (0, 200, 255), -1)
		self.img = res
	
		#self.subscriber.unregister()
		try:
			self.image_pub.publish(self.bridge.cv2_to_imgmsg(self.img, "bgr8"))
		except CvBridgeError as e:
			print(e)
		#Tracking Colour (Yellow) 
		(_,contours,hierarchy)=cv2.findContours(mask,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

		contour = max(contours, key=cv2.contourArea)
		area = cv2.contourArea(contour)
		if(area>500):
			x,y,w,h = cv2.boundingRect(contour)     
			self.img = cv2.rectangle(self.img,(x,y),(x+w,y+h),(255,0,0),3)
			self.regions(x,y,w,h)
			
		cv2.imshow('image',self.img)
		cv2.waitKey(5)

def main():
	rospy.init_node('image_converter', anonymous=True)
	bf = ballFinder()
	
	try:
		rospy.spin()
	except KeyboardInterrupt:
		print("Shutting down")
	cv2.destroyAllWindows()

if __name__ == '__main__':
	main()

