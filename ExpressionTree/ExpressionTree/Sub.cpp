#include "Sub.h"
#include "BaseTree.h"
#include "BaseNode.h"

BaseTree* Sub::clone()
{
    BaseNode* left = this->root->getLeftClone();
    BaseNode* right = this->root->getRightClone();
    BaseTree* clone = new Sub(left, right);

    map<string, double>::iterator itr;
    for (itr = this->variableTable.begin(); itr != this->variableTable.end(); ++itr)
    {
        clone->let(itr->first, itr->second);
    }
    return clone;
}
