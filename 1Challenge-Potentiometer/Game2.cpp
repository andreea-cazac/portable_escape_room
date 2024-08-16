#include "globals.h"
#include "Arduino.h"
#include "Game2.h"

unsigned long gameLoopStartTime = 0;
unsigned long gameLoopInterval = 1000;
bool buttonChecked = false;
std::array<int, 3> COLOR_TO_MATCH = generateColor();
int score = 0;
int SCORE_TO_ACHIEVE = 6;
int points = 200 ;

unsigned long gameStartTime = millis();

int playGame2(unsigned long startTimeMain, unsigned long timeLimit) {
  randomSeed(analogRead(A1));
  gameStartTime = millis();

  printWelcomeMsg2();
  printHuntedColor();
  delay(1000);

  while (score < SCORE_TO_ACHIEVE) {
    std::array<int, 3> returnedColor;
    bool colorChangeTimeExceeded = millis() - gameLoopStartTime > gameLoopInterval;
    if (colorChangeTimeExceeded) {
      returnedColor = generateColor();
      setColor(returnedColor[0], returnedColor[1], returnedColor[2]);
      gameLoopStartTime = millis();
    }

//Check button state
    if (readDebouncedButton2(PIN_BTN)) {
      gameLoopInterval = checkColor(returnedColor);
    }
    
     if (hasTimeExceeded(startTimeMain, timeLimit)) {
         setColor(0, 0, 0);
      printTimeOut();
      break;
    }
  }

  if(hasTimeExceeded(startTimeMain, timeLimit)){
  return points;
  } else{
  printFinalScore2();
  return points;    
  }
  
   setColor(0, 0, 0);
}

void setColor(int red, int green, int blue) {
  analogWrite(PIN_RED, red);
  analogWrite(PIN_GREEN, green);
  analogWrite(PIN_BLUE, blue);
}

std::array<int, 3> generateColor() {
  std::array<int, 3> blue = {0, 0, 255};
  std::array<int, 3> green = {0, 255, 0};
  std::array<int, 3> red = {255, 0, 0};
  std::array<int, 3> yellow = {255, 255, 0};
  std::array<int, 3> violet = {75, 0, 130};

  std::array<std::array<int, 3>, 5> mainArray = {blue, green, red, yellow, violet};

  int numArrays = mainArray.size();
  int randomIndex = random(numArrays);
  return mainArray[randomIndex];
}

long checkColor(std::array<int, 3> color) {
  long newInterval = gameLoopInterval;
  if (compareColors(color, COLOR_TO_MATCH)) {
    score++;
    printScore2(score);
    newInterval = max(100, static_cast<int>(gameLoopInterval - 100));
    playShortSound(true);
  } else {
    score = 0;
    newInterval = 1000;
    points -= 20;
    printDecreasedPoints(20);
    printScore2(score);
    playSadMusic();
  }
  return newInterval;
}

bool compareColors(std::array<int, 3> color1, std::array<int, 3> color2) {
  return color1[0] == color2[0] && color1[1] == color2[1] && color1[2] == color2[2];
}

bool readDebouncedButton2(int buttonPin) {
return readDebouncedButton(buttonPin);
}

String detectColor(int r, int g, int b) {
  if (r == 255 && g == 0 && b == 0) {
    return "Red";
  } else if (r == 0 && g == 255 && b == 0) {
    return "Green";
  } else if (r == 0 && g == 0 && b == 255) {
    return "Blue";
  } else if (r == 255 && g == 255 && b == 0) {
    return "Yellow";
  } else if (r == 75 && g == 0 && b == 130) {
    return "Violet";
  } else {
    return "Unknown";
  }
}

void printWelcomeMsg2() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Color hunt!");
  lcd.setCursor(0, 1);
  lcd.print("Reaction game");
  playPositiveMusic();
  playPositiveMusic();
  delay(4000);
}

void printHuntedColor() {
  COLOR_TO_MATCH = generateColor();
  String colorName = detectColor(COLOR_TO_MATCH[0], COLOR_TO_MATCH[1], COLOR_TO_MATCH[2]);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hunted color: ");
  lcd.setCursor(0, 1);
  lcd.print(String(colorName));
  setColor(COLOR_TO_MATCH[0], COLOR_TO_MATCH[1], COLOR_TO_MATCH[2]);
  delay(3000);
  setColor(0, 0, 0);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Color must be caught ");
  lcd.setCursor(0, 1);
  lcd.print(String(SCORE_TO_ACHIEVE) + " times in a row");
  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1 mistake = -20P");
  lcd.setCursor(0, 1);
  lcd.print("Now you have 200P!");
  delay(3000);

  for (int i = 3; i > 0; --i) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Start in: " + String(i));
    delay(1000);
  }

  lcd.clear();
  lcd.print("NOW!");
  delay(1000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Press button on: ");
  lcd.setCursor(0, 1);
  lcd.print(String(colorName));
  delay(100);
}

void printScore2(int score) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Score: " + String(score));
}

void printFinalScore2(){
   lcd.clear();
   lcd.setCursor(0, 0);
  lcd.print("Game finished!!!");
  lcd.setCursor(0, 1);
  lcd.print("Points: " + String(points));
  playPositiveMusic();
  delay(4000);
  lcd.clear();
}

void printDecreasedPoints(int points){
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("-" + String(points) + " points");
}
