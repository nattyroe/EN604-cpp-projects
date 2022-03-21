#include "BaseTree.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

void BaseTree::let(string variableName, double value)
{
    this->variableTable.insert(pair<string, double>(variableName, value));
}

ostream& operator<<(ostream& os, BaseTree& tree)
{
    map<string, double>::iterator itr;
    for (itr = tree.variableTable.begin(); itr != tree.variableTable.end(); ++itr)
    {
        os << itr->first << " = " << itr->second << '\n';
    }
    os << *tree.root;
    return os;
}