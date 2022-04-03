#include "Mul.h"
#include "BaseTree.h"
#include "BaseNode.h"

/// Create a clone of a given multiplication tree
BaseTree *Mul::clone()
{
    BaseNode *left = this->root->getLeftClone();
    BaseNode *right = this->root->getRightClone();
    BaseTree *clone = new Mul(left, right);

    copyVariableTableTo(clone);
    return clone;
}

/// Find the drivative of given multiplication tree on the given variable
BaseTree *Mul::derivative(string variable)
{
    // Create derivative of root node
    BaseNode *derivationNode = this->root->derive(variable);
    // Copy derivative node set to new tree
    BaseTree *derivation = new Mul(derivationNode);
    delete derivationNode;

    // Copy variable table to new tree
    copyVariableTableTo(derivation);
    return derivation;
}
