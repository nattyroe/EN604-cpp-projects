#pragma once
#include "BaseTree.h"
class Sub :
    public BaseTree
{
public:
    Sub(BaseNode* left, BaseNode* right);
    Sub(BaseTree* left, BaseNode* right);
    Sub(BaseNode* left, BaseTree* right);
    Sub(BaseTree* left, BaseTree* right);

protected:
    void createRoot();

};

