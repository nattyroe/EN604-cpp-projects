#pragma once
#include <iostream>
#include <string>
#include <map>

using namespace std;

class BaseNode
{
public:
    void setLeft(BaseNode *node) { this->left = node; };
    void setRight(BaseNode *node) { this->right = node; };

    string getData() { return this->data; };

    virtual double evaluate(const map<string, double> *variableTable) = 0;

protected:
    BaseNode *left = nullptr;
    BaseNode *right = nullptr;
    string data = "BASE NODE";
};

ostream &operator<<(ostream &os, BaseNode &node);