#pragma once
#include "BaseNode.h"
#include <iostream>

class BaseTree
{
public:
    double evaluate() { return this->root->evaluate(&this->variableTable); };
    void let(string variableName, double value);
    void setRoot(BaseNode *root) { this->root = root; };
    map<string, double> getVariableTable() { return this->variableTable; };

private:
    friend ostream& operator<<(ostream& os, BaseTree& tree);
    BaseNode *root = nullptr;
    map<string, double> variableTable;

};

ostream& operator<<(ostream& os, BaseTree& tree);
