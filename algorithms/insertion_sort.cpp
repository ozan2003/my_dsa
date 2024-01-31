#include <algorithm>
#include <iostream>
#include <vector>
#include <random>

const auto seed = std::random_device{}();

const auto rnd = [gen = std::mt19937{seed}, dist = std::uniform_int_distribution{1, 25}]() mutable -> int
{
    return dist(gen);
};

/**
 * The insertion sort algorithm.
 * The container will be sorted in-place.
 *
 * @param vec The vector to be sorted.
 */
void insertion_sort(std::vector<int>& vec)
{
    // Go left to right.
    for (auto curr = vec.begin(); curr != vec.end(); ++curr)
    {
        // Check each element and compare it to the elements to its left.
        // Track our previous element in case we need to swap.
        for (auto prev = curr - 1; prev >= vec.begin(); --prev)
        {
            // Swap if the previous element is greater than the current element
            // until we're at the beginning.
            if (*prev > *(prev + 1))
            {
                std::iter_swap(prev, prev + 1);
            }
        }
    }
}

int main()
{
    std::vector<int> vec(10);
    std::generate(vec.begin(), vec.end(), rnd);

    std::cout << "Before: ";
    for (const auto& item : vec)
    {
        std::cout << item << ' ';
    }

    insertion_sort(vec);

    std::cout << "\nAfter: ";
    for (const auto& item : vec)
    {
        std::cout << item << ' ';
    }
    std::cout << '\n';
}