#include <Pololu3piPlus32U4.h>
#include <PololuMenu.h>
#include "gbuffer.h"
#include "gbufferconnector.h"
#include "uart_def.h"
#include "uart.h"

extern GBufferConnector conn;
using namespace Pololu3piPlus32U4;

OLED display;
ButtonA buttonA;
LineSensors lineSensors;
Motors motors;

#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];

uint16_t maxSpeed = 250; 
uint16_t minSpeed = 200; 

uint16_t baseSpeed = minSpeed;

uint16_t calibSpeed = 100;


uint16_t kp; // coefficient of the P term * 256
uint16_t kd; // coefficient of the D term * 256
uint16_t ki; // coefficient of the I term * 256

int16_t prev = 0;
int16_t err_i = 0;

void DtoB(int16_t val) {

    // Extract the last 7 bits (LSB) and the sign bit + first 4 bits (MSB)
    uint16_t num = abs(val);
    unsigned char byteL = num & 0b1111111;
    unsigned char byteH = (num >> 7) & 0b1111;
    unsigned char signBit;

    if(val<0){
      signBit = 0b00000;
    }
    else{
      signBit = 0b10000;
    }

    uint8_t A = signBit | byteH;
    uint8_t B = 0b10000000 | byteL;

    UART_IO_BYTE = A;
    Serial.print("H: ");
    Serial.println(byteH);
    UART_IO_BYTE = B;
    Serial.print("L: ");
    Serial.println(byteL);
}

void PIDParam(){
  uint16_t battery = readBatteryMillivolts();
  if(battery > 3500){
    kp = 160;
    kd = 270;
    ki = 2;
  }
  else{
    kp = 125;
    kd = 190;
    ki = 1;
  }
}

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
  if (err_i > 200000){
    err_i = 200000;
  }
  if (err_i<-20000){
    err_i = -200000;
  }
  // 300000
  PIDParam();
  int16_t dSpeed = err * (int32_t)kp / 256 + err_d * (int32_t)kd / 256 + err_i * (int32_t)ki / 256;
  prev = err;

  int16_t leftSpeed = (int16_t)baseSpeed + dSpeed;
  int16_t rightSpeed = (int16_t)baseSpeed - dSpeed;
  
  leftSpeed = constrain(leftSpeed, minSpeed, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, minSpeed, (int16_t)maxSpeed);

  motors.setSpeeds(leftSpeed, rightSpeed);
  uint16_t battery = readBatteryMillivolts();
  display.print(battery);
  // delay(100);
  if (buttonA.getSingleDebouncedPress()){
    err = 0;
    prev = 0;
    err_i = 0;
    delay(100);
  }
}
