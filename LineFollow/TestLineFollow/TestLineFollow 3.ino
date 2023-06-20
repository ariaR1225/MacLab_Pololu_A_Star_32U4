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
  lineSpeed = 200;
  calibSpeed = lineSpeed/2;

}
void selectStandard(){
  lineSpeed = 150;
  calibSpeed = lineSpeed/2;
}
void selectTurtle(){
  lineSpeed = 100;
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

void setup(){
  selectTurtle();
  calibSensor();
  showReading();
}

void loop(){
  uint16_t pos = lineSensors.readLineBlack(lineSensorVal);
  if (pos > 1000){
    ledYellow(1);
    motors.setSpeeds(lineSpeed, lineSpeed);
  }
}

