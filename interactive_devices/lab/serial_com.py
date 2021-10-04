import serial
import sys
import pygame

# Initialize PyGame
pygame.init()

# Button Variables

## Button string indexes
JOYSTICK_X_IND = 0
JOYSTICK_Y_IND = 1
JOYSTICK_SW_IND = 2
TOGGLE_IND = 3
PUSH_BUTTON_IND = 4

## Joystick min/max for y and x
JOY_MAX = 512
JOY_MIN = -512
JOY_ERROR_RANGE = 75 # joystick tends to hover around these numbers at rest

# ESP32 Variables
port = '/dev/ttyUSB0'
baudrate = 115200
ser = serial.Serial(port,baudrate,timeout=0.001)

# PyGame Variables

guitar_sound = pygame.mixer.Sound("../music/334_sound.wav")

pause = False

def pause_music():
    global pause
    pygame.mixer.music.pause()
    pause = True

def unpause():
    global pause
    pygame.mixer.music.unpause()
    pause = False

def pygame_main():
    pygame.mixer.Sound.play(guitar_sound)
    
    # Set initial volume at less than max to leave wiggle room
    guitar_sound.set_volume(0.5)

def push_button_ctl(push_button_pos):
    global pause

    if push_button_pos:
        print("PLAY")
    else:
        pygame_main()
        if pause:
            unpause()
        else:
            pause_music()
        print("PAUSE")

def joystick_ctl(joy_x, joy_y, joy_sw):
    # Adjust volume using Joy X
    if joy_x > JOY_ERROR_RANGE or joy_x < (0 - JOY_ERROR_RANGE):
        curr_volume = guitar_sound.get_volume()
        map_joy = joy_x / JOY_MAX
        guitar_sound.set_volume(map_joy * curr_volume)
        print(map_joy)
        print(curr_volume)





while True:
    data = ser.read(1)
    data += ser.read(ser.inWaiting())
    data_str = str(data.decode('utf-8'))

    current_button_positions = data_str.split(",")
    
    if len(current_button_positions) == 5:
        joystick_x_pos = int(current_button_positions[JOYSTICK_X_IND])
        
        joystick_y_pos = int(current_button_positions[JOYSTICK_Y_IND])
        
        joystick_sw_pos = int(current_button_positions[JOYSTICK_SW_IND])

        joystick_ctl(joystick_x_pos, joystick_y_pos, joystick_sw_pos)
        
        toggle_pos = int(current_button_positions[TOGGLE_IND])
        
        push_button_pos = int(current_button_positions[PUSH_BUTTON_IND])
        push_button_ctl(push_button_pos)
    
        print(joystick_x_pos, joystick_y_pos, joystick_sw_pos, toggle_pos, push_button_pos)
