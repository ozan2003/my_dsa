#include <deque>
#include <generator>
#include <ranges>

template <std::ranges::range R>
auto sliding_window(R&& rng, const std::size_t n)
    -> std::generator<std::deque<std::ranges::range_reference_t<R>>>
{
    if (n == 0 || std::ranges::empty(rng) || n > std::ranges::size(rng))
    {
        co_return; // Empty generator (no windows to yield).
    }

    // Window with the first n elements.
    std::deque<std::ranges::range_reference_t<R>> window(rng.cbegin(),
                                               std::next(rng.cbegin(), n));
    // Iterate over until the end hits the range's end.
    for (auto it = std::next(rng.cbegin(), n); it != rng.cend();
         std::advance(it, 1))
    {
        co_yield window;
        // Move the window one step forward.
        window.pop_front();    // Pop the front element.
        window.push_back(*it); // Append the next element.
    }
    co_yield window; // Yield the last window.
}
