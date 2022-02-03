#include <iostream>
#include <optional>
#include <vector>

#define CAPACITY 10000

struct Node
{
    Node() = default;
    Node(int key, int value, Node* next) : _key(key), _value(value), _next(next) {}

    int _key    = 0;
    int _value  = 0;
    Node* _next = nullptr;
};

class LinkedList
{
public:
    LinkedList() {_head = new Node;}
    ~LinkedList();
    void pushFront(int key, int value);
    int getFront();
    void push(int key, int value);
    std::optional<int> seekAndGet(int key);
    std::optional<int> deleteNode(int key);
    size_t getSize() const {return _size;}
    bool empty() const {return _size == 0;}

private:
    Node* _head       = nullptr;
    std::size_t _size = 0;
};

LinkedList::~LinkedList()
{
    Node* temp = _head;
    while(temp != nullptr)
    {
        Node* toDelete = temp;
        temp = temp->_next;
        delete toDelete;
    }

}

void LinkedList::pushFront(int key, int value)
{
    Node* newNode = new Node(key, value, _head->_next);
    _head->_next = newNode;
    ++_size;
}

int LinkedList::getFront()
{
    return _head->_next->_value;
}

std::optional<int> LinkedList::seekAndGet(int key)
{
    Node* current = _head->_next;
    while (current != nullptr && current->_key != key)
    {
        current = current->_next;
    }

    if (current != nullptr)
    {
        return {current->_value};
    }
    return {};
}

std::optional<int> LinkedList::deleteNode(int key)
{
    Node* current = new Node;
    Node* previous = _head;

    current = _head->_next;

    while (current != nullptr && current->_key != key)
    {
        previous = current;
        current = current->_next;
    }

    if (current != nullptr)
    {
        int val = current->_value;
        previous->_next = current->_next;
        delete current;
        --_size;
        return {val};
    }
    delete current;
    return {};
}

void LinkedList::push(int key, int value)
{
    Node* current = _head->_next;
    while (current != nullptr && current->_key != key)
    {
        current = current->_next;
    }

    if (current != nullptr)
    {
        current->_value = value;
    }
    else
    {
        pushFront(key, value);
    }
}

class HashTable
{
public:
    HashTable() {_data = new LinkedList[CAPACITY];}
    ~HashTable() {delete [] _data;}

    void put(int key, int value);
    std::optional<int> get(int key);
    std::optional<int> deleteKey(int key);

private:
    int hash(int key);

private:
    LinkedList* _data = nullptr;
    std::size_t _size = 0;
};

void HashTable::put(int key, int value)
{
    int index = hash(key);
    if (_data[index].empty())
    {
        _data[index].pushFront(key, value);
    }
    else
    {
        _data[index].push(key, value);
    }
}

std::optional<int> HashTable::get(int key)
{
    int index = hash(key);
    if (!_data[index].empty())
    {
        return {_data[index].seekAndGet(key)};
    }
    else
    {
        return {};
    }
}

std::optional<int> HashTable::deleteKey(int key)
{
    int index = hash(key);
    if (!_data[index].empty())
    {
        return {_data[index].deleteNode(key)};
    }
    else
    {
        return {};
    }
}

int HashTable::hash(int key)
{
    return key % CAPACITY;
}


int main()
{
    int numCommands = 0, x = 0, y = 0;
    HashTable t;

    std::cin >> numCommands;
    std::string command;

    for (int i = 0; i < numCommands; ++i)
    {
        std::cin >> command;
        if(command == "put")
        {
            std::cin >> x >> y;
            t.put(x, y);
        }
        else if (command == "get")
        {
            std::cin >> x;
            std::optional<int> res = t.get(x);
            if (res.has_value())
            {
                std::cout << res.value() << '\n';
            }
            else
            {
                std::cout << "None\n";
            }
        }
        else if(command == "delete")
        {
            std::cin >> x;
            std::optional<int> res = t.deleteKey(x);
            if (res.has_value())
            {
                std::cout << res.value() << '\n';
            }
            else
            {
                std::cout << "None\n";
            }
        }

    }

    return 0;
}
