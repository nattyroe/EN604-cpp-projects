#include "BaseNode.h"
#include <string>
#include <iostream>

using namespace std;

/// Default destructor for BaseTree objects
BaseNode::~BaseNode()
{
    delete left;
    delete right;
} // End function ~BaseNode

/// Return clone of just left sub-node structure
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
} // End function getLeftClone

/// Return clone of just right sub-node structure
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
} // End function getRightClone

/// Stream insertion override for printing node info
ostream &operator<<(ostream &os, BaseNode &node)
{
    // Add parenthesis if there are left/right nodes
    if (node.left)
    {
        os << "(" << * node.left;
    }
    // Print node data
    os << node.data;
    if (node.right)
    {
        os << *node.right << ")";
    }
    return os;
} // End function << override
