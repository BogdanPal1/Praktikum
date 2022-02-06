#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Cmp
{
    bool operator()(const std::pair<int,int>& rhs, const std::pair<int,int>& lhs)
    {
        if (rhs.second == lhs.second)
        {
            return rhs.first < lhs.first;
        }
        return rhs.second > lhs.second;
    }
};

int main()
{
    Cmp comp;
    std::string s = "";
    std::string word = "";
    std::unordered_map<std::string, std::unordered_map<int, int>> docIndex;
    std::vector<std::unordered_map<int, int>> rels;
    int amountOfDocuments = 0;
    int amountOfQueries = 0;

    std::cin >> amountOfDocuments >> std::ws;
    for (int i = 0; i < amountOfDocuments; ++i)
    {
        std::getline(std::cin, s);
        std::stringstream x(s);

        while (std::getline(x, word, ' '))
        {
            ++docIndex[word][i];
        }
    }

    std::cin >> amountOfQueries >> std::ws;
    for (int i = 0; i < amountOfQueries; ++i)
    {
        std::getline(std::cin, s);
        std::stringstream x(s);

        std::unordered_map<int, int> docTemp;
        std::unordered_set<std::string> uniqueWords;
        while (std::getline(x, word, ' '))
        {
            if (uniqueWords.insert(word).second)
            {
                if (docIndex.find(word) != docIndex.end())
                {
                    for (const auto& t : docIndex[word])
                    {
                        docTemp[t.first + 1] += t.second;
                    }
                }
            }
        }
        rels.push_back(docTemp);
    }

    for (int j = 0; j < rels.size(); ++j)
    {
        std::vector<std::pair<int, int>> vt(rels[j].begin(), rels[j].end());
        std::sort(vt.begin(), vt.end(), comp);
        if (vt.size() < 5)
        {
            for (const auto& t : vt)
            {
                std::cout << t.first << " ";
            }
        }
        else
        {
            for (int i = 0; i < 5; ++i)
            {
                std::cout << vt[i].first << " ";
            }
        }
        std::cout << '\n';
    }
    return 0;
}
