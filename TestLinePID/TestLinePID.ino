// Line Following with PID Control

// Pin Definitions
#define LEFT_MOST_SENSOR A0
#define LEFT_SENSOR A1
#define CENTER_SENSOR A2
#define RIGHT_SENSOR A3
#define RIGHT_MOST_SENSOR A4
#define LEFT_MOTOR_PIN 5
#define RIGHT_MOTOR_PIN 6

// PID Constants
float kp = 1.2;   // Proportional constant
float ki = 1.0;   // Integral constant
float kd = 0.8;   // Derivative constant

// Setpoint (desired position on the line)
int setpoint = 512;

// Variables
int leftMostSensorValue, leftSensorValue, centerSensorValue, rightSensorValue, rightMostSensorValue;
int leftMotorSpeed, rightMotorSpeed;
int lastError = 0;
float integral = 0;

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);

  // Set pin modes
  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
}

void loop() {
  // Read sensor values
  leftMostSensorValue = analogRead(LEFT_MOST_SENSOR);
  leftSensorValue = analogRead(LEFT_SENSOR);
  centerSensorValue = analogRead(CENTER_SENSOR);
  rightSensorValue = analogRead(RIGHT_SENSOR);
  rightMostSensorValue = analogRead(RIGHT_MOST_SENSOR);

  // Calculate error
  int error = centerSensorValue - setpoint;

  // PID control
  integral += error;
  float derivative = error - lastError;
  float output = kp * error + ki * integral + kd * derivative;

  // Map the output to motor speeds
  leftMotorSpeed = constrain(255 - output, 0, 255);
  rightMotorSpeed = constrain(255 + output, 0, 255);

  // Apply motor speeds
  analogWrite(LEFT_MOTOR_PIN, leftMotorSpeed);
  analogWrite(RIGHT_MOTOR_PIN, rightMotorSpeed);

  // Print sensor readings to Serial Monitor
  Serial.print("Sensor Readings: ");
  Serial.print(leftMostSensorValue);
  Serial.print(" | ");
  Serial.print(leftSensorValue);
  Serial.print(" | ");
  Serial.print(centerSensorValue);
  Serial.print(" | ");
  Serial.print(rightSensorValue);
  Serial.print(" | ");
  Serial.println(rightMostSensorValue);

  // Print values to Serial Monitor
  Serial.print("Error: ");
  Serial.print(error);
  Serial.print(" | Output: ");
  Serial.println(output);

  // Update last error
  lastError = error;
}
