#include "Constant.h"

/// Constant node constructor
Constant::Constant(double value)
{
    this->value = value;
    this->data = to_string(this->value);
}

/// Evaluate constant, return value of constant
double Constant::evaluate(const map<string, double> *variableTable)
{
    return this->value;
}

/// Create clone of current constant node
BaseNode *Constant::clone()
{
    BaseNode* clone = new Constant(this->value);
    return clone;
}

/// Return derivative of this variable (0.0)
BaseNode *Constant::derive(string variable)
{
    return new Constant(0.0);
}
