#include "Stack.hpp"
#include <iostream>

int main()
{
    Stack<int> s(5);

    for (int i{}; i < 5; ++i)
    {
        s.push(i*i);
        std::cout << s.peek() << '\n';
    }
    
    std::cout << "\n\n";

    while (!s.empty())
    {
        std::cout << s.pop() << '\n';
    }
}