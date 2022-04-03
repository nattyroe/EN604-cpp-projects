#include "BaseTree.h"
#include "Operator.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

/// Constructor for base tree functionality using two BaseNodes
BaseTree::BaseTree(BaseNode *left, BaseNode *right, char oper)
{
    this->root = new Operator(oper);
    this->root->setLeft(left->clone());
    this->root->setRight(right->clone());
} // End function BaseTree constructor (node, node)

/// Constructor for base tree functionality a BaseNode and BaseTree
BaseTree::BaseTree(BaseTree *left, BaseNode *right, char oper)
{
    this->root = new Operator(oper);
    this->root->setLeft(left->cloneSubStructure());
    this->root->setRight(right->clone());
} // End function BaseTree constructor (tree, node)

/// Constructor for base tree functionality a BaseNode and BaseTree
BaseTree::BaseTree(BaseNode *left, BaseTree *right, char oper)
{
    this->root = new Operator(oper);
    this->root->setLeft(left->clone());
    this->root->setRight(right->cloneSubStructure());
} // End function BaseTree constructor (node, tree)

/// Constructor for base tree functionality using two BaseTree
BaseTree::BaseTree(BaseTree *left, BaseTree *right, char oper)
{
    this->root = new Operator(oper);
    this->root->setLeft(left->cloneSubStructure());
    this->root->setRight(right->cloneSubStructure());
} // End function BaseTree constructor (tree, tree)

/// Constructor for base tree using just a node for the root
BaseTree::BaseTree(BaseNode *root)
{
    this->root = root->clone();
} // End function BaseTree constructor from root

/// Default destructor for BaseTree objects
BaseTree::~BaseTree()
{
    delete this->root;
} // End function ~BaseTree

/// Set given variable to provided value
void BaseTree::let(string variableName, double value)
{
    this->variableTable.insert(pair<string, double>(variableName, value));
} // End function let

/// Creates a copy of all nodes in the tree, return the root node
BaseNode *BaseTree::cloneSubStructure()
{
    return this->root->clone();
} // End function cloneSubStructure

/// Copy variable table names and values to given tree
void BaseTree::copyVariableTableTo(BaseTree *newTree)
{
    map<string, double>::iterator itr;
    for (itr = this->variableTable.begin(); itr != this->variableTable.end(); ++itr)
    {
        newTree->let(itr->first, itr->second);
    }
} // End function copyVariableTableTo

/// Stream insertion override for printing tree info
ostream& operator<<(ostream& os, BaseTree& tree)
{
    // Print out current variable settings
    map<string, double>::iterator itr;
    for (itr = tree.variableTable.begin(); itr != tree.variableTable.end(); ++itr)
    {
        os << itr->first << " = " << itr->second << '\n';
    }
    // Print out tree nodes
    os << *tree.root;
    return os;
} // End function << override
