#include "Game4.h" 
#include "globals.h"
#include "Arduino.h"


 int potValue = 0;
 int pulse = 0;
 int chosenPulse = 0;
 unsigned long interval = 0;
 unsigned long startTime = 0;
 unsigned long elapsedTime = 0;
 bool gameStarted = false;
 bool gameFinished = false;
 bool buttonPressed = false;
 bool winStatus = false;
 int finalScore = 0;


int playGame4(unsigned long startTimeMain, unsigned long timeLimit) {
    
     printWelcomeMsg1();
     countdown();
     playRandomPulse();
     guessPulse();
     
   if(hasTimeExceeded(startTimeMain, timeLimit)){
       printTimeOut();
       return finalScore;
     } else {
     return finalScore;
     }
}

void playRandomPulse() {
   unsigned long startTime = millis();
  unsigned long endTime = startTime + SOUND_DURATION;
  
   randomSeed(analogRead(A0)); // Use the value of an unconnected pin as the seed
    pulse = random(MIN_BPM, MAX_BPM + 1);
   
         // play the pulse for 10 seconds
   while (millis() < endTime) {
      interval = 60000 / pulse; 
      digitalWrite(LED_BUILTIN, HIGH);
      tone(PIN_BUZZER, pulse, DURATION);
      delay(DURATION);
      digitalWrite(LED_BUILTIN, LOW);
      delay(interval - DURATION);  
    } 

  noTone(PIN_BUZZER); // turn off the buzzer
    } 


void guessPulse() {
  buttonPressed = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Adjust pot NOW!");
      delay(1000); 

   unsigned long startTime = millis();
  unsigned long endTime = startTime + GUESS_DURATION;


 // while guess time is not over yet
      while (millis() < endTime) {
        
        potValue = analogRead(PIN_POT); // read the potentiometer value
        chosenPulse = mapPotValueToPulse(potValue);

        interval = 60000 / chosenPulse; 
        digitalWrite(LED_BUILTIN, HIGH);
        tone(PIN_BUZZER , chosenPulse , DURATION);
        delay(DURATION);
        digitalWrite(LED_BUILTIN, LOW);
        delay(interval - DURATION);
        
        if (digitalRead(PIN_BTN) == LOW) {
          // the user pressed the button
          printUserGuess(chosenPulse);
          noTone(PIN_BUZZER);
          gameFinished = true;
           break; // exit the loop
        }

      }

      // guess time is over 
      if (millis() >= endTime) {
      printInitialPulse(pulse);
      winStatus = false;
      printFinalScore(winStatus);

      } else if(gameFinished){
      buttonPressed = false;
        //if the chosen pulse is in the range of 6 bms around the right pulse => User was right!
        if(chosenPulse <= pulse + 3 && chosenPulse >= pulse - 3){
          winStatus = true;
         printInitialPulse(pulse);
         delay(100);
         printFinalScore(winStatus);
        } else {
          winStatus = false;
          printInitialPulse(pulse);
          delay(100);
          printFinalScore(winStatus);
        }
        
      }
}


int mapPotValueToPulse(int potValue) {

int pulse = map(potValue, MIN_POT_VALUE, MAX_POT_VALUE, MIN_BPM, MAX_BPM); // map the potentiometer value to pulse range

return pulse;
}

//Countdown timer
void printWelcomeMsg1(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Potentiometer: ");
  lcd.setCursor(0, 1);
  lcd.print("Guess the beat! ");
  playPositiveMusic();
  playPositiveMusic();
  delay(4000);
}

void countdown(){
 for (int i = 3; i > 0; --i) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Start in: " + String(i));
  delay(1000);
 }

 lcd.clear();
 lcd.print("Listen " + String(SOUND_DURATION/1000) + " seconds!");
 delay(1000);
}

void printPressButtonMsg(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press button " );
  lcd.setCursor(0, 1);
  lcd.print(" to start!");
    delay(2000);
}

void printUserGuess(int guess){
lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your guess is:" );
  lcd.setCursor(0, 1);
  lcd.print(String(guess) + " bpm");
    delay(2000);  
}

void printInitialPulse(int pulse){
lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("The pulse was:" );
  lcd.setCursor(0, 1);
  lcd.print(String(pulse) + " bpm");
    delay(2000); 
}

void printFinalScore(bool win){
if(win){
  finalScore = 100;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("You won!" );
  lcd.setCursor(0, 1);
  lcd.print("+100 points!!!");
  playPositiveMusic();
  delay(4000);
} else {
 finalScore = -20;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("You lost!" );
  lcd.setCursor(0, 1);
  lcd.print("-20 points!!!");
  playSadMusic();
  delay(4000);
}
}


