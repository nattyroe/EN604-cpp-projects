#pragma once
#include "BaseTree.h"
class Div : public BaseTree
{
public:
    Div(BaseNode* left, BaseNode* right);
    Div(BaseTree* left, BaseNode* right);
    Div(BaseNode* left, BaseTree* right);
    Div(BaseTree* left, BaseTree* right);

protected:
    void createRoot();

};

