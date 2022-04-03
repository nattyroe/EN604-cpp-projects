/// @file
/// @author Nathan Roe
#pragma once
#include "BaseTree.h"

/// Mul tree for creating an Multiplication Expression Tree
///
/// Used for creating Multiplication Tree object
/// pointers and providing functionality
/// for multiplying two values/equations together
class Mul : public BaseTree
{
public:
    /// Constructors for creating a multiplication tree
    ///
    /// A set of constructors for possible combinations of
    /// variable/constant nodes and sub-trees
    /// @param *left - constant, variable, or subtree for left
    ///     side of equation
    /// @param *right - constant, variable, or subtree for right
    ///     side of equation
    Mul(BaseNode *left, BaseNode *right) : BaseTree(left, right, '*') {};
    Mul(BaseTree *left, BaseNode *right) : BaseTree(left, right, '*') {};
    Mul(BaseNode *left, BaseTree *right) : BaseTree(left, right, '*') {};
    Mul(BaseTree *left, BaseTree *right) : BaseTree(left, right, '*') {};

    /// Create a clone of a given multiplication tree
    BaseTree *clone();

    /// Find the drivative of given multiplication tree on the given variable
    BaseTree *derivative(string variable);

protected:

private:
    /// Mul tree constructor for setting by root node
    Mul(BaseNode *root) : BaseTree(root) {};
};
