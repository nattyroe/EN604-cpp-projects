#include "Mul.h"
#include "BaseTree.h"
#include "BaseNode.h"
#include "Operator.h"

using namespace std;

Mul::Mul(BaseNode *left, BaseNode *right)
{
    createRoot();
    this->root->setLeft(left->clone());
    this->root->setRight(right->clone());
}

Mul::Mul(BaseTree *left, BaseNode *right)
{
    createRoot();
    this->root->setLeft(left->cloneSubStructure());
    this->root->setRight(right->clone());
}

Mul::Mul(BaseNode *left, BaseTree *right)
{
    createRoot();
    this->root->setLeft(left->clone());
    this->root->setRight(right->cloneSubStructure());
}

Mul::Mul(BaseTree* left, BaseTree* right)
{
    createRoot();
    this->root->setLeft(left->cloneSubStructure());
    this->root->setRight(right->cloneSubStructure());
}

void Mul::createRoot()
{
    this->root = new Operator('*');
}
