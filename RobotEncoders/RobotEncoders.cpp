#include "RobotEncoders.h"

// Define the static instance pointer
RobotEncoders* RobotEncoders::instance = nullptr;

RobotEncoders::RobotEncoders() {
    instance = this; // Set the instance pointer for ISR access
    leftEncoderValue = 0;
    rightEncoderValue = 0;
}

void RobotEncoders::begin() {
    // Configure Timer1 for a 75 ms interrupt
    noInterrupts(); // Disable interrupts for configuration

    TCCR1A = 0; // Set entire TCCR1A register to 0
    TCCR1B = 0; // Same for TCCR1B

    // Set compare match register for 75ms increments
    OCR1A = 11718; // = 16000000 / (1024 * 1) - 1 (must be <65536)

    // Turn on CTC mode
    TCCR1B |= (1 << WGM12);

    // Set CS10 and CS12 bits for 1024 prescaler
    TCCR1B |= (1 << CS10) | (1 << CS12);

    // Enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);

    interrupts(); // Enable interrupts
}
// ISR function now accessible from outside the class
void RobotEncoders::isr() {
    if (instance) {
        instance->leftEncoderValue = instance->encoders.getCountsAndResetLeft();
        instance->rightEncoderValue = instance->encoders.getCountsAndResetRight();
    }
}

// ISR for Timer1
ISR(TIMER1_COMPA_vect) {
    RobotEncoders::isr();
}