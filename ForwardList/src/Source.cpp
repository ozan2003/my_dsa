#include "ForwardList.hpp"

#include <iostream>

int main()
{
    ForwardList<int> l{0,1,2,3,4,5};

    auto ll = l;

    std::cout << ll << "\n\n";
    std::cout << l << "\n\n";

}