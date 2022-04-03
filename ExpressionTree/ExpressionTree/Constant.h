#pragma once
#include "BaseNode.h"
#include <limits>

using namespace std;

/// Create a new node for representing constants
/// 
/// Creates a constant with a given value
class Constant : public BaseNode
{
public:
    /// Constant node constructor
    ///
    /// Creates a constant with the given value
    Constant(double value);

    /// Evaluate constant
    /// 
    /// @param variableTable - map linking variable names to values
    /// Returns value of this constant
    double evaluate(const map<string, double> *variableTable);

    /// Return derivative of this variable
    ///
    /// @param variable - variable the derivative is calculated on
    /// Returns 0
    BaseNode *derive(string variable);

    /// Create clone of current constant node
    BaseNode *clone();

private:
    /// Set default value to NaN
    double value = numeric_limits<double>::signaling_NaN();
};
