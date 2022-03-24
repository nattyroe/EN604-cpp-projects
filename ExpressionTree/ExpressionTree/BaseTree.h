#pragma once
#include "BaseNode.h"
#include <iostream>
#include <string>

using namespace std;

class BaseTree
{
public:
    BaseTree(BaseNode *left, BaseNode *right, char oper);
    BaseTree(BaseTree *left, BaseNode *right, char oper);
    BaseTree(BaseNode *left, BaseTree *right, char oper);
    BaseTree(BaseTree *left, BaseTree *right, char oper);

    double evaluate() { return this->root->evaluate(&this->variableTable); };
    void let(string variableName, double value);
    virtual BaseTree *derivative(string variable) = 0;

    map<string, double> getVariableTable() { return this->variableTable; };
    BaseNode *cloneSubStructure();
    virtual BaseTree *clone() = 0;

protected:
    BaseTree(BaseNode *root);
    friend ostream& operator<<(ostream& os, BaseTree& tree);
    BaseNode *root = nullptr;
    map<string, double> variableTable;
    void copyVariableTableTo(BaseTree *newTree);

private:

};

ostream& operator<<(ostream& os, BaseTree& tree);
