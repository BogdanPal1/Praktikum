#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
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

void makeDocIndex(std::unordered_map<std::string, std::unordered_map<int, int>>& index,
                  std::ifstream& fileStream,
                  int amountOfDocuments)
{
    std::string s = "";
    std::string word = "";

    for (int i = 0; i < amountOfDocuments; ++i)
    {
        std::getline(fileStream, s);
        std::stringstream strStream(s);

        while (std::getline(strStream, word, ' '))
        {
            ++index[word][i];
        }
    }
}

void findRelevance(std::unordered_map<std::string, std::unordered_map<int, int>>& index,
                   std::vector<std::vector<std::pair<int,int>>>& relevance,
                   std::ifstream& fileStream,
                   int amountOfRequests)
{
    Cmp comp;
    std::string s = "";
    std::string word = "";
    for (int i = 0; i < amountOfRequests; ++i)
    {
        std::getline(fileStream, s);
        std::stringstream strStream(s);

        std::unordered_map<int, int> relevanceForRequest;
        std::unordered_set<std::string> uniqueWords;
        while (std::getline(strStream, word, ' '))
        {
            if (uniqueWords.insert(word).second)
            {
                if (index.find(word) != index.end())
                {
                    for (const auto& t : index[word])
                    {
                        relevanceForRequest[t.first + 1] += t.second;
                    }
                }
            }
        }
        std::vector<std::pair<int, int>> vt(relevanceForRequest.begin(), relevanceForRequest.end());
        std::sort(vt.begin(), vt.end(), comp);
        if (vt.size() > 5)
        {
            relevance.push_back({vt.begin(), vt.begin() + 5});
        }
        else
        {
            relevance.push_back(vt);
        }
    }
}

void printDocumentID(std::vector<std::vector<std::pair<int,int>>> relevance)
{
    for (const auto& vec : relevance)
    {
        for (const auto& pair : vec)
        {
            std::cout << pair.first << " ";
        }
        std::cout << '\n';
    }
}

int main()
{
    std::string s = "";
    std::string word = "";
    int amountOfRequests = 0;
    int amountOfDocuments = 0;

    std::unordered_map<std::string, std::unordered_map<int, int>> docIndex;
    std::vector<std::vector<std::pair<int,int>>> relevance;

    std::ifstream ifs;
    ifs.open("input.txt");

    std::getline(ifs, s);
    std::stringstream x(s);
    x >> amountOfDocuments;

    makeDocIndex(docIndex, ifs, amountOfDocuments);

    std::getline(ifs, s);
    std::stringstream a(s);
    a >> amountOfRequests;
    findRelevance(docIndex, relevance, ifs, amountOfRequests);
    ifs.close();

    printDocumentID(relevance);

    return 0;
}
