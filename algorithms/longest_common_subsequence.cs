using System;
using System.Diagnostics;

namespace Sandbox;

public class Algorithm
{
    /// <summary>
    /// Finds the longest common subsequence (LCS) of two strings.
    /// 
    /// The LCS is the longest sequence that can be derived from both strings
    /// without changing the order of characters.
    /// <param name="first">The first string.</param>
    /// <param name="second">The second string.</param>
    /// <returns> A tuple containing the longest common subsequence and its length.</returns>
    public static (string subsequence, int length) LongestCommonSubsequence(
        ReadOnlySpan<char> first,
        ReadOnlySpan<char> second
    )
    {
        int m = first.Length;
        int n = second.Length;

        // Create the DP table filled with zeros
        int[,] dp = new int[m + 1, n + 1];

        // Fill the dp table
        for (int i = 1; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                // If characters match, extend the subsequence
                if (first[i - 1] == second[j - 1])
                {
                    dp[i, j] = dp[i - 1, j - 1] + 1;
                }
                // If characters don't match, take the best from previous results
                else
                {
                    dp[i, j] = Math.Max(dp[i - 1, j], dp[i, j - 1]);
                }
            }
        }

        // Reconstruct subsequence from dp.
        string subsequence = ReconstructSubsequence(first, second, dp);

        return (subsequence, dp[m, n]);
    }

    // Helper method to reconstruct the actual subsequence
    private static string ReconstructSubsequence(
        ReadOnlySpan<char> first,
        ReadOnlySpan<char> second,
        int[,] dp
    )
    {
        // Start from the bottom right of the dp table
        int i = first.Length;
        int j = second.Length;

        char[] result = new char[dp[i, j]];
        int index = dp[i, j] - 1;

        // Traverse the table from bottom right to top left
        while (i > 0 && j > 0)
        {
            // If characters match, add to result and move up-left
            if (first[i - 1] == second[j - 1])
            {
                result[index] = first[i - 1]; // Add character to end.
                --index;

                // Move diagonally up-left.
                --i;
                --j;
            }
            // If not, move in the direction of the larger value.
            else if (dp[i - 1, j] > dp[i, j - 1])
            {
                --i; // To up.
            }
            else
            {
                --j; // To left.
            }
        }

        return new(result);
    }
}
