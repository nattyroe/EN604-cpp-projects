#include "Variable.h"
#include "Constant.h"
#include <string>

using namespace std;

/// Variable node constructor
Variable::Variable(string name)
{
    this->data = name;
}

/// Evaluate variable based on given variable table
double Variable::evaluate(const map<string, double> *variableTable)
{
    // Attempt to find variable name in table
    auto result = variableTable->find(this->data);
    // Throw error if variable not found
    if (result == variableTable->end())
    {
        throw valuelessVariable;
    }
    // If variable is found, return value
    return result->second;
}

/// Create clone of current variable node
BaseNode *Variable::clone()
{
    BaseNode *clone = new Variable(this->data);
    return clone;
}

/// Return derivative of this variable
BaseNode *Variable::derive(string variable)
{
    // If derivative is on this variable, return 1
    if (variable == this->data)
    {
        return new Constant(1.0);
    }
    // Otherwise, return 0
    return new Constant(0.0);
}
