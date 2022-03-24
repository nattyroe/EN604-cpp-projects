#include "Sub.h"
#include "BaseTree.h"
#include "BaseNode.h"

BaseTree *Sub::clone()
{
    BaseNode *left = this->root->getLeftClone();
    BaseNode *right = this->root->getRightClone();
    BaseTree *clone = new Sub(left, right);

    copyVariableTableTo(clone);
    return clone;
}

BaseTree *Sub::derivative(string variable)
{
    BaseNode *derivationNode = this->root->derive(variable);
    BaseTree *derivation = new Sub(derivationNode);
    delete derivationNode;

    copyVariableTableTo(derivation);
    return derivation;
}
