//Servo-Control Class
//#define USE_PCA9685_SERVO_EXPANDER
#include <Wire.h>
#include <ServoEasing.hpp>
#include "Arduino.h"

class servoController {
  private:
    const int n_axes = 5;

    const int axis1_Channel = 0;
    const int axis2_Channel = 2;
    const int axis3_Channel = 4;
    const int axis4_Channel = 6;
    const int axis5_Channel = 8;

    const int __servoBaseMin = 446;
    const int __servoBaseMax = 2234;
    const float __omega_1Max = 1 / (0.19 / 60); //[deg/s]

    const int __servoShoulderMin = 446;
    const int __servoShoulderMax = 2234;
    const float __omega_2Max = 1 / (0.19 / 60); //[deg/s]

    const int __servoElbowMin = 446;
    const int __servoElbowMax = 2234;
    const float __omega_3Max = 60 / 0.1; //[deg/s]

    const int __servoWristMin = 714;
    const int __servoWristMax = 2500;
    const float __omega_4Max = 60 / 0.1; //[deg/s]

    const int __servoTiltMin = 682;
    const int __servoTiltMax = 2500;
    const float __omega_5Max = 60 / 0.1; //[deg/s]

    float baseAngleCurrent = 0;
    float baseAngleGoal = 0;
    float baseAnglePrevious = 0;

    float shoulderAngleCurrent = 0;
    float shoulderAngleGoal = 0;
    float shoulderAnglePrevious = 0;

    float elbowAngleCurrent = 0;
    float elbowAngleGoal = 0;
    float elbowAnglePrevious = 0;

    float wristAngleCurrent = 0;
    float wristAngleGoal = 0;
    float wristAnglePrevious = 0;

    float tiltAngleCurrent = 0;
    float tiltAngleGoal = 0;
    float tiltAnglePrevious = 0;

    float __angularSpeeds[5] = {__omega_1Max, __omega_2Max, __omega_3Max, __omega_4Max, __omega_5Max};

  public:
    servoController() {
    }

    void setupServos() {
      delay(200);
      ServoEasing servoBase(0x40);
      if (servoBase.attach(axis1_Channel, 0, __servoBaseMin, __servoBaseMax, -90, 90) == INVALID_SERVO) {
        Serial.println(
          F("Error attaching servo for -Base-. Maybe MAX_EASING_SERVOS=" STR(MAX_EASING_SERVOS) " is to small to hold all servos"));
      }
      else {
      }
      servoBase.write(90);
      delay(200);

      ServoEasing servoShoulder(0x40);
      if (servoShoulder.attach(axis2_Channel, 0, __servoShoulderMin, __servoShoulderMax, -90, 90) == INVALID_SERVO) {
        Serial.println(
          F("Error attaching servo for -Shoulder-. Maybe MAX_EASING_SERVOS=" STR(MAX_EASING_SERVOS) " is to small to hold all servos"));
      }
      else {
      }
      //delay(100);

      ServoEasing servoElbow(0x40);
      if (servoElbow.attach(axis3_Channel, 0, __servoElbowMin, __servoElbowMax, -90, 90) == INVALID_SERVO) {
        Serial.println(
          F("Error attaching servo for -Elbow-. Maybe MAX_EASING_SERVOS=" STR(MAX_EASING_SERVOS) " is to small to hold all servos"));
      }
      else {
      }
      //delay(100);

      ServoEasing servoWrist(0x40);
      if (servoWrist.attach(axis4_Channel, 0, __servoWristMin, __servoWristMax, -90, 90) == INVALID_SERVO) {
        Serial.println(
          F("Error attaching servo for -Wrist-. Maybe MAX_EASING_SERVOS=" STR(MAX_EASING_SERVOS) " is to small to hold all servos"));
      }
      else {
      }
      //delay(200);

      ServoEasing servoTilt(0x40);
      if (servoTilt.attach(axis5_Channel, 0, __servoTiltMin, __servoTiltMax, -90, 90) == INVALID_SERVO) {
        Serial.println(
          F("Error attaching servo for -Tilt-. Maybe MAX_EASING_SERVOS=" STR(MAX_EASING_SERVOS) " is to small to hold all servos"));
      }
      else {
      }

      delay(200);

      servoBase.setSpeed(int(__omega_1Max * 0.4));
      servoShoulder.setSpeed(int(__omega_2Max * 0.5));
      servoElbow.setSpeed(int(__omega_3Max * 0.75));
      servoWrist.setSpeed(int(__omega_4Max * 0.75));
      servoTilt.setSpeed(int(__omega_5Max * 0.75));

      setEaseToForAllServos(QuarticEaseIn);
    }

