#pragma once
#include "BaseNode.h"
#include <iostream>

class BaseTree
{
public:
    double evaluate() { return this->root->evaluate(&this->variableTable); };
    void let(string variableName, double value);

    map<string, double> getVariableTable() { return this->variableTable; };
    BaseNode* cloneSubStructure();

protected:
    friend ostream& operator<<(ostream& os, BaseTree& tree);
    virtual void createRoot() = 0;
    BaseNode* root = nullptr;
    map<string, double> variableTable;

private:

};

ostream& operator<<(ostream& os, BaseTree& tree);
