#include <iostream>
#include <vector>

class Deque
{
public:
    explicit Deque(int capacity);
    void push_back(int value);
    void push_front(int value);
    void pop_back();
    void pop_front();
private:
    std::vector<int> _data;
    int _front;
    int _back;
    int _size;
    int _capacity;

};

Deque::Deque(int capacity)
{
    _size = 0;
    _capacity = capacity;
    _front = _back = -1;
    _data.resize(_capacity);
}

void Deque::push_back(int value)
{
    if (_size == _capacity)
    {
        std::cout << "error\n";
        return;
    }

    if (_back == -1)
    {
        ++_front;
        ++_back;
    }
    else if (_back == _capacity - 1)
    {
        _back = 0;
    }
    else
    {
        ++_back;
    }
    _data[_back] = value;
    ++_size;
}

void Deque::push_front(int value)
{
    if (_size == _capacity)
    {
        std::cout << "error\n";
        return;
    }

    if (_front == -1)
    {
        ++_front;
        ++_back;
    }
    else if(_front == 0)
    {
        _front = _capacity - 1;
    }
    else
    {
        --_front;
    }
    _data[_front] = value;
    ++_size;
}

void Deque::pop_back()
{
    if (_size == 0)
    {
        std::cout << "error\n";
        return;
    }

    std::cout << _data[_back] << '\n';

    if (_front == _back)
    {
        _front = -1;
        _back = -1;
        --_size;
    }
    else if (_back == 0)
    {
        _back = _capacity - 1;
        --_size;
    }
    else
    {
        --_back;
        --_size;
    }
}

void Deque::pop_front()
{
    if (_size == 0)
    {
        std::cout << "error\n";
        return;
    }

    std::cout << _data[_front] << '\n';

    if (_front == _back)
    {
        _front = -1;
        _back = -1;
        --_size;
    }
    else
    {
        if (_front == _capacity - 1)
        {
            _front = 0;
            --_size;
        }
        else
        {
            ++_front;
            --_size;
        }
    }
}

int main()
{
    std::string command;
    int numCommands = 0, x = 0, dequeCapacity = 0;

    std::cin >> numCommands;
    std::cin >> dequeCapacity;

    Deque d(dequeCapacity);

    for (int i = 0; i < numCommands; ++i)
    {
        std::cin >> command;
        if (command == "pop_back")
        {
            d.pop_back();
        }
        else if(command == "pop_front")
        {
            d.pop_front();
        }
        else if(command == "push_back")
        {
            std::cin >> x;
            d.push_back(x);
        }
        else if(command == "push_front")
        {
            std::cin >> x;
            d.push_front(x);
        }
    }
    return 0;
}
