#include <Pololu3piPlus32U4Encoders.h>
#include <FastGPIO.h>
#include <avr/interrupt.h>
#include <Arduino.h>

// ... existing library code ...

namespace Pololu3piPlus32U4
{
    // ... existing namespace variables and functions ...

    // New variables to store speed
    static volatile int16_t speedLeft = 0;
    static volatile int16_t speedRight = 0;

    // Constants to define the timer period
    // The timer frequency (in Hz) - how often the timer interrupt will occur
    const uint16_t timerFrequency = 1000; // 1000 Hz or 1ms interval
    // The number of encoder counts per revolution of the wheel
    const uint16_t countsPerRevolution = 12; // Adjust this as necessary for your encoder

    // The wheel diameter (in meters)
    const float wheelDiameter = 0.1; // Adjust this as necessary for your wheel size

    // Function prototypes
    void calculateSpeed();

    void Encoders::initSpeedCalculation()
    {
        // Calculate the necessary timer count for the interval you want
        // Assumes a 16 MHz clock
        // Formula: timer count = (CPU frequency / prescaler) / desired frequency - 1
        uint16_t timerCount = (16000000 / (1 << 0) / timerFrequency) - 1;

        // Configure Timer1
        TCCR1A = 0; // set entire TCCR1A register to 0
        TCCR1B = 0; // same for TCCR1B

        // Set compare match register to desired timer count
        OCR1A = timerCount;

        // Turn on CTC mode
        TCCR1B |= (1 << WGM12);

        // Set CS10 bit for no prescaling
        TCCR1B |= (1 << CS10);

        // Enable timer compare interrupt
        TIMSK1 |= (1 << OCIE1A);

        // Initialize last read counts to zero
        countLeft = 0;
        countRight = 0;
    }

    // Timer1 ISR
    ISR(TIMER1_COMPA_vect)
    {
        calculateSpeed();
    }

    // Function to calculate the speed of the robot
    void calculateSpeed()
    {
        // Disable interrupts to get a consistent snapshot of the count variables
        cli();
        int16_t countsLeftSinceLast = countLeft;
        int16_t countsRightSinceLast = countRight;

        // Reset the count for the next period
        countLeft = 0;
        countRight = 0;

        // Re-enable interrupts
        sei();

        // Calculate speed in meters per second
        // Speed = (Counts / Counts per Revolution) * (Wheel Diameter * PI) / (Time per interrupt)
        float leftWheelSpeed = (countsLeftSinceLast / (float)countsPerRevolution) * (wheelDiameter * PI) / (1.0 / timerFrequency);
        float rightWheelSpeed = (countsRightSinceLast / (float)countsPerRevolution) * (wheelDiameter * PI) / (1.0 / timerFrequency);

        // Store the speed in a volatile variable if needed elsewhere in your program
        speedLeft = static_cast<int16_t>(leftWheelSpeed * 1000); // speed in mm/s
        speedRight = static_cast<int16_t>(rightWheelSpeed * 1000); // speed in mm/s
    }

    // Function to return the left wheel speed
    int16_t Encoders::getSpeedLeft()
    {
        int16_t speed = speedLeft;
        return flip ? -speed : speed;
    }

