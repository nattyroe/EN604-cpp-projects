#include "Div.h"
#include "BaseTree.h"
#include "BaseNode.h"

/// Create a clone of a given division tree
BaseTree *Div::clone()
{
    BaseNode *left = this->root->getLeftClone();
    BaseNode *right = this->root->getRightClone();
    BaseTree *clone = new Div(left, right);

    copyVariableTableTo(clone);

    return clone;
} // End function clone

/// Find the drivative of given division tree on the given variable
BaseTree *Div::derivative(string variable)
{
    // Create derivative of root node
    BaseNode *derivationNode = this->root->derive(variable);
    // Copy derivative node set to new tree
    BaseTree *derivation = new Div(derivationNode);
    delete derivationNode;

    // Copy variable table to new tree
    copyVariableTableTo(derivation);
    return derivation;
} // End function derivative
