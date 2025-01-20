#include <cctype>   // std::isdigit
#include <cmath>    // std::pow
#include <format>   // std::format
#include <iostream> // std::cout, std::cerr
#include <ranges>   // std::views::split, std::views::transform
#include <stack>    // std::stack
#include <string>   // std::string

// Check if the character is an operator.
constexpr bool is_operator(const char ch) noexcept
{
    return ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == '^';
}

// This function evaluates Reverse Polish Notation (RPN).
// For more info:
// https://aquarchitect.github.io/swift-algorithm-club/Shunting%20Yard/
double postfix_eval(const std::string& postfix)
{
    std::stack<double> nums{};

    // Read the postfix token by token.
    for (const auto& token : std::views::split(postfix, ' ') |
                                 std::views::transform(
                                     [](auto&& r)
                                     {
                                         return std::string(r.begin(), r.end());
                                     }))
    {
        // First character of the token.
        // This'll be used to determine if the token is a number or an operator.
        const char ch = token.front();

        // If the token starts with a digit or a minus sign (indicating
        // negative number)...
        if (std::isdigit(ch) || (ch == '-' && token.size() > 1))
        {
            // ... push the (whole) number onto the stack.
            nums.push(std::stod(token));
        }
        // If the token is an operator...
        else if (is_operator(ch) && nums.size() >= 2)
        {
            // ... pop and store the top two elements from the stack.
            const auto second = nums.top();
            nums.pop();

            const auto first = nums.top();
            nums.pop();

            // Perform the operation and push the result back onto the stack.
            switch (ch)
            {
                case '+':
                {
                    nums.push(first + second);
                    break;
                }
                case '-':
                {
                    nums.push(first - second);
                    break;
                }
                case '*':
                {
                    nums.push(first * second);
                    break;
                }
                case '/':
                {
                    // Don't allow division by zero.
                    if (second == 0.0)
                    {
                        throw std::invalid_argument("Division by zero.");
                    }
                    nums.push(first / second);
                    break;
                }
                case '^':
                {
                    nums.push(std::pow(first, second));
                    break;
                }
                default:
                    break;
            }
        }
        else
        {
            throw std::invalid_argument(
                std::format("Unknown character '{}'. Check your input.",
                            token.front()));
        }
    }
    // The result is the only element left on the stack.
    return nums.empty() ? 0.0 : nums.top();
}
