#include <iostream>

struct Node
{
    Node(int value, Node* next, Node* prev) : _val(value), _next(next), _prev(prev){}
    int _val;
    Node* _next;
    Node* _prev;
};

class Deque
{
public:
    Deque() = default;
    explicit Deque(int capacity);
    ~Deque();
    void push_back(int value);
    void push_front(int value);
    void pop_back();
    void pop_front();
private:
    Node* _head;
    Node* _tail;
    int _capacity;
    int _size;
};

Deque::Deque(int capacity)
{
    _capacity = capacity;
    _tail = _head = nullptr;
    _size = 0;
}

Deque::~Deque()
{
    _capacity = 0;

    if (_size != 0)
    {
        while (_head != nullptr)
        {
            Node* temp = _head;
            _head = _head->_next;
            delete temp;
        }
    }
    _size = 0;
}

void Deque::push_back(int value)
{
    if (_size == _capacity)
    {
        std::cout << "error\n";
        return;
    }

    Node* newNode = new Node(value, nullptr, nullptr);
    if (_size == 0)
    {
        _head = _tail = newNode;
        ++_size;
    }
    else
    {
        _tail->_next = newNode;
        newNode->_prev = _tail;
        _tail = newNode;
        ++_size;
    }
}

void Deque::push_front(int value)
{
    if (_size == _capacity)
    {
        std::cout << "error\n";
        return;
    }

    Node* newNode = new Node(value, nullptr, nullptr);
    if (_size == 0)
    {
        _tail = _head = newNode;
        ++_size;
    }
    else
    {
        _head->_prev = newNode;
        newNode->_next = _head;
        _head = newNode;
        ++_size;
    }
}

void Deque::pop_back()
{
    if (_size == 0)
    {
        std::cout << "error\n";
        return;
    }

    std::cout << _tail->_val << '\n';
    Node* temp = _tail;
    _tail = _tail->_prev;
    delete temp;
    --_size;
}

void Deque::pop_front()
{
    if (_size == 0)
    {
        std::cout << "error\n";
        return;
    }

    std::cout << _head->_val << '\n';
    Node* temp = _head;
    _head = _head->_next;
    delete temp;
    --_size;
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
