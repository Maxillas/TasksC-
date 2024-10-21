//____________Описание задачи____________
/*
Пример входного файла:
Иванов Иван: 3515454
Сидоров Иван: 3515422
Сидоров Олег: 23515423
Петров Иван: 3515455
Программа должна выводить данные отсортированные по именам, фамилиям и номерам. Перед выводом, программа должна спрашивать - по какому параметру сортировать и ставить этот параметр в начало вывода:
Пример:
Для сортировки по именам введите – 1, по фамилиям введите- 2, по телефонам введите- 3
Ввод: 1
Вывод:
Иван Иванов: 3515454
Иван Сидоров: 3515422
Иван Петров: 3515455
Олег Сидоров: 23515423
Ввод : 3
Вывод:
3515422: Сидоров Иван
3515454: Иванов Иван
3515455: Петров Иван
23515423: Сидоров Олег
*/
//_______________________________________

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
