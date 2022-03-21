// ExpressionTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "BaseNode.h"
#include "Constant.h"
#include "Variable.h"
#include "Operator.h"
#include "BaseTree.h"
#include <iostream>
#include <map>

using namespace std;

int main()
{
    BaseTree *tree = new BaseTree();

    Constant *constant = new Constant(1.1);

    Variable *variable = new Variable("X");
    tree->let("X", 5.0);

    Operator *oper = new Operator('*');
    oper->setLeft(constant);
    oper->setRight(variable);
    tree->setRoot(oper);
    cout << *tree << "=" << tree->evaluate();

}