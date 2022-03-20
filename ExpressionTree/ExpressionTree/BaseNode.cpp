#include "BaseNode.h"
#include <string>
#include <iostream>

using namespace std;

ostream &operator<<(ostream &os, BaseNode &node)
{
    os << node.getData();
    return os;
}