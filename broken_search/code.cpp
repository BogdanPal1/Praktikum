/*
 * ID 64568277
 * Спринт 3. Задача "Поиск в сломанном массиве"
 * Палкин Богдан. Когорта 20.
 *
 * -- ПРИНЦИП РАБОТЫ --
 * По условию задания имеется отсортированный массив, к которому
 * фактически был применен сдвиг. Это означает, что в массиве есть
 * две отсортированные части, к которым можно применить бинарный поиск.
 *
 * Идея алгоритма была взята из статьи, доступной по следующей ссылке:
 * https://www.geeksforgeeks.org/search-an-element-in-a-sorted-and-pivoted-array/
 *
 * -- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
 * По условию задания поиск в массиве, должен осуществляться за O(log N).
 *
 * В данной реализации так же как и в обычном алгоритме бинарного поиска
 * на каждом шаге происходит разделение массива на две приблизительно равные по
 * размеру части до тех пор пока не будет найден искомый элемент или индекс
 * левой границы не превысит индекс правой(в этом случае считается, что элемент
 * не найден и функция вернет значение -1). Отличием данной реализации является
 * то, что после нахождения индекса середины массива, если элемент по данному
 * индексу не равен искомому, происходит проверка на то, какая из частей является
 * отсортированной. Временная сложность данной проверки равна О(1).
 *
 * Так как сложность обычного алгоритма бинарного поиска составляет
 * O(log N), то и сложность алгоритма представленного в данном решении и
 * основанного на обычном алгоритме бинарного поиска будет O(log N).
 *
 * -- ВРЕМЕННАЯ СЛОЖНОСТЬ --
 * Как и для обычного алгоритма бинарного поиска временная сложность
 * алгоритма, использованного для решения задачи, равна O(log N) из-за
 * того, что на каждом шаге количество входных данных уменьшается в 2 раза.
 *
 * -- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
 * Так как при работе алгоритма фактически необходимо место для хранения
 * трех индексов и не выделяется дополнительной памяти для массива, простран-
 * ственная сложность равна О(1).
 */

#include "solution.h"
#include <vector>
#include <cassert>
#include <algorithm>

auto pivot(const std::vector<int>& vec)
{
    if (*vec.begin() < *(vec.end() - 1))
    {
        return vec.end();
    }

    auto left = vec.begin();
    auto right = vec.end();

    while (left != right)
    {
        auto mid = left + (right - left) / 2;

        if (*mid > *(mid + 1))
        {
            return mid;
        }
        else if (*mid < *(mid - 1))
        {
            return mid - 1;
        }
        else if (*left >= *mid)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return vec.end();
}

int broken_search(const std::vector<int>& vec, int k) {

    auto p = pivot(vec);

    auto posIter = vec.begin();

    if (k >= *vec.begin() && p != vec.end())
    {
        posIter = std::lower_bound(vec.begin(), p, k);
    }
    else if (k <= *(vec.end() - 1) && p != vec.end())
    {
        posIter = std::lower_bound(p, vec.end(), k);
    }
    else
    {
        posIter = std::lower_bound(vec.begin(), vec.end(), k);
    }

    if (*posIter != k)
    {
        return -1;
    }

    return posIter - vec.begin();
}

void test() {
    std::vector<int> arr = {19, 21, 100, 101, 1, 4, 5, 7, 12};
    assert(6 == broken_search(arr, 5));
}
