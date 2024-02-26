#include "fmt/ranges.h"

#include <algorithm> // std::min_element, std::iter_swap
#include <chrono>    // std::chrono::steady_clock, std::chrono::duration
#include <vector>    // std::vector
#include <concepts>  // std::convertible_to

template <typename T>
concept Comparable = requires(T a, T b) {
    {
        a < b
    } -> std::convertible_to<bool>;
};

/**
 * Sorts the elements in-place using the selection sort algorithm.
 * Note that since it has O(n^2) time complexity, it's not suitable for large
 * containers.
 *
 * @param vec The vector to be sorted.
 */
template <Comparable T>
void selection_sort(std::vector<T>& vec)
{
    // There's no need to look at the last element since the last comparison
    // always with itself.
    for (auto it = vec.begin(); it < vec.end() - 1; ++it)
    {
        // Find the smallest element in the range [it++, vec.end()).
        auto min_item = std::min_element(it, vec.end());
        // Swap the smallest element with the first element in the range [it++, vec.end())
        // through iterators.
        std::iter_swap(min_item, it);
    }
}

namespace chr = std::chrono;

int main()
{
    constexpr std::size_t SIZE{15}; // Size of the vector.

    std::vector vec{8, 5, 6, 3, 2, 4, 7};

    fmt::println("Before selection sort: {}", vec);

    // Time the function.
    const auto start = chr::steady_clock::now();
    selection_sort(vec);
    const auto end = chr::steady_clock::now();

    fmt::println("After selection sort: {}", vec);

    // Print the elapsed time.
    const chr::duration<double, std::nano> elapsed{end - start};
    fmt::print("Elapsed time: {:.4f}ns.\n", elapsed.count());
}