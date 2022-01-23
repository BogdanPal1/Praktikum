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

int partition(std::vector<Competitor>& vec, int left, int right)
{
    int pivot = vec[right]._solvedProblems;
    int i = (left - 1);

    for (int j = left; j <= right - 1; j++)
    {
        if (vec[j]._solvedProblems > pivot)
        {
            i++;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[i + 1], vec[right]);
    return (i + 1);
}

void quickSort(std::vector<Competitor>& vec, int low, int high)
{
    if (low < high)
    {
        int pi = partition(vec, low, high);
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

void print(const std::vector<Competitor>& vec)
{
    for (const auto& c : vec)
    {
        std::cout << c._name << " " << c._solvedProblems << '\n';
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

    quickSort(v, 0, v.size() - 1);
    print(v);
    return 0;
}
