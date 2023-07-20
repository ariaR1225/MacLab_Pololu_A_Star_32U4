#include <Wire.h>
#include <Pololu3piPlus32U4.h>
#include <Pololu3piPlus32U4IMU.h>

using namespace Pololu3piPlus32U4;

IMU imu;

//#include "TurnSensor.h"

char buffer[100];

void setup()
{
  Wire.begin();

  if (!imu.init())
  {
    // Failed to detect the compass.
    ledRed(1);
    while(1)
    {
      Serial.println(F("Failed to initialize IMU sensors."));
      delay(100);
    }
  }

  imu.enableDefault();
}
void loop() {
  imu.read();
  snprintf_P(buffer, sizeof(buffer), PSTR("Z: %6d"), 
    imu.g.z
  );
  Serial.println(buffer);

  delay(100);
}
