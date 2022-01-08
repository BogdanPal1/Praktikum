/****************************************
 * ID 61834274                          *
 * Палкин Богдан. Когорта 20. Спринт 1. *
 * Задача B. Ловкость рук.              *
 ****************************************/

#include <string>
#include <iostream>
#include <unordered_map>

int main()
{
    int k = 0;     // Количество клавиш, которые можно нажать одновременно
    int count = 0; // Счётчик баллов за успешные нажатия на клавиши

    // Здесь будут храниться счётчики для каждого значения поля
    // от 1 до 9, кроме символа "."
    std::unordered_map<char, int> field;
    std::string line;

    std::cin >> k;
    std::getline(std::cin, line);

    for (int i = 0; i < 4; ++i)
    {
        std::getline(std::cin, line);
        for (auto c : line)
        {
            if (std::isdigit(c))
            {
                field[c] += 1;
            }
        }
    }

    for (auto i : field)
    {
        if (i.second <= 2 * k)
        {
            ++count;
        }
    }

    std::cout << count << '\n';
    return 0;
}
