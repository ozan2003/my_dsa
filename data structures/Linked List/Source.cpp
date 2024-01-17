#include "DList.hpp"
#include <iostream>

int main()
{
    DList<int> d{1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::cout << d << "---- " << d.size() << '\n';
    d.append(300);
    std::cout << d << "---- " << d.size() << '\n';
    d.remove_back();
    std::cout << d << "---- " << d.size() << '\n';
    d.remove_front();
    std::cout << d << "---- " << d.size() << '\n';
    d.insert(6, 1000);
    std::cout << d << "---- " << d.size() << '\n';
    std::cout << "d[7] = " << d[7] << " ---- " << d.size() << '\n';
}