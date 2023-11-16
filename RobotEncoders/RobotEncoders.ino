#include <Pololu3piPlus32U4Encoders.h>
#include "RobotEncoders.h"

RobotEncoders robotEncoders;

// PD Controller Parameters
float kp = 1.0; // Proportional gain
float kd = 0.1; // Derivative gain

// Desired Speeds (Setpoints)
float desiredLeftSpeed = 0.0;
float desiredRightSpeed = 0.0;

// Previous errors for derivative calculation
float previousLeftError = 0.0;
float previousRightError = 0.0;

void setup() {
    Serial.begin(9600);
    robotEncoders.begin(); // Initialize the robot encoders
}

void loop() {

    // Calculate current speeds
    float currentLeftSpeed = robotEncoders.leftEncoderValue / 75.0;
    float currentRightSpeed = robotEncoders.rightEncoderValue / 75.0;

    // Calculate errors
    float leftError = desiredLeftSpeed - currentLeftSpeed;
    float rightError = desiredRightSpeed - currentRightSpeed;

    // Calculate derivative of errors
    float leftDerivative = (leftError - previousLeftError);
    float rightDerivative = (rightError - previousRightError);

    // Calculate control signals
    float leftControl = Kp * leftError + Kd * leftDerivative;
    float rightControl = Kp * rightError + Kd * rightDerivative;

    // Actuate motors with control signals
    // Note: You'll need to write the code to actually control the motors based on the control signals
    // e.g., setMotorSpeed(leftControl, rightControl);

    // Update previous error and time for next iteration
    previousLeftError = leftError;
    previousRightError = rightError;
    previousTime = currentTime;

    // Print debug information
    Serial.print("Left Control: ");
    Serial.print(leftControl);
    Serial.print(", Right Control: ");
    Serial.println(rightControl);

    delay(100); // Adjust this delay based on your control loop requirements
}
