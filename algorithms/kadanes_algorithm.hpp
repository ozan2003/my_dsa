#pragma once

#include <algorithm>
#include <limits>
#include <ranges>
#include <type_traits>

// Kadane's algorithm.
template <std::ranges::range R, typename T = std::ranges::range_value_t<R>>
    requires std::is_arithmetic_v<T>
T max_subarray_sum(R&& rng) // Use universal reference for std::ranges::range's
                            // incompatible with const, like std::views::filter.
{
    T best_sum = std::numeric_limits<T>::min();

    for (T current_sum{}; const auto& value : rng)
    {
        // Accumulate the numbers.
        current_sum = std::max(value, current_sum + value);
        best_sum    = std::max(best_sum, current_sum); // Take the peak sum.
    }
    return best_sum;
}
