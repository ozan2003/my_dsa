#include <algorithm>
#include <concepts>
#include <vector>

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
