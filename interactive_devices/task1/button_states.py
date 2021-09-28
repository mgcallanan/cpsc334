import RPi.GPIO as GPIO # Import Raspberry Pi GPIO library

PUSH_BUTTON_GPIO = 12
TOGGLE_SWITCH_GPIO = 4
JOYSTICK_SW_GPIO = 13
JOYSTICK_Y_GPIO = 6
JOYSTICK_X_GPIO = 5

push_count = 0
push_state = 0

toggle_count = 0
toggle_state = 0

joy_y = 0
joy_x = 0
joy_press = 0
joy_state = 0

def change_state(channel):
    global push_state
    global toggle_state
    global joy_state

    if channel == PUSH_BUTTON_GPIO:
        push_state = 1
        toggle_state = 0
        joy_state = 0
    elif channel == TOGGLE_SWITCH_GPIO:
        push_state = 0
        toggle_state = 1
        joy_state = 0
    elif channel == JOYSTICK_SW_GPIO or channel == JOYSTICK_Y_GPIO or channel == JOYSTICK_X_GPIO:
        push_state = 0
        toggle_state = 0
        joy_state = 1


def push_button_callback(channel):
    global push_count
    push_count += 1
    change_state(channel)

    print("Push button was pushed!" + str(push_count))

def toggle_switch_callback(channel):
    global toggle_count
    toggle_count += 1
    change_state(channel)

    print("Toggle button on!" + str(toggle_count))


def joystick_sw_switch_callback(channel):
    global joy_press
    joy_press += 1
    change_state(channel)

    print("joystick switch pressed!" + str(joy_press))

def joystick_y_switch_callback(channel):
    global joy_y
    joy_y += 1
    change_state(channel)

    print("joystick y axis pressed!" + str(joy_y))

def joystick_x_switch_callback(channel):
    global joy_x
    joy_x += 1
    change_state(channel)

    print("joystick x axis pressed!" + str(joy_x))


GPIO.setwarnings(False) # Ignore warning for now
GPIO.setmode(GPIO.BCM) # Use physical pin numbering


GPIO.setup(PUSH_BUTTON_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # Set pin 10 to be an input pin and set initial value to be pulled low (off)
GPIO.add_event_detect(PUSH_BUTTON_GPIO, GPIO.RISING,callback=push_button_callback, bouncetime=200) # Setup event on pin 10 rising edge

GPIO.setup(TOGGLE_SWITCH_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # Set pin 10 to be an input pin and set initial value to be pulled low (off)
GPIO.add_event_detect(TOGGLE_SWITCH_GPIO, GPIO.BOTH,callback=toggle_switch_callback, bouncetime=200) # Setup event on pin 10 rising edge

GPIO.setup(JOYSTICK_SW_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP) # Set pin 10 to be an input pin and set initial value to be pulled low (off)
GPIO.add_event_detect(JOYSTICK_SW_GPIO, GPIO.RISING,callback=joystick_sw_switch_callback) # Setup event on pin 10 rising edge

GPIO.setup(JOYSTICK_Y_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # Set pin 10 to be an input pin and set initial value to be pulled low (off)
GPIO.add_event_detect(JOYSTICK_Y_GPIO, GPIO.RISING,callback=joystick_y_switch_callback) # Setup event on pin 10 rising edge

GPIO.setup(JOYSTICK_X_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # Set pin 10 to be an input pin and set initial value to be pulled low (off)
GPIO.add_event_detect(JOYSTICK_X_GPIO, GPIO.RISING,callback=joystick_x_switch_callback) # Setup event on pin 10 rising edge

while True:
    print("You are in NO state")
    if push_state:
        print("You are in the push button state!")
    elif toggle_state:
        print("You are in the toggle state!")
    elif joy_state:
        print("You are in the joystick state!")

message = input("Press enter to quit\n\n") # Run until someone presses enter
GPIO.cleanup() # Clean up