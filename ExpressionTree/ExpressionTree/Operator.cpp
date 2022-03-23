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

BaseNode *Operator::clone()
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

BaseNode *Operator::derive(string variable)
{
    if (!this->left || !this->right)
    {
        throw invalidOperator;
    }

    BaseNode *newOper = nullptr;
    BaseNode *leftBranch = nullptr;
    BaseNode *rightBranch = nullptr;
    BaseNode *numerator = nullptr;
    BaseNode *denominator = nullptr;

    switch (this->oper)
    {
    case '+':
        newOper = new Operator('+');
        newOper->setLeft(this->left->derive(variable));
        newOper->setRight(this->right->derive(variable));
        return newOper;

    case '-':
        newOper = new Operator('-');
        newOper->setLeft(this->left->derive(variable));
        newOper->setRight(this->right->derive(variable));
        return newOper;

    case '*':
        newOper = new Operator('+');

        leftBranch = new Operator('*');
        leftBranch->setLeft(this->left->clone());
        leftBranch->setRight(this->right->derive(variable));

        rightBranch = new Operator('*');
        rightBranch->setRight(this->right->clone());
        rightBranch->setLeft(this->left->derive(variable));

        newOper->setLeft(leftBranch);
        newOper->setRight(rightBranch);
        return newOper;

    case '/':
        newOper = new Operator('-');

        numerator = new Operator('-');

        leftBranch = new Operator('*');
        leftBranch->setLeft(this->left->clone());
        leftBranch->setRight(this->right->derive(variable));

        rightBranch = new Operator('*');
        rightBranch->setRight(this->right->clone());
        rightBranch->setLeft(this->left->derive(variable));

        numerator->setLeft(leftBranch);
        numerator->setRight(rightBranch);

        denominator = new Operator('*');
        denominator->setLeft(this->right->clone());
        denominator->setRight(this->right->clone());

        newOper->setLeft(numerator);
        newOper->setRight(denominator);
        return newOper;

    default:
        throw invalidOperator;
    }
}
