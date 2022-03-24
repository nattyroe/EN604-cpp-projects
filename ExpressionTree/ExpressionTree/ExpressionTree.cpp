// ExpressionTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "BaseNode.h"
#include "Constant.h"
#include "Variable.h"
#include "Operator.h"
#include "BaseTree.h"
#include "Mul.h"
#include "Div.h"
#include "Add.h"
#include "Sub.h"
#include <iostream>
#include <map>

using namespace std;

int main()
{
    BaseTree *t = new Add(new Mul(new Constant(2.3),
                                  new Variable("Xray")),
                          new Mul(new Variable("Yellow"),
                                  new Sub(new Variable("Zebra"),
                                          new Variable("Xray"))));
    t->let("Xray", 2.0);
    t->let("Yellow", 3.0);
    t->let("Zebra", 5.0);
    cout << *t << "=" << t->evaluate() << endl;

    BaseTree *derived = t->derivative("Xray");
    cout << *derived << "=" << derived->evaluate() << endl;

    cout << endl;

    BaseTree *t2 = t->clone();
    cout << *t2 << "=" << t2->evaluate() << endl;

    cout << endl;

    t = new Sub(new Mul(new Constant(2.3),
                        new Variable("Xray")),
                new Mul(new Variable("Yellow"),
                        new Sub(new Variable("Zebra"),
                                new Variable("Xray"))));
    t->let("Xray", 2.0);
    t->let("Yellow", 3.0);
    t->let("Zebra", 5.0);
    cout << *t << "=" << t->evaluate() << endl;
    derived = t->derivative("Xray");
    cout << *derived << "=" << derived->evaluate() << endl;

    cout << endl;

    t = new Mul(new Mul(new Constant(2.3),
                        new Variable("Xray")),
                new Mul(new Variable("Yellow"),
                        new Sub(new Variable("Zebra"),
                                new Variable("Xray"))));
    t->let("Xray", 2.0);
    t->let("Yellow", 3.0);
    t->let("Zebra", 5.0);
    cout << *t << "=" << t->evaluate() << endl;
    derived = t->derivative("Xray");
    cout << *derived << "=" << derived->evaluate() << endl;

    cout << endl;

    t = new Div(new Mul(new Constant(2.3),
                        new Variable("Xray")),
                new Mul(new Variable("Yellow"),
                        new Sub(new Variable("Zebra"),
                                new Variable("Xray"))));
    t->let("Xray", 2.0);
    t->let("Yellow", 3.0);
    t->let("Zebra", 5.0);
    cout << *t << "=" << t->evaluate() << endl;
    derived = t->derivative("Xray");
    cout << *derived << "=" << derived->evaluate() << endl;
}
