#pragma once
#include "BaseNode.h"
#include <iostream>

class BaseTree
{
public:
    BaseTree(BaseNode* left, BaseNode* right, char oper);
    BaseTree(BaseTree* left, BaseNode* right, char oper);
    BaseTree(BaseNode* left, BaseTree* right, char oper);
    BaseTree(BaseTree* left, BaseTree* right, char oper);

    double evaluate() { return this->root->evaluate(&this->variableTable); };
    void let(string variableName, double value);

    map<string, double> getVariableTable() { return this->variableTable; };
    BaseNode* cloneSubStructure();
    virtual BaseTree *clone() = 0;

protected:
    friend ostream& operator<<(ostream& os, BaseTree& tree);
    BaseNode* root = nullptr;
    map<string, double> variableTable;

private:

};

ostream& operator<<(ostream& os, BaseTree& tree);
