// Include global variables and pin definitions
#include "globals.h"
#include <vector>
// Include Game 1
#include "Game1.h" 
#include "Game2.h"
#include "Game3.h"
#include "Game4.h"

TM1638plus tm(PIN_STB, PIN_CLK, PIN_DIO );
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_BTN, INPUT_PULLUP);
  Serial.begin(9600); // initialize serial communication

  // Initialize the whadda model
  tm.displayBegin();
   // Initialize the display
  lcd.init();
  // Turn off the backlight
  lcd.noBacklight();
  delay(2000); // Wait for 2 seconds
  // Turn on the backlight
  lcd.backlight();
  delay(2000); // Wait for another 2 seconds
}

unsigned long startTimeMain = 0;
const unsigned long timeLimit =  8 * 60 * 1000; // 8 minutes in millisecond;
int totalScore = 0;

int gameScore1;
int gameScore2;
int gameScore3;
int gameScore4;

int gamesFinished = 0;

bool gameGoing = true;
bool timeGameOut = false;

void loop() {
  startTimeMain = millis();

  while (gameGoing && !timeGameOut) {
    //GAME 1
    gameScore1 = playGame1(startTimeMain, timeLimit);

    if (hasTimeExceeded(startTimeMain, timeLimit)) {
      printTimeOut();
      timeGameOut = true;
      break;
    } else {
      totalScore += gameScore1;
      gamesFinished++;
      printScore(totalScore);
    }

   //GAME 2
    gameScore2 = playGame2(startTimeMain, timeLimit);

    if (hasTimeExceeded(startTimeMain, timeLimit)) {
      printTimeOut();
      timeGameOut = true;
      break;
    } else {
      totalScore += gameScore2;
      gamesFinished++;
      printScore(totalScore);
    }

     //GAME 3
    gameScore3 = playGame3(startTimeMain, timeLimit);

    if (hasTimeExceeded(startTimeMain, timeLimit)) {
      printTimeOut();
      timeGameOut = true;
      break;
    } else {
      gamesFinished++;
      totalScore += gameScore3;
      printScore(totalScore);
    }

    //GAME 4
    gameScore4 = playGame4(startTimeMain, timeLimit);

    if (hasTimeExceeded(startTimeMain, timeLimit)) {
      printTimeOut();
      timeGameOut = true;
      break;
    } else {
      gamesFinished++;
      totalScore += gameScore4;
      printScore(totalScore);
    }

    gameGoing = false;
  }

  if (!timeGameOut) {
    printFinalScore();
  }
}


void printScore(int score){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your score is: " );
  lcd.setCursor(0, 1);
  lcd.print(String(score) + " POINTS!");
    delay(2000);
}

void printFinalScore(){
   lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Congratulations!!!" );
   lcd.clear();
   delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("You collected: ");
   lcd.setCursor(0, 1);
  lcd.print(String(totalScore) + " points!");
    delay(3000);
}