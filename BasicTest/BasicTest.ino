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

uint16_t maxSpeed; // max is 400

// Select Mode
void selectHyper(){
  motors.flipLeftMotor(true);
  motors.flipRightMotor(true);
  maxSpeed = 150;
}
void selectStandard(){
  motors.flipLeftMotor(true);
  motors.flipRightMotor(true);
  maxSpeed = 100;
}
void selectTurtle(){
  motors.flipLeftMotor(true);
  motors.flipRightMotor(true);
  maxSpeed = 50;
}

// Display Readings
void showReadings(){
  while(1){
    display.clear();
    lineSensors.read(lineSensorVal);
    display.gotoXY(0, 0);
    display.print(lineSensorVal[0]);
    delay(100);
  }
}

void setup(){
  selectTurtle();
  showReadings();
}

void loop(){
  motors.setSpeeds(maxSpeed, maxSpeed);
}
