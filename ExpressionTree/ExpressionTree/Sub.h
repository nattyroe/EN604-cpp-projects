#pragma once
#include "BaseTree.h"

class Sub : public BaseTree
{
public:
    Sub(BaseNode *left, BaseNode *right) : BaseTree(left, right, '-') {};
    Sub(BaseTree *left, BaseNode *right) : BaseTree(left, right, '-') {};
    Sub(BaseNode *left, BaseTree *right) : BaseTree(left, right, '-') {};
    Sub(BaseTree *left, BaseTree *right) : BaseTree(left, right, '-') {};

    BaseTree* clone();

protected:

};

