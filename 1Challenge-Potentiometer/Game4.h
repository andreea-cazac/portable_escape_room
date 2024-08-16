#ifndef GAME4_H
#define GAME4_H


#define WAITING_TIME 1000
#define DURATION 100
#define MIN_BPM 60
#define MAX_BPM 240
#define MIN_POT_VALUE 0
#define MAX_POT_VALUE 1023
#define SOUND_DURATION 10000//seconds
#define GUESS_DURATION 30000 // 30 seconds


extern int potValue;
extern int pulse;
extern int chosenPulse;
extern unsigned long interval;
extern unsigned long startTime;
extern unsigned long elapsedTime;
extern bool gameStarted;
extern bool gameFinished;
extern bool buttonPressed;
extern bool winStatus;
extern int finalScore;
extern  int tries;

int playGame4(unsigned long startTime, unsigned long timeLimit);
void playRandomPulse();
void guessPulse();
int mapPotValueToPulse(int potValue);
void printWelcomeMsg1();
void printPressButtonMsg();
void printUserGuess(int guess);
void printInitialPulse(int pulse);
void printFinalScore(bool win);
void printTime(unsigned long elapsedTime);
void countdown();


#endif