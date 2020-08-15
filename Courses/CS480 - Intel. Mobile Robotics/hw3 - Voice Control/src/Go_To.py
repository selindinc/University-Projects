#!/usr/bin/env python

'''
'''

import rospy
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
import actionlib
from actionlib_msgs.msg import *
from geometry_msgs.msg import Pose, Point, Quaternion
from tf.transformations import quaternion_from_euler

class GoToPose():

    def __init__(self):
    
        rospy.init_node('move_base_sequence')

        self.goal_sent = False
        self.goal_cnt = 0
        self.pose_seq = list()

        pos = {'x': 1.06, 'y' : 0.22}
        quaternion = Quaternion(0.000, 0.000, 0.000, 1.000)
        self.pose_seq.append(Pose(Point(pos['x'], ['y'], 0.000),quaternion))

        position = {'x': 1.22, 'y' : -6.57}
        self.pose_seq.append(Pose(Point(pos['x'], ['y'], 0.000),quaternion))

        position = {'x': 6.66, 'y' : -5.78}
        self.pose_seq.append(Pose(Point(pos['x'], ['y'], 0.000),quaternion))


        position = {'x': 1.52, 'y' : -9.13}
        self.pose_seq.append(Pose(Point(pos['x'], ['y'], 0.000),quaternion))


        position = {'x': 3.93, 'y' : 0.65}
        self.pose_seq.append(Pose(Point(pos['x'], ['y'], 0.000),quaternion))

        position = {'x': 5.55, 'y' : -6.12}
        self.pose_seq.append(Pose(Point(pos['x'], ['y'], 0.000),quaternion))
        
        # Tell the action client that we want to spin a thread by default
        self.move = actionlib.SimpleActionClient("move", MoveBaseAction)

        # Allow up to 5 seconds for the action server to come up
        rospy.loginfo("Waiting for move_base action server...")
        server_up = self.move.wait_for_server(rospy.Duration(10.0))
        if not server_up:
            rospy.logerr("Timed out waiting for Calibration"
                         " Server to connect. Check your ROS networking"
                         "  and/or reboot the robot.")
            rospy.signal_shutdown("Timed out waiting for Action Server")
            sys.exit(1) 

        # What to do if shut down (e.g. Ctrl-C or failure)
        rospy.on_shutdown(self.shutdown)
        self.ros_move()
    
    def next(self):
        self.goal_cnt += 1
        rospy.loginfo("Goal pose "+str(self.goal_cnt)+" reached") 
        if self.goal_cnt< len(self.pose_seq):
            next_goal = MoveBaseGoal()
            next_goal.target_pose.header.frame_id = "map"
            next_goal.target_pose.header.stamp = rospy.Time.now()
            next_goal.target_pose.pose = self.pose_seq[self.goal_cnt]
            rospy.loginfo("Sending goal pose "+str(self.goal_cnt+1)+" to Action Server")
            rospy.loginfo(str(self.pose_seq[self.goal_cnt]))
            self.move.send_goal(next_goal, self.done_cb, self.active_cb, self.feedback_cb) 
        else:
            rospy.loginfo("Final goal pose reached!")
            rospy.signal_shutdown("Final goal pose reached!")
            return

	def ros_move(self):
        
		# Send a goal
		self.goal_sent = True
		goal = MoveBaseGoal()
		goal.target_pose.header.frame_id = 'map'
		goal.target_pose.header.stamp = rospy.Time.now()

		goal.target_pose.pose = pose_seq[goal_cnt]

		# Start moving
		rospy.loginfo("Sending goal location ...")
		self.move.send_goal(pose_seq[self.goal_cnt], self.next)

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
	    GoToPose()

	except rospy.ROSInterruptException:
		rospy.loginfo("Quitting")

