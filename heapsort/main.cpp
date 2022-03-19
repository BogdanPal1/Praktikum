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
    void print();
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

void Heap::print()
{
    for (const auto& c : _data)
    {

        std::cout << c._name << '\n';
    }
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


int main()
{
    int numOfCompetitors = 0;
    int numOfSolvedProblems = 0;
    int penalty = 0;
    std::string name = "";

    std::cin >> numOfCompetitors;
    Heap h(numOfCompetitors, (numOfCompetitors + 1));

    for (int i = 0; i < numOfCompetitors; ++i)
    {
        std::cin >> name;
        std::cin >> numOfSolvedProblems;
        std::cin >> penalty;

        Competitor c(name, numOfSolvedProblems, penalty);
        h.add(c);
    }

    std::vector<Competitor> v;
    for (int i = 1; i < numOfCompetitors + 1; ++i)
    {
        v.push_back(h.getMaxPriority());
    }

    for (const auto& c : v)
    {
        std::cout << c._name << '\n';
    }


    return 0;
}

