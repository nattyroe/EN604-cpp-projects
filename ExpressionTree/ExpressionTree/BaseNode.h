/// @file
/// @author Nathan Roe
#pragma once
#include <iostream>
#include <string>
#include <map>

using namespace std;

/// Base object for creating nodes for Expression Trees
///
/// Used for providing base functionality to expression
/// tree nodes for trees, variables, and operators
class BaseNode
{
public:
    /// Default destructor for BaseTree objects
    virtual ~BaseNode();

    /// Set left node to give BaseNode
    /// @param node - node to set as left linked node
    void setLeft(BaseNode *node) { this->left = node; };
    /// Set right node to give BaseNode
    /// @param node - node to set as right linked node
    void setRight(BaseNode *node) { this->right = node; };

    /// Return the current info contained in node
    string getData() { return this->data; };

    /// Evaluated node and linked nodes as an expression
    /// 
    /// Evaluates current and linked nodes to find equation
    /// value based on variables contained in given variable
    /// table
    /// @param variableTable - map containing variable names
    ///     and values
    /// Returns float of the resulting equation value
    virtual double evaluate(const map<string, double> *variableTable) = 0;

    /// Calculate and return a derivative of current and linked nodes
    /// 
    /// Creates a new tree containing the derivative of the current
    /// nodes and linked sub-nodes on the given variable
    /// @param variable - variable name to calulate derivative on
    /// Returns a node containing derivative equation
    virtual BaseNode *derive(string variable) = 0;

    /// Clone node and linked sub-nodes
    /// 
    /// Recursively clones this node and all linked nodes
    /// Returns a clone of the current node
    virtual BaseNode *clone() = 0;

    /// Return clone of just left sub-node structure
    BaseNode *getLeftClone();
    /// Return clone of just right sub-node structure
    BaseNode *getRightClone();

protected:
    /// Set stream insertion operator as friend
    friend ostream& operator<<(ostream& os, BaseNode& node);
    BaseNode *left = nullptr;
    BaseNode *right = nullptr;
    string data = "BASE NODE";
};

/// Stream insertion override for printing node info
ostream &operator<<(ostream &os, BaseNode &node);
