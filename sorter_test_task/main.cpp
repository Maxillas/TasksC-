#include <iostream>

#include "sorter.h"
#include "sortertests.h"

int main()
{
    ushort sortingMethod;
    std::cout << "Для сортировки по именам введите - 1,\n"
                 "по фамилиям введите - 2,\n"
                 "по телефонам введите - 3\n" << std::endl;
    std::cin >> sortingMethod;

    Sorter fileSorter(static_cast<SORTING_METHOD>(sortingMethod), "../../tests/test1.txt");

    std::cout << "Ввод: " << sortingMethod << std::endl;
    std::cout << "Вывод: " << std::endl;
    for (const auto& i : fileSorter.sorting()) {
        if(sortingMethod == static_cast<int>(SORTING_METHOD::FIRST_NAME)) {
            std::cout << i.firstName + ' '
                      << i.lastName + ':' + ' '
                      << i.number << std::endl;
            continue;
        }
        if(sortingMethod == static_cast<int>(SORTING_METHOD::NUMBER)) {
            std::cout << i.number + ':' + ' '
                      << i.lastName + ' '
                      << i.firstName << std::endl;
            continue;
        }
        std::cout << i.lastName + ' '
                  << i.firstName + ':' + ' '
                  << i.number << std::endl;
    }

    // Tests
    SorterTests tester;
    if(!tester.test1()) {
        std::cout << "Ошибка в тесте №1" << std::endl;
        return 0;
    }
    if(!tester.test2()) {
        std::cout << "Ошибка в тесте №2" << std::endl;
        return 0;
    }
    if(!tester.test3()) {
        std::cout << "Ошибка в тесте №3" << std::endl;
        return 0;
    }
    std::cout << "Тесты успешно пройдены" << std::endl;
    // End tests

    return 0;
}
