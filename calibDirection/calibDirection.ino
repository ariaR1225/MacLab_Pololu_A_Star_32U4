#include <Wire.h>
#include <Pololu3piPlus32U4.h>
#include <PololuMenu.h>
#include <Pololu3piPlus32U4IMU.h>

using namespace Pololu3piPlus32U4;

OLED display;
LineSensors lineSensors;
Motors motors;
IMU imu;

//#include "TurnSensor.h"
#include "SensorGyroZ.h"

uint16_t calibSpeed = 100;

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

void sensorReadShow(){
  sensorUpdate();
  display.clear();
  display.print((((int32_t)ang >> 16) * 360) >> 16);
  display.print(F("   "));
  delay(100);

}

void setup(){
  sensorSetup();
  sensorReadShow();
  calibSensor();
  sensorReadShow();
 }

void loop(){
  // if button A is pressed >> reset
  sensorUpdate();
  display.clear();
  display.print((((int32_t)ang >> 16) * 360) >> 16);
  display.print(F("   "));
  delay(100);
}