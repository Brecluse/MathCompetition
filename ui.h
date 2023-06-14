#ifndef UI_H
#define UI_H

#include "user.h"
#include "result.h"
#include <vector>

User loginOrSignup(vector<User> &users);

void clearScreen();

void displayMainMenu();

void startCompetition(User &user, vector<Record> &results);

void viewPersonalHistory(vector<Record> &records);

// int addUser(User*);

#endif
