#include "Sub.h"
#include "BaseTree.h"
#include "BaseNode.h"
#include "Operator.h"

using namespace std;

Sub::Sub(BaseNode* left, BaseNode* right)
{
    createRoot();
    this->root->setLeft(left->clone());
    this->root->setRight(right->clone());
}

Sub::Sub(BaseTree* left, BaseNode* right)
{
    createRoot();
    this->root->setLeft(left->cloneSubStructure());
    this->root->setRight(right->clone());
}

Sub::Sub(BaseNode* left, BaseTree* right)
{
    createRoot();
    this->root->setLeft(left->clone());
    this->root->setRight(right->cloneSubStructure());
}

Sub::Sub(BaseTree* left, BaseTree* right)
{
    createRoot();
    this->root->setLeft(left->cloneSubStructure());
    this->root->setRight(right->cloneSubStructure());
}

void Sub::createRoot()
{
    this->root = new Operator('-');
}