    void moveToSynchronized(float deg1, float deg2, float deg3, float deg4, float deg5, int delayT) {
      ServoEasing::ServoEasingArray[0]->setEaseTo(deg1);
      ServoEasing::ServoEasingArray[1]->setEaseTo(deg2);
      ServoEasing::ServoEasingArray[2]->setEaseTo(deg3);
      ServoEasing::ServoEasingArray[3]->setEaseTo(deg4);
      ServoEasing::ServoEasingArray[4]->setEaseTo(deg5);

      synchronizeAllServosAndStartInterrupt(true);
    }

    void simpleMoveTo(float deg1, float deg2, float deg3, float deg4, float deg5) {
      //    servoBase.setEaseTo(deg1);
      //    servoShoulder.setEaseTo(deg2);
      //    servoElbow.setEaseTo(deg3);
      //    servoWrist.setEaseTo(deg4);
      //    servoTilt.startEaseTo(deg5);
      ServoEasing::ServoEasingArray[0]->setEaseTo(deg1);
      ServoEasing::ServoEasingArray[1]->setEaseTo(deg2);
      ServoEasing::ServoEasingArray[2]->setEaseTo(deg3);
      ServoEasing::ServoEasingArray[3]->setEaseTo(deg4);
      ServoEasing::ServoEasingArray[4]->startEaseTo(deg5);

      while (ServoEasing::areInterruptsActive()) {
      }
      delay(1000);
    }

    void moveOneAxis(int axis, float deg) {
      ServoEasing::ServoEasingArray[axis - 1]->easeTo(deg);
    }

    void setAngularSpeed(int axis, float percentage) {
      ServoEasing::ServoEasingArray[axis - 1]->setSpeed(int(__angularSpeeds[axis - 1]*percentage));
    }

    void processSingleAxisMovement(String serialString) {
      //1_n_AXIS_VAL_SPEEDXXX => Move Single Axis
      int axis;
      int degree;
      int speed_percentage;
      String axis_str, degree_str, speed_str;
      
      int delimiter1 = serialString.indexOf('/');
      int delimiter2 = serialString.indexOf('/', delimiter1 + 1);
      int delimiter3 = serialString.indexOf('/', delimiter2 + 1);

      axis_str = serialString.substring(delimiter1 + 1, delimiter2);
      degree_str = serialString.substring(delimiter2 + 1, delimiter3);
      speed_str = serialString.substring(delimiter3 + 1);

      axis = axis_str.toInt();
      degree = degree_str.toInt();
      speed_percentage = speed_str.toInt();
      
      moveOneAxis(axis, degree);
    }
      //TODO

    void processMultiAxisMovement(String serialString) {
      //2_THETA1_THETA2_THETA3_THETA4_THETA5_SPEEDXXX => Move all Axes with a specific % Speed and profil
      String theta1_str, theta2_str, theta3_str, theta4_str, theta5_str; 
      String speed_str;
      float theta1, theta2, theta3, theta4, theta5;
      int speed_percentage;
      
      int delimiter1 = serialString.indexOf('/', 0);
      int delimiter2 = serialString.indexOf('/', delimiter1 + 1);
      int delimiter3 = serialString.indexOf('/', delimiter2 + 1);
      int delimiter4 = serialString.indexOf('/', delimiter3 + 1);
      int delimiter5 = serialString.indexOf('/', delimiter4 + 1);
      int delimiter6 = serialString.indexOf('/', delimiter5 + 1);

      theta1_str = serialString.substring(delimiter1 + 1, delimiter2);
      theta2_str = serialString.substring(delimiter2 + 1, delimiter3);
      theta3_str = serialString.substring(delimiter3 + 1, delimiter4);
      theta4_str = serialString.substring(delimiter4 + 1, delimiter5);
      theta5_str = serialString.substring(delimiter5 + 1, delimiter6);

      speed_str = serialString.substring(delimiter6 + 1);

      theta1 = theta1_str.toFloat();
      theta2 = theta2_str.toFloat();
      theta3 = theta3_str.toFloat();
      theta4 = theta4_str.toFloat();
      theta5 = theta5_str.toFloat();

      speed_percentage = speed_str.toInt();

      moveToSynchronized(theta1, theta2, theta3, theta4, theta5, 20);
      //TODO
    }

};
