#ifndef QUESTION_H
#define QUESTION_H
#include <vector>
#include <string>

using namespace std;

struct Question
{
    string expr;
    int result;

    explicit Question(const string &expr, int result)
        : expr(expr), result(result){};

    static Question generateSimple();
    static Question generateMixed();
};

vector<Question> generateSimpleQuestions(int number);
vector<Question> generateMixedQuestions(int number);
#endif
