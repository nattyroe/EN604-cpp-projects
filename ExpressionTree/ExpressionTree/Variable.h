#pragma once
#include "BaseNode.h"
#include <string>
#include <map>
#include <exception>

using namespace std;

class Variable : public BaseNode
{
public:
    Variable(string name);

    double evaluate(const map<string, double> *variableTable);
    
    class valuelessVariable : public std::exception
    {
    public:
        virtual const char *what() const throw()
        {
            return "Cannot Evaluate Variable; No Value Set";
        }
    } valuelessVariable;
};

