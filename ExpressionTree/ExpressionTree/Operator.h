/// @file
/// @author Nathan Roe
#pragma once
#include "BaseNode.h"
#include <exception>

using namespace std;

/// Create a new node for representing operators
/// 
/// Creates an operator of a given type
class Operator : public BaseNode
{
public:
    /// Operator node constructor
    ///
    /// Creates an operator of the given type
    Operator(char oper);
    
    /// Evaluate equation by finding the result of left *oper* right
    ///
    /// @param variableTable - map linking variable names to values
    /// Return double of the result of equation evaluation
    double evaluate(const map<string, double> *variableTable);

    /// Return derivative of this operator and linked nodes
    ///
    /// @param variable - variable the derivative is calculated on
    /// Returns BaseNode pointer with derivative based on operator type
    BaseNode *derive(string variable);

    /// Create clone of current operator node
    BaseNode *clone();

    /// Error for creating an operator of an invalid type or
    ///    attempting evaluation of a node without two lined
    ///    sub-nodes
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
