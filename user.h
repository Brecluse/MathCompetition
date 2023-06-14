#ifndef USER_H
#define USER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct User {
  string username;
  int grade;
  string school;

  void serialize(ofstream &stream) const;

  void deserialize(ifstream &stream);

  static void saveToFile(const vector<User> &users, const string &filename);

  static void readFromFile(vector<User> &users, const string &filename);
};

#endif
