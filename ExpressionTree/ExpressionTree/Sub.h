#pragma once
#include "BaseTree.h"
#include <string>

using namespace std;

class Sub : public BaseTree
{
public:
    Sub(BaseNode *left, BaseNode *right) : BaseTree(left, right, '-') {};
    Sub(BaseTree *left, BaseNode *right) : BaseTree(left, right, '-') {};
    Sub(BaseNode *left, BaseTree *right) : BaseTree(left, right, '-') {};
    Sub(BaseTree *left, BaseTree *right) : BaseTree(left, right, '-') {};

    BaseTree* clone();

    BaseTree* derivative(string variable);

protected:

private:
    Sub(BaseNode* root) : BaseTree(root) {};
};

