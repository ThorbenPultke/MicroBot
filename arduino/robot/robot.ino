//Servo-Control Script
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define SERVO_FREQ 100 // Digital Frequency
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); //Init of pwm servo driver

int incomingBytes;
int runningFlag = 0;

//Init of servo parameters (pulse lengths). Min corresponds with -90 Degree, Max with +90 Degree, home with 0 Degree.
const int servoBaseMin = 160;
const int servoBaseHome = 500;
const int servoBaseMax = 880;
const float omega_1Max = 60/190; //[deg/ms]
float baseAngleCurrent = 0;
float baseAngleGoal = 0;
float baseAnglePrevious = 0;

const int servoShoulderMin = 190;
const int servoShoulderHome = 540;
const int servoShoulderMax = 890;
const float omega_2Max = 60/190; //[deg/ms]
float shoulderAngleCurrent = 0;
float shoulderAngleGoal = 0;
float shoulderAnglePrevious = 0;

const int servoElbowMin = 200;
const int servoElbowHome = 550;
const int servoElbowMax = 870;
const float omega_3Max = 60/100; //[deg/ms]
float elbowAngleCurrent = 0;
float elbowAngleGoal = 0;
float elbowAnglePrevious = 0;

const int servoWristMin = 270;
const int servoWristHome = 600;
const int servoWristMax = 930;
const float omega_4Max = 60/100; //[deg/ms]
float wristAngleCurrent = 0;
float wristAngleGoal = 0;
float wristAnglePrevious = 0;

const int servoTiltMin = 250;
const int servoTiltHome = 580;
const int servoTiltMax = 940;
const float omega_5Max = 60/100; //[deg/ms]
float tiltAngleCurrent = 0;
float tiltAngleGoal = 0;
float tiltAnglePrevious = 0;

void setup() {
 Serial.begin(9600); //incoming commands from usb-serial-connection
 Serial.println("Servo-Controller initialising...");

 pwm.begin();
 pwm.setOscillatorFrequency(27000000);
 pwm.setPWMFreq(SERVO_FREQ); 
 Serial.println("pwm ok.");

 delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() != 0)
  {

  }
  else if (runningFlag != 0)
  {

  }
  }

