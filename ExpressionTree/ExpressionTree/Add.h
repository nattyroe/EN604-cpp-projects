#pragma once
#include "BaseTree.h"

class Add : public BaseTree
{
public:
    Add(BaseNode *left, BaseNode *right) : BaseTree(left, right, '+') {};
    Add(BaseTree *left, BaseNode *right) : BaseTree(left, right, '+') {};
    Add(BaseNode *left, BaseTree *right) : BaseTree(left, right, '+') {};
    Add(BaseTree *left, BaseTree *right) : BaseTree(left, right, '+') {};

protected:

};

