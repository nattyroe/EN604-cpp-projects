#include "BaseTree.h"
#include "Operator.h"
#include <iostream>
#include <string>
#include <map>

using namespace std; 

BaseTree::BaseTree(BaseNode* left, BaseNode* right, char oper)
{
    this->root = new Operator(oper);
    this->root->setLeft(left->clone());
    this->root->setRight(right->clone());
}

BaseTree::BaseTree(BaseTree* left, BaseNode* right, char oper)
{
    this->root = new Operator(oper);
    this->root->setLeft(left->cloneSubStructure());
    this->root->setRight(right->clone());
}

BaseTree::BaseTree(BaseNode* left, BaseTree* right, char oper)
{
    this->root = new Operator(oper);
    this->root->setLeft(left->clone());
    this->root->setRight(right->cloneSubStructure());
}

BaseTree::BaseTree(BaseTree* left, BaseTree* right, char oper)
{
    this->root = new Operator(oper);
    this->root->setLeft(left->cloneSubStructure());
    this->root->setRight(right->cloneSubStructure());
}

void BaseTree::let(string variableName, double value)
{
    this->variableTable.insert(pair<string, double>(variableName, value));
}

BaseNode* BaseTree::cloneSubStructure()
{
    return this->root->clone();
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