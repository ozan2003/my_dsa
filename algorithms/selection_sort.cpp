#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

/**
 * Sorts the elements in the given vector using the selection sort algorithm.
 * Note that since it has O(n^2) time complexity, it's not suitable for large
 * containers.
 * 
 * @param vec The vector to be sorted.
 */
void selection_sort(std::vector<int>& vec)
{
    // Start from the beginning.
    // There's no need to look at the last element since the last comparison
    // always with itself.
    for (auto it = vec.begin(); it < vec.end() - 1; ++it)
    {   
        // Find the smallest element in the range [it, vec.end()).
        auto min_item = std::min_element(it, vec.end()); 
        // Swap the smallest element with the first element in the range [it, vec.end()).
        std::iter_swap(min_item, it);                   
    }
}

const auto seed = std::random_device{}();

constexpr int         MIN_LIMIT{-50};
constexpr int         MAX_LIMIT{50};
constexpr std::size_t SIZE{25};

const auto rnd = [engine = std::mt19937{seed},
                  distr  = std::uniform_int_distribution{MIN_LIMIT, MAX_LIMIT}]() mutable -> int
{
    return distr(engine);
};

auto main() -> int
{
    std::vector<int> vec(SIZE);
    std::generate(vec.begin(), vec.end(), rnd);
    
    for (const auto& item : vec)
    {
        std::cout << item << ' ';
    }

    const auto start = std::chrono::steady_clock::now();
    selection_sort(vec);
    const auto end = std::chrono::steady_clock::now();

    std::cout << '\n';
    for (const auto& item : vec)
    {
        std::cout << item << ' ';
    }

    const std::chrono::duration<double, std::nano> elapsed{end - start};
    std::cout << "\nElapsed time: " << elapsed.count() << "ns\n";
}