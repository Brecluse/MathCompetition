#ifndef UI_H
#define UI_H

#include "user.h"
#include <vector>

User loginOrSignup(vector<User>& users);
void clearScreen();
void displayMainMenu();
void startCompetition();
void viewResults();
void viewPersonalHistory();
void viewSchoolResults();
void setDifficultyLevel();
void setQuestionTime();
void updateResult(int totalScore, int totalTime);
void displayResult();
void displayPersonalHistory();
void displaySchoolResults();

// int addUser(User*);

#endif
