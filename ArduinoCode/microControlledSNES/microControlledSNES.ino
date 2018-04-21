#include <LiquidCrystal.h>
// microControllerSNES.ino
// Takes commands from serial and sends to pins
// Used to controlled an SNES mini controller using Twitch IRC
// Copyright (C) 2018: CommunityController


// Setting up the LCD
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
 
// map of pins
// LED connected to digital pin 9
enum pinMap  {
  LEFT_PIN = 24,
  RIGHT_PIN = 26,
  UP_PIN = 30,
  DOWN_PIN = 28,
  A_PIN = 40,
  B_PIN = 38,
  X_PIN = 42,
  Y_PIN = 44,
  L_PIN = 32,
  R_PIN = 40,
  SELECT_PIN = 36,
  START_PIN = 34,
};


// setup method:
void setup()
{
  // set standard baud rate
  Serial.begin(9600);

  // sanity check, print ready back through serial
  Serial.println("Ready");
  lcd.print("I'm Ready!");

  // Setting pins to INPUT spoof a 100 MOhm resistor
  pinMode(LEFT_PIN, INPUT);
  pinMode(RIGHT_PIN, INPUT);
  pinMode(UP_PIN, INPUT);
  pinMode(DOWN_PIN, INPUT);
  pinMode(B_PIN, INPUT);
  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);
  pinMode(L_PIN, INPUT);
  pinMode(R_PIN, INPUT);
  pinMode(SELECT_PIN, INPUT);
  pinMode(START_PIN, INPUT);
}

// button presses
boolean buttonPress (unsigned int a_unButton, unsigned char a_ucNumPresses) {

  for (int iii = 1; iii <= a_ucNumPresses; iii++)  {
    // set specific pin to output voltage
    pinMode(a_unButton, OUTPUT);

    // write pin low to simulate pressing
    digitalWrite(a_unButton, LOW);
    delay(100);

    // reset pin back to input voltage
    pinMode(a_unButton, INPUT);
    delay(250);
  }
  return true;
}


// prints out on the attached LCD whenever there is a valid button push
unsigned int ifValidButtonPush (char a_cButton) {
  // Sucess status of button press
  boolean bPressStatus = true;

  switch (a_cButton) {
    case 'L':
      buttonPress(LEFT_PIN, 1);
      lcd.print("Moving left!");
      break;

    case 'R':
      buttonPress(RIGHT_PIN, 1);
      lcd.print("Moving right!");
      break;

    case 'U':
      buttonPress(UP_PIN, 1);
      lcd.print("Moving up!");
      break;

    case 'D':
      buttonPress(DOWN_PIN, 1);
      lcd.print("Moving down!");
      break;

    case 'A':
      buttonPress(A_PIN, 1);
      lcd.print("Pressing A!");
      break;

    case 'B':
      buttonPress(B_PIN, 1);
      lcd.print("Pressing B!");
      break;

    case 'X':
      buttonPress(X_PIN, 1);
      lcd.print("Pressing X!");
      break;

    case 'Y':
      buttonPress(Y_PIN, 1);
      lcd.print("Pressing Y!");
      break;

    case 'H':
      buttonPress(L_PIN, 1);
      lcd.print("Pressing the left trigger!");
      break;

    case 'C':
      buttonPress(R_PIN, 1);
      lcd.print("Pressing the right trigger!");
      break;

    case 'E':
      buttonPress(SELECT_PIN, 1);
      lcd.print("Pressing Select!");
      break;

    case 'S':
      buttonPress(START_PIN, 1);
      lcd.print("Pressing Start!");
      break;
    default:
      bPressStatus = false;
      break;
  }
  return bPressStatus;
}

// main loop
void loop()
{
  // Variable to store command from IRC
  char cInputCommand = ' ';

  // Ensure serial is not busy (checks if data has been sent before reading again)
  if (Serial.available()) {

    // Read the incoming data
    cInputCommand = Serial.read();

    // Send command to push button
    ifValidButtonPush(cInputCommand);

    // TODO: Is this even necessary?
    // send the command back in a new line so that it is not all one long line
    Serial.println(cInputCommand);
  }
  delay(100); // delay for 1/10 of a second
}
