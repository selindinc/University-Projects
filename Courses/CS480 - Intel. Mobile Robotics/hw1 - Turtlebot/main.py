#!/usr/bin/env python

'''
'''
import roslib
import rospy
import sys
import cv2
import numpy as np
import time
import math
import imutils
from cv_bridge import CvBridge,CvBridgeError

from geometry_msgs.msg import Twist, Point
from std_msgs.msg import String
from sensor_msgs.msg import Image
PI = 3.1415926535897

class ballFinder:

	def __init__(self):
		self.image_pub = rospy.Publisher("image_topic_2",Image)
		self.pub_vel = rospy.Publisher('cmd_vel_mux/input/navi', Twist, queue_size=1)
		
		self.bridge = CvBridge()
		self.image_sub = rospy.Subscriber("/camera/rgb/image_raw",Image,self.callback)
		self.img = np.zeros(shape=[512, 512, 3], dtype=np.uint8)
		self.move = False
		
	
	def move2(self):
		self.move = True
		vel = Twist()
		vel.linear.x = 0.5
		vel.angular.z = 0.5 #left
		self.pub_vel.publish(vel)
		self.move = False		

	def callback(self,ros_data):
		if(not self.move):			
			vel = Twist()
			vel.linear.x = 0
			vel.angular.z = 0 #left
			self.pub_vel.publish(vel)
			min_YCrCb = np.array([0,133,77],np.uint8)
			max_YCrCb = np.array([235,173,127],np.uint8)
			
			'''Callback function of subscribed topic. 
			Here images get converted and features detected'''
			self.img = self.bridge.imgmsg_to_cv2(ros_data, "bgr8")

			self.img = imutils.resize(self.img, width=400)
			imageYCrCb = cv2.cvtColor(self.img, cv2.COLOR_BGR2YCR_CB)
			skinMask = cv2.inRange(imageYCrCb, min_YCrCb, max_YCrCb)

			# apply a series of erosions and dilations to the mask
			# using an elliptical kernel
			kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (11, 11))
			skinMask = cv2.erode(skinMask, kernel, iterations=2)
			skinMask = cv2.dilate(skinMask, kernel, iterations=2)

			# blur the mask to help remove noise, then apply the
			# mask to the frame
			skinMask = cv2.GaussianBlur(skinMask, (3, 3), 0)
			skin = cv2.bitwise_and(self.img, self.img, mask=skinMask)
			
			grey = cv2.cvtColor(skin, cv2.COLOR_BGR2GRAY)
			value = (35, 35)
			blurred = cv2.GaussianBlur(grey, value, 0)
			_, thresh1 = cv2.threshold(blurred, 127, 255,
						cv2.THRESH_BINARY_INV+cv2.THRESH_OTSU)
			#cv2.imshow('Thresholded', thresh1)
			_, contours, hierarchy = cv2.findContours(thresh1.copy(),cv2.RETR_TREE, 
								cv2.CHAIN_APPROX_NONE)
			max_area = -1
		
			for i in range(len(contours)):
				cnt=contours[i]
				area = cv2.contourArea(cnt)
				if(area>max_area):
					max_area=area
					ci=i
			cnt=contours[ci]
			x,y,w,h = cv2.boundingRect(cnt)
			cv2.rectangle(skin,(x,y),(x+w,y+h),(0,0,255),0)
			hull = cv2.convexHull(cnt)
			drawing = np.zeros(skin.shape,np.uint8)
			cv2.drawContours(drawing,[cnt],0,(0,255,0),0)
			cv2.drawContours(drawing,[hull],0,(0,0,255),0)
			hull = cv2.convexHull(cnt,returnPoints = False)
			defects = cv2.convexityDefects(cnt,hull)
			count_defects = 0
			cv2.drawContours(thresh1, contours, -1, (0,255,0), 3)

			if(defects.shape[0] != None):
				for i in range(defects.shape[0]):
					s,e,f,d = defects[i,0]
					start = tuple(cnt[s][0])
					end = tuple(cnt[e][0])
					far = tuple(cnt[f][0])
					a = math.sqrt((end[0] - start[0])**2 + (end[1] - start[1])**2)
					b = math.sqrt((far[0] - start[0])**2 + (far[1] - start[1])**2)
					c = math.sqrt((end[0] - far[0])**2 + (end[1] - far[1])**2)
					angle = math.acos((b**2 + c**2 - a**2)/(2*b*c)) * 57
					if angle <= 90:
						count_defects += 1
						cv2.circle(skin,far,1,[0,0,255],-1)
					cv2.line(skin,start,end,[0,255,0],2)
			if count_defects == 1:#2
				self.move2()
			elif count_defects == 2:#3
				#self.move3()
				a=0
			elif count_defects == 3:#4
				#self.move4()
				a=0
			elif count_defects == 4:#5
				#self.move5()
				a=0
			else:#0-1
				#self.move0()
				a=0
			
			all_img = np.hstack((drawing, skin))
			cv2.imshow('Contours', all_img)
			k = cv2.waitKey(10)

def main():
	rospy.init_node('image_converter', anonymous=True)
	bf = ballFinder()
	rate = rospy.Rate(10)
	try:
		rospy.spin()
	except KeyboardInterrupt:
		print("Shutting down")
	cv2.destroyAllWindows()

if __name__ == '__main__':
	main()

