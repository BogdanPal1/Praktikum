#include <iostream>
#include <stack>
#include <cmath>

bool isNumber(const std::string& str)
{
    return str.find_first_of("0123456789") != std::string::npos;
}

int main()
{
    std::stack<int> numStack;
    std::string input;

    while (std::cin >> input)
    {
        if (isNumber(input))
        {
            numStack.push(std::stoi(input));
        }
        else if(input == "+")
        {
            int a = numStack.top();
            numStack.pop();
            int b = numStack.top();
            numStack.pop();
            numStack.push(a + b);
        }
        else if(input == "-")
        {
            int a = numStack.top();
            numStack.pop();
            int b = numStack.top();
            numStack.pop();
            numStack.push(b - a);
        }
        else if(input == "*")
        {
            int a = numStack.top();
            numStack.pop();
            int b = numStack.top();
            numStack.pop();
            numStack.push(a * b);
        }
        else if(input == "/")
        {
            int a = numStack.top();
            numStack.pop();
            int b = numStack.top();
            numStack.pop();
            numStack.push(std::floor(b / static_cast<double>(a)));
        }
    }
    std::cout << numStack.top() << '\n';
    return 0;
}
