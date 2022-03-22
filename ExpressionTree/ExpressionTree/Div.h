#pragma once
#include "BaseTree.h"

class Div : public BaseTree
{
public:
    Div(BaseNode *left, BaseNode *right) : BaseTree(left, right, '/') {};
    Div(BaseTree *left, BaseNode *right) : BaseTree(left, right, '/') {};
    Div(BaseNode *left, BaseTree *right) : BaseTree(left, right, '/') {};
    Div(BaseTree *left, BaseTree *right) : BaseTree(left, right, '/') {};

protected:

};

