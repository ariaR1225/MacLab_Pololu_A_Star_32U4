#include <Pololu3piPlus32U4.h>

using namespace Pololu3piPlus32U4;

Encoders encoders;
Buzzer buzzer;
Motors motors;
ButtonA buttonA;
ButtonC buttonC;

const char encoderErrorLeft[] PROGMEM = "!<c2";
const char encoderErrorRight[] PROGMEM = "!<e2";

char report[80];

void setup(){}

void loop()
{
  static uint8_t displayErrorLeftCountdown = 0;
  static uint8_t displayErrorRightCountdown = 0;

  if ((uint8_t)(millis() - lastDisplayTime) >= 100)
  {
    lastDisplayTime = millis();

    int16_t countsLeft = encoders.getCountsLeft();
    int16_t countsRight = encoders.getCountsRight();

    bool errorLeft = encoders.checkErrorLeft();
    bool errorRight = encoders.checkErrorRight();

    if (errorLeft)
    {
      // An error occurred on the left encoder channel.
      // Display it for the next 10 iterations and also beep.
      displayErrorLeftCountdown = 10;
      //buzzer.playFromProgramSpace(encoderErrorLeft);
    }

    if (errorRight)
    {
      // An error occurred on the right encoder channel.
      // Display for the next 10 iterations and also beep.
      displayErrorRightCountdown = 10;
      //buzzer.playFromProgramSpace(encoderErrorRight);
    }

    // Update the screen with encoder counts and error info.
    display.noAutoDisplay();
    display.clear();
    display.print(countsLeft);
    display.gotoXY(0, 1);
    display.print(countsRight);
    if (displayErrorLeftCountdown)
    {
      // Show an exclamation point on the first line to
      // indicate an error from the left encoder.
      display.gotoXY(7, 0);
      display.print('!');
      displayErrorLeftCountdown--;
    }
    if (displayErrorRightCountdown)
    {
      // Show an exclamation point on the second line to
      // indicate an error from the left encoder.
      display.gotoXY(7, 1);
      display.print('!');
      displayErrorRightCountdown--;
    }
    display.display();

    // Send the information to the serial monitor also.
    snprintf_P(report, sizeof(report),
        PSTR("%6d %6d %1d %1d"),
        countsLeft, countsRight, errorLeft, errorRight);
    Serial.println(report);
  }

  if (buttonA.isPressed())
  {
    motors.setSpeeds(400, 400);
  }
  else if (buttonC.isPressed())
  {
    motors.setSpeeds(-400, -400);
  }
  else
  {
    motors.setSpeeds(0, 0);
  }
}
