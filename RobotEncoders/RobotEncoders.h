#ifndef RobotEncoders_h
#define RobotEncoders_h

#include <Arduino.h>
#include <Pololu3piPlus32U4Encoders.h>  // This is an example, use the correct header file name


class RobotEncoders {
public:
    RobotEncoders();
    void begin();
    volatile int16_t leftEncoderValue;
    volatile int16_t rightEncoderValue;
    static RobotEncoders* instance; // Static instance for ISR access
    static void isr();              // ISR for the timer - now public

private:
    Pololu3piPlus32U4::Encoders encoders; // Use the correct type from the Pololu library
};

#endif
