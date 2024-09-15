#include <algorithm>
#include <concepts>
#include <iostream>
#include <random>
#include <vector>

const auto seed = std::random_device{}();

const auto rnd = [gen  = std::mt19937{seed},
                  dist = std::uniform_int_distribution{0, 40}]() mutable -> int
{
    return dist(gen);
};

/**
 * Sorts the elements in-place using the insertion sort algorithm.
 *
 * @param vec The vector to be sorted.
 */
template <std::totally_ordered T, std::predicate<T, T> Pred = std::less<T>>
void insertion_sort(std::vector<T>& vec, Pred&& pred = Pred{})
{
    // Go left to right.
    for (auto curr = std::next(vec.begin()); curr != vec.end(); ++curr)
    {
        // Check each element and compare it to the elements to its left.
        // Track our previous element in case we need to swap.
        for (auto prev = curr; prev != vec.begin(); --prev)
        {
            // Move prev to the left until it's less than the element to its
            // left.
            if (*prev < *(prev - 1))
            {
                std::iter_swap(prev, prev - 1);
            }
        }
    }
}

void print(const std::vector<int>& vec)
{
    for (const auto& elem : vec)
    {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

int main()
{
    std::vector<int> vec(10);
    std::generate(vec.begin(), vec.end(), rnd);

    std::cout << "Before sorting: ";
    print(vec);
    insertion_sort(vec, std::less_equal{});
    std::cout << "After sorting:  ";
    print(vec);
}