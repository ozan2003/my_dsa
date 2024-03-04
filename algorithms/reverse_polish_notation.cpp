#include <cctype>   // std::isdigit
#include <cmath>    // std::pow
#include <format>   // std::format
#include <iostream> // std::cout, std::cerr
#include <ranges>   // std::views::split
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
    for (const auto& token : std::views::split(postfix, ' '))
    {
        // Convert the token to a piece of string.
        const std::string token_piece(token.begin(), token.end());

        // First character of the token.
        // This'll be used to check if the token is a number or an operator.
        const char ch = *token_piece.begin();

        // If the token starts with a digit or a minus sign (indicating
        // negative number)...
        if (std::isdigit(ch) || (ch == '-' && token_piece.size() > 1))
        {
            // ... push the (whole) number onto the stack.
            nums.push(std::stod(token_piece));
        }
        // If the token is an operator...
        else if (is_operator(ch))
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
                            token_piece));
        }
    }
    // The result is the only element left on the stack.
    return nums.empty() ? 0.0 : nums.top();
}

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        std::cout << postfix_eval(argv[1]) << '\n';
    }
    else
    {
        std::cerr << "No argument provided.\n";
    }
}