#!/usr/bin/env python

'''
'''

# TurtleBot must have minimal.launch & amcl_demo.launch
# running prior to starting this script
# For simulation: launch gazebo world & amcl_demo prior to run this script

import rospy
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
import actionlib
from actionlib_msgs.msg import *
from geometry_msgs.msg import Pose, Point, Quaternion

class GoToPose():
	def __init__(self):

		self.goal_sent = False

	# What to do if shut down (e.g. Ctrl-C or failure)
		rospy.on_shutdown(self.shutdown)

	def ros_move(self, pos, quat):

		# Tell the action client that we want to spin a thread by default
		self.move = actionlib.SimpleActionClient("move", MoveBaseAction)

		# Allow up to 5 seconds for the action server to come up
		while(not move.wait_for_server(rospy.Duration.from_sec(5.0))):
			rospy.loginfo("Waiting for the move action server to come up")

		# Send a goal
		self.goal_sent = True
		goal = MoveBaseGoal()
		goal.target_pose.header.frame_id = 'map'
		goal.target_pose.header.stamp = rospy.Time.now()

		goal.target_pose.pose.position =  Point(pos['x'], pos['y'], 0.000)
		goal.target_pose.pose.orientation.x = quat['r1']
		goal.target_pose.pose.orientation.y = quat['r2']
		goal.target_pose.pose.orientation.z = quat['r3']
		goal.target_pose.pose.orientation.w = quat['r4']

		# Start moving
		rospy.loginfo("Sending goal location ...")
		self.move.send_goal(goal)

		# Allow TurtleBot up to 60 seconds to complete task
		success = self.move.wait_for_result(rospy.Duration(60)) 

		state = self.move.get_state()
		result = False

		if success and state == GoalStatus.SUCCEEDED:
		# We made it!
			rospy.loginfo("Destination reached")
			result = True
		else:
			self.move.cancel_goal()
			rospy.loginfo("Failed to reach the destination")

			self.goal_sent = False
		return result

	def shutdown(self):
		if self.goal_sent:
			self.move.cancel_goal()
			rospy.loginfo("Stop")
			rospy.sleep(1)

	if __name__ == '__main__':
		try:
			rospy.init_node('nav_test', anonymous=False)
			navigator = GoToPose()

			#1
			position = {'x': 1.06, 'y' : 0.22}
			quaternion = {'r1' : 0.000, 'r2' : 0.000, 'r3' : 0.000, 'r4' : 1.000}

			success = navigator.ros_move(position, quaternion)
			rospy.loginfo("This is Corner1")


			rospy.sleep(1)


			#2
			position = {'x': 1.22, 'y' : -6.57}

			success = navigator.ros_move(position, quaternion)
			rospy.loginfo("This is Corner2")


			rospy.sleep(1)

			#3
			position = {'x': 6.66, 'y' : -5.78}

			success = navigator.ros_move(position, quaternion)
			rospy.loginfo("This is Corner3")


			rospy.sleep(1)

			#4

			position = {'x': 3.93, 'y' : 0.65}

			success = navigator.ros_move(position, quaternion)
			rospy.loginfo("This is Corner4")


			rospy.sleep(1)

			#5
			position = {'x': 1.52, 'y' : -9.13}

			success = navigator.ros_move(position, quaternion)
			rospy.loginfo("This is Corner5")


			rospy.sleep(1)

			#6
			position = {'x': 5.55, 'y' : -6.12}

			success = navigator.ros_move(position, quaternion)
			rospy.loginfo("This is Corner6")


			rospy.sleep(1)

		except rospy.ROSInterruptException:
			rospy.loginfo("Quitting")

