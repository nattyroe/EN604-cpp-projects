#include "Div.h"
#include "BaseTree.h"
#include "BaseNode.h"
#include "Operator.h"

using namespace std;

Div::Div(BaseNode* left, BaseNode* right)
{
    createRoot();
    this->root->setLeft(left->clone());
    this->root->setRight(right->clone());
}

Div::Div(BaseTree* left, BaseNode* right)
{
    createRoot();
    this->root->setLeft(left->cloneSubStructure());
    this->root->setRight(right->clone());
}

Div::Div(BaseNode* left, BaseTree* right)
{
    createRoot();
    this->root->setLeft(left->clone());
    this->root->setRight(right->cloneSubStructure());
}

Div::Div(BaseTree* left, BaseTree* right)
{
    createRoot();
    this->root->setLeft(left->cloneSubStructure());
    this->root->setRight(right->cloneSubStructure());
}

void Div::createRoot()
{
    this->root = new Operator('/');
}

