#include <NewPing.h>
#include <AFMotor.h>

// NewPing
#define TRIGGER_PIN  10 // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PIN     9  // Arduino pin tied to echo pin on ping sensor.
#define MAX_DISTANCE 50 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

#define LFT       0
#define RGT       1
#define FRT       2

int distance[3] = {
  MAX_DISTANCE,
  MAX_DISTANCE,
  MAX_DISTANCE
};

int delta[3] = {
  MAX_DISTANCE,
  MAX_DISTANCE,
  MAX_DISTANCE
};

int currentDistanceCm = MAX_DISTANCE;

// AFMotor
#define LFT_MOTOR  3
#define RGT_MOTOR  4

AF_DCMotor motors[2] = {
  AF_DCMotor(LFT_MOTOR),
  AF_DCMotor(RGT_MOTOR)
};

#define TURN_SPEED  255
#define DRIVE_SPEED 255
#define MOTOR_TURN  100
#define MOTOR_DRIVE 200

void setup() {
  // put your setup code here, to run once:
  tankStop();
  delay(1000);
}

void loop() {

  delay(MOTOR_DRIVE);
  scan();
  delay(MOTOR_DRIVE);
  scan();
  
  // Move
  if(delta[FRT] > 1 || delta[FRT] < -1) {

    drive(delta[FRT]);
  
  } else if(delta[LFT] > 1 || delta[LFT] < -1) {

    tankLft();
    drive(delta[LFT]);
    
  } else if(delta[RGT] > 1 || delta[RGT] < -1) {

    tankRgt();
    drive(delta[RGT]);
    
  }
}

void scan() {

  scanFront(); 
  scanLeft();  
  scanRight();
}

void scanFront() {

  measureDistance();
  set(FRT);
}

void scanLeft() {

  tankLft();
  measureDistance();
  set(LFT);
  tankRgt();
}

void scanRight() {

  tankRgt();
  measureDistance();
  set(RGT);
  tankLft();
}

void measureDistance() {

  sonar.ping_timer(setCurrentDistance);
  delay(MOTOR_TURN);
}

void setCurrentDistance() { // Timer2 interrupt calls this function every 24uS where you can check the ping status.

  if (sonar.check_timer()) { // This is how you check to see if the ping was received.

    // Here's where you can add code.
    currentDistanceCm = (sonar.ping_result / US_ROUNDTRIP_CM);
  }
}

void set(int direction) {

  delta[direction]    = currentDistanceCm - distance[direction];
  distance[direction] = currentDistanceCm;
}

void drive(int delta) {

  if(delta > 1) {

    tankFwd();
    
  } else {

    tankRev();
  }
}

void tankFwd() {

  Serial.println(" FORWARD");
  
  motors[LFT].run(FORWARD);
  motors[RGT].run(FORWARD);
  
  motors[LFT].setSpeed(DRIVE_SPEED);
  motors[RGT].setSpeed(DRIVE_SPEED);

  delay(MOTOR_DRIVE);

  tankStop();
}

void tankRev() {

  Serial.println(" REVERSE");

  motors[LFT].run(BACKWARD);
  motors[RGT].run(BACKWARD);
  
  motors[LFT].setSpeed(DRIVE_SPEED);
  motors[RGT].setSpeed(DRIVE_SPEED);

  delay(MOTOR_DRIVE);

  tankStop();
}

void tankRgt() {

  Serial.println(" RIGHT");

  motors[LFT].run(BACKWARD);
  motors[RGT].run(FORWARD);
  
  motors[LFT].setSpeed(TURN_SPEED);
  motors[RGT].setSpeed(TURN_SPEED);

  delay(MOTOR_TURN);

  tankStop();

  delay(MOTOR_TURN);
}

void tankLft() {

  Serial.println(" LEFT");
  
  motors[LFT].run(FORWARD);
  motors[RGT].run(BACKWARD);
  
  motors[LFT].setSpeed(TURN_SPEED);
  motors[RGT].setSpeed(TURN_SPEED);

  delay(MOTOR_TURN);

  tankStop();

  delay(MOTOR_TURN);
}

void tankStop() {

  motors[LFT].run(RELEASE);
  motors[RGT].run(RELEASE);

  motors[LFT].setSpeed(0);
  motors[RGT].setSpeed(0);
}

