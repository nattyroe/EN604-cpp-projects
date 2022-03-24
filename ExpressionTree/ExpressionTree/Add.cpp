#include "Add.h"
#include "BaseTree.h"
#include "BaseNode.h"

BaseTree *Add::clone()
{
    BaseNode *left = this->root->getLeftClone();
    BaseNode *right = this->root->getRightClone();
    BaseTree *clone = new Add(left, right);

    copyVariableTableTo(clone);
    return clone;
}

BaseTree *Add::derivative(string variable)
{
    BaseNode *derivationNode = this->root->derive(variable);
    BaseTree *derivation = new Add(derivationNode);
    delete derivationNode;

    copyVariableTableTo(derivation);
    return derivation;
}
