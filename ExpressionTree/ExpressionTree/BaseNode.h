#pragma once
#include <iostream>
#include <string>
#include <map>

using namespace std;

class BaseNode
{
public:
    virtual ~BaseNode();

    void setLeft(BaseNode *node) { this->left = node; };
    void setRight(BaseNode *node) { this->right = node; };

    string getData() { return this->data; };

    virtual double evaluate(const map<string, double> *variableTable) = 0;

protected:
    friend ostream& operator<<(ostream& os, BaseNode& node);
    BaseNode *left = nullptr;
    BaseNode *right = nullptr;
    string data = "BASE NODE";
};

ostream &operator<<(ostream &os, BaseNode &node);