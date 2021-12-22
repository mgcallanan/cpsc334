#include <ESP32Servo.h>

// FOR SERVO
Servo leftMouthServo;  // create servo object to control a servo
Servo rightMouthServo;
Servo leftEyeServo;
Servo rightEyeServo;

// FOR BUTTONS
int buttonOne = 33;
int buttonTwo = 32;
int buttonThree = 27;

// 16 servo objects can be created on the ESP32

int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int leftMouthServoPin = 13;
int rightMouthServoPin = 14;
int leftEyeServoPin = 25;
int rightEyeServoPin = 26;

int happyLeftMouth = 30;
int happyRightMouth = 90;
int sadLeftMouth = 90;
int sadRightMouth = 30;
int neutralLeftMouth = 60;
int neutralRightMouth = 60;

int happyLeftEye = 30;
int happyRightEye = 90;
int sadLeftEye = 90;
int sadRightEye = 30;
int neutralLeftEye = 60;
int neutralRightEye = 60;

int twitchFactor = 15;

// state for switching servos
/**
 * 0 - left eye
 * 1 - right eye
 * 2 - right mouth
 * 3 - left mouth
 */
int servoState = 0;

int currentLeftEyeDeg = 0;
int currentRightEyeDeg = 0;
int currentLeftMouthDeg = 0;
int currentRightMouthDeg = 0;

// servo angles
/**
 * on right side
 * 0 = happy
 * 60 = neutral
 * 120 = sad
 * 
 * on left side
 * 
 */

void setup(){

  // FOR SERVO
    // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  leftMouthServo.setPeriodHertz(50);    // standard 50 hz servo
  leftMouthServo.attach(leftMouthServoPin, 300, 2600); // attaches the servo on pin 13 to the servo object

  leftMouthServo.write(60);
  currentLeftMouthDeg = 60;

  rightMouthServo.setPeriodHertz(50);    // standard 50 hz servo
  rightMouthServo.attach(rightMouthServoPin, 300, 2600); // attaches the servo on pin 13 to the servo object

  rightMouthServo.write(60);
  currentRightMouthDeg = 60;

  leftEyeServo.setPeriodHertz(50);    // standard 50 hz servo
  leftEyeServo.attach(leftEyeServoPin, 300, 2600); // attaches the servo on pin 13 to the servo object

  leftEyeServo.write(60);
  currentLeftEyeDeg = 60;

  rightEyeServo.setPeriodHertz(50);    // standard 50 hz servo
  rightEyeServo.attach(rightEyeServoPin, 300, 2600); // attaches the servo on pin 13 to the servo object

  rightEyeServo.write(60);
  currentRightEyeDeg = 60;

  // FOR BUTTONS
  pinMode(buttonOne, INPUT_PULLUP); // config GIOP33 as input pin and enable the internal pull-up resistor
  pinMode(buttonTwo, INPUT_PULLUP); // config GIOP33 as input pin and enable the internal pull-up resistor
  pinMode(buttonThree, INPUT_PULLUP); // config GIOP33 as input pin and enable the internal pull-up resistor

  
  Serial.begin(115200);
}

void happy_face() {
   // happy
  Serial.println("HAPPY MOUTHnRight: " + String(happyRightMouth) + "; Left: " + String(happyLeftMouth));
  rightMouthServo.write(happyRightMouth);
  leftMouthServo.write(happyLeftMouth);
  currentRightMouthDeg = happyRightMouth;
  currentLeftMouthDeg = happyLeftMouth;

  Serial.println("HAPPY EYE Right: " + String(happyRightEye) + "; Left: " + String(happyLeftEye));
  rightEyeServo.write(happyRightEye);
  leftEyeServo.write(happyLeftEye);
  currentRightEyeDeg = happyRightEye;
  currentLeftEyeDeg = happyLeftEye;
}

void neutral_face() {
  // neutral
  Serial.println("NEUTRAL MOUTH Right: " + String(neutralRightMouth) + "; Left: " + String(neutralLeftMouth));
  rightMouthServo.write(neutralRightMouth);
  leftMouthServo.write(neutralLeftMouth);
  currentRightMouthDeg = neutralRightMouth;
  currentLeftMouthDeg = neutralLeftMouth;

  Serial.println("NEUTRAL EYE Right: " + String(neutralRightEye) + "; Left: " + String(neutralLeftEye));
  rightEyeServo.write(neutralRightEye);
  leftEyeServo.write(neutralLeftEye);
  currentRightEyeDeg = neutralRightEye;
  currentLeftEyeDeg = neutralLeftEye;
}

void sad_face() {
  // sad
  Serial.println("SAD MOUTH Right: " + String(sadRightMouth) + "; Left: " + String(sadLeftMouth));
  rightMouthServo.write(sadRightMouth);
  leftMouthServo.write(sadLeftMouth);
  currentRightMouthDeg = sadRightMouth;
  currentLeftMouthDeg = sadLeftMouth;

  Serial.println("SAD EYE Right: " + String(sadRightEye) + "; Left: " + String(sadLeftEye));
  rightEyeServo.write(sadRightEye);
  leftEyeServo.write(sadLeftEye);
  currentRightEyeDeg = sadRightEye;
  currentLeftEyeDeg = sadLeftEye;
}

