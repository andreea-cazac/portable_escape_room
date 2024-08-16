#ifndef GAME2_H
#define GAME2_H

#include <array>

// extern int buttonState;
// extern int lastButtonState;
// extern unsigned long lastDebounceTime;
extern unsigned long gameLoopStartTime;
extern unsigned long gameLoopInterval;
extern bool buttonChecked;
extern unsigned long gameStartTime;
extern int score;
extern std::array<int, 3> COLOR_TO_MATCH;
extern int GAME_DURATION;

int playGame2(unsigned long startTime, unsigned long timeLimit);
void setColor(int red, int green, int blue);
std::array<int, 3> generateColor();
bool readDebouncedButton2(int buttonPin);
long checkColor(std::array<int, 3> color);
String detectColor(int r, int g, int b);
bool compareColors(std::array<int, 3> color1, std::array<int, 3> color2);
void printWelcomeMsg2();
void printHuntedColor();
void printScore2(int score);
void printDecreasedPoints(int points);
void printFinalScore2();
bool hasTimeExceeded2();
void printTimeOut2();

#endif
