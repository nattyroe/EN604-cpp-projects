#pragma once
#include "BaseNode.h"
#include <map>
#include <exception>

using namespace std;

class Operator : public BaseNode
{
public:
    Operator(char oper);

    double evaluate(const map<string, double> *variableTable);
    BaseNode *derive(string variable);

    BaseNode *clone();

    class invalidOperator : public std::exception
    {
    public:
        virtual const char *what() const throw()
        {
            return "Cannot Evaluate Operator";
        }
    } invalidOperator;

private:
    char oper = ' ';
};
