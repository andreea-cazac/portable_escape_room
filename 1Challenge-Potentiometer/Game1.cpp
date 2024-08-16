#include <vector>
#include "globals.h"
#include "Game1.h"
#include "Arduino.h"

int buttonValues2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
bool gameStarted2 = true;
int score4 = 0;
bool timeout = false;
bool gamePassed = false;


int playGame1(unsigned long startTime, unsigned long timeLimit){

  while(!timeout && !gamePassed){
  if(gameStarted2){
  printWelcomeMsg4();
  // Level 1
  playLevel(1, 4);

   // Level 2
  playLevel(2, 6);

  // Level 3
  playLevel(3, 8);

  gamePassed = true;
  }
  }

 if (hasTimeExceeded(startTimeMain, timeLimit)){
    gameStarted2 = false;
    return score4;
    } else {
    printFinalScore4(score4);
    gameStarted2 = false;
    return score4;
    }

}


void lightUpLights(std::vector<int> randomSequence){
for ( int i = 0; i < randomSequence.size(); i++) {
  //if the randomized led is 7 => the 6 position must be turned on
  int position = randomSequence[i] - 1;
  lightUpLed(position);
}
}

void lightUpLed(int position){
tm.setLED(position, true); // Turn on the LED for the mole
delay(1000);
tm.setLED(position, false); // Turn off the LED for the mole
delay(300);
}

std::vector<int> generateRandomSequence(int numLimit){
  std::vector<int> randomSequence;
  // Generate a random seed
randomSeed(analogRead(A1)); // Use an unconnected analog pin as the seed for better randomness
for (int i = 0; i < numLimit; i++) {
  int randomNumber = random(1, numOfLights+1); // Generate a random number between minValue and maxValue, inclusive
 randomSequence.push_back(randomNumber); // Add the random number to the vector
  delay(500); // Add a small delay between each iteration (optional)
}
return randomSequence;
}

bool checkSequence(std::vector<int> generatedSequence){

  //check if user keeps the correct sequence
bool isCorrectSequence = true;
//check if user completed the sequence with success
bool sequenceCompleted = false; // New variable to indicate if the sequence has been completed

int counter = 0;
int sequenceSize = generatedSequence.size();

while (isCorrectSequence && !sequenceCompleted) {
  uint8_t buttons = tm.readButtons();
      
       //If any button pressed => check
      if (buttons != 0) {
        // Check if the pressed button matches the sequence
        for (int i = 0; i < 8; i++) {
          //check if each button on position[i] was pressed 
          if ((1 << i) & buttons) {
             lightUpLed(i);
            if (generatedSequence[counter] == i + 1) {
              //if there are other leds to guess => counter++ and go on
              if(counter < sequenceSize-1){
              counter++;
              playShortSound(true);
              } else {
              sequenceCompleted = true;
              break;
              }

            } else {
              isCorrectSequence = false;
            }
            break;
          }
        }
      }
    }

if(isCorrectSequence){
 return true;
} else {
  return false;
}
}

void prizeLevel(int level, bool winStatus){

if(level == 1){
if(winStatus){
  score4 += 50;
}  
} else if(level == 2){
if(winStatus){
  score4 += 100;
} 
} else if(level == 3){
if(winStatus){
  score4 += 200;
} 
}

  if(winStatus){
  playPositiveMusic();
  } else {
  playSadMusic();
  }


if(level != 3){
printScore4(score4);
} 
}

void printWelcomeMsg4(){
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Memory game!");
   delay(4000);
}

//Countdown timer
void timer(){
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


void playLevel(int level, int sequenceSize) {
     if (hasTimeExceeded(startTimeMain, timeLimit)) {
     timeout = true;
     return;
    }

   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Level: " + String(level));
   lcd.setCursor(0, 1);
   lcd.print("Memorize leds: " + String(sequenceSize));
   delay(1000);
   lcd.clear();

    std::vector<int> generatedSequence = generateRandomSequence(sequenceSize);
    timer();
    lightUpLights(generatedSequence);
    printUsersTurn();

    if(checkSequence(generatedSequence)){
    prizeLevel(level, true);
    } else {
    prizeLevel(level, false);
    }
  
}

void printUsersTurn() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your turn!");
   delay(1000);
}

void printScore4(int score4){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Score now: " + String(score4));
  delay(1000);  
}

void printFinalScore4(int score4){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("You collected: ");
   lcd.setCursor(0, 1);
  lcd.print(String(score4) + " points!");
  delay(1000);
}
