using System;
using System.Linq;

namespace Sandbox;

public static class BitExtensions
{
    /// <summary>
    /// Returns the bits of an integer as an enumerable sequence.
    /// </summary>
    /// <param name="num"> The integer to convert to bits.</param>
    /// <returns>An enumerable sequence of bits.</returns>
    public static IEnumerable<int> Bits(this int num)
    {
        for (int i = 0; i < 32; ++i)
        {
            yield return (num & (1 << i)) != 0 ? 1 : 0;
        }
    }
}

public class Algorithm
{
    /// <summary>
    /// Finds the missing number in an array of integers from 0 to n.
    /// </summary>
    /// <param name="nums">Array of integers with one missing number from the range [0..n].</param>
    /// <param name="n">The upper bound of the range (inclusive).</param>
    /// <returns>The missing number in the range [0..n].</returns>
    public static int FindMissingNumber(int[] nums, int n)
    {
        int missingNum = 0;

        // Check each bit position (0 to log2(n))
        // 32 bits is enough for int
        for (int bit = 0; bit < 32; ++bit)
        {
            int expectedOnes = 0;
            int actualOnes = 0;

            // Count expected 1s at this bit position in complete range [0..n]
            foreach (int i in Enumerable.Range(0, n + 1))
            {
                if (i.Bits().ElementAt(bit) == 1)
                {
                    ++expectedOnes;
                }
            }

            // Count actual 1s at this bit position in given array
            foreach (int num in nums)
            {
                if (num.Bits().ElementAt(bit) == 1)
                {
                    ++actualOnes;
                }
            }

            // If we have fewer 1s than expected, missing number has 1 at this bit
            if (expectedOnes > actualOnes)
            {
                missingNum |= 1 << bit;
            }
        }

        return missingNum;
    }

    // Helper method to show the algorithm step by step
    public static void DemonstrateAlgorithm(int[] nums, int n)
    {
        Console.WriteLine("\n=== Step-by-step demonstration ===");
        Console.WriteLine($"Array: {string.Join(", ", nums)}");
        Console.WriteLine($"Range: [0..={n}]");

        int missing = 0;
        int max_set_bit = (int)Math.Log2(n) + 1;

        for (int bit = 0; bit < max_set_bit; ++bit)
        {
            int expectedOnes = 0;
            int actualOnes = 0;

            Console.Write($"\nBit {bit}:");

            // Expected count
            Console.Write("\n  Expected pattern: ");
            for (int i = 0; i <= n; ++i)
            {
                int bitValue = i.Bits().ElementAt(bit);
                Console.Write(bitValue);

                if (bitValue == 1)
                {
                    ++expectedOnes;
                }
            }
            Console.Write($" (ones: {expectedOnes})");

            // Actual count
            Console.Write("\n  Actual pattern:   ");
            for (int i = 0; i <= n; ++i)
            {
                bool has_found = false;
                foreach (int num in nums)
                {
                    if (num == i)
                    {
                        has_found = true;
                        break;
                    }
                }

                if (has_found)
                {
                    int bitValue = (i >> bit) & 1;
                    Console.Write(bitValue);
                    if (bitValue == 1)
                    {
                        ++actualOnes;
                    }
                }
                else
                {
                    Console.Write("?"); // missing number
                }
            }
            Console.Write($" (ones: {actualOnes})");

            if (expectedOnes > actualOnes)
            {
                missing |= 1 << bit;
                Console.Write($" -> Missing number has 1 at bit {bit}");
            }
            else
            {
                Console.Write($" -> Missing number has 0 at bit {bit}");
            }
        }

        Console.WriteLine($"\n\nMissing number in binary: {Convert.ToString(missing, 2)}");
        Console.WriteLine($"Missing number in decimal: {missing}");
    }
}
