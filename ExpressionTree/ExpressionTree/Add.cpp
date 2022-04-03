#include "Add.h"
#include "BaseTree.h"
#include "BaseNode.h"

/// Create a clone of a given addition tree
BaseTree *Add::clone()
{
    BaseNode *left = this->root->getLeftClone();
    BaseNode *right = this->root->getRightClone();
    BaseTree *clone = new Add(left, right);

    copyVariableTableTo(clone);
    return clone;
}

/// Find the drivative of given addition tree on the given variable
BaseTree *Add::derivative(string variable)
{
    // Create derivative of root node
    BaseNode *derivationNode = this->root->derive(variable);
    // Copy derivative node set to new tree
    BaseTree *derivation = new Add(derivationNode);
    delete derivationNode;

    // Copy variable table to new tree
    copyVariableTableTo(derivation);
    return derivation;
}
