#include "Stack.hpp"
#include <iostream>
#include <chrono>

int main()
{
    Stack<int> s(100);

    auto t1 = std::chrono::steady_clock::now();
    for (int i{}; i < 100; ++i)
    {
        s.push(i);
        std::cout << s.top() << '\n';
    }
    
    std::cout << "\n\n";

    while (!s.empty())
    {
        std::cout << s.pop() << '\n';
    }
    auto t2 = std::chrono::steady_clock::now();

    std::chrono::duration<float, std::milli> t = t2 - t1;
    std::cout << "\nTime taken: " << t.count() << "ms\n";
}