#include "Mul.h"
#include "BaseTree.h"
#include "BaseNode.h"

BaseTree* Mul::clone()
{
    BaseNode* left = this->root->getLeftClone();
    BaseNode* right = this->root->getRightClone();
    BaseTree* clone = new Mul(left, right);

    copyVariableTableTo(clone);
    return clone;
}

BaseTree* Mul::derivative(string variable)
{
    BaseNode* derivationNode = this->root->derive(variable);
    BaseTree* derivation = new Mul(derivationNode);
    delete derivationNode;

    copyVariableTableTo(derivation);
    return derivation;
}
