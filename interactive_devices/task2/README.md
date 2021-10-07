# Interactive Devices: Elm Street Soundsape

The code in this repository is for Module 2, Task 2: Interactive Devices.

## Overview

For my performable device, I opted to use the ESP32 in combination with the Raspberry Pi to create auditory output. My project produces sounds intended to replicate the sounds I hear every day living off of Elm Street in New Haven. It plays ambient street noise throughout its runtime, while alternating through sounds when the performer adjusts and presses certain buttons. More technical details can be found below.

## Hardware

### Circuiting: ESP32 & Raspberry Pi

The input buttons are all plugged into the ESP32 via GPIO, and the ESP32 is sendings signals to the Raspberry Pi via a USB 3.0 connection.

### Inputs: Joystick, Push Button, & Toggle

There are three inputs being used in connection with the ESP32. The joystick, which outputs its x, y, and switch value, provides analog output for Arduino to read.

The push button and toggle switch provide a 1/0 values if they are being pressed or not, and this output is read via digital out.

### Output: Bluetooth Audio

The sound from the device is being output via Bluetooth from the Raspberry Pi to a JBL Clip 3 Bluetooth speaker. This requires set-up using the `bluetoothctl` CLI tool that comes built into the Raspberry Pi. [Further instructions can be found here.](https://www.okdo.com/project/set-up-a-bluetooth-speaker-with-a-raspberry-pi/?ok_ts=1633319052097)

### Enclosure: Cardboard

The enclosure is in the shape of a car, given the streetscape theme of the audio. It was made by carving shapes out of a cardboard box and creating slits where the input buttons could rest. The decorative aspects of the box was done by (an extremely unprofessional's) artist handrawing abilities.

## Software

### Arduino

The code running on the ESP32 that receives the button inputs via the Serial monitor is written using `.ino` files. The Arduino code can be found in the `joystick/joystick.ino` file in this repository and requires installation of the [Arduino IDE](https://www.arduino.cc/en/software).

### Python

The Pi runs a Python script in order to parse incoming button inputs from the ESP32 and play sounds corresponding to the buttons being pressed. It parses the ESP32 messages using the `serial` library, and plays/adjusts sounds using the `pygame` library.
