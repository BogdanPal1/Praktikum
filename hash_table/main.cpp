/*
 * ID 64880596
 * Спринт 4. Задача B "Хеш-таблица".
 * Палкин Богдан. Когорта 20.
 *
 * -- ПРИНЦИП РАБОТЫ --
 *
 * В данном задании необходимо реализовать хеш-таблицу со
 * следующими ограничениями:
 *
 *  - Нельзя использовать имеющиеся в языках программирования
 *  реализации хеш-таблиц.
 *  - Число хранимых в таблице ключей не превосходит 10^5.
 *  - Разрешать коллизии следует с помощью метода цепочек или
 *  с помощью открытой адресации.
 *  - Все операции должны выполняться за O(1) в среднем.
 *  - Поддерживать рехеширование и масштабирование хеш-таблицы не требуется.
 *  - Ключи и значения, id сотрудников и их зарплата, —– целые числа.
 *  - Поддерживать произвольные хешируемые типы не требуется.
 *
 * Для решения ипользовался встроенный вектор, хранящий в себе указатели на
 * связанные списки LLBucket. Связанные списки используются для разрешения
 * коллизий методом цепочек.
 *
 * -- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
 *
 * Доказательство корректности можно разделить на две части:
 *  1. Доказательство того, что реализация удовлетворяет требованиям из
 *  задания.
 *  2. Демонстрация работы программы, основанной на представленной
 *  реализации.
 *
 * Первую часть доказательства можно расписать по пунктам:
 *  1. В решении не используется имеющаяся в С++ реализаци хеш-таблицы
 *  unordered_map.
 *  2. Максимальный размер выделяемых ячеек для хранения ключей(_capacity)
 *  равен 10000.
 *  3. Для разрешения коллизий используется самописный связанный список
 *  в качестве корзины. Метод цепочек реализуется с использованием связанного
 *  списка.
 *  4. В среднем когда каждая корзина хранит в себе лишь один элемент
 *  опрерации выполняются за время О(1).
 *  5. Рехеширование и масштабирование не поддерживается.
 *  6. Поддержки произвольных типов нет.
 *
 * Вторая часть доказательства представлена на прилагаемых скриншотах.
 *
 * -- ВРЕМЕННАЯ СЛОЖНОСТЬ --
 *
 * В среднем, когда в корзинах хранится по одному элементу, сложность
 * доступа к элементу по ключу, а также удаления по ключу постоянна О(1).
 * Вставка нового элемента всегда выполняется за постоянное время, так
 * как она происходит в голову корзины.
 *
 * -- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
 *
 * Пространство для хранения хеш-таблицы состоит из пространства для хранения
 * указателей на головы корзин N, а также из пространства для хранения
 * конкретного элемента M.
 * Общая пространственная сложность равна О(N * M).
 */

#include <iostream>
#include <optional>
#include <vector>

struct Node
{
    Node() = default;
    Node(int key, int value, Node* next) : _key(key), _value(value), _next(next) {}

    int _key    = 0;
    int _value  = 0;
    Node* _next = nullptr;
};

class LLBucket
{
public:
    LLBucket() {_head = new Node;}
    ~LLBucket();
    void pushFront(int key, int value);
    int getFront();
    void push(int key, int value);
    bool empty() const {return _size == 0;}
    std::optional<int> seekAndGet(int key);
    std::optional<int> deleteNode(int key);

private:
    Node* _head       = nullptr;
    std::size_t _size = 0;
};

LLBucket::~LLBucket()
{
    Node* temp = _head;
    while(temp != nullptr)
    {
        Node* toDelete = temp;
        temp = temp->_next;
        delete toDelete;
    }
}

void LLBucket::pushFront(int key, int value)
{
    Node* newNode = new Node(key, value, _head->_next);
    _head->_next = newNode;
    ++_size;
}

int LLBucket::getFront()
{
    return _head->_next->_value;
}

std::optional<int> LLBucket::seekAndGet(int key)
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
    return std::nullopt;
}

std::optional<int> LLBucket::deleteNode(int key)
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
    return std::nullopt;
}

void LLBucket::push(int key, int value)
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
    HashTable() {_data = new LLBucket[_capacity];}
    ~HashTable() {delete [] _data;}

    void put(int key, int value);
    std::optional<int> get(int key);
    std::optional<int> deleteKey(int key);

private:
    int getIndex(int key);

private:
    LLBucket* _data             = nullptr;
    const std::size_t _capacity = 10000;
    std::size_t _size           = 0;
};

void HashTable::put(int key, int value)
{
    int index = getIndex(key);
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
    int index = getIndex(key);
    if (!_data[index].empty())
    {
        return {_data[index].seekAndGet(key)};
    }
    else
    {
        return std::nullopt;
    }
}

std::optional<int> HashTable::deleteKey(int key)
{
    int index = getIndex(key);
    if (!_data[index].empty())
    {
        return {_data[index].deleteNode(key)};
    }
    else
    {
        return std::nullopt;
    }
}

int HashTable::getIndex(int key)
{
    return key % _capacity;
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
