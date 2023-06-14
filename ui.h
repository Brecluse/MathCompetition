#ifndef UI_H
#define UI_H

#include "user.h"
#include "record.h"
#include <vector>

User loginOrSignup(vector<User> &users);

void clearScreen();

void displayMainMenu();

void startCompetition(vector<Record> &results);

void viewPersonalHistory(User &user,vector<Record> &records);

// int addUser(User*);

#endif
