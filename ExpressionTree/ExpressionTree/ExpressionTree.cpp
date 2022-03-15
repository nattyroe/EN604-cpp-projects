// ExpressionTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "BaseNode.h"
#include "Constant.h"
#include "Variable.h"
#include "Operator.h"
#include <iostream>
#include <map>

using namespace std;

int main()
{
    BaseNode *baseNode = new BaseNode();

    Constant *constant = new Constant(1.1);

    Variable *variable = new Variable("X");
    map<string, double> variableTable;
    variableTable.insert(pair<string,double>("X", 5.0));
    cout << *variable << " = " << variable->evaluate(&variableTable) << endl;

    Operator *oper = new Operator('*');
    oper->setLeft(constant);
    oper->setRight(variable);
    cout << *constant << *oper << *variable << "=" << oper->evaluate(&variableTable);

}