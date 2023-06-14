#ifndef EXPR_H
#define EXPR_H

#include <string>
using namespace std;
struct Expr
{
  std::string value;
  Expr* left;
  Expr* right;

  explicit Expr(const std::string& val)
    : value(val), left(nullptr), right(nullptr) {}

  double evaluate() const;
  std::string toString() const;
};

Expr* parseExpression(const std::string& expr);
double evaluateExpression(const std::string& expr);
#endif  // EXPR_H
