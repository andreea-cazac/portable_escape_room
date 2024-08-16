#ifndef GLOBALS_H
#define GLOBALS_H

#include <TM1638plus.h>
#include <LiquidCrystal_I2C.h>
// Global variables

#define PIN_POT A0
#define PIN_STB 2
#define PIN_CLK 3
#define PIN_DIO 4
#define PIN_BUZZER 7
#define PIN_BTN 8
#define PIN_RED 9
#define PIN_GREEN 10
#define PIN_BLUE 11

extern TM1638plus tm; // "true" for common anode displays, "false" for common cathode displays
extern LiquidCrystal_I2C lcd;

//for timing
extern unsigned long startTimeMain;
extern const unsigned long timeLimit;

//for debouncing
extern int buttonState;
extern int lastButtonState;
extern unsigned long lastDebounceTime;

bool readDebouncedButton(int buttonPin);
bool hasTimeExceeded(unsigned long startTime, unsigned long timeLimit);
void printTimeOut();
//TO implement
void playPositiveMusic();
void playShortSound(bool feedback);
void playSadMusic();
void playGameOverMusic();
void lightUpLed(bool feedback);
#endif