#include "BaseTree.h"
#include "Operator.h"
#include <iostream>
#include <string>
#include <map>

using namespace std; 

BaseTree::BaseTree(BaseNode *left, BaseNode *right, char oper)
{
    this->root = new Operator(oper);
    this->root->setLeft(left->clone());
    this->root->setRight(right->clone());
}

BaseTree::BaseTree(BaseTree *left, BaseNode *right, char oper)
{
    this->root = new Operator(oper);
    this->root->setLeft(left->cloneSubStructure());
    this->root->setRight(right->clone());
}

BaseTree::BaseTree(BaseNode *left, BaseTree *right, char oper)
{
    this->root = new Operator(oper);
    this->root->setLeft(left->clone());
    this->root->setRight(right->cloneSubStructure());
}

BaseTree::BaseTree(BaseTree *left, BaseTree *right, char oper)
{
    this->root = new Operator(oper);
    this->root->setLeft(left->cloneSubStructure());
    this->root->setRight(right->cloneSubStructure());
}

BaseTree::BaseTree(BaseNode *root)
{
    this->root = root->clone();
}

void BaseTree::let(string variableName, double value)
{
    this->variableTable.insert(pair<string, double>(variableName, value));
}

BaseNode *BaseTree::cloneSubStructure()
{
    return this->root->clone();
}

void BaseTree::copyVariableTableTo(BaseTree *newTree)
{
    map<string, double>::iterator itr;
    for (itr = this->variableTable.begin(); itr != this->variableTable.end(); ++itr)
    {
        newTree->let(itr->first, itr->second);
    }
}

ostream& operator<<(ostream& os, BaseTree& tree)
{
    map<string, double>::iterator itr;
    for (itr = tree.variableTable.begin(); itr != tree.variableTable.end(); ++itr)
    {
        os << itr->first << " = " << itr->second << '\n';
    }
    os << *tree.root;
    return os;
}
