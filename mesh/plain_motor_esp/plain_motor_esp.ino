#include <Stepper.h>
#include <ESP32Servo.h>

// FOR STEPPER 1
#define A1 25
#define B1 26
#define C1 27
#define D1 14

// FOR STEPPER 2
#define A2 17
#define B2 5
#define C2 18
#define D2 19

// FOR STEPPER 3
#define A3 32
#define B3 15
#define C3 4
#define D3 16
 
#define NUMBER_OF_STEPS_PER_REV 2048 // change this to fit the number of steps per revolution

Stepper myStepper1(NUMBER_OF_STEPS_PER_REV, A1, C1, B1, D1); 
Stepper myStepper2(NUMBER_OF_STEPS_PER_REV, A2, C2, B2, D2);
Stepper myStepper3(NUMBER_OF_STEPS_PER_REV, A3, C3, B3, D3);


void setup(){
  
  // FOR STEPPER
  // set the speed at 5 rpm
  //myStepper1.setSpeed(5);
  //myStepper2.setSpeed(5);
  myStepper3.setSpeed(20);

  
  Serial.begin(115200);
}


void loop(){

  int x = 5;

  // Spin the stepper motor x * 360 deg
  for (int i = 0; i < NUMBER_OF_STEPS_PER_REV * x; i++) {
    //myStepper1.step(1);
    //myStepper2.step(1);
    myStepper3.step(-1);
  }

//  // pause for troubleshooting
//  delay(5000);
//
//  // Spin the stepper motor an opposite x* 360 deg
//  for (int i = 0; i < NUMBER_OF_STEPS_PER_REV * x; i++) {
//    //myStepper1.step(-1);
//    //myStepper2.step(-1);
//    myStepper3.step(-1);
 // }
  


}
