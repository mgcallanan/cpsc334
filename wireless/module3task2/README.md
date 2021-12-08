# Module 3: Wireless Blindfolded Stop and Seek

The code in this repository is for the installation art module as a part of CPSC 334. This project was done as a partner project with [Maansi Dasari](https://github.com/maansi-dasari).

## Overview

For this installation art project, we wanted to make an interactive experience for prospective visitors that would entertain their sense of play but would also test their intuition with their game partner. The inspiration from this game is drawn from a multitude of childhood playground games, but the combination is fortified with the use of wireless enclosures that are durable and transportable.

To give a brief summary of the rules of Blindfolded Stop and Seek, there are two players who each hold a Stop Light Enclosure. They start on opposite ends of the room, and their eyes remain closed for the duration of the game. The goal is to navigate towards each other and touch the enclosures to each other to "win" the game. In order to move, they must hit their enclosure, and wait for a "Player X" signal. They have three seconds to move, as indicated by an auditory countdown. They can either hit to move again, or the opposite player can hit their enclosure to move. If the players hit their boxes at the same time, they lose the game. There is an ongoing pitch in the background that gets higher as players get closer and lower as they move further apart. It is a test of intuition and navigational skills between two people.

## Hardware

This kind of wireless, interactive game necessitates the use of multiple sensors between two mircocontrollers (in this case, ESP32s) and a computer (laptop in our usage).

### Piezoelectric Sensors

Piezoelectric sensors provide meaningful data, especially in an activity-determined environment/module, that indicates vibration across its surface. This can be caused by intense movement, knocking the sensor and/or enclosure it's held in, and other sorts of activity that would cause a vibration to the enclosure.

In our system, each enclosure is equipped with a piezoelectric sensors that sends its vibrational data to the computer via the ESP32's WiFI functionality. It provides the data we need to sense whether a player has hit their enclosure to indicate their want to try to move towards their partner.

### Distance between ESP32s (WiFi)

Another important aspect of the system is the ability to measure (in not the most accurate way) the distance between the two enclosures. We decided to use the ESP32s themselves and gather data about the WiFi strength between the two of them.

By configuring one as an [Access Point](https://www.linksys.com/us/r/resource-center/what-is-a-wifi-access-point/#:~:text=An%20access%20point%20is%20a,signal%20to%20a%20designated%20area.) (essentially a WiFi hotspot), and setting up the other to connect directly to the Access Point as a [Station](<https://en.wikipedia.org/wiki/Station_(networking)#:~:text=In%20IEEE%20802.11%20(Wi%2DFi,be%20fixed%2C%20mobile%20or%20portable.>), we can get the RSSI (Received Signal Strength Indicator) as a measure of distance. The farther apart the ESP32s are, the larger the magnitude of the RSSI.

In our system, [`maansi_board`](https://github.com/mgcallanan/cpsc334/tree/master/wireless/module3task2/maansi_board) is being used as the Station and [`mary_board`](https://github.com/mgcallanan/cpsc334/tree/master/wireless/module3task2/mary_board) is being used as the Access Point.

### Portable USB Chargers

In order to power the two ESP32s, we used two portable USB chargers that provided 5V output into the ESP32 and connected via micro-USB to USB cables. The ESP32s immediately run their programs on boot (a.k.a. upon being plugged in).

### Computer (Laptop)

In order to parse and denoise the raw data received from the ESP32s, we have to use a computer that runs Python and SuperCollider to produce and adjust sounds.

The Access Point ESP32 connects to the laptop via UDP over WiFI and sends its piezoelectric data, along with the piezoelectrid and RSSI data from the Station ESP32.

The computer receives this data and produces sound. We use a laptop in this case, but you could also use a Raspberry Pi.

## Software

This project would not be possible without the use of multiple powerful pieces of software, and each hardware component is responsible for running a different aspect of the software. This makes for a very intricate, but rewarding, system design.

### Arduino

The code that is used to collect the piezoelectric sensor and RSSI data is found in the [`maansi_board`](https://github.com/mgcallanan/cpsc334/tree/master/wireless/module3task2/maansi_board) and [`mary_board`](https://github.com/mgcallanan/cpsc334/tree/master/wireless/module3task2/mary_board) directories. In order to compile and upload this code, you have to download the [Arduino IDE](https://www.arduino.cc/en/software).

### Python

The python code that receives and processes the WiFi messages from the ESP32s and communicated OSC messages to Supercollider is contained in `socket_read.py`. To run it, be sure to update the IP address in the code to match the ip address of your laptop, and then run `python3 socket_read.py`.

### SuperCollider
The Supercollider code that receives OSC messages from python and plays the game audio is found in `emit_sounds.scd`. To run the Supercollider code for the first time, press Cmd + Enter while highlighting the line `s.boot` to start the server. After that, place your cursor anywhere in the remaining block of code and again press Cmd + Enter. Make sure that the ESP32s are both plugged in and that the python code is running, and the game should be ready to play!

## Demo
Watch the video demo of the game being played here: https://www.youtube.com/watch?v=ZMSY8BEKJMI
