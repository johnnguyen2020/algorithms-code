# Nicolas Binford
#
# This version of the program uses tkinter instead of imshow to show images
#
# Uses the following programs as a reference:
# Cozmotography - Edge Detection
# https://github.com/cozplay/cozplay-demos/tree/master/cozmotography-edge-detection
# Adrian Rosebrock - Ball Tracking with OpenCV
# https://www.pyimagesearch.com/2015/09/14/ball-tracking-with-opencv/

import os
import cv2
import numpy
import PIL.Image
import PIL.ImageFont
import PIL.ImageTk
import tkinter
import time
import asyncio
import cozmo
from cozmo.util import degrees, distance_mm, speed_mmps
from cozmo.exceptions import RobotBusy
from random import randint

class CozmoSoccer:
    def __init__(self):
        self._robot = None

        # Initialize variables for tkinter
        self._tk_root = 0
        self._tk_label_output = 0

        self.min_object_radius = 10
        # Image size is 320x240 with tkinter, might want to adjust these
        self.left_of_screen = 75
        self.right_of_screen = 225

        self.first_kick = False # Keeps track of robot being in its initial kick state
        self.search_for_ball = False # Keeps track of robot being in its searching for ball state
        self.go_to_ball = False # Keeps track of robot being in its moving to ball state
        self.setup_turn = False
        self.find_goal = False # Keeps track of robot being in its goal finding state
        self.orange_on = True # Keeps track of what color robot is looking for (orange or black)
        self.goal_radius = 30 # Radius threshold for objects ball is tracking, used to trigger specific actions
        self.global_radius = 0 # Stores the current radius of an object being track, initialized at 0
        self.turn_angle = 0 # Keeps track of the current turn angle when searching for ball
        self.left_turn = False # Keeps track of robot being in a left turn state (used when moving towards ball)
        self.go_straight = False # Keeps track of robot being in a driving straight state (used when moving towards ball)
        self.first_angle = True # Keeps track of robot being in state where it adjusts to kick the ball initially at an angle
        self.rand_angle = randint(-10, 10) # Random angle calculation for initial kick

        cozmo.connect(self.run)

    # Finds the object on the camera and returns its centroid (x, y)
    def detect_object(self, current_frame):
        # BGR range for orange
        if self.orange_on:
            color_lower = (0, 100, 230)
            color_upper = (130, 170, 255)
        # BGR range for black (color of goalposts)
        if self.orange_on == False:
            #color_lower = (0, 0, 0)
            #color_upper = (40, 40, 40)
            #yellow
            color_lower = (0, 204, 204)
            color_upper = (153, 255, 255)

        # Localize the object and remove imperfections
        mask = cv2.inRange(current_frame, color_lower, color_upper)
        mask = cv2.erode(mask, None, iterations=2)
        mask = cv2.dilate(mask, None, iterations=2)

        # Find contours in the object
        cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
            cv2.CHAIN_APPROX_SIMPLE)[-2]

        # If at least one contour was found
        if len(cnts) > 0:
            # Get the largest contour by area
            largest_contour = max(cnts, key=cv2.contourArea)

            # Calculate the centroid using the moments of the largest contour
            # Centroid is coordinates with 0, 0 being at the top left
            M = cv2.moments(largest_contour)
            centroid = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))

            # Calculate the minimum enclosing circle
            ((x, y), radius) = cv2.minEnclosingCircle(largest_contour)
            self.global_radius = radius

            # If the object is close enough, draw its centroid and enclosing circle
            # on the frame
            if radius > self.min_object_radius:
                cv2.circle(current_frame, (int(x), int(y)), int(radius),
                    (0, 255, 255), 2)
                cv2.circle(current_frame, centroid, 5, (0, 0, 255), -1)
                return centroid
            else:
                return None
    
    def follow_ball(self, centroid):
    	# If the first_angle state is true, the robot adjust the angle at which its kicking the ball
        if self.first_angle == True:
            try:
                print(self.rand_angle)
                self._robot.turn_in_place(degrees(self.rand_angle))
                self.first_kick = True
                self.first_angle = False
            except RobotBusy:
                pass
        
        # If the first_kick state is true, the robot drives forward at its top speed and kicks the ball.
        if self.first_kick == True:
            try:
                self._robot.drive_straight(distance_mm(200), speed_mmps(200), should_play_anim=False)
                self.first_kick = False
                time.sleep(1)
                print('firstkick')
                self.search_for_ball = True
            except RobotBusy:
                pass

		# If the search_for_ball state is true, the robot turns in place in increments of 20 degrees
		# looking for the orange ball
        if self.search_for_ball == True:
        	# If there is no centroid (the robot does not see the orange ball) the robot turns in 
        	# place in 20 degree increments looking for it.
            if centroid is None:
                try:
                    self._robot.turn_in_place(degrees(20))
                    # The turn angle is kept track of to later determine if the robot is turn right or left
                    self.turn_angle = self.turn_angle+20
                    print('searchforball')
                except RobotBusy:
                    pass
			
	    # If the centroid is present (the robot sees the orange ball), the robot will enter the 
	    # go_to_ball state
            if centroid is not None:
            	# If the mod of the angle turned by 360 is less than 180, the robot is turning left,
            	# otherwise, it is turning right. This information will be used in a future action.
                if (self.turn_angle % 360) <= 180:
                    self.left_turn = True
                self.search_for_ball = False
                self.go_to_ball = True
                print('foundball')
		
		# If the go_to_ball state is true, the robot will move towards the ball and position 
		# itself behind it so that it can kick it towards the goal.
        if self.go_to_ball == True:
            print('gotoball')
        	# If the centroid is present (the robot can see the orange ball) and the current radius
        	# is less than the radius threshold (meaning the ball is not close to the robot), the robot 
        	# moves toward the ball.
            if centroid is not None and self.global_radius < self.goal_radius:
                # Get x-coordinate of centroid
                x_direction = centroid[0]
                # If ball is to the left of image
                if x_direction <= self.left_of_screen:
                    try:
                        self._robot.turn_in_place(degrees(20))
                    except RobotBusy:
                        pass
                # If ball is in the middle of image
                elif x_direction <= self.right_of_screen:
                    try:
                        self._robot.drive_straight(distance_mm(30), speed_mmps(100), should_play_anim=False)
                    except RobotBusy:
                        pass
                # If ball is to the right of image
                else:                
                    try:
                        self._robot.turn_in_place(degrees(-20))
                    except RobotBusy:
                        pass
                print(self.global_radius)

	    # If the centroid is not present (the robot cannot see the orange ball), the robot
	    # will turn in place in 20 degree increments .
            if centroid is None:
                try:
                    self._robot.turn_in_place(degrees(20))
                    self.turn_angle = self.turn_angle+20
                    print('search for ball')
                except RobotBusy:
                    pass

            if self.global_radius >= self.goal_radius:
                self.go_to_ball = False
                self.setup_turn = True
			
	# If the centroid is present (the robot can see the orange ball) and the current radius
        # is greater than the radius threshold (meaning the ball is close to the robot), the robot 
        # turns left or right (depending on location) to position itself behind the ball.
        if self.setup_turn:
            # If turn_left is true, the robot knows it is to the left side of the goal and will turn 
            # left to move behind the ball.
            print(self.turn_angle)
            print(self.turn_angle % 360)
            if self.left_turn:
                try:
                    self._robot.turn_in_place(degrees(60))
                    self.setup_turn = False
                    self.go_straight = True
                    print('closetoball')
                    print(self.global_radius)
                    print('closetoball')
                except RobotBusy:
                    pass

	    # If turn_left is false, the robot knows it is to 
            # the right side of the goal and will turn right to move behind the ball. 
            if self.left_turn == False:
                try:
                    self._robot.turn_in_place(degrees(-60))
                    self.setup_turn = False
                    self.go_straight = True
                    print('closetoball')
                    print(self.global_radius)
                    print('closetoball')
                except RobotBusy:
                    pass
			
	    # Once the robot has turn, it enters the go_straight state, where it moves forward enough
	    # to get behind the ball and in a position to kick it.
        if self.go_straight:
            try:
                self._robot.drive_straight(distance_mm(100), speed_mmps(100), should_play_anim=False)
                # The robot will now switch the color it is looking for to black in order to search
                # for the cubes (goalposts). The next state is looking for the goalposts.
                self.orange_on = False
                self.go_straight = False
                self.go_to_ball = False
                self.find_goal = True
                print('setupkick')
                time.sleep(2)
                centroid = None
            except RobotBusy:
                pass

	# If the find_goal state is true, the robot will turn in 45 degree increments looking
	# for the black goalposts
        if self.find_goal == True:
            # If the there is no centroid (the robot cannot see the black goalposts), the robot
            # turns in 45 degree increments looking for the black goalposts.
            if centroid is None:
                try:
                    self._robot.turn_in_place(degrees(-45))
                    print('searchgoal')
                except RobotBusy:
                    pass
            
            # If the there is a centroid (the robot can see the black goalposts), the robot
            # enters the kicking state to kick the ball.
            if centroid is not None:
                try:
                    print('bbc')
                    # The robot will begin searching for the color orange again, as the ball is the 
                    # next object to be searched for.
                    self.orange_on = True
                    self.find_goal = False
                    self.first_kick = True
                except RobotBusy:
                    pass
                    
    def on_new_camera_image(self, event, *, image:cozmo.world.CameraImage, **kw):
        raw_image = image.raw_image

        # Convert PIL Image to OpenCV Image
        # See: http://stackoverflow.com/questions/14134892/convert-image-from-pil-to-opencv-format
        cv2_image = cv2.cvtColor(numpy.array(raw_image), cv2.COLOR_RGB2BGR)

        ball_center = self.detect_object(cv2_image)
        self.follow_ball(ball_center)

        # Convert modified OpenCV image back to PIL to display it
        final_image = PIL.Image.fromarray(cv2.cvtColor(cv2_image, cv2.COLOR_BGR2RGB))

        # Display image with tkinter
        display_image_output = PIL.ImageTk.PhotoImage(image=final_image)
        self._tk_label_output.imgtk = display_image_output
        self._tk_label_output.configure(image=display_image_output)
        self._tk_root.update()

    # async - basically, the whole program runs in one thread (needed for tkinter)
    # You don't have to worry about it
    async def set_up_cozmo(self, coz_conn):
        # set_event_loop allows the program to continuously process images
        asyncio.set_event_loop(coz_conn._loop)
        # await - goes along with async
        self._robot = await coz_conn.wait_for_robot()
        self._robot.camera.image_stream_enabled = True
        # Color camera is disabled by default, have to enable it
        self._robot.camera.color_image_enabled = True
        self._robot.add_event_handler(cozmo.world.EvtNewCameraImage, self.on_new_camera_image)
        self._robot.set_head_angle(cozmo.util.Angle(degrees=0))

    async def run(self, coz_conn):
        # Set up Cozmo
        await self.set_up_cozmo(coz_conn)

        # Set up tkinter so that the image can be displayed
        self._tk_root = tkinter.Tk()
        self._tk_label_output = tkinter.Label(self._tk_root)
        self._tk_label_output.pack()

        # Have to do ctrl+C to exit
        while True:
            await asyncio.sleep(0)


if __name__ == '__main__':
    CozmoSoccer()

