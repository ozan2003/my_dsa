#include "ForwardList.hpp"

#include <iostream>

int main()
{
    ForwardList<int> l{0,1,2,3,4,5};
    ForwardList<int> ll{0,10,20,30,40,50};


    ll = l;

    std::cout << ll << "\n\n";
    std::cout << l << "\n\n";

}