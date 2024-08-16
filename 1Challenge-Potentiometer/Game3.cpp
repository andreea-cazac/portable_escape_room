#include "globals.h"
#include "Game3.h"
#include "Arduino.h"

int buttonValues[8] = {0, 0, 0, 0, 0, 0, 0, 0};

//results 1 level
int caughtMoles1 = 0;
int lostMoles1 = 0;
//results 2 level
int caughtMoles2 = 0;
int lostMoles2 = 0;
//results 3 level
int caughtMoles3 = 0;
int lostMoles3 = 0;

int finalScore3 = 0;
int previousLightedMole = 0;

int levelsPassed = 0;
bool levelPassed = true;
bool timeOut = false;


int playGame3(unsigned long startTime, unsigned long timeLimit) {
  printWelcomeMsg3();

  while(levelsPassed < 3 && !timeOut){
    // Level 1
        printLevel(1);
      for (int i = 0; i < 45; ++i) {
         if (!hasTimeExceeded(startTimeMain, timeLimit)){
        printScore3(1);
        lightUpMole(1);
        } else {
          timeOut = true;
          break;
        }
      }

      if(timeOut){
      break;
      } else {
      printFinalScore3();
      levelPassed = checkPassedLevel(finalScore3, 450);
      }
      //gamePass = levelPassed;
    

    // Level 2
    if (levelPassed) {
      levelsPassed++;
      printLevel(2);
      for (int i = 0; i < 30; ++i) {
          if (!hasTimeExceeded(startTimeMain, timeLimit)){
        printScore3(2);
        lightUpMole(2);
           } else {
        timeOut = true;
        break;
       }
      }

       if(timeOut){
      break;
      } else {
      printFinalScore3();
      levelPassed = checkPassedLevel(finalScore3, 650);
      }
      // gamePass = levelPassed;
    }

    // Level 3
    if (levelPassed) {
      levelsPassed++;
      printLevel(3);
      for (int i = 0; i < 20; ++i) {
        if (!hasTimeExceeded(startTimeMain, timeLimit)){
        lightUpMole(3);
        printScore3(3);
           } else {
        timeOut = true;
        break;
       }
      }
      
       if(timeOut){
      break;
      } else {
      printFinalScore3();
      levelPassed = checkPassedLevel(finalScore3, 800);
      }

      if(levelPassed){
      levelsPassed++;
      }
    //  gamePass = levelPassed;
    }
  }

  if (hasTimeExceeded(startTimeMain, timeLimit)){
       printTimeOut();
       return finalScore3;
    } else {
       printFinalScore3();
       return finalScore3;
    }
}


void lightUpMole(int level) {
    int displayInterval; 
    int mole;
    bool newLightedMole = false;

    // Set the interval for moles to appear (in milliseconds)
  if(level == 1){
  displayInterval = 700;
  } else if(level == 2){
  displayInterval = 500;
  } else if(level == 3){
  displayInterval = 350;
  }

  unsigned long currentMillis = millis();
  unsigned long previousMillis = 0;
  bool moleWhacked = false;


//while the random mole repeated again, choose a different random mole
while(!newLightedMole){
  randomSeed(analogRead(A1)); // Use the value of an unconnected pin as the seed
  mole = random(numOfMoles);

  if(previousLightedMole != mole){
    previousLightedMole = mole;
    newLightedMole = true;
  }
}
  
  tm.setLED(mole, true); // Turn on the LED for the mole
  previousMillis = currentMillis;

  while (currentMillis - previousMillis <= displayInterval) {
    if (readButton(mole)) {
      caughtMole(level);
      moleWhacked = true;
      playShortSound(true);
      break;
    }
    currentMillis = millis();
  }

  tm.setLED(mole, false); // Turn off the LED for the mole

  if (!moleWhacked) {
    lostMole(level);
    playShortSound(false);
  } 
}

bool readButton(int mole) {
 // Read the button state
  int buttonValue = tm.readButtons();

 // Store the button values into the array using bitwise operations
  buttonValues[0] = (buttonValue & 0b00000001) >> 0;
  buttonValues[1] = (buttonValue & 0b00000010) >> 1;
  buttonValues[2] = (buttonValue & 0b00000100) >> 2;
  buttonValues[3] = (buttonValue & 0b00001000) >> 3;
  buttonValues[4] = (buttonValue & 0b00010000) >> 4;
  buttonValues[5] = (buttonValue & 0b00100000) >> 5;
  buttonValues[6] = (buttonValue & 0b01000000) >> 6;
  buttonValues[7] = (buttonValue & 0b10000000) >> 7;

if(buttonValues[mole] == 1){
return true;
}

return false;
}

void lostMole(int level){
if(level == 1){
lostMoles1++;  
} else if(level == 2){
lostMoles2++;
} else if(level == 3){
lostMoles3++;
}
}

void caughtMole(int level){
if(level == 1){
caughtMoles1++;  
} else if(level == 2){
caughtMoles2++;
} else if(level == 3){
caughtMoles3++;
}
}

void printWelcomeMsg3(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Whack a mole!");
  playPositiveMusic();
  playPositiveMusic();
  delay(4000);
}

void printScore3(int level){

  int caughtMoles = 0;
  int lostMoles = 0;

  if(level == 1){
    caughtMoles = caughtMoles1;
    lostMoles = lostMoles1;
  } else if(level == 2){
    caughtMoles = caughtMoles2;
    lostMoles = lostMoles2;
  } else if(level == 3){
    caughtMoles = caughtMoles3;
    lostMoles = lostMoles3;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Level: " + String(level));
  lcd.setCursor(0, 1);
  lcd.print("C: " + String(caughtMoles) + " L: " + String(lostMoles));
    delay(200);
}

void printLevel(int level){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Level: " + String(level));

if(level == 2 || level == 3) {
  lcd.setCursor(0, 1);
  lcd.print("Time gets faster!");
}
 delay(1000);

 startInTimer();
}

//Countdown timer
void startInTimer(){
 for (int i = 3; i > 0; --i) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Start in: " + String(i));
  delay(1000);
 }

 lcd.clear();
 lcd.print("NOW!");
 delay(1000);
}

int printFinalScore3(){

 finalScore3 = ((caughtMoles1 + caughtMoles2 + caughtMoles3) * 10) - ((lostMoles1 + lostMoles2 + lostMoles3) * 3);
 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("You have: " + String(finalScore3));
  lcd.setCursor(0, 1);
  lcd.print("points!!!");
    delay(4000);

  return finalScore3;
}

bool checkPassedLevel(int totalScore, int passScore) {
  if(totalScore > passScore) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Next level!");
    playPositiveMusic();
    delay(1000);
    return true;
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Not enough points to pass...");
    lcd.setCursor(0, 1);
    lcd.print("Try again!");
    playSadMusic();
    delay(1000);
    resetValues();
    return false;
  }
}

void resetValues(){
  //results 1 level
 caughtMoles1 = 0;
 lostMoles1 = 0;
//results 2 level
 caughtMoles2 = 0;
 lostMoles2 = 0;
//results 3 level
 caughtMoles3 = 0;
lostMoles3 = 0;

 finalScore3 = 0;
 previousLightedMole = 0;

 levelsPassed = 0;
}