#include "Constant.h"

Constant::Constant(double value)
{
    this->value = value;
    this->data = to_string(this->value);
}

double Constant::evaluate(const map<string, double> *variableTable)
{
    return this->value;
}

BaseNode* Constant::clone()
{
    BaseNode* clone = new Constant(this->value);
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