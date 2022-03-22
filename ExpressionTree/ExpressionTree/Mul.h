#pragma once
#include "BaseTree.h"

class BaseNode;

using namespace std;

class Mul : public BaseTree
{
public:
    Mul(BaseNode *left, BaseNode *right);
    Mul(BaseTree *left, BaseNode *right);
    Mul(BaseNode *left, BaseTree *right);
    Mul(BaseTree *left, BaseTree *right);

protected:
    void createRoot();

};

