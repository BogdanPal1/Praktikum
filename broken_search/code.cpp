#include "solution.h"
#include <vector>
#include <cassert>

int binSearch(const std::vector<int>& vec, int x, int left, int right)
{
    if (left > right)
    {
        return -1;
    }

    int mid = (left + right) / 2;

    if (vec[mid] == x)
    {
        return mid;
    }

    if (vec[left] < vec[mid])
    {
        if ((vec[left] <= x) && (vec[mid] >= x))
        {
            return binSearch(vec, x, left, mid - 1);
        }
        else
        {
            return binSearch(vec, x, mid + 1, right);
        }
    }
    else if (vec[right] > vec[mid])
    {
        if ((vec[mid] <= x) && (vec[right] >= x))
        {
            return binSearch(vec, x, mid + 1, right);
        }
        else
        {
            return binSearch(vec, x, left, mid - 1);
        }
    }
    else if (vec[mid] == vec[left])
    {
        if (vec[mid] != vec[right])
        {
            return binSearch(vec, x, mid + 1, right);
        }
        else
        {
            int result = binSearch(vec, x, left, mid - 1);
            if(result == -1)
            {
                return binSearch(vec, x, mid + 1, right);
            }
            else
            {
                return result;
            }
        }
    }
}

int broken_search(const std::vector<int>& vec, int k) {
    return binSearch(vec, k, 0, vec.size() - 1);
}

void test() {
    std::vector<int> arr = {19, 21, 100, 101, 1, 4, 5, 7, 12};
    assert(6 == broken_search(arr, 5));
}
