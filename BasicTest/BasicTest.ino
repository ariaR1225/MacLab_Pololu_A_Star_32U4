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
void loadCustomCharacters()
{
  static const char levels[] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 63, 63, 63, 63, 63, 63, 63
  };
  display.loadCustomCharacter(levels + 0, 0);  // 1 bar
  display.loadCustomCharacter(levels + 1, 1);  // 2 bars
  display.loadCustomCharacter(levels + 2, 2);  // 3 bars
  display.loadCustomCharacter(levels + 3, 3);  // 4 bars
  display.loadCustomCharacter(levels + 4, 4);  // 5 bars
  display.loadCustomCharacter(levels + 5, 5);  // 6 bars
  display.loadCustomCharacter(levels + 6, 6);  // 7 bars
}
void printBar(uint8_t height)
{
  if (height > 8) { height = 8; }
  const char barChars[] = {' ', 0, 1, 2, 3, 4, 5, 6, (char)255};
  display.print(barChars[height]);
}
void showReadings()
{
  display.clear();

  while(!buttonB.getSingleDebouncedPress())
  {
    uint16_t position = lineSensors.readLineBlack(lineSensorVal);

    display.gotoXY(0, 0);
    display.print(position);
    display.print("    ");
    display.gotoXY(0, 1);
    for (uint8_t i = 0; i < NUM_SENSOR; i++)
    {
      uint8_t barHeight = map(lineSensorVal[i], 0, 1000, 0, 8);
      printBar(barHeight);
    }

    delay(50);
  }
}

void setup(){
  loadCustomCharacters();
  selectTurtle();
  motors.setSpeeds(maxSpeed, maxSpeed);
}

void loop(){
  int16_t position = lineSensors.readLineBlack(lineSensorVal);
  display.print(position);
  motors.setSpeeds(maxSpeed, maxSpeed);
}
