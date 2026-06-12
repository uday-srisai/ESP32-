# ESP32 Line Follower Robot

## Overview

This project is an autonomous Line Follower Robot built using an ESP32 microcontroller, L298N motor driver, and three IR sensors. The robot detects a black line on a white surface and follows the path automatically by controlling two DC motors.

## Components Used

- ESP32 Development Board
- L298N Motor Driver
- 3 IR Sensors
- 2 DC BO Motors
- Robot Chassis
- Wheels
- Battery Pack
- DC-DC Buck Converter
- Power Switch
- Connecting Wires

## Features

- Real-time line detection using IR sensors
- Autonomous path following
- PWM-based motor speed control using ESP32 LEDC
- Left and right path correction
- Simple and efficient control logic
- Tested on straight paths and curved tracks

## Working Principle

The robot uses three IR sensors:

- Left Sensor (L)
- Center Sensor (C)
- Right Sensor (R)

Sensor logic:

| L | C | R | Action |
|---|---|---|--------|
| 0 | 1 | 0 | Forward |
| 1 | 0 | 0 | Left Turn |
| 1 | 1 | 0 | Left Turn |
| 0 | 0 | 1 | Right Turn |
| 0 | 1 | 1 | Right Turn |
| 1 | 1 | 1 | Forward |
| 0 | 0 | 0 | Stop |


## Author
LinkedIn:
www.linkedin.com/in/udaysrisai
