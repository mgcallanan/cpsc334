# Module 6: Mesh Network Robot Ghost

This module was done as a part of a class project, with this installation being created as a partner project with [Sophia DeVito](https://github.com/devitos-yale).

All code and other files relating to this project can be found in this repository.

## Overview

The goal of this project was to create a kinetic sculpture installation in AKW (the computer science department building at Yale University) that would aid in guiding visitors between locations in our "AI takeover" exhibit. A stairwell at the back of the building had a large shaft that provided the perfect opportunity to raise and lower a dismembered robot head (spooky AI, remember!) to entice visitors to move to the next station of the exhibit.

We realized this vision using a stepper motor, lots of fishing line, and two ESP-32s!

## Hardware

- 1 x 28BYJ-48 - 5V Stepper Motor
- 2 x ESP32 (that have ESP-Now enabled)
- 1 x 12 V power cable

## Software

- Arduino
  - Stepper.h library
  - esp-now.h library
- SuperCollider
- Python
  - OSC library
  - PySerial library

## How to Run

1. Upload the [`wifi_motor_esp`](https://github.com/mgcallanan/cpsc334/blob/master/mesh/wifi_motor_esp/wifi_motor_esp.ino) code to the ESP that will be running the stepper motor.
2. Upload the [`ghost_esp`](https://github.com/mgcallanan/cpsc334/blob/master/mesh/ghost_esp/ghost_esp.ino) code to the ESP that is attached to the robot head.
3. Upload the [`remote`](https://github.com/mgcallanan/cpsc334/blob/master/mesh/remote/remote.ino) code to the ESP that is controlling the remote.
4. Begin running [`motor_read.py`](https://github.com/mgcallanan/cpsc334/blob/master/mesh/motor_read.py) in your terminal (and ensure your motor ESP32 is plugged into the correct [`USB dev port`](https://github.com/mgcallanan/cpsc334/blob/bbfd3ff1fd0f4cd346d80616b0bbf67ab946d5ef/mesh/motor_read.py#L6))
5. Boot and run [`ghost_tone.scd`](https://github.com/mgcallanan/cpsc334/blob/master/mesh/ghost_tone.scd) in SuperCollider and the RSSI pitches should begin playing!
