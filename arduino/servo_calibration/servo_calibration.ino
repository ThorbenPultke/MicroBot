#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define SERVO_FREQ 60 // Analog servos run at ~50 Hz updates
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
uint16_t selected_port = -1;
uint16_t last_pwm = -1;

void setup() {

  Serial.begin(9600);
  Serial.println("Calibration for Servos. Default range [150-600] pwm");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
  Serial.println("Please enter the channel on which the servo is attached (pwm board): ");
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() == 0)
  {
  }
  uint16_t Input = String(Serial.readString()).toInt();
  if (selected_port == -1 and Input >= 0 and Input <= 16)
  {
    selected_port = Input;
    Serial.print("Selected channel: ");
    Serial.println(String(selected_port));
    Serial.println("driving servo to expected zero-pose (pulse_length=375)");
    pwm.setPWM(selected_port, 0, 375);
    //pwm.writeMicroseconds(selected_port, microsec);
    last_pwm = 375;
  }

  else if (Input == -1)
  {
    Serial.println("Detached current channel.");
    selected_port = -1;
  }

  else if (selected_port != -1 and Input != -1)
  {
    int Var_for_Calc = Input;
    Serial.print("Driving Servo to pulse_length: ");
    Serial.println(String(Input));
    if (Input > last_pwm)
    {
      Serial.println("Driving servo forward...");
      for (uint16_t pulse = last_pwm; pulse < Input; pulse++)
      {
        //pwm.writeMicroseconds(selected_port, pulse);
        pwm.setPWM(selected_port, 0, pulse);
      }
    }

    else if (Input < last_pwm)
    {
      Serial.println("Driving servo backward...");
      for (uint16_t pulse = last_pwm; pulse > Input; pulse--)
      {
        //pwm.writeMicroseconds(selected_port, pulse);
        pwm.setPWM(selected_port, 0, pulse);
        //delay(20);
      }
    }
    Serial.println("finished.");
    int servoEasepwm = ((int32_t) Var_for_Calc * (16666 / 32)) / (4096 / 32);
    Serial.print("Servo-Ease signal:");
    Serial.println(String(servoEasepwm));
    last_pwm = Input;

  }
  else
  {
    Serial.println("No valid input, please try again.");
  }



}
