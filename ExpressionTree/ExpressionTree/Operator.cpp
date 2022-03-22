#include "Operator.h"
#include <map>

using namespace std;

Operator::Operator(char oper)
{
    this->oper = oper;
    this->data = this->oper;
}

double Operator::evaluate(const map<string, double> *variableTable)
{
    if (!this->left || !this->right)
    {
        throw invalidOperator;
    }

    double left = this->left->evaluate(variableTable);
    double right = this->right->evaluate(variableTable);

    switch (this->oper)
    {
    case '*':
        return left * right;
    case '/':
        return left / right;
    case '+':
        return left + right;
    case '-':
        return left - right;
    default:
        throw invalidOperator;
    }
}

BaseNode* Operator::clone()
{
    BaseNode* clone = new Operator(this->oper);
    if (this->left)
    {
        clone->setLeft(this->left->clone());
    }
    if (this->right)
    {
        clone->setRight(this->right->clone());
    }
    return clone;
}
