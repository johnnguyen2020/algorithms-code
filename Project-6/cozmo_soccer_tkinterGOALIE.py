#John Nguyen and Ray Trebicka
#Taskin Padir
#Cozmo Final Project
#Nicolas Binford
#
# This version of the program uses tkinter instead of imshow to show images
#
# Uses the following programs as a reference:
# Cozmotography - Edge Detection
# https://github.com/cozplay/cozplay-demos/tree/master/cozmotography-edge-detection
# Adrian Rosebrock - Ball Tracking with OpenCV
# https://www.pyimagesearch.com/2015/09/14/ball-tracking-with-opencv/
#
#Cozmo Goalie FSM localizes ball -> rotates(x) --> go_foward(y) --> go_backward(y) --> rotate_start_position(-x) --> localizes ball
#             x degrees is either -75, 0, 75 degrees and y distance is 350 mm 

import os
import time
import cv2
import numpy
import PIL.Image
import PIL.ImageFont
import PIL.ImageTk
import tkinter
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

        self.hypotnuse = 350 #hypotnuse in mm
        self.test = False    #FSM condition indicate rotation action completed
        self.test2 = False   #FSM condtion indicate move foward action completed
        self.test3 = False   #FSM condition indicate ball is on right side
        self.test4 = False   #FSM condition indicate ball is on left side
        

        cozmo.connect(self.run)

    # Finds the object on the camera and returns its centroid (x, y)
    def detect_object(self, current_frame):
        # BGR range for orange
        color_lower = (0, 100, 230)
        color_upper = (130, 170, 255)

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
        if centroid is not None:
            # Get x-coordinate of centroid
            x_direction = centroid[0]
       
            # If ball is in the middle of image and ball on Right
            if x_direction >= self.right_of_screen and self.test == False:
                try:
                    self._robot.turn_in_place(degrees(-75))
                    print('Right')
                    self.test = True
                    self.test3 = True
                except RobotBusy:
                    pass
            
            # If ball is in the middle of image and ball on Left
            elif x_direction <= self.left_of_screen and self.test == False:
                try:
                    self._robot.turn_in_place(degrees(75))                   
                    print('Left')
                    self.test = True
                    self.test4 = True
                    #print('4')
                    #print(self.test)
                except RobotBusy:
                    pass
                
##            else:                
##                try:
##                    self._robot.drive_straight(distance_mm(self.hypotnuse), speed_mmps(100))
##                    self.test2 = True
##                    print('1')
##                except RobotBusy:
##                    pass
            
        #Move foward action
        if self.test == True:
            try:
                self._robot.drive_straight(distance_mm(self.hypotnuse), speed_mmps(300))
                self.test = False
                self.test2 = True
                print('strightFoward')
            except RobotBusy:
                pass

        #Move backward/return to Goal
        if self.test2 == True:
            try:
                self._robot.drive_straight(distance_mm(-self.hypotnuse), speed_mmps(300))
                self.test = False
                self.test2 = False
                print('straightBack')
            except RobotBusy:
                pass

        #Rotate to start position
        if self.test3 == True:
            try:
                self._robot.turn_in_place(degrees(75))
                self.test3 = False
                print('RotateLeft2Start')
            except RobotBusy:
                pass

        #Rotate to start position
        if self.test4 == True:
            try:
                self._robot.turn_in_place(degrees(-75))
                self.test4 = False
                print('RotateRight2Start')
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

