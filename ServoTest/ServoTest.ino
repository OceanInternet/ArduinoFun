#include <Servo.h>

Servo robotServo;

int servoCenter = 85;

int servoLeft   = servoCenter + 45;
int servoRight  = servoCenter - 45;

int servoPosition = servoCenter;

void setup() {
  robotServo.attach(10);
  robotServo.write(servoCenter);
}

void loop() {

  robotServo.write(servoLeft);
  delay(250);
  robotServo.write(servoCenter);
  delay(250);
  robotServo.write(servoRight);
  delay(250);
  robotServo.write(servoCenter);
  delay(250);
}
