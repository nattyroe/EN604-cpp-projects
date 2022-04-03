/// @file
/// @author Nathan Roe
#pragma once
#include "BaseTree.h"

/// Sub tree for creating an Addition Expression Tree
///
/// Used for creating Subtraction Tree object
/// pointers and providing functionality
/// for subtracting two values/equations
class Sub : public BaseTree
{
public:
    /// Constructors for creating a subtraction tree
    ///
    /// A set of constructors for possible combinations of
    /// variable/constant nodes and sub-trees
    /// @param *left - constant, variable, or subtree for left
    ///     side of equation
    /// @param *right - constant, variable, or subtree for right
    ///     side of equation
    Sub(BaseNode *left, BaseNode *right) : BaseTree(left, right, '-') {};
    Sub(BaseTree *left, BaseNode *right) : BaseTree(left, right, '-') {};
    Sub(BaseNode *left, BaseTree *right) : BaseTree(left, right, '-') {};
    Sub(BaseTree *left, BaseTree *right) : BaseTree(left, right, '-') {};

    /// Create a clone of a given subtraction tree
    BaseTree *clone();

    /// Find the drivative of given subtraction tree on the given variable
    BaseTree *derivative(string variable);

protected:

private:
    /// Sub tree constructor for setting by root node
    Sub(BaseNode *root) : BaseTree(root) {};
};
