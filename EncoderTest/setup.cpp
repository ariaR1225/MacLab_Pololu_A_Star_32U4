#include <Arduino.h>

#include <Pololu3piPlus32U4.h>

using namespace Pololu3piPlus32U4;
Encoders encoders;

volatile long encoderPosition = 0;
int lastEncoded = 0;

void setup() {
  Serial.begin(9600);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(2), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), updateEncoder, CHANGE);

  // Configure Timer 1 for 1 kHz
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; //initialize counter value to 0
  // set compare match register for 1 kHz increments
  OCR1A = 15999; // = 16000000 / (1 * 1000) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 bit for no prescaler
  TCCR1B |= (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
}

ISR(TIMER1_COMPA_vect) {
  // Timer1 interrupt service routine
  // This code runs every 1 ms
  // You can use this ISR to handle time-sensitive tasks,
  // but keep it short to avoid affecting the timer accuracy.
}

void updateEncoder() {
  int MSB = digitalRead(2); //MSB = most significant bit
  int LSB = digitalRead(3); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderPosition++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderPosition--;

  lastEncoded = encoded; //store this value for next time
}

void loop() {
  Serial.println(encoderPosition);
  delay(100); // Just to make the output readable
}
