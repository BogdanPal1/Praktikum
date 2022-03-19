/*
 * ID 65058128
 * Спринт 4. Задача А "Поисковый индекс"
 * Палкин Богдан. Когорта 20.
 *
 * -- ПРИНЦИП РАБОТЫ --
 *
 * В данном задании требуется построить поисковый индекс по
 * документам и после обработки запросов на поиск необходимо
 * вывести по 5 самых релевантных для каждого запроса документов.
 *
 * Решение задачи состоит в следующем:
 *
 * Последовательно считываются подаваемые на вход документы.
 * Для каждого слова заполняется хеш-таблица следущего вида:
 *
 * unordered_map<string, unordered_map<int, int>> docIndex
 *
 * где ключем является слово, а значением является ещё одна хеш-таблица,
 * в которой ключем уже является номер документа, а значением -
 * количество раз, когда в данном документе встретилось слово.
 *
 * После заполнения индекса. Происходит последовательное считывание
 * запросов.
 * Для каждого запроса создаются временные хеш-таблица и множество,
 * которые имеют вид:
 *
 * unordered_map<int, int> relevanceForRequest;
 * unordered_set<string> uniqueWords;
 *
 * Для каждого уникального слова из запроса(уникальность обеспечивается
 * использованием множества), если оно имеется в индексе, программа
 * проходит по всем документам, в которых имеется данное слово и заполняет
 * хеш-таблицу relevanceForRequest.
 *
 * После того как были обработаны все слова из текущего запроса создаётся
 * вектор, содержащий пары значений (номер документа, релевантность).
 * Данный вектор сортируется и 5 самых релевантных документов заносятся в
 * итоговый вектор, хранящий в себе самые релевантные документы для всех
 * запросов.
 *
 * -- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
 *
 * Доказательство корректности представлено в виде скриншота работы программы
 * для входных данных input.txt из первого теста в Яндекс.Контест.
 *
 * -- ВРЕМЕННАЯ СЛОЖНОСТЬ --
 *
 * Временная сложность алгоритма расчёта релевантностей зависит от нескольких
 * факторов. Первый фактор - количество запросов N. Второй фактор - количество
 * слов в запросе M. Третий фактор - длина слов, т.к. хеш-функция линейно зависит
 * от неё. Четвёртый фактор - количество документов L, которые необходимо просмотреть
 * для каждого слова. Пятый фактор - скорость сортировки вектора пар.
 * Грубо временную сложность алгоритма можно представить как O(N * M * L).
 *
 * -- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
 *
 * Пространство, необходимое для работы алгоритма зависит от количества документов N,
 * подаваемых на вход, а также количества запросов M.
 * Пространственную сложность можно оценить как O(N * M).
 */

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

void findRelevance(const std::unordered_map<std::string, std::unordered_map<int, int>>& index,
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
                auto pos = index.find(word);
                if (pos != index.end())
                {
                    for (const auto& t : (pos->second))
                    {
                        relevanceForRequest[t.first + 1] += t.second;
                    }
                }
            }
        }
        
        std::vector<std::pair<int, int>> vt(relevanceForRequest.begin(), relevanceForRequest.end());
        
        if (vt.size() > 5)
        {
            std::partial_sort(vt.begin(), vt.begin() + 5, vt.end(), comp);
            relevance.push_back({vt.begin(), vt.begin() + 5});
        }
        else
        {
            std::sort(vt.begin(), vt.end(), comp);
            relevance.push_back(vt);
        }
    }
}

void printDocumentID(const std::vector<std::vector<std::pair<int,int>>> relevance)
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
