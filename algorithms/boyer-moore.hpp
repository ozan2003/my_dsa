#pragma once

#include <concepts>
#include <optional>
#include <vector>

/**
 * @brief Find the majority element in a sequence using Boyer-Moore majority
vote algorithm. [1]
 * [1]:
https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm
 * @param seq The sequence of elements.
 * @return Returns an arbitrary majority element if it exists, otherwise returns
std::nullopt.
 */
template <typename T>
    requires std::equality_comparable<T> && std::assignable_from<T&, T> &&
             std::default_initializable<T>
constexpr std::optional<T> boyer_moore(const std::vector<T>& seq) noexcept
{
    T curr_candidate{}; // Remembered item.

    // First pass: Find the majority candidate.
    for (std::size_t tally{}; const T& x : seq)
    {
        if (tally == 0)
        {
            curr_candidate = x;
            tally          = 1;
        }
        else if (curr_candidate == x)
        {
            ++tally;
        }
        else
        {
            --tally;
        }
    }

    // Second pass: Verify if the candidate is indeed the majority element.
    for (std::size_t majority_count{}; const T& x : seq)
    {
        if (x == curr_candidate)
        {
            ++majority_count;
            if (majority_count > seq.size() / 2)
            {
                return curr_candidate;
            }
        }
    }

    return std::nullopt;
}