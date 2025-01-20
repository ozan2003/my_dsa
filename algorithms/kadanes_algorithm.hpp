#include <iostream>
#include <limits>
#include <type_traits>
#include <vector>

// Kadane's algorithm.
template <typename T>
    requires std::is_arithmetic_v<T> || std::is_floating_point_v<T>
T max_subarray_sum(const std::vector<T>& arr)
{
    auto best_sum = std::numeric_limits<T>::min();

    for (T current_sum{}; const auto& value : arr)
    {
        // Accumulate the numbers.
        current_sum = std::max(value, current_sum + value);
        best_sum    = std::max(best_sum, current_sum); // Take the peak sum.
    }
    return best_sum;
}
