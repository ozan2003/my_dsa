#include <iostream>
#include <vector>

constexpr int SIZE{20'000'000};

/*
 * @brief Perform binary search. The container must be sorted.
 * @param vec The array to be worked on. 
 * @param target The number to be searched on array.
 * @return The index of "target". -1 if it's not found.
 */
int bin_search(const std::vector<int>& vec, const int target)
{
    auto front = vec.begin();   // The first element.
    auto rear  = vec.end() - 1; // The last element.

    while (front <= rear)
    {
        auto mid = front + (rear - front) / 2; // Divide the container in half.
        // This is equivalent to (front + rear / 2).

        if (*mid < target)
        {
            // If the target is less than middle,
            // discard the left side, including middle.
            front = mid + 1; // front is now one after the middle.
        }
        else if (*mid > target)
        {
            // If the target is more than middle,
            // discard the right side, including middle.
            rear = mid - 1; // rear is one front of the middle.
        }
        else
        {
            // If the target is equal to middle,
            // return its index by returning the distance between the first.
            // std::vector<T>::difference_type is actually std::ptrdiff_t which is long long.
            return static_cast<int>(mid - vec.begin());
        }
    }

    return -1; // Indicate nothing is found.
}

int main()
{
    std::vector<int> v;
    v.reserve(SIZE);

    for (std::size_t i{}; i < v.capacity(); ++i)
    {
        v.push_back(static_cast<int>(i));
    }

    std::cout << bin_search(v, 19'090'112) << '\n';
}