#include "question.h"
#include <cmath>
#include "expr.h"
#include <sstream>
#include <iostream>

using namespace std;

string intToString(int value)
{
    stringstream ss;
    ss << value;
    return ss.str();
}

string generateExpression(int operand1, int operand2, char op)
{
    string expression;
    expression += intToString(operand1) + ' ' + op + ' ' + intToString(operand2);
    return expression;
}

Question Question::generateSimple()
{
    string expression;

    // Generate random operands
    int operand1 = rand() % 21; // Random number between 0 and 20
    int operand2 = rand() % 21; // Random number between 0 and 20

    // Generate random operator
    char op;
    int operatorIndex = rand() % 4; // Random number between 0 and 3
    switch (operatorIndex)
    {
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
    int result = solveExpression(expression);
    cout << Expr(expression).toString() << " = " << result << endl;
    return Question(expression, result);
}

vector<Question> generateSimpleQuestions(int number)
{
    vector<Question> questions;
    for (int i = 0; i < number; i++)
    {
        questions.push_back(Question::generateSimple());
    }
    getchar();
    getchar();
    return questions;
}

vector<Question> generateMixedQuestions(int number)
{
    vector<Question> questions;
    return questions;
}
