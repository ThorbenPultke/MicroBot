#define USE_PCA9685_SERVO_EXPANDER
#include <ServoEasing.hpp>
#include <Arduino.h>
#include "servo_control.h"
#include "display.h"
#include "led_strip.h"
servoController Controller;
LCD_Display LCD;
LED_Strip LED;
int Mode = 1; //integer handling different use-cases for the MicroBot. 1: serial-connection, 2: random position, 3: teached trajectory
bool serialConnected = false; //Bool handling the connection state for a serial-connection
String serialString; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(4800);
  Serial.setTimeout(1000);
  LCD.setupLCD();
  LCD.writeText("Setting up...");
  LED.setupLED();
  LED.setColor(3);
  delay(1000);
  Controller.setupServos();
  LCD.writeText("Setup done, proceeding...");
  LED.setColor(2);
  delay(3000);
  LCD.writeText("SERIAL-MODE. WAITING FOR SERIAL.");
}

//Defined Strings for Serial_connection:
//1_n_AXIS_VAL_SPEEDXXX => Move Single Axis
//2_THETA1_THETA2_THETA3_THETA4_THETA5_SPEEDXXX => Move all Axes with a specific % Speed and profil

void loop() {
  if (Mode == 1) {
    //LED.setColor(2);
    //LCD.writeText("SERIAL-MODE. WAITING FOR SERIAL");
    if (Serial.available()) {
      LED.setColor(2);
      serialString = Serial.readString();
      LCD.writeText(serialString);
      delay(3000);
      if (serialString.substring(0, 1)=="1") {
        LCD.writeText("SERIAL-MODE. MOVING SINGLE AXIS");
        LED.setColor(4);
        Controller.processSingleAxisMovement(serialString);
        delay(1000);
        LCD.writeText("Test");
      }
      else if (serialString.substring(0, 1)=="2") {
        LCD.writeText("SERIAL-MODE. MOVING MULTI AXES");
        LED.setColor(4);
        Controller.processMultiAxisMovement(serialString);
      }
      else {
        LED.setColor(1);
        LCD.writeText("Corrupted Instruction received...");
        delay(3000);
      }
      
      LED.setColor(2);
      LCD.writeText("SERIAL-MODE. WAITING FOR SERIAL.");
    };
  }

  else if (Mode == 2) {

  }

  else if (Mode == 3) {

  }

  //Cycle end
}
