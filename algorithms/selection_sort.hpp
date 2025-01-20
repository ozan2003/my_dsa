#include <algorithm> // std::min_element, std::iter_swap
#include <chrono>    // std::chrono::steady_clock, std::chrono::duration
#include <cmath>     // std::log10
#include <concepts>  // std::totally_ordered, std::predicate
#include <iostream>  // std::cout
#include <vector>    // std::vector

/**
 * Sorts the elements in-place using the selection sort algorithm.
 * Note that since it has O(n^2) time complexity, it's not suitable for large
 * containers.
 *
 * @param vec The vector to be sorted.
 */
template <std::totally_ordered T, std::predicate<T, T> Pred = std::less<T>>
void selection_sort(std::vector<T>& vec, Pred&& pred = Pred{})
{
    // There's no need to look at the last element since the last comparison
    // always with itself.
    for (auto it = vec.begin(); it < vec.end() - 1; ++it)
    {
        // Find the smallest element in the range [it++, vec.end()).
        auto min_item = std::min_element(it, vec.end(), pred);
        // Swap the smallest element with the first element in the range [it++,
        // vec.end()) through iterators.
        std::iter_swap(min_item, it);
    }
}
