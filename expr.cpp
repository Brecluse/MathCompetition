#include "expr.h"
#include <iostream>
#include <sstream>
#include <queue>

queue<string> lexer(const string &expression)
{
    queue<string> tokens;
    stringstream ss(expression);
    string token;

    while (ss >> token)
    {
        tokens.push(token);
    }

    return tokens;
}

Expr *parser(queue<string> &tokens)
{
    if (tokens.empty())
    {
        return NULL;
    }

    queue<Expr *> nodeQueue;

    while (!tokens.empty())
    {
        string token = tokens.front();
        tokens.pop();

        Expr *node = new Expr(token);

        if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (nodeQueue.size() < 2)
            {
                // Not enough operands for the operator, handle error
                // For simplicity, let's delete the created nodes and return nullptr
                delete node;
                while (!nodeQueue.empty())
                {
                    delete nodeQueue.front();
                    nodeQueue.pop();
                }
                return NULL;
            }

            node->right = nodeQueue.front();
            nodeQueue.pop();
            node->left = nodeQueue.front();
            nodeQueue.pop();
        }

        nodeQueue.push(node);
    }

    if (nodeQueue.size() != 1)
    {
        // Invalid expression, handle error
        // For simplicity, let's delete the created nodes and return nullptr
        while (!nodeQueue.empty())
        {
            delete nodeQueue.front();
            nodeQueue.pop();
        }
        return NULL;
    }

    return nodeQueue.front();
}

// Evaluate the expression tree
double evaluateExpression(Expr *node)
{
    if (node == NULL)
    {
        return 0.0;
    }

    if (node->left == NULL && node->right == NULL)
    {
        std::istringstream iss(node->value);
        double value;
        iss >> value;
        return value;
    }

    double leftValue = evaluateExpression(node->left);
    double rightValue = evaluateExpression(node->right);

    if (node->value == "+")
    {
        return leftValue + rightValue;
    }
    else if (node->value == "-")
    {
        return leftValue - rightValue;
    }
    else if (node->value == "*")
    {
        return leftValue * rightValue;
    }
    else if (node->value == "/")
    {
        if (rightValue == 0.0)
        {
            // Handle division by zero error
            throw "Division by zero!";
        }
        return rightValue / leftValue;
    }

    return 0.0;
}

double Expr::evaluate()
{
    return evaluateExpression(this);
}

// Function to solve the expression
double solveExpression(const string &expr)
{
    queue<string> tokens = lexer(expr);
    Expr *root = parser(tokens);
    double result = root->evaluate();
    return result;
}

void toStringHelper(const Expr *expr, ostringstream &oss)
{
    if (expr->left == NULL && expr->right == NULL)
    {
        oss << expr->value;
    }
    else
    {
        oss << "(";
        if (expr->left != NULL)
        {
            toStringHelper(expr->left, oss);
        }
        oss << " " << expr->value << " ";
        if (expr->right != NULL)
        {
            toStringHelper(expr->right, oss);
        }
        oss << ")";
    }
}

string Expr::toString() const
{
    ostringstream oss;
    toStringHelper(this, oss);
    return oss.str();
}
