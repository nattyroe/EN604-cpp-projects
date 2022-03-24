#include "Div.h"
#include "BaseTree.h"
#include "BaseNode.h"

BaseTree *Div::clone()
{
    BaseNode *left = this->root->getLeftClone();
    BaseNode *right = this->root->getRightClone();
    BaseTree *clone = new Div(left, right);

    copyVariableTableTo(clone);

    return clone;
}

BaseTree *Div::derivative(string variable)
{
    BaseNode *derivationNode = this->root->derive(variable);
    BaseTree *derivation = new Div(derivationNode);
    delete derivationNode;

    copyVariableTableTo(derivation);
    return derivation;
}
