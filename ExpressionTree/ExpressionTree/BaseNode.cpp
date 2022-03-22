#include "BaseNode.h"
#include <string>
#include <iostream>

using namespace std;

BaseNode::~BaseNode()
{
    delete left;
    delete right;
}

ostream &operator<<(ostream &os, BaseNode &node)
{
    if (node.left)
    {
        os << "(" << * node.left;
    }
    os << node.data;
    if (node.right)
    {
        os << *node.right << ")";
    }
    return os;
}