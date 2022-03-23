#include "Variable.h"
#include "Constant.h"
#include <string>

using namespace std;

Variable::Variable(string name)
{
    this->data = name;
}

double Variable::evaluate(const map<string, double> *variableTable)
{
    auto result = variableTable->find(this->data);
    if (result == variableTable->end())
    {
        throw valuelessVariable;
    }
    return result->second;
}

BaseNode *Variable::clone()
{
    BaseNode* clone = new Variable(this->data);
    if (this->left)
    {
        clone->setLeft(this->left->clone());
    }
    if (this->right)
    {
        clone->setRight(this->right->clone());
    }
    return clone;
}

BaseNode *Variable::derive(string variable)
{
    if (variable == this->data)
    {
        return new Constant(1.0);
    }
    return new Constant(0.0);
}
