/// @file
/// @author Nathan Roe
#pragma once
#include "BaseTree.h"

/// Div tree for creating an Division Expression Tree
///
/// Used for creating Division Tree object
/// pointers and providing functionality
/// for dividing two values/equations
class Div : public BaseTree
{
public:
    /// Constructors for creating a division tree
    ///
    /// A set of constructors for possible combinations of
    /// variable/constant nodes and sub-trees
    /// @param *left - constant, variable, or subtree for left
    ///     side of equation
    /// @param *right - constant, variable, or subtree for right
    ///     side of equation
    Div(BaseNode *left, BaseNode *right) : BaseTree(left, right, '/') {};
    Div(BaseTree *left, BaseNode *right) : BaseTree(left, right, '/') {};
    Div(BaseNode *left, BaseTree *right) : BaseTree(left, right, '/') {};
    Div(BaseTree *left, BaseTree *right) : BaseTree(left, right, '/') {};

    /// Create a clone of a given division tree
    BaseTree *clone();

    /// Find the drivative of given division tree on the given variable
    BaseTree *derivative(string variable);

protected:

private:
    /// Div tree constructor for setting by root node
    Div(BaseNode *root) : BaseTree(root) {};
};
