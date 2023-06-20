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
  maxSpeed = 200;
}
void selectStandard(){
  motors.flipLeftMotor(true);
  motors.flipRightMotor(true);
  maxSpeed = 200;
}
void selectTurtle(){
  motors.flipLeftMotor(true);
  motors.flipRightMotor(true);
  maxSpeed = 200;
}

// Display Readings
void showReadings(){
  while(1){
    display.clear();
    lineSensors.read(lineSensorVal);
    uint16_t pos;
    pos = lineSensors.readLineBlack(lineSensorVal);
    display.gotoXY(0, 0);
    display.print(pos);
    delay(10);
  }
}

void setup(){
  selectStandard();
  lineSensors.emittersOn();
  showReadings();
}

void loop(){
  uint16_t pos;
  pos = lineSensors.readLineBlack(lineSensorVal);
  if (pos > 2000){
    ledRed(1);
    motors.setSpeeds(maxSpeed, maxSpeed); 
  }
}
