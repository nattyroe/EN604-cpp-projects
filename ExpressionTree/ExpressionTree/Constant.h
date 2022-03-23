#pragma once
#include "BaseNode.h"
#include <string>
#include <limits>
#include <map>

class Constant : public BaseNode
{
public:
    Constant(double value);

    double evaluate(const map<string, double> *variableTable);
    BaseNode *derive(string variable);

    BaseNode *clone();

private:
    double value = numeric_limits<double>::signaling_NaN();
};
