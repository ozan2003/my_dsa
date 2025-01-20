#include <ranges>
#include <vector>

/**
 * @brief Perform binary search. The range must be sorted.
 * @tparam Rng The type of the range.
 * @param rng The range to be searched.
 * @param target The number to be searched on range.
 * @return The iterator to the found element, one past the end if not found.
 */
template <std::ranges::range Rng>
std::vector<int>::const_iterator bin_search(
    const Rng&                             rng,
    const std::ranges::range_value_t<Rng>& target)
{
    auto front = rng.begin();   // The first element.
    auto rear  = rng.end() - 1; // The last element.

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
            return mid;
        }
    }
    // Indicate nothing is found by returning non-valid iterator.
    return rng.end();
}
