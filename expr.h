#ifndef EXPR_H
#define EXPR_H
#include <string>
using namespace std;

// Node of the expression tree
struct Expr
{
    string value;
    Expr *left;
    Expr *right;

    explicit Expr(const string &val)
        : value(val), left(NULL), right(NULL) {}

    double evaluate();

    string toString() const;
};

double evaluateExpression(Expr *root);
double solveExpression(const string &expr);
#endif
