#include <Wire.h>
#include <Pololu3piPlus32U4.h>
#include <PololuMenu.h>
#include <Pololu3piPlus32U4IMU.h>

using namespace Pololu3piPlus32U4;

OLED display;
Motors motors;
IMU imu;

//#include "TurnSensor.h"
#include "SensorGyroZ.h"

void setup(){
  sensorSetup();
 }

void loop(){
  sensorUpdate();
  display.clear();
  display.print((((int32_t)ang >> 16) * 360) >> 16);
  display.print(F("   "));
  delay(100);
}