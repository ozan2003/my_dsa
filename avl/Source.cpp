#include "AVLTree.hpp"
#include <iostream>
#include <chrono>

namespace chr = std::chrono;

int main()
{
    AVLTree<int> avl;

    auto t1 = chr::steady_clock::now();
    for (const auto& i : {374,37,631,102,358,77,73,792,33,366,965,800,758,651,321,455,556,415,96,674,348,698,992,424,709,112,622,682,323,853,634,408,506,409,577,17,798,712,361,677,984,106,107,812,633,552,512,847,194,804,788,45,859,592,141,142,457,458,480,56,639,926,39,310,656,23,436,369,770,169,700,936,910,525,701,667,129,961,88,660,82,939,316})
    {
        avl.insert(i);
    }
    avl.print(); std::cout << "\n\n";

    std::cout << avl.sum();

    auto t2 = chr::steady_clock::now();

    chr::duration<float, std::milli> t = t2 - t1;
    std::cout << "\nTook " << t.count() << " miliseconds.\n";
}