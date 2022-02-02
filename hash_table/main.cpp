#include <iostream>
#include <optional>
#include <vector>

#define CAPACITY 10000

struct Node
{
    Node() = default;
    Node(int value, Node* next) : _value(value), _next(next) {}
    int _value = 0;
    Node* _next = nullptr;
};

class LinkedList
{
public:
    LinkedList() {_head = new Node;}
    ~LinkedList();
    void pushFront(int value);
    int getFront();
    size_t getSize() const {return _size;}
    bool empty() const {return _size == 0;}
private:
    Node* _head = nullptr;
    std::size_t _size = 0;
};

LinkedList::~LinkedList()
{
    Node* temp = _head;
    while(_head != nullptr)
    {
        temp = _head->_next;
        delete _head;
        _head = temp;
    }
}

void LinkedList::pushFront(int value)
{
    Node* newNode = new Node(value, _head);
    _head = newNode;
    ++_size;
}

int LinkedList::getFront()
{
    return _head->_value;
}

class HashTable
{
public:
    HashTable() {_data = new LinkedList[CAPACITY];}
    ~HashTable() {delete [] _data;}

    void put(int key, int value);
    std::optional<int> get(int key);
    std::optional<int> deleteKey(int key){}
private:
    int hash(int key);
private:
    LinkedList* _data = nullptr;
    std::size_t _size = 0;
};

void HashTable::put(int key, int value)
{
    int index = hash(key);
    _data[index].pushFront(value);
}

std::optional<int> HashTable::get(int key)
{
    int index = hash(key);
    if (!_data[index].empty())
    {
        int i = _data[index].getFront();
        return {i};
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
        if (command == "get")
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
            t.deleteKey(x);
        }
        else if(command == "put")
        {
            std::cin >> x >> y;
            t.put(x, y);
        }
    }

    return 0;
}








