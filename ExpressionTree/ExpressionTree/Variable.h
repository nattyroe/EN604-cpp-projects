/// @file
/// @author Nathan Roe
#pragma once
#include "BaseNode.h"
#include <exception>

using namespace std;

/// Create a new node for representing Variables
/// 
/// Creates a vairable node with a given name
class Variable : public BaseNode
{
public:
    /// Variable node constructor
    ///
    /// Creates a variable with the given name
    Variable(string name);

    /// Evaluate variable based on given variable table
    /// 
    /// @param variableTable - map linking variable names to values
    /// Returns value from variable table for current variable
    double evaluate(const map<string, double> *variableTable);

    /// Return derivative of this variable
    ///  
    /// @param variable - variable the derivative is calculated on
    /// Returns 1 if variable name is this variable, 0 otherwise
    BaseNode *derive(string variable);

    /// Create clone of current variable node
    BaseNode *clone();

    /// Error for attempting to evaluate variable if node value
    ///    is not contained in table
    class valuelessVariable : public std::exception
    {
    public:
        virtual const char *what() const throw()
        {
            return "Cannot Evaluate Variable; No Value Set";
        }
    } valuelessVariable;
};
