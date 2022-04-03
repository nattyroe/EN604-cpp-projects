/// @file
/// @author Nathan Roe
#pragma once
#include "BaseNode.h"
#include <iostream>
#include <string>

using namespace std;

/// Base object for creating Expression Trees
///
/// Used for creating generic Expression Tree object
/// pointers and providing functionality
/// for all Expression Tree types
class BaseTree
{
public:
    /// Constructors for base tree functionality
    ///
    /// A set of constructors for possible combinations of
    /// variable/constant nodes and sub-trees
    /// @param *left - constant, variable, or subtree for left
    ///     side of equation
    /// @param *right - constant, variable, or subtree for right
    ///     side of equation
    /// @param oper - character representing equation operator,
    ///     +, -, /, or *
    BaseTree(BaseNode *left, BaseNode *right, char oper);
    BaseTree(BaseTree *left, BaseNode *right, char oper);
    BaseTree(BaseNode *left, BaseTree *right, char oper);
    BaseTree(BaseTree *left, BaseTree *right, char oper);

    /// Default destructor for BaseTree objects
    virtual ~BaseTree();

    /// Evaluate equation based on current variable values
    ///
    /// Returns a float of the calculated equation value
    double evaluate() { return this->root->evaluate(&this->variableTable); };

    /// Set given variable to provided value
    ///
    /// variableName - string name of variable to set
    /// value - float value to set 
    void let(string variableName, double value);

    /// Find the drivative of the equation on the given variable
    ///
    /// Calculate the derivative on given value and return
    /// a new expression tree with the derived equation and
    /// the same variables as the original.
    /// @param variable - variable one which to calculate derivative
    /// Return a new variable tree with the derivative
    virtual BaseTree *derivative(string variable) = 0;

    /// Create a clone of a given expresson tree
    ///
    /// Create and return a copy of the expression tree with same
    /// equation and variable values
    /// Return a BaseTree pointer with a copied version of the tree
    virtual BaseTree *clone() = 0;

protected:
    /// BaseTree constructor for setting by root node
    ///
    /// Used internally to create derivatives from
    /// the derivitive of the current root node
    /// @param *root -  BaseNode to use as the new tree's root
    BaseTree(BaseNode *root);

    /// Set the stream operator as a friend
    friend ostream& operator<<(ostream& os, BaseTree& tree);
    BaseNode *root = nullptr;
    map<string, double> variableTable;

    /// Copy variable table names and values to another tree
    /// 
    /// @param newTree - Copies current tree variableTable
    ///     to this tree
    void copyVariableTableTo(BaseTree *newTree);

private:
    /// Creates a copy of all nodes in the tree
    /// 
    /// Copies all nodes in the tree and returns
    /// the root node of the copy
    /// Returns the root node of the copied tree
    BaseNode *cloneSubStructure();
};

/// Stream insertion override for printing tree info
ostream& operator<<(ostream& os, BaseTree& tree);
