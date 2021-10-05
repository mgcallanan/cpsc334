import serial
import sys
import pygame

pygame.init()

# Button Variables

push_button_count = 0
toggle_off = True

## Button string indexes
JOYSTICK_X_IND = 0
JOYSTICK_Y_IND = 1
JOYSTICK_SW_IND = 2
TOGGLE_IND = 3
PUSH_BUTTON_IND = 4

## Joystick min/max for y and x
JOY_MAX = 512
JOY_MIN = -512
JOY_ERROR_RANGE = 100 # joystick tends to hover around these numbers at rest

# ESP32 Variables
port = '/dev/ttyUSB0'
baudrate = 115200
ser = serial.Serial(port,baudrate,timeout=0.001)

# PyGame Variables
initial_volume = 0.5
ambient_street_noise = pygame.mixer.Sound("./music/ambient_street_noise.wav")
ambient_street_noise.set_volume(0.5)
engine_rev = pygame.mixer.Sound("./music/engine_rev_1.wav")
engine_rev.set_volume(0.5)
siren = pygame.mixer.Sound("./music/siren_1.wav")
siren.set_volume(0.5)

pause = False

def push_button_ctl(push_button_pos):
    global pause
    global push_button_count

    push_button_count += push_button_pos

    if push_button_count >= 20 and not toggle_off:
        print("OKay playing engine rev")
        engine_rev.play()
    elif push_button_count >= 40 and not toggle_off:
        print("okay playing siren")
        siren.play()
    elif push_button_count >= 60 and not toggle_off:
        print("play driver's license")
        siren.play()

def joystick_ctl(joy_x, joy_y, joy_sw):
    # Adjust volume using Joy X
    if joy_x > JOY_ERROR_RANGE:
        curr_volume = ambient_street_noise.get_volume()
        map_joy = joy_x / JOY_MAX
        map_joy = map_joy if map_joy > 0 else map_joy * -1
        ambient_street_noise.set_volume(map_joy )
        print(map_joy)
        print(curr_volume)
    elif joy_x < (0 - JOY_ERROR_RANGE):

# Function that runs based on toggle switch position
def toggle_ctl(tog_pos):
    global toggle_off
    if tog_pos == 1:
        print("tog would e playing")
        toggle_off = False
        ambient_street_noise.play()
    else:
        toggle_off = True
        pygame.mixer.stop()




# Initialize PyGame
# pygame.init()
pygame.mixer.init(40000, -16, 4, 1024)

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

        toggle_ctl(toggle_pos)
        
        push_button_pos = int(current_button_positions[PUSH_BUTTON_IND])
        push_button_ctl(push_button_pos)
    
        print(joystick_x_pos, joystick_y_pos, joystick_sw_pos, toggle_pos, push_button_pos, push_button_count)
