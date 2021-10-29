#include <Stepper.h>
#include <ESP32Servo.h>

// FOR STEPPER
#define A 25
#define B 26
#define C 27
#define D 14
 
#define NUMBER_OF_STEPS_PER_REV 2048 // change this to fit the number of steps per revolution
Stepper myStepper(NUMBER_OF_STEPS_PER_REV, A, C, B, D); //switch B and C? going off of random nerd tutorial


// FOR SERVO
Servo myservo;  // create servo object to control a servo
// 16 servo objects can be created on the ESP32
 
int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int servoPin = 13;

void setup(){
  
  // FOR STEPPER
  // set the speed at 5 rpm
  myStepper.setSpeed(5);

  // FOR SERVO
    // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 300, 2600); // attaches the servo on pin 13 to the servo object

  myservo.write(0);
  
  Serial.begin(115200);
}

void servo_rotate() {
  for (int p = pos; p <= pos + 10; p += 1) { // increments servo 10 deg
    // in steps of 1 degree
    myservo.write(p);    // tell servo to go to position in variable 'pos'
    delay(15);             // waits 15ms for the servo to reach the position
  }
  
  pos += 10;

  if (pos >= 180) { // if servo has gone 180 deg, resets to origin pos
    pos = 0;
    myservo.write(pos);
  }
}


void loop(){

  // Spin the stepper motor 360 deg
  for (int i = 0; i < NUMBER_OF_STEPS_PER_REV; i++) {
    myStepper.step(1);
  }

  // When stepper motor has spun 360, spin servo 10 deg
  servo_rotate();
}
