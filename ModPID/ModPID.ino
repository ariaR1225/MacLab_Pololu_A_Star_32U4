#include <Pololu3piPlus32U4.h>
#include <PololuMenu.h>

using namespace Pololu3piPlus32U4;

OLED display;

LineSensors lineSensors;
Motors motors;


#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];

uint16_t maxSpeed = 35; //35
uint16_t minSpeed = 25; //25

uint16_t baseSpeed = minSpeed;

uint16_t calibSpeed = 100;


// uint16_t kp = 4; // coefficient of the P term * 256
// uint16_t kd = 2; // coefficient of the D term * 256
// uint16_t ki = 0; // coefficient of the I term * 256
float kp = 1/64;
float kd = 1/128;
float ki = 0.0;

int16_t prev = 0;
int16_t err_i = 0;

void calibSensor(){
  delay(200);
  display.clear();
  display.print(F("Calib"));
  uint8_t calib_count = 60;
  for(uint16_t i = 0; i < calib_count; i++){
    if (i > calib_count/4 && i <= calib_count/4*3){
      motors.setSpeeds(calibSpeed, -calibSpeed);
    }
    else{
      motors.setSpeeds(-calibSpeed, calibSpeed);
    }
    lineSensors.calibrate();
  }
  motors.setSpeeds(0,0);
}


void setup()
{
  motors.flipLeftMotor(true);
  motors.flipRightMotor(true);
  calibSensor();
}

void loop()
{
  display.clear();
  int16_t pos = lineSensors.readLineBlack(lineSensorValues);

  int16_t err = pos - 2000; // 2000 indicates the middle of the line
  int16_t err_d = err - prev;
  err_i = err_i + err ;
//  int16_t dSpeed = err * (int32_t)kp / 256 + err_d * (int32_t)kd / 256 + err_i * (int32_t)ki / 1024;
  int16_t dSpeed = err*kp + err_d*kd + err_i*ki;
  prev = err;

  int16_t leftSpeed = (int16_t)baseSpeed + dSpeed;
  int16_t rightSpeed = (int16_t)baseSpeed - dSpeed;

  leftSpeed = constrain(leftSpeed, minSpeed, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, minSpeed, (int16_t)maxSpeed);
  display.print(err);
  String serr = String(err);
  Serial.println(err);

  motors.setSpeeds(leftSpeed, rightSpeed);
}
