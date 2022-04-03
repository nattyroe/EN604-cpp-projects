#include "Sub.h"
#include "BaseTree.h"
#include "BaseNode.h"

/// Create a clone of a given subtraction tree
BaseTree *Sub::clone()
{
    BaseNode *left = this->root->getLeftClone();
    BaseNode *right = this->root->getRightClone();
    BaseTree *clone = new Sub(left, right);

    copyVariableTableTo(clone);
    return clone;
}

/// Find the drivative of given addition tree on the given variable
BaseTree *Sub::derivative(string variable)
{
    // Create derivative of root node
    BaseNode *derivationNode = this->root->derive(variable);
    // Copy derivative node set to new tree
    BaseTree *derivation = new Sub(derivationNode);
    delete derivationNode;

    // Copy variable table to new tree
    copyVariableTableTo(derivation);
    return derivation;
}
