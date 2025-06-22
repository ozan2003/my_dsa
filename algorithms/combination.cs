using System;
using System.Diagnostics;

namespace Sandbox;

public class Algorithm
{
    // Calculate C(n, k) using dynamic programming.
    static long combination_dp(long n, long k)
    {
        if (n < 0 || k < 0)
        {
            throw new ArgumentException("n and k must be non-negative");
        }
        else if (n < k)
        {
            throw new ArgumentException("n must be greater than or equal to k");
        }

        if (k > n / 2)
        {
            k = n - k;
        }

        long[,] dp = new long[n + 1, k + 1];

        for (long i = 0; i <= n; ++i)
        {
            dp[i, 0] = 1; // C(i,0) = 1 for all i
            for (long j = 1; j <= Math.Min(i, k); ++j)
            {
                dp[i, j] = dp[i - 1, j - 1] + dp[i - 1, j];
            }
        }

        return dp[n, k];
    }
}
