#pragma once

/* The shunting yard algorithm is used for
 * converting infix expression to postfix.

 * For more info:
 https://aquarchitect.github.io/swift-algorithm-club/Shunting%20Yard/
 */
#include <algorithm> // std::count
#include <cctype>    // std::isdigit
#include <format>    // std::format
#include <stack>     // std::stack
#include <stdexcept> // std::invalid_argument
#include <string>    // std::string

// Check if the character is an operator.
constexpr bool is_operator(const char ch) noexcept
{
    return ch == '^' || ch == '*' || ch == '/' || ch == '+' || ch == '-';
}

// Assign the operators a number according to their predecence.
constexpr int precedence_of(const char op) noexcept
{
    // '^' > '*' and '/' > '+' and '-'
    if (op == '^')
    {
        return 3;
    }
    else if (op == '*' || op == '/')
    {
        return 2;
    }
    else if (op == '+' || op == '-')
    {
        return 1;
    }
    return 0;
}

std::string to_postfix(const std::string& infix)
{
    // Check for mismatching opening and closing parentheses.
    if (std::count(infix.begin(), infix.end(), '(') !=
        std::count(infix.begin(), infix.end(), ')'))
    {
        throw std::invalid_argument{
            "Mismatching parentheses. Check your input.\n"};
    }

    std::stack<char> operators{};
    std::string      postfix{};
    postfix.reserve(infix.length());

    // If the character is...
    for (auto it = infix.begin(); it != infix.end(); ++it)
    {
        // ... a digit, add it to the postfix expression.
        if (isdigit(*it))
        {
            // If the number has more than one digit, add all of them to the
            // string.
            std::string num_str{};
            while (it < infix.end() && isdigit(*it))
            {
                num_str += *it;
                ++it;
            }
            --it; // Decrement i because it is incremented one more time in the
                  // for loop.

            postfix += num_str;
            postfix += ' ';
        }
        // ... a space, skip it.
        else if (*it == ' ')
        {
            continue;
        }
        // ... an operator, pop operators from the stack and add them to the
        // postfix expression until an operator with lower precedence is
        // encountered.
        else if (is_operator(*it))
        {
            while (!operators.empty() &&
                   precedence_of(operators.top()) >= precedence_of(*it))
            {
                postfix += operators.top();
                postfix += ' ';
                operators.pop();
            }
            // The current operator is pushed onto the stack.
            operators.push(*it);
        }
        // ... an opening parentheses, push it onto the stack.
        // (This is done because the operators inside the parentheses have
        // higher precedence than the operators outside.)
        else if (*it == '(')
        {
            operators.push(*it);
        }
        // ... a closing parentheses, pop operators from the stack and add them
        // to the postfix expression until an opening parentheses is encountered
        // (also check if the stack is empty).
        else if (*it == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                postfix += operators.top();
                postfix += ' ';
                operators.pop();
            }
            operators.pop(); // Open parenthesis is also popped.
        }
        else
        {
            throw std::invalid_argument{
                std::format("Unknown character '{}' in the input.", *it)};
        }
    }

    // Pop the remaining operators from the stack and add them to the postfix
    // expression.
    while (!operators.empty())
    {
        postfix += operators.top();
        postfix += ' ';
        operators.pop();
    }

    return postfix;
}
