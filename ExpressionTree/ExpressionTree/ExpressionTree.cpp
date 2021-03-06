// @file
// @author Nathan Roe
//
// Demonstrates the functionality of for creating and evaluating
// Expression Tree equations and thier derivatives. Shows
// examples of calculating several trees with roots as operators
// of addition, subtraction, multiplication, and division, as
// well as generating and evaluating thier derivatives.

#include "Constant.h"
#include "Variable.h"
#include "BaseTree.h"
#include "Mul.h"
#include "Div.h"
#include "Add.h"
#include "Sub.h"
#include <iostream>

using namespace std;

// Run example expression trees and derivations, and print results
int main()
{
    // Create Expression Tree with root Addition node
    cout << "Test Addition Tree" << endl;
    BaseTree *t = new Add(new Mul(new Constant(2.3),
                                  new Variable("Xray")),
                          new Mul(new Variable("Yellow"),
                                  new Sub(new Variable("Zebra"),
                                          new Variable("Xray"))));
    t->let("Xray", 2.0);
    t->let("Yellow", 3.0);
    t->let("Zebra", 5.0);
    cout << *t << "=" << t->evaluate() << endl;

    // Evaluate and print derivative
    cout << "Test Addition Tree derivation" << endl;
    BaseTree *derived = t->derivative("Xray");
    cout << *derived << "=" << derived->evaluate() << endl;

    cout << endl;

    // Demonstrate clone capability
    cout << "Test Clone Capability" << endl;
    BaseTree *t2 = t->clone();
    cout << *t2 << "=" << t2->evaluate() << endl;

    cout << endl;

    // Demonstrate Expression Tree with root Subtraction node
    cout << "Test Subtraction Tree and Derivation" << endl;
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

    // Demonstrate Expression Tree with root Multiplication node
    cout << "Test Multiplication Tree and Derivation" << endl;
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

    // Demonstrate Expression Tree with root Division node
    cout << "Test Division Tree and Derivation" << endl;
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
} // End function main
