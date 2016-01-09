#include <AFMotor.h>
#include <NewPing.h>

// AFMotor
#define LFT_MOTOR  3
#define RGT_MOTOR  4
#define LFT        0
#define RGT        1

AF_DCMotor motors[2] = {
  AF_DCMotor(LFT_MOTOR),
  AF_DCMotor(RGT_MOTOR)
};

// NewPing
#define TRIGGER_PIN  10  // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PIN     9  // Arduino pin tied to echo pin on ping sensor.
#define MAX_DISTANCE 110 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

unsigned int  pingSpeed = 50; // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
unsigned long pingTimer;     // Holds the next ping time.

int targetDistanceCm  = 20;
int currentDistanceCm = 20;

void setup()
{
  pingTimer = millis(); // Start now.

  motors[LFT].setSpeed(0);
  motors[RGT].setSpeed(0);
  motors[LFT].run(RELEASE);
  motors[RGT].run(RELEASE);
}

void loop()
{
  updateSonar();
  int delta = currentDistanceCm - targetDistanceCm;
  int speed = (delta > 0) ? 200 + delta/2 : 200 - delta/2;

  motors[LFT].setSpeed(speed);
  motors[RGT].setSpeed(speed);

  if(delta > 5) { // Forward

    motors[LFT].run(FORWARD);
    motors[RGT].run(FORWARD);

  } else if(delta < -5) { // Reverse

    motors[LFT].run(BACKWARD);
    motors[RGT].run(BACKWARD);

  } else { // (delta == 0) Stop

    motors[LFT].setSpeed(255);
    motors[RGT].setSpeed(255);

    motors[LFT].run(BACKWARD);
    motors[RGT].run(FORWARD);

    delay(50);

    motors[LFT].setSpeed(speed);
    motors[RGT].setSpeed(speed);

    motors[LFT].run(RELEASE);
    motors[RGT].run(RELEASE);
  }
}

void updateSonar() {

  // Notice how there's no delays in this sketch to allow you to do other processing in-line while doing distance pings.
  if (millis() >= pingTimer) {   // pingSpeed milliseconds since last ping, do another ping.
    
    pingTimer += pingSpeed;      // Set the next ping time.
    sonar.ping_timer(echoCheck); // Send out the ping, calls "echoCheck" function every 24uS where you can check the ping status.
  }
}

void echoCheck() { // Timer2 interrupt calls this function every 24uS where you can check the ping status.

  if (sonar.check_timer()) { // This is how you check to see if the ping was received.

    // Here's where you can add code.
    currentDistanceCm = (sonar.ping_result / US_ROUNDTRIP_CM);
  }
}

void printDistanceCm() {

  Serial.print("Ping: ");
  Serial.print(currentDistanceCm); // Ping returned, uS result in ping_result, convert to cm with US_ROUNDTRIP_CM.
  Serial.print("cm");
  Serial.print("\n");
}

