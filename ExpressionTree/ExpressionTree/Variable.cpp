#include "Variable.h"
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