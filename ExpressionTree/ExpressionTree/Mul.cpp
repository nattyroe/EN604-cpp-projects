#include "Mul.h"
#include "BaseTree.h"
#include "BaseNode.h"

BaseTree* Mul::clone()
{
    BaseNode* left = this->root->getLeftClone();
    BaseNode* right = this->root->getRightClone();
    BaseTree* clone = new Mul(left, right);

    map<string, double>::iterator itr;
    for (itr = this->variableTable.begin(); itr != this->variableTable.end(); ++itr)
    {
        clone->let(itr->first, itr->second);
    }
    return clone;
}
