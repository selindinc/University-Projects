#!/usr/bin/env python

import rospy
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from tf import transformations
 
import math

state_ = 0
# 0 = nothing, 1 = turn left, 2 = follow wall, 3 = turn right, 4 = go back, 5 reverse find wall

regions_ = {
    'right': 0,
    'fright': 0,
    'front': 0,
    'fleft': 0,
    'left': 0,
}

def clbk_laser(msg):
    global regions_
    regions_ = {
        'right':  min(min(msg.ranges[0:143]), 10),
        'fright': min(min(msg.ranges[144:287]), 10),
        'front':  min(min(msg.ranges[288:431]), 10),
        'fleft':  min(min(msg.ranges[432:575]), 10),
        'left':   min(min(msg.ranges[576:713]), 10),
    }
    
    take_action()

def change_state(state):
    global state_    
    if state is not state_:
        print ('Wall follower - [%s]' % (state))
        state_ = state

def take_action():
    global regions_
    regions = regions_
    msg = Twist()
    linear_x = 0
    angular_z = 0
    
    d = 1.5
    d2 = 1
    if regions['fright'] > d and regions['front'] > d and regions['fleft'] > d:
        #state_description = 'case 1 - nothing'
        change_state(0)
    elif math.isnan(regions['fright']) and regions['front'] > d and regions['fleft'] > d:
        #state_description = 'case 1 - nothing'
        change_state(0)
    elif regions['fright'] > d and math.isnan(regions['front']) and regions['fleft'] > d:
        #state_description = 'case 1 - nothing'
        change_state(0)
    elif regions['fright'] > d and regions['front'] > d and math.isnan(regions['fleft']):
        #state_description = 'case 1 - nothing'
        change_state(0)
        
    elif regions['fright'] < d and regions['front'] > d and regions['fleft'] > d:
        #state_description = 'case 2 - fright'
        if regions['fright'] < d2:
            change_state(1)
        else:
            change_state(2)
    elif regions['fright'] < d and math.isnan(regions['front']) and regions['fleft'] > d:
        #state_description = 'case 2 - fright'
        if regions['fright'] < d2:
            change_state(1)
        else:
            change_state(2)
    elif regions['fright'] < d and regions['front'] > d and math.isnan(regions['fleft']):
        #state_description = 'case 2 - fright'
        if regions['fright'] < d2:
            change_state(1)
        else:
            change_state(2)
        
        
    elif regions['fright'] > d and regions['front'] < d and regions['fleft'] > d:
        #state_description = 'case 3 - front'
        change_state(1)
    elif math.isnan(regions['fright']) and regions['front'] < d and regions['fleft'] > d:
        #state_description = 'case 3 - front'
        change_state(1)
    elif regions['fright'] > d and regions['front'] < d and math.isnan(regions['fleft']):
        #state_description = 'case 3 - front'
        change_state(1)
        
    elif regions['fright'] > d and regions['front'] > d and regions['fleft'] < d:
        #state_description = 'case 4 - fleft'
        change_state(0)
    elif math.isnan(regions['fright']) and regions['front'] > d and regions['fleft'] < d:
        #state_description = 'case 4 - fleft'
        change_state(0)
    elif regions['fright'] > d and math.isnan(regions['front']) and regions['fleft'] < d:
        #state_description = 'case 4 - fleft'
        change_state(0)
        
    elif regions['fright'] < d and regions['front'] < d and regions['fleft'] > d:
        #state_description = 'case 5 - front and fright'
        change_state(1)
    elif math.isnan(regions['fright']) and regions['front'] < d and regions['fleft'] > d:
        #state_description = 'case 5 - front and fright'
        change_state(1)
    elif regions['fright'] < d and math.isnan(regions['front']) and regions['fleft'] > d:
        #state_description = 'case 5 - front and fright'
        change_state(1)
    elif regions['fright'] < d and regions['front'] < d and math.isnan(regions['fleft']):#geri?
        #state_description = 'case 5 - front and fright'
        change_state(1)
        
    elif regions['fright'] > d and regions['front'] < d and regions['fleft'] < d:
        #state_description = 'case 6 - front and fleft'
        change_state(0)
    elif math.isnan(regions['fright']) and regions['front'] < d and regions['fleft'] < d:
        #state_description = 'case 6 - front and fleft'
        change_state(0)
    elif regions['fright'] > d and math.isnan(regions['front']) and regions['fleft'] < d:#sadece sag?
        #state_description = 'case 6 - front and fleft'
        change_state(0)
    elif regions['fright'] > d and regions['front'] < d and math.isnan(regions['fleft']):#sadece sag!
        #state_description = 'case 6 - front and fleft'
        change_state(3)
        
        
    elif regions['fright'] < d and regions['front'] > d and regions['fleft'] < d:
        #state_description = 'case 7 - fleft and fright'
        if regions['fright'] < d2:
            change_state(1)
        else:
            change_state(2)
    elif math.isnan(regions['fright']) and regions['front'] > d and regions['fleft'] < d:#saga carmpis olabilirim
        #state_description = 'case 7 - fleft and fright'
        if regions['fright'] < d2:
            change_state(1)
        else:
            change_state(2)
    elif regions['fright'] < d and math.isnan(regions['front']) and regions['fleft'] < d:
        #state_description = 'case 7 - fleft and fright'
        if regions['fright'] < d2:
            change_state(1)
        else:
            change_state(2)
    elif regions['fright'] < d and regions['front'] > d and math.isnan(regions['fleft']):
        #state_description = 'case 7 - fleft and fright'
        if regions['fright'] < d2:
            change_state(1)
        else:
            change_state(2)
        
    elif regions['fright'] < d and regions['front'] < d and regions['fleft'] < d:
        #state_description = 'case 8 - front and fleft and fright'
        if regions['front']<d2:
            change_state(1)
        else:
            if regions['fright'] < d2:
                change_state(1)
            else:
                change_state(2)
    elif math.isnan(regions['fright']) and regions['front'] < d and regions['fleft'] < d:
        #state_description = 'case 8 - front and fleft and fright'
        if regions['front']<d2:
            change_state(1)
        else:
            if regions['fright'] < d2:
                change_state(1)
            else:
                change_state(2)
    elif regions['fright'] < d and math.isnan(regions['front']) and regions['fleft'] < d:
        #state_description = 'case 8 - front and fleft and fright'
        if regions['front']<d2:
            change_state(1)
        else:
            if regions['fright'] < d2:
                change_state(1)
            else:
                change_state(2)
    elif regions['fright'] < d and regions['front'] < d and math.isnan(regions['fleft']):
        #state_description = 'case 8 - front and fleft and fright'
        if regions['front']<d2:
            change_state(1)
        else:
            if regions['fright'] < d2:
                change_state(1)
            else:
                change_state(2)
            
    elif math.isnan(regions['fright']) and math.isnan(regions['front']) and regions['fleft'] > d:
        #state_description = 'case 9 - front and fright'
        if math.isnan(regions['right']):
            change_state(1)
        else:
            change_state(0)
        print("fright - front +")
    
    elif math.isnan(regions['fright']) and math.isnan(regions['front']) and regions['fleft'] < d:#geri(?)
        #state_description = 'case 9 - front and fright'
        print('4')     
        print("fright - front -")
    
    elif regions['fright'] > d and math.isnan(regions['front']) and math.isnan(regions['fleft']):
        #sadece sag
        change_state(0)
        print("fleft - front +")
    
    elif regions['fright'] < d and math.isnan(regions['front']) and math.isnan(regions['fleft']):
        #sadece sag
        if regions['fright'] < d2:
            change_state(0)
        else:
            change_state(2)
        print("fleft - front -")
    
    elif math.isnan(regions['fright']) and regions['front'] > d and math.isnan(regions['fleft']):
        if regions['fright'] < d2:
            change_state(1)
        else:
            change_state(2)       
        print("fright - fleft +")
    
    elif math.isnan(regions['fright']) and regions['front'] < d and math.isnan(regions['fleft']):
        #sadece geri
        if regions['fright'] < d2:
            change_state(1)
        else:
            change_state(2)
        print("fright - fleft -")
    
    else:
        #state_description = 'case 9 - unknown'
        rospy.loginfo(regions)

	
	
