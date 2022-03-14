#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using Competitor = std::tuple<std::string, int, int>;

using Iterator = std::vector<Competitor>::iterator;

struct Cmp
{
    bool operator()(const Competitor& first, const Competitor& second)
    {
        auto [nameOfFirst, firstSolvedProblems, firstPenalty] = first;
        auto [nameOfSecond, secondSolvedProblems, secondPenalty] = second;

        if (firstSolvedProblems == secondSolvedProblems)
        {
            if (firstPenalty == secondPenalty)
            {
                return nameOfFirst < nameOfSecond;
            }
            return firstPenalty < secondPenalty;
        }
        return firstSolvedProblems > secondSolvedProblems;
    }
};

class Heap
{
public:
    Heap(std::size_t size, Cmp comp) : _comp(comp), _data(size, Competitor()){}
    void add(const Competitor& competitor);
    Competitor getMaxPriotity();
    void print();
private:
    void siftUp(std::size_t index);
    void siftDown();
private:
    std::size_t _index = 0;
    Cmp _comp;
    std::vector<Competitor> _data;
};

void Heap::add(const Competitor& competitor)
{
    _data[++_index] = competitor;
    siftUp(_index);
}

void Heap::print()
{
    for (const auto& c : _data)
    {
        auto [name, problems, penalty] = c;
        std::cout << name << '\n';
    }
}

void Heap::siftUp(std::size_t index)
{
    std::size_t parentIndex = index / 2;
    if (parentIndex > 0)
    {
        if (_comp(_data[parentIndex], _data[index]))
        {
            std::swap(_data[parentIndex], _data[index]);
            siftUp(parentIndex);
        }
    }
}

std::vector<Competitor> sort(Heap& heap)
{
}


int main()
{
    int numOfCompetitors = 0;
    int numOfSolvedProblems = 0;
    int penalty = 0;
    std::string name = "";

    std::cin >> numOfCompetitors;
    Cmp comp;
    Heap h((numOfCompetitors + 1), comp);

    for (int i = 0; i < numOfCompetitors; ++i)
    {
        std::cin >> name;
        std::cin >> numOfSolvedProblems;
        std::cin >> penalty;

        Competitor c = {name, numOfSolvedProblems, penalty};
        h.add(c);
    }
    h.print();

    return 0;
}


