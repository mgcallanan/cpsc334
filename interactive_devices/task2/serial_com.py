import serial
import sys
import pygame

pygame.init()
pygame.mixer.init(49000, -16, 1, 1024)
# Button Variables

joy_sw_count = 0
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
ambient_street_noise.set_volume(initial_volume)
street_noise_playing = False

engine_rev = pygame.mixer.Sound("./music/engine_rev_1.wav")
engine_rev.set_volume(initial_volume)
engine_rev_playing = False

siren = pygame.mixer.Sound("./music/siren_1.wav")
siren.set_volume(initial_volume)
siren_playing = False

drivers_license = pygame.mixer.Sound("./music/drivers_license.wav")
drivers_license.set_volume(initial_volume)
dl_playing = False

honk = pygame.mixer.Sound("./music/honk.wav")
honk.set_volume(initial_volume)
honk_playing = False


pause = False

def push_button_ctl(push_button_pos):
    global pause
    global joy_sw_count

    global engine_rev_playing
    global dl_playing
    global siren_playing 

    # Play honking noise when push button pressed
    if push_button_pos:
        honk.play()

def joystick_ctl(joy_x, joy_y, joy_sw):

    global joy_sw_count
    global engine_rev_playing
    global dl_playing
    global siren_playing 

    # Adjust volume using Joy X
    curr_volume = ambient_street_noise.get_volume()

    # Map Joy X into volume range of [0, 1.0]
    new_volume = 0 + ((1.0 - 0) / (JOY_MAX - JOY_MIN)) * (joy_x - JOY_MIN)
    
    ambient_street_noise.set_volume(new_volume)
    siren.set_volume(new_volume)
    engine_rev.set_volume(new_volume)
    drivers_license.set_volume(new_volume)
    honk.set_volume(new_volume)

    # Reset push button count if it gets too high
    if joy_sw_count >= 80:
        joy_sw_count = 0

    if not joy_sw:
        joy_sw_count += 1

    # Cycle through the three feature sounds when joystick is pressed and held for 2 seconds
    if joy_sw_count >= 60 and not toggle_off:
        print("play driver's license")
        if not dl_playing:
            drivers_license.play()            
            dl_playing = True
    elif joy_sw_count >= 40 and not toggle_off:
        print("okay playing siren")
        if not siren_playing:
            siren.play()
            siren_playing = True
    elif joy_sw_count >= 20 and not toggle_off:
        print("OKay playing engine rev")
        if not engine_rev_playing:
            engine_rev.play()
            engine_rev_playing = True

# Function that runs based on toggle switch position
def toggle_ctl(tog_pos):
    global toggle_off
    global street_noise_playing
    global engine_rev_playing
    global dl_playing
    global siren_playing 
    global honk_playing

    # If the toggle is on, then play sounds, otherwise, don't.
    if tog_pos == 1:
        print("tog would e playing")
        toggle_off = False
        if not street_noise_playing:
            ambient_street_noise.play(-1)
            street_noise_playing = True
    else:
        toggle_off = True
        pygame.mixer.stop()
        street_noise_playing = False
        engine_rev_playing = False
        dl_playing = False
        siren_playing = False
        honk_playing = False




while True:
    # Read data from serial
    data = ser.read(1)
    data += ser.read(ser.inWaiting())
    data_str = str(data.decode('utf-8'))

    # Split ESP32 numbers into a string array
    current_button_positions = data_str.split(",")
    
    if len(current_button_positions) == 5:
        joystick_x_pos = int(current_button_positions[JOYSTICK_X_IND])
        
        joystick_y_pos = int(current_button_positions[JOYSTICK_Y_IND])
        
        joystick_sw_pos = int(current_button_positions[JOYSTICK_SW_IND])

        # Pass joystick positions into joystick callback function
        joystick_ctl(joystick_x_pos, joystick_y_pos, joystick_sw_pos)
        
        toggle_pos = int(current_button_positions[TOGGLE_IND])

        # Pass toggle position into toggle callback function
        toggle_ctl(toggle_pos)
        
        push_button_pos = int(current_button_positions[PUSH_BUTTON_IND])

        # Pass push button position into toggle callback function
        push_button_ctl(push_button_pos)
    
        print(joystick_x_pos, joystick_y_pos, joystick_sw_pos, toggle_pos, push_button_pos, joy_sw_count)
