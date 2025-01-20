#include <bit>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <string>

/**
 * @brief Find the prime factors of a number using Pollard's rho algorithm
 * repeatedly.
 * @param N The starting number.
 * @return A map of prime factors and their frequencies.
 *
 * @warning Since the algorithm is probabilistic, it may not always return the
 * correct factors or may not factorize the number or some factors at all.
 */
std::map<std::int64_t, std::size_t> pollards_rho(std::int64_t N)
{
    std::map<std::int64_t, std::size_t> factors{};
    if (N == 0 || N == 1)
    {
        return factors;
    }

    if (N < 0)
    {
        ++factors[-1];
        N = -N;
    }

    // If n is even, add the count of 2 to the factors.
    if (N % 2 == 0)
    {
        factors[2] += std::countr_zero(static_cast<std::uint64_t>(N));
        N >>= factors.at(2); // n /= 2^k

        if (N == 1)
        {
            return factors;
        }
    }

    // Select an x_0 uniformly at random from [2, n - 1].
    // x_0 is chosen as 2 for simplicity.
    //
    // Floyd's cycle-finding algorithm.
    // x => x_i
    // y => x_i+1
    std::int64_t x{2}, y{x}, d{1};
    // f(x_i+1) = x_i^2 + 1 mod n
    auto f = [N](const std::int64_t num) noexcept
    {
        return (num * num + 1) % N;
    };

    // If we obtain a factor greater than 1, we are done.
    while (d == 1)
    {
        x = f(x);
        y = f(f(y));
        d = std::gcd(std::abs(x - y), N);
    }

    /**
     * if (d == N)
     * {
     *     return std::nullopt;
     * }
     * else
     * {
     *     return d;
     * }
     */
    // The algorithm normally returns either a non-trivial factor d or failure,
    // but we need to find all prime(?) factors.

    if (d == N)
    {
        ++factors[N];
    }
    else
    {
        // Look for other factors.
        for (const auto& [factor, freq] : pollards_rho(d))
        {
            factors[factor] += freq;
        }

        for (const auto& [factor, freq] : pollards_rho(N / d))
        {
            factors[factor] += freq;
        }
    }
    return factors;
}

int main(int argc, char* argv[])
{
    const auto arg     = argc == 2 ? std::stoll(argv[1]) : 0;
    const auto factors = pollards_rho(arg);
    /*for (const auto& factor : factors)
    {
        std::cout << factor << '\n';
    }*/
    for (const auto& [factor, freq] : factors)
    {
        std::cout << factor << ':' << freq << '\n';
    }
}