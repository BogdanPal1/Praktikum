/*
 * ID 64549800
 * Спринт 3. Задача "Эффективная быстрая сортировка"
 * Палкин Богдан. Когорта 20.
 *
 * -- ПРИНЦИП РАБОТЫ --
 * Программа последовательно считывает данные участников и сохраняет
 * их в векторе. После этого вызывается функция сортировки, которая
 * сортирует вектор участников по заданным в задаче условиям.
 * После сортировки вызывается функция print, которая выводит имена
 * участников соревнования.
 *
 * При решении задачи был использован вид функции сортировки из
 * стандартной библиотеки С++:
 * https://en.cppreference.com/w/cpp/algorithm/sort
 *
 * Функция сортировки на вход принимает два итератора и
 * функтор, используемый для сравнения элементов.
 *
 * Для реализации метода разделения был использован подход с выбором
 * в качестве опорного элемента последнего элемента массива, описанный
 * в книге Алгоритмы: построение и анализ(Томас Х. Кормен, Чарльз И. Лейзерсон,
 * Рональд Л. Ривест, Клиффорд Штайн.)
 *
 * -- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
 * По условию задачи сортировка не должна потреблять О(n) памяти для
 * промежуточных данных.
 *
 * В данной реализации алгоритма сортировки дополнительная память выделяется
 * только для итераторов.Промежуточные результаты не хранятся в массивах.
 * Таким образом алгоритм сортировки потребляет О(1) дополнительной памяти.
 *
 * -- ВРЕМЕННАЯ СЛОЖНОСТЬ --
 * Временная сложность алгоритма составляет в среднем О(nlogn).
 * Так как массив делится на две части, глубина рекурсии будет равна log n,
 * при этом на каждом уровне необходимо совершить n сравнений. Вместе
 * это обусловливает временную сложность алгоритма равную О(nlogn).
 *
 * -- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
 * При работе алгоритма не происходит сохранения промежуточных результатов
 * в дополнительных массивах. Память выделяется только для итераторов,
 * количество которых постоянно и не зависит от входных данных.
 *
 * Таким образом пространственная сложность алгоритма равна О(1).
 */

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using Competitor = std::tuple<std::string, int, int>;

using Iterator = std::vector<Competitor>::iterator;

struct Cmp
{
    bool operator()(const Iterator& first, const Iterator& second)
    {
        auto [nameOfFirst, firstSolvedProblems, firstPenalty] = *first;
        auto [nameOfSecond, secondSolvedProblems, secondPenalty] = *second;

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

Iterator partition(Iterator begin, Iterator end, Cmp comp)
{
    Iterator pivot = end - 1;
    Iterator i = begin;

    for (Iterator j = begin; j != end - 1; ++j)
    {
        if (comp(j, pivot))
        {
            std::swap(*i, *j);
            ++i;
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
        auto [name, problems, penalty] = c;
        std::cout << name << '\n';
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

        Competitor c = {name, numOfSolvedProblems, penalty};
        v.push_back(c);
    }

    Cmp comp;
    sort(v.begin(), v.end(), comp);
    print(v);
    return 0;
}
