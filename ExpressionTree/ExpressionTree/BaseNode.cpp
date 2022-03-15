#include "BaseNode.h"
#include <string>
#include <iostream>
#include <limits>

using namespace std;

double BaseNode::evaluate(const map<string, double>* variableTable)
{
    return numeric_limits<double>::signaling_NaN();
}

ostream &operator<<(ostream &os, BaseNode &node)
{
    os << node.getData();
    return os;
}