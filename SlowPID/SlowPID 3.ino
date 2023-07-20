# include <Pololu3piPlus32U4.h>
# include <PololuMenu.h>

# define NUM_SENSOR 5
# define MID_LINE 2000

using namespace Pololu3piPlus32U4;

OLED display; 

LineSensors lineSensors;
Motors motors;

unsigned int lineSensorVal[NUM_SENSOR];

uint16_t highSpeed = 25; // max is 400
uint16_t lowSpeed = 15; // max is 400
uint16_t Speed = 20;
uint16_t calibSpeed = 100; // max is 400

float kp = 1/4; // max is 1
float kd = .0; // max is 1
float prev = 0;

// Calibration
void calibSensor(){
  delay(500);
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

// Display Readings
void showReading(){
  while(1){
    display.clear();
    //lineSensors.read(lineSensorVal);
    uint16_t pos = lineSensors.readLineBlack(lineSensorVal);
    display.gotoXY(0, 0);
    display.print(pos);
    delay(100);
  }
}

void setup(){
  calibSensor();
  //showReading();
}

void loop(){
  display.clear();
  int16_t pos = lineSensors.readLineBlack(lineSensorVal);

  // PD
  // need to scale pos err and speed?
  // pos err -2000 ~ 2000
  // speed range -5 ~ 5 (0 ~ 400)
  int16_t err = pos - MID_LINE;
  int16_t err_d = err - prev;
  int16_t dSpeed = kp*err - kd*err_d ;
  prev = err;

  int16_t lSpeed = Speed + dSpeed;
  int16_t rSpeed = Speed - dSpeed; 

    // anti-windup
  if (lSpeed < lowSpeed){
    lSpeed = lowSpeed;
  }
  if (lSpeed > highSpeed){
    lSpeed = highSpeed;
  }
  if (rSpeed < lowSpeed){
    rSpeed = lowSpeed;
  }
  if (rSpeed > highSpeed){
    rSpeed = highSpeed;
  }

  //motors.setSpeeds(lSpeed, rSpeed);
  display.print(kp);
  delay(100);
}

