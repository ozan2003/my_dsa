#include "BinSearchTree.hpp"
#include <iostream>

int main()
{
    BinSearchTree<int> bst;

    for (const int& i : {30, 40, 10, 50, 20, 5, 35})
    {
        bst.insert(i);
    }
    bst.print();

}