#include "expr.h"
#include <cctype>
#include <stack>

double evaluateNode(const Expr* node)
{
  if (node->value == "+")
    return evaluateNode(node->left) + evaluateNode(node->right);
  if (node->value == "-")
    return evaluateNode(node->left) - evaluateNode(node->right);
  if (node->value == "*")
    return evaluateNode(node->left) * evaluateNode(node->right);
  if (node->value == "/")
    return evaluateNode(node->left) / evaluateNode(node->right);
  return std::stoi(node->value);
}

double Expr::evaluate() const
{
  return evaluateNode(this);
}

std::string Expr::toString() const
{
  if (left == nullptr && right == nullptr) {
    return value;
  } else {
    return "(" + left->toString() + " " + value + " " + right->toString() + ")";
  }
}

Expr* parseExpression(const std::string& expr)
{
  std::stack<Expr*> exprStack;
  std::stack<char> opStack;

  std::string num;
  for (char c : expr) {
    if (std::isdigit(c)) {
      num += c;
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      if (!num.empty()) {
        exprStack.push(new Expr(num));
        num.clear();
      }
      while (!opStack.empty() && (opStack.top() == '*' || opStack.top() == '/')) {
        Expr* right = exprStack.top();
        exprStack.pop();
        Expr* left = exprStack.top();
        exprStack.pop();
        Expr* op = new Expr(std::string(1, opStack.top()));
        op->left = left;
        op->right = right;
        exprStack.push(op);
        opStack.pop();
      }
      opStack.push(c);
    }
  }
  if (!num.empty()) {
    exprStack.push(new Expr(num));
  }
  while (!opStack.empty()) {
    Expr* right = exprStack.top();
    exprStack.pop();
    Expr* left = exprStack.top();
    exprStack.pop();
    Expr* op = new Expr(std::string(1, opStack.top()));
    op->left = left;
    op->right = right;
    exprStack.push(op);
    opStack.pop();
  }

  return exprStack.top();
}

double evaluateExpression(const std::string& expr)
{
  Expr* root = parseExpression(expr);
  double result = root->evaluate();
  delete root;
  return result;
}
