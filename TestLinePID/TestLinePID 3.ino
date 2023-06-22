# include <Pololu3piPlus32U4.h>
# include <PololuMenu.h>

# define NUM_SENSOR 5
# define MID_LINE 2000

using namespace Pololu3piPlus32U4;

OLED display; 

LineSensors lineSensors;
Motors motors;

unsigned int lineSensorVal[NUM_SENSOR];

uint16_t highSpeed = 80; // max is 400
uint16_t lowSpeed = 30; // max is 400
uint16_t Speed = 55;
uint16_t calibSpeed = 100; // max is 400

float kp = 0.5; // max is 1
float kd = 0.; // max is 1
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

// Navigation
void turnRight(){
  motors.setSpeeds(lowSpeed,highSpeed);
  //display.print(F("right"));
}
void turnLeft(){
  motors.setSpeeds(highSpeed,lowSpeed);
  //display.print(F("left"));
}
void goForward(){
  motors.setSpeeds(highSpeed,highSpeed);
  //display.print(F("forward"));
}
void goBackward(){
  motors.setSpeeds(-lowSpeed,-lowSpeed);
  //display.print(F("backward"));
}

void setup(){
  calibSensor();
  //showReading();
}

void loop(){
  display.clear();

  uint16_t pos = lineSensors.readLineBlack(lineSensorVal);

  // PD
  float err = pos - MID_LINE;
  float err_d = err - prev;
  uint16_t dSpeed = kp*err - kd*err_d ;
  prev = err;
  // anti-windup
  if (dSpeed < lowSpeed){
    dSpeed = lowSpeed;
  }
  if (dSpeed > highSpeed){
    dSpeed = highSpeed;
  }
  uint16_t lSpeed = Speed + dSpeed;
  uint16_t rSpeed = Speed - dSpeed; 
  motors.setSpeeds(lSpeed, rSpeed);
  display.print(lSpeed); 
  Serial.println(err);
  delay(100);
}

