
#ifndef GAME3_H
#define GAME3_H

#define numOfMoles 8 // Set the number of moles, TM1638plus has 8 LEDs

extern unsigned long previousMillis;
extern int buttonValues[8];
//to avoid repeated lighted moles
extern int previousLightedMole;
//results 1 level
extern int caughtMoles1;
extern int lostMoles1;
//results 2 level
extern int caughtMoles2;
extern int lostMoles2;
//results 3 level
extern int caughtMoles3;
extern int lostMoles3;
extern int finalScore3;
extern bool timeOut;

int playGame3(unsigned long startTime, unsigned long timeLimit);
void lightUpMole(int level);
bool readButton(int mole);
void printScore3(int level);
void printLevel(int level);
void caughtMole(int level);
void lostMole(int level);
int printFinalScore3();
void startInTimer();
void printWelcomeMsg3();
bool checkPassedLevel(int totalScore, int passScore);
void resetValues();


#endif