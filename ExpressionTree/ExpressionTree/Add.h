#pragma once
#include "BaseTree.h"
class Add : public BaseTree
{
public:
    Add(BaseNode* left, BaseNode* right);
    Add(BaseTree* left, BaseNode* right);
    Add(BaseNode* left, BaseTree* right);
    Add(BaseTree* left, BaseTree* right);

protected:
    void createRoot();

};

