#ifndef MONOTONICSTACK_HPP
#define MONOTONICSTACK_HPP

#include <concepts>
#include <functional>
#include <stack>
#include <type_traits>

// A monotonic stack is one in which the elements maintain their monotonicity.
// Their items comply with Comp. For instance, if Comp is std::less, stack items
// will decrease. If Comp is std::greater, the stack items increase. You can
// think of it as an ordered stack.
template <typename T,
          typename Container = std::deque<T>,
          typename Comp      = std::less<T>>
    requires std::predicate<Comp, const T&, const T&>
class MonotonicStack : public std::stack<T, Container>
{
public:
    using container_type  = Container;
    using value_type      = typename Container::value_type;
    using size_type       = typename Container::size_type;
    using reference       = typename Container::reference;
    using const_reference = typename Container::const_reference;

private:
    Comp comp{};

public:
    /**
     * @brief Adds an item to the stack.
     * @param val The item to add to the stack.
     */
    constexpr void push(const_reference val)
    {
        while (!this->empty() && !comp(val, this->top()))
        {
            // Pop until comp(val, top) is true.
            std::stack<value_type>::pop();
        }
        std::stack<value_type>::push(val);
    }

    /**
     * @brief Adds an item to the stack.
     * @param val The item to add to the stack.
     */
    constexpr void push(value_type&& val)
    {
        while (!this->empty() && !comp(val, this->top()))
        {
            // Pop until comp(val, top) is true.
            std::stack<value_type>::pop();
        }
        std::stack<value_type>::push(std::move(val));
    }

    /**
     * @brief Adds an item to the stack.
     * @param args The arguments to use to construct the item.
     * @return The item added to the stack.
     */
    template <typename... Args>
    constexpr decltype(auto) emplace(Args&&... args)
    {
        /*
         * In order to maintain the monotonicity of the stack, I create the
         * item twice.
         *
         * Once to compare with the top of the stack, and once to
         * emplace onto the stack.
         */
        const value_type val(std::forward<Args>(args)...);
        while (!this->empty() && !comp(val, this->top()))
        {
            // Pop until comp(val, top) is true.
            std::stack<value_type>::pop();
        }
        return std::stack<value_type>::emplace(std::forward<Args>(args)...);
    }
};
#endif // MONOTONICSTACK_HPP
