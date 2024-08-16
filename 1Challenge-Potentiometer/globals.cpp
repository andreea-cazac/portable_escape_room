#include "globals.h"
#include "Arduino.h"

bool readDebouncedButton(int buttonPin) {
  static int buttonState = digitalRead(buttonPin);
  static int lastButtonState = buttonState;
  static unsigned long lastDebounceTime = millis();
  
  int reading = digitalRead(buttonPin);
  bool buttonPressed = false;

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > 50) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        buttonPressed = true;
      }
    }
  }

  lastButtonState = reading;
  return buttonPressed;
}

bool hasTimeExceeded(unsigned long startTime, unsigned long timeLimit) {
  return millis() - startTime >= timeLimit;
}

void printTimeOut(){
   lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time out!" );
  lcd.setCursor(0, 1);
  lcd.print("GAME OVER!");
  playGameOverMusic();
  delay(3000);
  lcd.clear();
}

void playPositiveMusic(){
tone(PIN_BUZZER, 523, 125); 
lightUpLed(true);
delay(50); // C5
tone(PIN_BUZZER, 659, 125); 
lightUpLed(true);
delay(50); // E5
tone(PIN_BUZZER, 784, 250); 
lightUpLed(true);
delay(200); // G5
tone(PIN_BUZZER, 1046, 250); 
lightUpLed(true);
delay(200); // C6
}

void playSadMusic(){
tone(PIN_BUZZER, 392, 125); 
lightUpLed(false);
delay(150); // G4
tone(PIN_BUZZER, 349, 125); 
lightUpLed(false);
delay(150); // F4
tone(PIN_BUZZER, 330, 250); 
lightUpLed(false);
delay(300); // E4
tone(PIN_BUZZER, 294, 250); 
lightUpLed(false);
delay(300); // D4  
}

void playGameOverMusic(){
tone(PIN_BUZZER, 659, 125); 
delay(150); // E5
tone(PIN_BUZZER, 587, 125); 
delay(150); // D5
tone(PIN_BUZZER, 554, 250); 
delay(300); // C#5
tone(PIN_BUZZER, 494, 250); 
delay(300); // B4
}

void playShortSound(bool feedback){
  //if user pressed on the right button or any other positive move => feedback is true => positive song
  if(feedback){
  tone(PIN_BUZZER, 1174, 250); 
  delay(300); // D6
  } else {
  tone(PIN_BUZZER, 392, 125); 
  delay(150); // G4
  tone(PIN_BUZZER, 349, 125); 
  delay(150); // F4
  }
}

void lightUpLed(bool feedback){
  int red = 0;
  int green = 0;
  int blue = 0;
  
//if user pressed on the right button or any other positive move => feedback is true => positive song
  if(feedback){
  green = 255;
  } else {
  red = 255;
  }

  analogWrite(PIN_RED, red);
  analogWrite(PIN_GREEN, green);
  analogWrite(PIN_BLUE, blue);
  delay(100);
//turn off
  analogWrite(PIN_RED, 0);
  analogWrite(PIN_GREEN, 0);
  analogWrite(PIN_BLUE, 0);
}

