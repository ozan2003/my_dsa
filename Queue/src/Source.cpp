#include "Queue.hpp"
#include <iostream>

int main()
{
    Queue<int> q(4);

    q.enqueue(10);
    q.enqueue(20);
    q.dequeue();
    q.enqueue(30);
    q.enqueue(40);
    q.dequeue();
    q.dequeue();
    q.enqueue(50);
    q.dequeue();
    q.enqueue(60);
    q.enqueue(70);
    q.dequeue();
    q.dequeue();
}