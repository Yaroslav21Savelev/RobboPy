# RobboPy
-----------
ROBBO module for python
------------------------
A Python module for programming Robbo platform via Raspberry PI

Adding
-------------
First of all install UART on your Raspberry PI and configure it
------------
Just copy file robbo.py to the same directory where your code is located an type
-------------
import robbo
-------------
Functions
---------------
robbo.motors(motorNumber, motorDirection, speed)
-
This command lets you access to built-in engines
-
robbo.rotate(direction, angle)
-
This command lets you rotate on a certain angle. direction a/d, angle 90/180/270
----------

The first argument is the number of engine 0/1
------------
The second one is direction 0/1
-------------
The third is speed 0-255
-----------------

robbo.flash(pad, state)
------------
This command lets you access to a led
-
The first arguments is the pad number 1-5
-
The second one is state(on\off) 0/1
-
robbo.aPadRead/dPadRead/sharp/ultrasonic/distance(pad)
-
Theese commands let you access to any sensor
-
You just have to type "pad" argument 1-5
-
dPadRead - digital mode of line sensor and button
-
aPadRead - analog mode of line sensor and brightness sensor
-
sharp - infrared Sharp distance sensor
-
ultrasonic - ultrasonic distance sensor
-
distance - standart distance sensor
================================================================================
License
-
This project is under GNU general public license
-
For more information please see LICENSE file
-
