#include <iostream>
#include <string>
#include <vector>

struct Competitor
{
    Competitor(const std::string& name, int solvedProblems, int penalty) :
        _name(name), _solvedProblems(solvedProblems), _penalty(penalty) {}

    std::string _name = "";
    int _solvedProblems = 0;
    int _penalty = 0;
};

using Iterator = std::vector<Competitor>::iterator;

struct Cmp
{
    bool operator()(const Iterator& first, const Iterator& second)
    {
        if (first->_solvedProblems == second->_solvedProblems)
        {
            if(first->_penalty == second->_penalty)
            {
                if (first->_name < second->_name)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else if (first->_penalty < second->_penalty)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (first->_solvedProblems > second->_solvedProblems)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

Iterator partition(Iterator begin, Iterator end, Cmp comp)
{
    Iterator pivot = std::prev(end, 1);
    Iterator i = begin;

    for (Iterator j = begin; j != pivot; ++j)
    {
        if (comp(j, pivot))
        {
            std::swap(*i++, *j);
        }
    }
    std::swap(*i, *pivot);
    return i;
}

void sort(Iterator begin, Iterator end, Cmp comp)
{
    if (std::distance(begin, end) < 2)
    {
        return;
    }

    Iterator pi = partition(begin, end, comp);
    sort(begin, pi, comp);
    sort(pi + 1, end, comp);
}

void print(const std::vector<Competitor>& vec)
{
    for (const auto& c : vec)
    {
        std::cout << c._name << '\n';
    }
}

int main()
{
    std::vector<Competitor> v;

    int numOfCompetitors = 0;
    int numOfSolvedProblems = 0;
    int penalty = 0;
    std::string name = "";

    std::cin >> numOfCompetitors;

    for (int i = 0; i < numOfCompetitors; ++i)
    {
        std::cin >> name;
        std::cin >> numOfSolvedProblems;
        std::cin >> penalty;

        Competitor c(name, numOfSolvedProblems, penalty);
        v.push_back(c);
    }

    Cmp comp;
    sort(v.begin(), v.end(), comp);
    print(v);
    return 0;
}