    // Function to return the right wheel speed
    int16_t Encoders::getSpeedRight()
    {
        int16_t speed = speedRight;
        return flip ? -speed : speed;
    }
}
  
 #define LEFT_XOR   8
 #define LEFT_B     IO_E2
 #define RIGHT_XOR  7
 #define RIGHT_B    23
  
 namespace Pololu3piPlus32U4
 {
  
 static volatile bool lastLeftA;
 static volatile bool lastLeftB;
 static volatile bool lastRightA;
 static volatile bool lastRightB;
  
 static volatile bool errorLeft;
 static volatile bool errorRight;
  
 // These count variables are uint16_t instead of int16_t because
 // signed integer overflow is undefined behavior in C++.
 static volatile uint16_t countLeft;
 static volatile uint16_t countRight;
  
 ISR(PCINT0_vect)
 {
     bool newLeftB = FastGPIO::Pin<LEFT_B>::isInputHigh();
     bool newLeftA = FastGPIO::Pin<LEFT_XOR>::isInputHigh() ^ newLeftB;
  
     countLeft += (newLeftA ^ lastLeftB) - (lastLeftA ^ newLeftB);
  
     if((lastLeftA ^ newLeftA) & (lastLeftB ^ newLeftB))
     {
         errorLeft = true;
     }
  
     lastLeftA = newLeftA;
     lastLeftB = newLeftB;
 }
  
 static void rightISR()
 {
     bool newRightB = FastGPIO::Pin<RIGHT_B>::isInputHigh();
     bool newRightA = FastGPIO::Pin<RIGHT_XOR>::isInputHigh() ^ newRightB;
  
     countRight += (newRightA ^ lastRightB) - (lastRightA ^ newRightB);
  
     if((lastRightA ^ newRightA) & (lastRightB ^ newRightB))
     {
         errorRight = true;
     }
  
     lastRightA = newRightA;
     lastRightB = newRightB;
 }
  
 void Encoders::init2()
 {
     // Set the pins as pulled-up inputs.
     FastGPIO::Pin<LEFT_XOR>::setInputPulledUp();
     FastGPIO::Pin<LEFT_B>::setInputPulledUp();
     FastGPIO::Pin<RIGHT_XOR>::setInputPulledUp();
     FastGPIO::Pin<RIGHT_B>::setInputPulledUp();
  
     // Enable pin-change interrupt on PB4 for left encoder, and disable other
     // pin-change interrupts.
     PCICR = (1 << PCIE0);
     PCMSK0 = (1 << PCINT4);
     PCIFR = (1 << PCIF0);  // Clear its interrupt flag by writing a 1.
  
     // Enable interrupt on PE6 for the right encoder.  We use attachInterrupt
     // instead of defining ISR(INT6_vect) ourselves so that this class will be
     // compatible with other code that uses attachInterrupt.
     attachInterrupt(4, rightISR, CHANGE);
  
     // Initialize the variables.  It's good to do this after enabling the
     // interrupts in case the interrupts fired by accident as we were enabling
     // them.
     lastLeftB = FastGPIO::Pin<LEFT_B>::isInputHigh();
     lastLeftA = FastGPIO::Pin<LEFT_XOR>::isInputHigh() ^ lastLeftB;
     countLeft = 0;
     errorLeft = 0;
  
     lastRightB = FastGPIO::Pin<RIGHT_B>::isInputHigh();
     lastRightA = FastGPIO::Pin<RIGHT_XOR>::isInputHigh() ^ lastRightB;
     countRight = 0;
     errorRight = 0;
 }
  
 bool Encoders::flip;
  
 void Encoders::flipEncoders(bool f)
 {
   flip = f;
 }
  
 int16_t Encoders::getCountsLeft()
 {
     init();
  
     cli();
     int16_t counts = countLeft;
     sei();
     return flip ? -counts : counts;
 }
  
 int16_t Encoders::getCountsRight()
 {
     init();
  
     cli();
     int16_t counts = countRight;
     sei();
     return flip ? -counts : counts;
 }
  
 int16_t Encoders::getCountsAndResetLeft()
 {
     init();
  
     cli();
     int16_t counts = countLeft;
     countLeft = 0;
     sei();
     return flip ? -counts : counts;
 }
  
 int16_t Encoders::getCountsAndResetRight()
 {
     init();
  
     cli();
     int16_t counts = countRight;
     countRight = 0;
     sei();
     return flip ? -counts : counts;
 }
  
 bool Encoders::checkErrorLeft()
 {
     init();
  
     bool error = errorLeft;
     errorLeft = 0;
     return error;
 }
  
 bool Encoders::checkErrorRight()
 {
     init();
  
     bool error = errorRight;
     errorRight = 0;
     return error;
 }
  
 }
