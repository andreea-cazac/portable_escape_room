#ifndef GAME1_H
#define GAME1_H

#define numOfLights 8 // Set the number of lights, TM1638plus has 8 LEDs

extern int buttonValues2[8];
extern bool gameStarted2;
extern int score4;
extern bool timeout;
extern bool gamePassed;

int playGame1(unsigned long startTime, unsigned long timeLimit);
void lightUpLed(int position);
void lightUpLights(std::vector<int>);
std::vector<int> generateRandomSequence(int numLimit);
bool checkButtons(std::vector<int> generatedSequence);
bool checkSequence(std::vector<int> generatedSequence);
void printWelcomeMsg4();
void timer();
void printUsersTurn();
void playLevel(int level, int sequenceSize);
int prizeLevel(int level);
void printFinalScore4(int score);
void printScore4(int score);

#endif
