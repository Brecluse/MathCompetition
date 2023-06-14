#include <iostream>
#include <cctype>

using namespace std;

bool eval_expr(const char **pe, int &lhs, bool inside = false);
char skip_ws(const char **pe);
bool eval_prim(const char **pe, int &res);
bool eval_term(const char **pe, int &res);
bool eval_factor(const char **pe, int &res);

char skip_ws(const char **pe) {
  while (**pe == ' ') ++(*pe);
  return **pe;
}

bool eval_prim(const char **pe, int &res) {
  char c = skip_ws(pe);
  if (c == '(') {
    ++(*pe);
    if (!eval_expr(pe, res, true)) return false;
    ++(*pe);
    return true;
  }
  if (isdigit(c)) {
    res = 0;
    while (isdigit(c)) {
      res = 10 * res + c - '0';
      c = *(++(*pe));
    }
    return true;
  }
  return false;
}

bool eval_factor(const char **pe, int &res) {
  if (!eval_term(pe, res)) return false;
  char op;
  while ((op = skip_ws(pe)) && (op == '+' || op == '-')) {
    ++(*pe);
    int rhs;
    if (!eval_term(pe, rhs)) return false;
    switch (op) {
      case '+':
        res += rhs;
        break;
      case '-':
        res -= rhs;
        break;
    }
  }
  return true;
}

bool eval_term(const char **pe, int &res) {
  if (!eval_prim(pe, res)) return false;
  char op;
  while ((op = skip_ws(pe)) && (op == '*' || op == '/')) {
    ++(*pe);
    int rhs;
    if (!eval_prim(pe, rhs)) return false;
    switch (op) {
      case '*':
        res *= rhs;
        break;
      case '/':
        res /= rhs;
        break;
    }
  }
  return true;
}

bool eval_expr(const char **pe, int &lhs, bool inside) {
  if (!eval_factor(pe, lhs)) return false;
  char op;
  while ((op = skip_ws(pe)) && (op == '+' || op == '-')) {
    ++(*pe);
    int rhs;
    if (!eval_factor(pe, rhs)) return false;
    switch (op) {
      case '+':
        lhs += rhs;
        break;
      case '-':
        lhs -= rhs;
        break;
    }
  }
  return inside ? op == ')' : !op;
}

bool evaluate(const char *e, int &result) {
  return eval_expr(&e, result);
}

double evalExpr(const string &expr) {
  // Convert string to C-style string
  const char *exprCString = expr.c_str();
  int result;
  evaluate(exprCString, result);
  return static_cast<double>(result);
}