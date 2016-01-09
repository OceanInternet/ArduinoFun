#include <IRLib.h>
#include <AFMotor.h>

// IRremote
int receiver = 10; // Signal Pin of IR receiver to Arduino Digital Pin 11

/*-----( Declare objects )-----*/
IRrecv   My_Receiver(receiver); // create instance of 'irrecv'
IRdecode My_Decoder;            // create instance of 'decode_results'

// AFMotor
#define LFT_MOTOR  3
#define RGT_MOTOR  4
#define LFT        0
#define RGT        1

AF_DCMotor motors[2] = {
  AF_DCMotor(LFT_MOTOR),
  AF_DCMotor(RGT_MOTOR)
};

// tANK
#define TANK_STOP 0xA70
#define TANK_FWD  0x2F0
#define TANK_REV  0xAF0
#define TANK_LFT  0x2D0
#define TANK_RGT  0xCD0

#define TURN_SPEED  255
#define DRIVE_SPEED 255
#define MOTOR_TURN  20
#define MOTOR_DRIVE 100

unsigned long command = TANK_STOP;

void setup() {

  My_Receiver.No_Output();//Turn off any unused IR LED output circuit
  
  Serial.begin(9600);
  Serial.println("Initialise...");

  tankStop();

  My_Receiver.enableIRIn(); // Start the receiver
}

void loop() {
  
  if (My_Receiver.GetResults(&My_Decoder)) {

    My_Decoder.decode();
    
    command = My_Decoder.value;

    translateIR();

    My_Receiver.resume();
    
  } else {
    
    tankStop();
  }
}

void translateIR() {

  Serial.println(command, HEX);
  
  switch(command) {

    case TANK_STOP:
      tankStop();
      break;
    
    case TANK_FWD:
      tankFwd();
      break;
    
    case TANK_REV:
      tankRev();
      break;
    
    case TANK_LFT:
      tankLft();
      break;
    
    case TANK_RGT:
      tankRgt();
      break;
    
    default:
      tankStop();
      Serial.println(command, HEX);
      break;
  }

}

void tankFwd() {

  Serial.println(" FORWARD");
  
  motors[LFT].run(FORWARD);
  motors[RGT].run(FORWARD);
  
  motors[LFT].setSpeed(DRIVE_SPEED);
  motors[RGT].setSpeed(DRIVE_SPEED);

  delay(MOTOR_DRIVE);
}

void tankRev() {

  Serial.println(" REVERSE");

  motors[LFT].run(BACKWARD);
  motors[RGT].run(BACKWARD);
  
  motors[LFT].setSpeed(DRIVE_SPEED);
  motors[RGT].setSpeed(DRIVE_SPEED);

  delay(MOTOR_DRIVE);
}

void tankRgt() {

  Serial.println(" RIGHT");

  motors[LFT].run(BACKWARD);
  motors[RGT].run(FORWARD);
  
  motors[LFT].setSpeed(TURN_SPEED);
  motors[RGT].setSpeed(TURN_SPEED);

  delay(MOTOR_TURN);
}

void tankLft() {

  Serial.println(" LEFT");
  
  motors[LFT].run(FORWARD);
  motors[RGT].run(BACKWARD);
  
  motors[LFT].setSpeed(TURN_SPEED);
  motors[RGT].setSpeed(TURN_SPEED);

  delay(MOTOR_TURN);
}

void tankStop() {

  motors[LFT].run(RELEASE);
  motors[RGT].run(RELEASE);

  motors[LFT].setSpeed(0);
  motors[RGT].setSpeed(0);
}
