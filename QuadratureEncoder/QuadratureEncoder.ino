#include <QuadratureEncoder.h>

#define ENCODER0 0b00000011

QuadratureEncoder encoder();

void setup()
{
  InitialiseIO();
  InitialiseInterrupt();
  Serial.begin(9600);
  Serial.println("Initialised...");
}

void loop() {

//  int currentMillis = millis();
//  int deltaMillis = currentMillis - encoderMillis;
//  int motorSpeed = (encoderClicks / PULSES_PER_REV / GEAR_RATIO) / (deltaMillis / 6000);
//  
//  Serial.print("Speed:  ");
//  Serial.println(motorSpeed);
//  encoderClicks = 0;
//  encoderMillis = currentMillis;
  delay(100);
}

void InitialiseIO() {

  // Initialise A0-A1 as input
  for (int i = A0; i < A2; i++) {
    pinMode(i, INPUT);     // Pin i is input
    digitalWrite(i, HIGH); // Configure internal pull-up resistor
  }

//  // Initialise encoderMillis
//  encoderMillis = millis();
}

void InitialiseInterrupt() {

  noInterrupts();       // switch interrupts off while messing with their settings
  PCICR  |= 0b00000010; // Turn on Pin Change Interrupts (turn on port c)
  PCMSK1 |= 0b00000011; // Choose Which Pins to Interrupt (A0, A1)
  interrupts();         // turn interrupts back on
}

ISR(PCINT1_vect) {    // Interrupt service routine. Every single PCINT8..14 (=ADC0..5) change

  int state   = ENCODER0 & PINC;

//  if (encoderState != state) {
//    encoder.update(state);
//  }
}

/* Pin to interrupt map:
   D8-D13          = PCINT 0-5   = PCIR0 = PB = PCIE0 = PCMSK0
   A0-A5 (D14-D19) = PCINT 8-13  = PCIR1 = PC = PCIE1 = PCMSK1
   D0-D7           = PCINT 16-23 = PCIR2 = PD = PCIE2 = PCMSK2
*/
