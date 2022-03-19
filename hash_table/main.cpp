/*
 * ID 64939419
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
 * Для решения ипользовался встроенный вектор, хранящий в себе двухсвязанные
 * списки std::list<std::pair<int,int>>. Связанные списки используются для 
 * разрешения коллизий методом цепочек.
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
 *  1. В решении не используется имеющаяся в С++ реализация хеш-таблицы
 *  unordered_map.
 *  2. Максимальный размер выделяемых ячеек для хранения ключей(_capacity)
 *  равен 10000.
 *  3. Для разрешения коллизий используется двухсвязанный список std::list
 *  в качестве корзины. Метод цепочек реализуется с использованием связанного
 *  списка.
 *  4. В среднем, когда каждая корзина хранит в себе лишь один элемент,
 *  опрерации выполняются за время О(1).
 *  5. Рехеширование и масштабирование не поддерживается.
 *  6. Поддержки произвольных типов нет.
 *
 * Вторая часть доказательства представлена на прилагаемых скриншотах.
 * На скриншоте TEST_RESULT показаны данные, поданные на вход программы и 
 * результаты её выполнения.
 * На скриншоте CONTEST_OUTPUT показан ответ, который должен был быть получен в 
 * результате корректной работы программы для использованных входных данных.
 * Данный скриншот взят из Яндекс.Контест для этой задачи.
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

#include <functional>
#include <algorithm>
#include <iostream>
#include <optional>
#include <vector>
#include <list>

class HashTable
{
public:
    HashTable() {_data.resize(_capacity);}

    void put(int key, int value);
    std::optional<int> get(int key);
    std::optional<int> deleteKey(int key);

private:
    std::size_t getIndex(int key);

private:
    std::vector<std::list<std::pair<int,int>>> _data;
    const std::size_t _capacity = 10000;
    std::size_t _size           = 0;
};

void HashTable::put(int key, int value)
{
    std::size_t index = getIndex(key);
    if (_data[index].empty())
    {
        _data[index].push_front({key, value});
    }
    else
    {
        auto pos = std::find_if(_data[index].begin(), _data[index].end(), [key](const std::pair<int,int>& p)
        {
            return p.first == key;
        });

        if(pos != _data[index].end())
        {
            pos->second = value;
        }
        else
        {
            _data[index].push_front({key, value});
        }
    }
}

std::optional<int> HashTable::get(int key)
{
    std::size_t index = getIndex(key);
    if (!_data[index].empty())
    {
        auto pos = std::find_if(_data[index].begin(), _data[index].end(), [key](const std::pair<int,int>& p)
        {
            return p.first == key;
        });

        if(pos != _data[index].end())
        {
            return {pos->second};
        }
        else
        {
            return std::nullopt;
        }
    }
    else
    {
        return std::nullopt;
    }
}

std::optional<int> HashTable::deleteKey(int key)
{
    std::size_t index = getIndex(key);
    if (!_data[index].empty())
    {
        auto pos = std::find_if(_data[index].begin(), _data[index].end(), [key](const std::pair<int,int>& p)
        {
            return p.first == key;
        });
        if (pos != _data[index].end())
        {
            int val = pos->second;
            _data[index].erase(pos);
            return {val};
        }
        else
        {
            return std::nullopt;
        }
    }
    else
    {
        return std::nullopt;
    }
}

std::size_t HashTable::getIndex(int key)
{
    return std::hash<int>{}(key) % _capacity;
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
