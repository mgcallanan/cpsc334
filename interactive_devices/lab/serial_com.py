import serial
import sys
import pygame

# Button Variables
JOYSTICK_X_IND = 0
JOYSTICK_Y_IND = 1
JOYSTICK_SW_IND = 2
TOGGLE_IND = 3
PUSH_BUTTON_IND = 4

# ESP32 Variables
port = '/dev/ttyUSB0'
baudrate = 115200
ser = serial.Serial(port,baudrate,timeout=0.001)

# PyGame Variables
pause = False

def pause():
    pygame.mixer.music.pause()

def unpause():
    global pause
    pygame.mixer.music.unpause()
    pause = False


def push_button_ctl(push_button_pos):



pygame.init()

while True:
    data = ser.read(1)
    data += ser.read(ser.inWaiting())
    data_str = str(data.decode('utf-8'))

    current_button_positions = data_str.split(",")
    
    if len(current_button_positions) == 5:
        joystick_x_pos = current_button_positions[JOYSTICK_X_IND]
        joystick_y_pos = current_button_positions[JOYSTICK_Y_IND]
        joystick_sw_pos = current_button_positions[JOYSTICK_SW_IND]
        toggle_pos = current_button_positions[TOGGLE_IND]
        push_button_pos = current_button_positions[PUSH_BUTTON_IND]
    
        print(joystick_x_pos, joystick_y_pos, joystick_sw_pos, toggle_pos, push_button_pos)