void twitch_servo() {

  if (servoState == 0) {
    leftEyeServo.write(currentLeftEyeDeg + twitchFactor);
    delay(200);
    leftEyeServo.write(currentLeftEyeDeg);
    delay(200);
    servoState += 1;
  }
  else if (servoState == 1) {
    rightEyeServo.write(currentRightEyeDeg + twitchFactor);
    delay(200);
    rightEyeServo.write(currentRightEyeDeg);
    delay(200);
    servoState += 1;
  }
  else if (servoState == 2) {
      rightMouthServo.write(currentRightMouthDeg + twitchFactor);
      delay(200);
      rightMouthServo.write(currentRightMouthDeg);
      delay(200);
    servoState += 1;
  }
  else if (servoState == 3) {
    leftMouthServo.write(currentLeftMouthDeg + twitchFactor);
    delay(200);
    leftMouthServo.write(currentLeftMouthDeg);
    delay(200);
    servoState = 0;
  }
}

void clockwise_turn() {
  
  if (servoState - 1 == 0) {
    if (currentLeftEyeDeg > 0 && currentLeftEyeDeg < 180) {
      leftEyeServo.write(currentLeftEyeDeg + 1);
      delay(15);
      currentLeftEyeDeg += 1;
    } else if (currentLeftEyeDeg == 0) {
      currentLeftEyeDeg = 1;
    } else if (currentLeftEyeDeg >= 180) {
      currentLeftEyeDeg = 179;
    }
  }
  else if (servoState - 1 == 1) {
    if (currentRightEyeDeg > 0 && currentRightEyeDeg < 180) {
      rightEyeServo.write(currentRightEyeDeg + 1);
      delay(15);
      currentRightEyeDeg += 1;
    } else if (currentRightEyeDeg == 0) {
      currentRightEyeDeg = 1;
    } else if (currentRightEyeDeg >= 180) {
      currentRightEyeDeg = 179;
    }
  }
  else if (servoState - 1 == 2) {
    if (currentRightMouthDeg > 0 && currentRightMouthDeg < 180) {
      rightMouthServo.write(currentRightMouthDeg + 1);
      delay(15);
      currentRightMouthDeg += 1;
    } else if (currentRightMouthDeg == 0) {
      currentRightMouthDeg = 1;
    } else if (currentRightMouthDeg >= 180) {
      currentRightMouthDeg = 179;
    }
  }
  else if (servoState - 1 == -1) {
    if (currentLeftMouthDeg > 0 && currentLeftMouthDeg < 180) {
      leftMouthServo.write(currentLeftMouthDeg + 1);
      delay(15);
      currentLeftMouthDeg += 1;
    } else if (currentLeftMouthDeg == 0) {
      currentLeftMouthDeg = 1;
    } else if (currentLeftMouthDeg >= 180) {
      currentLeftMouthDeg = 179;
    }
  }
}

void counter_clockwise_turn() {
  
  if (servoState - 1 == 0) {
    if (currentLeftEyeDeg > 0 && currentLeftEyeDeg < 180) {
      leftEyeServo.write(currentLeftEyeDeg - 1);
      delay(15);
      currentLeftEyeDeg -= 1;
    } else if (currentLeftEyeDeg == 0) {
      currentLeftEyeDeg = 1;
    } else if (currentLeftEyeDeg >= 180) {
      currentLeftEyeDeg = 179;
    }
    
  }
  else if (servoState - 1 == 1) {
    if (currentRightEyeDeg > 0 && currentRightEyeDeg < 180) {
      rightEyeServo.write(currentRightEyeDeg - 1);
      delay(15);
      currentRightEyeDeg -= 1;
    } else if (currentRightEyeDeg == 0) {
      currentRightEyeDeg = 1;
    } else if (currentRightEyeDeg >= 180) {
      currentRightEyeDeg = 179;
    }
    
  }
  else if (servoState - 1 == 2) {
    if (currentRightMouthDeg > 0 && currentRightMouthDeg < 180) {
      rightMouthServo.write(currentRightMouthDeg - 1);
      delay(15);
      currentRightMouthDeg -= 1;
    } else if (currentRightMouthDeg == 0) {
      currentRightMouthDeg = 1;
    } else if (currentRightMouthDeg >= 180) {
      currentRightMouthDeg = 179;
    }
  }
  else if (servoState - 1 == -1) {
    if (currentLeftMouthDeg > 0 && currentLeftMouthDeg < 180) {
      leftMouthServo.write(currentLeftMouthDeg - 1);
      delay(15);
      currentLeftMouthDeg -= 1;
    } else if (currentLeftMouthDeg == 0) {
      currentLeftMouthDeg = 1;
    } else if (currentLeftMouthDeg >= 180) {
      currentLeftMouthDeg = 179;
    }
  }
}

void rotate_faces() {

  happy_face();
  delay(5000);
  
  neutral_face();
  
  delay(5000);

  sad_face();
  delay(5000);

  neutral_face();
  delay(10000);
}



void loop(){
  // rotate_faces();
  int buttonOneState = digitalRead(buttonOne);
  int buttonTwoState = digitalRead(buttonTwo);
  int buttonThreeState = digitalRead(buttonThree);

  Serial.println(servoState);
  Serial.print(currentLeftEyeDeg);
  Serial.print(" ");
  Serial.print(currentRightEyeDeg);
  Serial.print(" ");
  Serial.print(currentRightMouthDeg);
  Serial.print(" ");
  Serial.print(currentLeftMouthDeg);
  Serial.print(" ");

  if (!buttonOneState) {
    twitch_servo();
  } else if (!buttonTwoState) {
    clockwise_turn();
  } else if (!buttonThreeState) {
    counter_clockwise_turn();
  }
//  } else if (!buttonOneState) {
//    
//  }
  
  // Serial.print(buttonOneState); Serial.print(buttonTwoState); Serial.println(buttonThreeState);
  // rotate_eye();
}
