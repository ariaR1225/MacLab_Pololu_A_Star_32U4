# include <Pololu3piPlus32U4.h>
# include <PololuMenu.h>

# define NUM_SENSOR 5

using namespace Pololu3piPlus32U4;

OLED display; 

LineSensors lineSensors;
Motors motors;
ButtonA buttonA;
ButtonB buttonB;
ButtonC buttonC;

unsigned int lineSensorVal[NUM_SENSOR];

uint16_t lineSpeed; // max is 400
uint16_t calibSpeed; // max is 400

// Select Mode
void selectHyper(){
  lineSpeed = 300;
  calibSpeed = lineSpeed/2;

}
void selectStandard(){
  lineSpeed = 250;
  calibSpeed = lineSpeed/2;
}
void selectTurtle(){
  lineSpeed = 80;
  calibSpeed = lineSpeed/2;
}

// Calibration
void calibSensor(){
  delay(1000);
  display.clear();
  display.print(F("Calib"));
  for(uint16_t i = 0; i < 100; i++){
    if (i > 25 && i <= 75){
      motors.setSpeeds(calibSpeed,-calibSpeed);
    }
    else{
      motors.setSpeeds(-calibSpeed,calibSpeed);
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
void goStraight(){
  motors.setSpeeds(lineSpeed,lineSpeed);
  display.print(F("straight"));
}

void setup(){
  selectTurtle();
  calibSensor();
  //showReading();
}

void loop(){
  uint16_t pos = lineSensors.readLineBlack(lineSensorVal);
  // turn left 
  display.clear();
  if (pos >= 0 && pos < 1000){
    turnLeft();
  }
  // go straight
  else if (pos >= 1000 && pos < 3000){
    goStraight();
  }
  // turn right
  else if (pos > 3000 && pos <= 4000){
    turnRight();
  }
  else{
    motors.setSpeeds(0,0);
    display.print(F("error"));
  }
  delay(50);
}

