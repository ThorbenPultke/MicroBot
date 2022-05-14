/*
   The SUPER KNOB for 9G Servo Testing
   Author : Paul Pavish
   Purpose : To test and find the MIN_PULSE_WIDTH & MAX_PULSE_WIDTH of a 9G Servo
              thereby attaining a complete 180 degree rotation
   Released in  Youtube Channel : Paul Pavish
                Video Topic     : The Problem with 9G Servos
                Video Category  : Creator Fix
                Code & blog URL : www.basicsexplained.com/creator/
*/

//Including required libraries

#include<Servo.h>

//Creating a Servo Object 's'

Servo s;

//Global Initialization

//Analog Pins

int Res_100 = A2;
int Res_10 = A1;
int Res_2 = A0;

//Servo Pin

const int Servo_Pin = 9;

//Resolution variables

int R_100, R_10, R_2;
int Micros;
int Pre_val;

void setup() {

  //Initialize Serial Communication

  Serial.begin(9600);

  //Attaching Servo object to Servo pin

  s.attach(9, 400, 2600);

}

void Read_Knobs() {

  R_100 = map(analogRead(Res_100), 0, 1023, 4, 26);
  R_10 = map(analogRead(Res_10), 0, 1023, 0, 10);
  R_2 = map(analogRead(Res_2), 0, 1023, -4, 4);
}

void Calc_Microsec() {

  Micros = (R_100 * 100) + (R_10 * 10) + (R_2 * 2);

}

void Wait_for_new_val() {

  while (Micros == Pre_val) {
    Read_Knobs();
    Calc_Microsec();
  }

  Pre_val = Micros;

}

void loop() {
  // put your main code here, to run repeatedly:

  Read_Knobs();
  Calc_Microsec();
  s.writeMicroseconds(Micros);
  Serial.println(Micros);
  Wait_for_new_val();
  delay(10);

}
