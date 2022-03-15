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