#include "Heapsort.hpp"

#include <chrono>
#include <iostream>
#include <random>
#include <vector>

constexpr int MIN{100};
constexpr int MAX{100'000};
constexpr int SIZE{10'000};

namespace chr = std::chrono;

const auto seed = std::random_device{}();

int main()
{
    const auto rnd = [engine = std::mt19937{seed}, dist = std::uniform_int_distribution{MIN, MAX}]() mutable -> int
    {
        return dist(engine);
    };

    try
    {
        std::vector<int> items(SIZE);
        std::generate(items.begin(), items.end(), rnd);

        const auto start = chr::system_clock::now();
        heap_sort(items);
        const auto end = chr::system_clock::now();

        const chr::duration<float, std::milli> elapsed{end - start};

        for (const auto& item : items)
        {
            std::cout << item << ' ';
        }
        std::cout << "\nTook " << elapsed.count() << "ms.\n";
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << '\n';
    }
}