# include <Pololu3piPlus32U4.h>
# include <PololuMenu.h>

# define NUM_SENSOR 5

using namespace Pololu3piPlus32U4;

OLED display; 

LineSensors lineSensors;
Motors motors;

unsigned int lineSensorVal[NUM_SENSOR];

uint16_t lineSpeed; // max is 400
uint16_t calibSpeed; // max is 400
uint16_t avepos;
uint16_t sensorValues[5];
uint16_t K = .5;
uint16_t linePos;


// Select Mode
void selectHyper(){
  lineSpeed = 300;
  calibSpeed = lineSpeed;

}
void selectStandard(){
  lineSpeed = 250;
  calibSpeed = lineSpeed;
}
void selectTurtle(){
  lineSpeed = 100;
  calibSpeed = 60;
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
  display.clear();
  display.print(F("Finished"));
  delay(6000);
}
// Display Readings
void showReading(){
    for(uint16_t j = 0;j < 5; j++){
        display.clear();
        display.gotoXY(0, 0);
        display.print(j+1);
        display.print(sensorValues[j]);
        delay(1000);
    }
}



void setup(){
  selectTurtle();
  calibSensor();
  //showReading();
}



void loop(){
  motors.setSpeeds(0,0);
  lineSensors.read(sensorValues);
  linePos = (int(sensorValues[2])-int(sensorValues[0])) + K*(int(sensorValues[2])-int(sensorValues[1])) + K*(int(sensorValues[3])-int(sensorValues[2])) + (int(sensorValues[4])-int(sensorValues[2]));
  showReading();
  display.clear();
  display.print(F("Loop D"));
  delay(1000);
  display.clear();
  display.print(int(linePos));
  delay(2000);
  
}





