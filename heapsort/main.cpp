/*
 * ID 66214603
 * Спринт 5. Задача А "Пирамидальная сортировка"
 * Палкин Богдан. Когорта 20.
 * 
 * -- ПРИНЦИП РАБОТЫ --
 * 
 * В данном задании необходимо реализовать алгоритм Пирамидальной
 * сортировки, с помощью которого будет происходить упорядочивание
 * участников соревнование по заданным критериям.
 * 
 * Принип работы полностью основан на теории из данного спринта и
 * представляет собой три шага:
 *     1. Создаётся куча;
 *     2. Куча заполняется элементами(участниками), при этом сохраняет
 *        свои свойства. Участник с наилучшими результатами находится
 *        на вершине кучи.
 *     3. После этого из кучи забираются наиболее приоритетные элементы.
 * 
 * После выполнения алгоритма получается массив отсортированный в 
 * порядке от большего к меньшему.
 * 
 * -- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
 * 
 * Доказательство корректности работы алгоритма представленно на скриншотах,
 * приложенных к архиву. На тестовых примерах вывод после работы алгоритма
 * совпадает с ответом на платформе Яндекс.Контест.
 * 
 * -- ВРЕМЕННАЯ СЛОЖНОСТЬ --
 * 
 * Временная сложность работы алгоритма складывается из нескольких составля-
 * ющих:
 *     1. Создание исходной кучи происходит за линейное время O(n)
 *        и зависит от необходимого размера кучи;
 *     2. Добавление нового элемента в кучу происходит в среднем
 *        за O(nlog n);
 *     3. Извлечение наиболее приоритетного элемента из кучи происходит
 *        в среднем за О(nlog n);
 * В сумме все это дает сложность в O(nlog n).
 * 
 * -- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
 * Так как для реализации кучи нам нужно создать массив, то пространственная
 * сложность будет равна O(n), где n - количество элементов, которые необходимо
 * отсортировать. 
 * */

#include <iostream>
#include <string>
#include <vector>

struct Competitor
{
    Competitor() = default;
    Competitor(const std::string& name, int solvedProblems, int penalty) :
        _name(name), _solvedProblems(solvedProblems), _penalty(penalty){}
    bool operator<(const Competitor& rhs);

    std::string _name;
    int _solvedProblems = 0;
    int _penalty = 0;
};


bool Competitor::operator<(const Competitor &rhs)
{
    if (_solvedProblems == rhs._solvedProblems)
    {
        if (_penalty == rhs._penalty)
        {
            return _name > rhs._name;
        }
        return _penalty > rhs._penalty;
    }
    return _solvedProblems < rhs._solvedProblems;
}

class Heap
{
public:
    Heap(std::size_t size, std::size_t capacity) : _size(size), _data(capacity, Competitor()){}
    void add(const Competitor& competitor);
    Competitor getMaxPriority();

private:
    void siftUp(std::size_t index);
    void siftDown(std::size_t index);

private:
    std::size_t _size = 0;
    std::size_t _index = 0;
    std::vector<Competitor> _data;
};

void Heap::add(const Competitor& competitor)
{
    _data[++_index] = competitor;
    siftUp(_index);
}

Competitor Heap::getMaxPriority()
{
    Competitor res = _data[1];
    _data[1] = _data[_size];
    _data.resize(_size);
    --_size;
    siftDown(1);
    return res;
}

void Heap::siftUp(std::size_t index)
{
    std::size_t parentIndex = index / 2;
    if (parentIndex > 0)
    {
        if (_data[parentIndex] < _data[index])
        {
            std::swap(_data[parentIndex], _data[index]);
            siftUp(parentIndex);
        }
    }
}

void Heap::siftDown(std::size_t index)
{
    std::size_t largest = 0;
    std::size_t left = 2 * index;
    std::size_t right = 2 * index + 1;

    if (_size < left)
        return;

    if ((right <= _size) && (_data[left] < _data[right]))
    {
        largest = right;
    }
    else
    {
        largest = left;
    }

    if (_data[index] < _data[largest])
    {
        std::swap(_data[largest], _data[index]);
        siftDown(largest);
    }
}

void heapsort(std::vector<Competitor>& vec)
{
    Heap h(vec.size(), (vec.size() + 1));

    for (const auto& c : vec)
    {
        h.add(c);
    }

    for (std::size_t i = 0; i < vec.size(); ++i)
    {
        vec[i] = h.getMaxPriority();
    }
}

int main()
{
    int numOfCompetitors = 0;
    int numOfSolvedProblems = 0;
    int penalty = 0;
    std::string name = "";
    std::vector<Competitor> vec;

    std::cin >> numOfCompetitors;

    for (int i = 0; i < numOfCompetitors; ++i)
    {
        std::cin >> name;
        std::cin >> numOfSolvedProblems;
        std::cin >> penalty;

        Competitor c(name, numOfSolvedProblems, penalty);
        vec.push_back(c);
    }

    heapsort(vec);

    for (const auto& c : vec)
    {
        std::cout << c._name << '\n';
    }

    return 0;
}
