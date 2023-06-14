#include "question.h"
#include <cmath>
#include "expr.h"
#include <sstream>
#include <iostream>

using namespace std;

string intToString(int value) {
  stringstream ss;
  ss << value;
  return ss.str();
}

string generateExpression(int operand1, int operand2, char op) {
  string expression;
  expression += intToString(operand1) + ' ' + op + ' ' + intToString(operand2);
  return expression;
}

Question Question::generateSimple() {
  string expression;

  // Generate random operands
  int operand1 = rand() % 21; // Random number between 0 and 20
  int operand2 = rand() % 21; // Random number between 0 and 20

  // Generate random operator
  char op;
  int operatorIndex = rand() % 4; // Random number between 0 and 3
  switch (operatorIndex) {
    case 0:
      op = '+';
      break;
    case 1:
      op = '-';
      break;
    case 2:
      op = '*';
      break;
    case 3:
      op = '/';
      // Ensure that operand1 is evenly divisible
      operand1 = operand2 * (rand() % 21); // Random multiple of operand2
      break;
  }

  // Construct the expression string
  expression = generateExpression(operand1, operand2, op);
  int result = evalExpr(expression);
  return Question(expression, result);
}

// Function to generate a random integer within a given range
int getRandomInt(int min, int max) {
  return min + rand() % (max - min + 1);
}
Question Question::generateMixed() {
  std::ostringstream oss;
  int numOperands = rand() % 2 + 3;  // Random number of operands between 3 and 4
  int operand;
  char operatorChar;
  bool isDivisible = true;

  // Generate the first operand
  operand = rand() % 21;
  oss << operand;

  for (int i = 1; i < numOperands; ++i) {
    // Generate the operator
    operatorChar = "+-*/"[rand() % 4];
    oss << ' ' << operatorChar << ' ';

    // Generate the next operand
    operand = rand() % 21;

    if (operatorChar == '/') {
      // If it's a division, ensure the division is evenly divisible
      if (operand == 0 || (operand != 0 && (oss.str()[oss.str().size() - 2] - '0') % operand != 0)) {
        isDivisible = false;
        break;
      }
    }

    oss << operand;
  }

  if (!isDivisible) {
    // If the generated expression is not valid, generate a new one
    oss.str("");
    return Question::generateMixed();
  }

  string expr = oss.str();
  int result = evalExpr(expr);
  return Question(expr, result);
}

vector<Question> generateSimpleQuestions(int number) {
  vector<Question> questions;
  for (int i = 0; i < number; i++) {
    questions.push_back(Question::generateSimple());
  }
  return questions;
}

vector<Question> generateMixedQuestions(int number) {
  vector<Question> questions;
  for (int i = 0; i < number; i++) {
    questions.push_back(Question::generateMixed());
  }
  return questions;
}
