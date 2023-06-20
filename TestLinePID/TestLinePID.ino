# include <Pololu3piPlus32U4.h>
# include <PololuMenu.h>

# define NUM_SENSOR 5
# define MID_LINE 2000

using namespace Pololu3piPlus32U4;

OLED display; 

LineSensors lineSensors;
Motors motors;

unsigned int lineSensorVal[NUM_SENSOR];

uint16_t lineSpeed = 50; // max is 400
uint16_t calibSpeed = 100; // max is 400

uint16_t kp = .5; // max is 1
uint16_t kd = 0; // max is 1
uint16_t err;
uint16_t prev = 0;

// Calibration
void calibSensor(){
  delay(500);
  display.clear();
  display.print(F("Calib"));
  for(uint16_t i = 0; i < 100; i++){
    if (i > 25 && i <= 75){
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
  motors.setSpeeds(0,lineSpeed);
  display.print(F("right"));
}
void turnLeft(){
  motors.setSpeeds(lineSpeed,0);
  display.print(F("left"));
}
void goForward(){
  motors.setSpeeds(lineSpeed,lineSpeed);
  display.print(F("forward"));
}
void goBackward(){
  motors.setSpeeds(lineSpeed,lineSpeed);
  display.print(F("backward"));
}


void setup(){
  calibSensor();
  //showReading();
}

void loop(){
  uint16_t pos = lineSensors.readLineBlack(lineSensorVal);
  uint16_t npos;
  uint16_t dpos; 
  // turn left 
  display.clear();
  err = pos - 2000;
  dpos = err * kp + (err - prev) * kd;
  prev = err;
  npos = pos + dpos;
  pos = npos;
  
  if (npos >= 0 && npos < 1000){
    turnLeft();
  }
  // go straight
  else if (npos >= 1000 && npos < 3000){
    goForward();
  }
  // turn right
  else if (npos > 3000 && npos <= 4000){
    turnRight();
  }
  else{
    motors.setSpeeds(0,0);
    display.print(F("error"));
  }
  delay(50);
}

