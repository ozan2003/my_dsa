#pragma once

#include <algorithm>
#include <string_view>
#include <vector>

/**
 * @brief Finds the Levenshtein distance between two strings.
 *
 * The Levenshtein distance between two strings is the minimum number of
 * single-character edits (insertions, deletions, or substitutions) required to
 * change one string into the other.
 * @param s1 The first string.
 * @param s2 The second string.
 * @return The Levenshtein distance between the two strings.
 */
std::size_t levenshtein_dist(std::string_view s1, std::string_view s2)
{
    const std::size_t m{s1.length()};
    const std::size_t n{s2.length()};

    // Special cases.
    if (m == 0)
    {
        return n;
    }
    else if (n == 0)
    {
        return m;
    }

    std::vector d(m + 1, std::vector<std::size_t>(n + 1));

    for (std::size_t i{}; i <= m; ++i)
    {
        d[i][0] = i;
    }

    for (std::size_t j{}; j <= n; ++j)
    {
        d[0][j] = j;
    }

    for (std::size_t j{1}; j <= n; ++j)
    {
        for (std::size_t i{1}; i <= m; ++i)
        {
            const std::size_t substitution_cost{s1[i - 1] == s2[j - 1] ? 0 : 1};

            d[i][j] = std::min({d[i - 1][j] + 1,
                                d[i][j - 1] + 1,
                                d[i - 1][j - 1] + substitution_cost});
        }
    }

    return d[m][n];
}
