/// @file
/// @author Nathan Roe
#pragma once
#include "BaseTree.h"

/// Add tree for creating an Addition Expression Treee
///
/// Used for creating Addition Tree object
/// pointers and providing functionality
/// for adding two values/equations together
class Add : public BaseTree
{
public:
    /// Constructors for creating an addition tree
    ///
    /// A set of constructors for possible combinations of
    /// variable/constant nodes and sub-trees
    /// @param *left - constant, variable, or subtree for left
    ///     side of equation
    /// @param *right - constant, variable, or subtree for right
    ///     side of equation
    Add(BaseNode *left, BaseNode *right) : BaseTree(left, right, '+') {};
    Add(BaseTree *left, BaseNode *right) : BaseTree(left, right, '+') {};
    Add(BaseNode *left, BaseTree *right) : BaseTree(left, right, '+') {};
    Add(BaseTree *left, BaseTree *right) : BaseTree(left, right, '+') {};

    /// Create a clone of a given addition tree
    BaseTree *clone();

    /// Find the drivative of given addition tree on the given variable
    BaseTree *derivative(string variable);

protected:

private:
    /// Add tree constructor for setting by root node
    Add(BaseNode *root) : BaseTree(root) {};
};
