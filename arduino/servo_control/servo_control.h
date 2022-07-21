//Servo-Control Script
#define USE_PCA9685_SERVO_EXPANDER 
#include <ServoEasing.hpp>
class servoController {
  private:
    const int n_axes = 5; 

    const int axis1_Pin = 0;
    const int axis2_Pin = 1;
    const int axis3_Pin = 2;
    const int axis4_Pin = 3;
    const int axis5_Pin = 4;

    const int __servoBaseMin = 525;
    const int __servoBaseMax = 2600;
    const float __omega_1Max = 1/(0.19/60); //[deg/s]

    const int __servoShoulderMin = 300;
    const int __servoShoulderMax = 2310;
    const float __omega_2Max = 1/(0.19/60); //[deg/s]

    const int __servoElbowMin = 500;
    const int __servoElbowMax = 2308;
    const float __omega_3Max = 60/0.1; //[deg/s]

    const int __servoWristMin = 714;
    const int __servoWristMax = 2500;
    const float __omega_4Max = 60/0.1; //[deg/s]

    const int __servoTiltMin = 682;
    const int __servoTiltMax = 2500;
    const float __omega_5Max = 60/0.1; //[deg/s]

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

  public:
    servoController() {
    init();
    }

  void init() {
    ServoEasing servoBase; 
    ServoEasing servoShoulder; 
    ServoEasing servoElbow; 
    ServoEasing servoWrist; 
    ServoEasing servoTilt; 

    servoBase.attach(axis1_Pin, __servoBaseMin, __servoBaseMax, 0, 180);
    servoShoulder.attach(axis2_Pin, __servoShoulderMin, __servoShoulderMax, 0, 180);
    servoElbow.attach(axis3_Pin, __servoElbowMin, __servoElbowMax, 0, 180);
    servoWrist.attach(axis4_Pin, __servoWristMin, __servoWristMax, 0, 180);
    servoTilt.attach(axis5_Pin, __servoTiltMin, __servoTiltMax, 0, 180);

    delay(500);

    servoBase.setSpeed(__omega_1Max*0.2);
    servoShoulder.setSpeed(__omega_2Max*0.2);
    servoElbow.setSpeed(__omega_3Max*0.2);
    servoWrist.setSpeed(__omega_4Max*0.2);
    servoTilt.setSpeed(__omega_5Max*0.2);

    setEaseToForAllServos(EASE_CUBIC_IN_OUT);
  }

  void moveToSynchronized(float deg1, float deg2, float deg3, float deg4, float deg5) {
    ServoEasing::ServoEasingArray[0]->setEaseTo(deg1);
    ServoEasing::ServoEasingArray[1]->setEaseTo(deg2);
    ServoEasing::ServoEasingArray[3]->setEaseTo(deg3);
    ServoEasing::ServoEasingArray[3]->setEaseTo(deg4);
    ServoEasing::ServoEasingArray[4]->setEaseTo(deg5);

    synchronizeAllServosAndStartInterrupt(false);
  }

};
