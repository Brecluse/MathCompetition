#ifndef QUESTION_H
#define QUESTION_H

#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Question {
  string expr;
  int result;

  explicit Question()
    : expr(), result(0) {};

  explicit Question(const string &expr, int result)
    : expr(expr), result(result) {};

  void serialize(ofstream &stream) const;

  void deserialize(ifstream &stream);

  static Question generateSimple();

  static Question generateMixed();
};

vector<Question> generateSimpleQuestions(int number);

vector<Question> generateMixedQuestions(int number);

#endif
