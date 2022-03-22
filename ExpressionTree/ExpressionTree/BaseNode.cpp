#include "BaseNode.h"
#include <string>
#include <iostream>

using namespace std;

BaseNode::~BaseNode()
{
    delete left;
    delete right;
}

BaseNode *BaseNode::getLeftClone()
{
    if (this->left)
    {
        return this->left->clone();
    }
    else
    {
        return nullptr;
    }
}

BaseNode *BaseNode::getRightClone()
{
    if (this->right)
    {
        return this->right->clone();
    }
    else
    {
        return nullptr;
    }
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