def find_wall():
    msg = Twist()
    msg.linear.x = 0.4
    msg.angular.z = -0.2
    return msg
 
def turn_left():
    msg = Twist()
    msg.linear.x = 0
    msg.angular.z = 0.5
    return msg
 
def follow_the_wall():
    global regions_
    msg = Twist()
    msg.linear.x = 0.2
    msg.angular.z = 0
    return msg

def turn_right():
    msg = Twist()
    msg.linear.x = 0
    msg.angular.z = -0.5
    return msg

def go_back():
    msg = Twist()
    msg.linear.x = -0.5
    msg.angular.z = 0
    return msg
    
def reverse_find_wall():
    msg = Twist()
    msg.linear.x = -0.1
    msg.angular.z = -0.2
    return msg

def main():
    global pub_, state_
    
    rospy.init_node('reading_laser',anonymous=True)
    
    pub_ = rospy.Publisher('/cmd_vel_mux/input/navi', Twist, queue_size=10)
    
    sub = rospy.Subscriber('/scan', LaserScan, clbk_laser)
    
    rate = rospy.Rate(10)
    print("a")

    while not rospy.is_shutdown():
        msg = Twist()
        if state_ == 0:
            msg = find_wall()
        elif state_ == 1:
            msg = turn_left()
        elif state_ == 2:
            msg = follow_the_wall()
            pass
        elif state_ == 3:
            msg = turn_right()
        elif state_ == 4:
            msg = go_back()
        elif state_ == 5:
            reverse_find_wall()

        else:
            rospy.logerr('Unknown state!')
        
        pub_.publish(msg)
        
        rate.sleep()
 
if __name__ == '__main__':
    main()
