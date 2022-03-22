#include "Add.h"
#include "BaseTree.h"
#include "BaseNode.h"
#include "Operator.h"

using namespace std;

Add::Add(BaseNode* left, BaseNode* right)
{
    createRoot();
    this->root->setLeft(left->clone());
    this->root->setRight(right->clone());
}

Add::Add(BaseTree* left, BaseNode* right)
{
    createRoot();
    this->root->setLeft(left->cloneSubStructure());
    this->root->setRight(right->clone());
}

Add::Add(BaseNode* left, BaseTree* right)
{
    createRoot();
    this->root->setLeft(left->clone());
    this->root->setRight(right->cloneSubStructure());
}

Add::Add(BaseTree* left, BaseTree* right)
{
    createRoot();
    this->root->setLeft(left->cloneSubStructure());
    this->root->setRight(right->cloneSubStructure());
}

void Add::createRoot()
{
    this->root = new Operator('+');
}
