#pragma once
#include "BaseTree.h"
#include <string>

using namespace std;

class Add : public BaseTree
{
public:
    Add(BaseNode *left, BaseNode *right) : BaseTree(left, right, '+') {};
    Add(BaseTree *left, BaseNode *right) : BaseTree(left, right, '+') {};
    Add(BaseNode *left, BaseTree *right) : BaseTree(left, right, '+') {};
    Add(BaseTree *left, BaseTree *right) : BaseTree(left, right, '+') {};

    BaseTree *clone();

    BaseTree *derivative(string variable);

protected:

private:
    Add(BaseNode *root) : BaseTree(root) {};
};
