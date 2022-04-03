#include "Operator.h"
#include <map>

using namespace std;

/// Operator node constructor
Operator::Operator(char oper)
{
    // Verify operator is a valid type
    if (!(oper == '*' or oper == '/' or
          oper == '+' or oper == '-'))
    {
        throw invalidOperator;
    }
    this->oper = oper;
    this->data = this->oper;
}

/// Evaluate equation by finding the result of left *oper* right
double Operator::evaluate(const map<string, double> *variableTable)
{
    // If no left/right nodes are found, throw error
    if (!this->left || !this->right)
    {
        throw invalidOperator;
    }

    // Evaluate left and right substructures
    double left = this->left->evaluate(variableTable);
    double right = this->right->evaluate(variableTable);

    // Calculate left *oper* right based on operator type
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

/// Create clone of current operator node
BaseNode *Operator::clone()
{
    BaseNode *clone = new Operator(this->oper);
    // Clone left substructure
    if (this->left)
    {
        clone->setLeft(this->left->clone());
    }
    // Clone right substructure
    if (this->right)
    {
        clone->setRight(this->right->clone());
    }
    return clone;
}

/// Return derivative of this operator and linked nodes
BaseNode *Operator::derive(string variable)
{
    // If no left/right nodes are found, throw error
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
    // Calculate derivative of u + v
    // (du + dv)
    case '+':
        newOper = new Operator('+');
        newOper->setLeft(this->left->derive(variable));
        newOper->setRight(this->right->derive(variable));
        return newOper;

    // Calculate derivative of u - v
    // (du - dv)
    case '-':
        newOper = new Operator('-');
        newOper->setLeft(this->left->derive(variable));
        newOper->setRight(this->right->derive(variable));
        return newOper;

    // Calculate derivative of u * v
    // (u*dv + v*du)
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

    // Calculate derivative of u / v
    // ((v*du - u*dv) / v*v)
    case '/':
        newOper = new Operator('/');

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

    // Throw error for invalid operator
    default:
        throw invalidOperator;
    }
}
