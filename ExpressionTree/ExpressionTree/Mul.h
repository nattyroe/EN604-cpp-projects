#pragma once
#include "BaseTree.h"

class Mul : public BaseTree
{
public:
    Mul(BaseNode *left, BaseNode *right) : BaseTree(left, right, '*') {};
    Mul(BaseTree *left, BaseNode *right) : BaseTree(left, right, '*') {};
    Mul(BaseNode *left, BaseTree *right) : BaseTree(left, right, '*') {};
    Mul(BaseTree *left, BaseTree *right) : BaseTree(left, right, '*') {};

protected:

};

