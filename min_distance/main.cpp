/****************************************
 * ID 61910115                          *
 * Палкин Богдан. Когорта 20. Спринт 1. *
 * Задача А. Ближайший ноль.            *
 ****************************************/

#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>

//Функция, которая вычисляет расстояния справа от нуля
void distanceRight(const std::vector<int>& sites, std::vector<int>& rightDist);

//Функция, которая вычисляет расстояния слева от нуля
void distanceLeft(const std::vector<int>& sites, std::vector<int>& leftDist);

// Функция, которая вычисляет минимальное значение расстояния справа и слева
std::vector<int> minDistance(const std::vector<int>& left, const std::vector<int>& right);

int main()
{
    int size = 0, site = 0;
    std::vector<int> sites, reversedSites, rightDist, leftDist;
    //std::deque<int> leftDist;

    std::cin >> size;
    for (auto i = 0; i < size; ++i)
    {
        std::cin >> site;
        sites.push_back(site);
    }

    distanceRight(sites, rightDist);
    distanceLeft(sites, leftDist);
    std::reverse(leftDist.begin(), leftDist.end());

    sites = minDistance(leftDist, rightDist);

    for (auto i : sites)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}

void distanceRight(const std::vector<int>& sites, std::vector<int>& rightDist)
{
    int distance = sites.size();
    for (auto elem = sites.cbegin(); elem != sites.cend(); ++elem)
    {
        if (*elem == 0)
        {
            distance = 0;
        }
        else
        {
            ++distance;
        }
        rightDist.push_back(distance);
    }
}

void distanceLeft(const std::vector<int>& sites, std::vector<int>& leftDist)
{
    int distance = sites.size();
    for (auto elem = sites.crbegin(); elem != sites.crend(); ++elem)
    {
        if (*elem == 0)
        {
            distance = 0;
        }
        else
        {
            ++distance;
        }
        leftDist.push_back(distance);
    }
}

std::vector<int> minDistance(const std::vector<int>& left, const std::vector<int>& right)
{
    std::vector<int> minDist;
    for (decltype (left.size()) i = 0; i < left.size(); ++i)
    {
        if (left[i] <= right[i])
        {
            minDist.push_back(left[i]);
        }
        else
        {
            minDist.push_back(right[i]);
        }
    }
    return minDist;
}
