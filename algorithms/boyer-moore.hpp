#include <algorithm>
#include <concepts>
#include <optional>
#include <vector>

// Implementation of the Boyer-Moore majority vote algorithm.
// https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm
//
// Returns an arbitrary majority element if it exists, otherwise returns
// std::nullopt.
//
// Given an sequence of `n` elements, the majority element is the element that
// occurs more than `n/2` times.
template <typename T>
    requires std::equality_comparable<T> && std::assignable_from<T&, T> &&
             std::default_initializable<T>
constexpr std::optional<T> boyer_moore(const std::vector<T>& seq) noexcept
{
    std::size_t counter{};
    T           curr_candidate{}; // Remembered item.

    for (const T& x : seq)
    {
        if (counter == 0)
        {
            curr_candidate = x;
            counter        = 1;
        }
        else if (curr_candidate == x)
        {
            ++counter;
        }
        else
        {
            --counter;
        }
    }

    // Second pass to validate the majority item.
    counter = std::ranges::count(seq, curr_candidate);
    if (counter > seq.size() / 2)
    {
        return curr_candidate;
    }
    else
    {
        return std::nullopt;
    }
}