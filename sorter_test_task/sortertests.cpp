#include "sortertests.h"
#include "sorter.h"

SorterTests::SorterTests() {}

bool SorterTests::test1()
{
    Sorter sorter(static_cast<SORTING_METHOD>(1), "../../tests/test1.txt");
    auto result = sorter.sorting();
    if ((result[0].firstName == "Иван" && result[0].lastName == "Иванов") &&
        (result[1].firstName == "Иван" && result[1].lastName == "Сидоров") &&
        (result[2].firstName == "Иван" && result[2].lastName == "Петров") &&
        (result[3].firstName == "Олег" && result[3].lastName == "Сидоров")) {
        return true;
    }
    return false;
}

bool SorterTests::test2()
{
    Sorter sorter(static_cast<SORTING_METHOD>(2), "../../tests/test1.txt");
    auto result = sorter.sorting();
    if ((result[0].firstName == "Иван" && result[0].lastName == "Иванов") &&
        (result[1].firstName == "Иван" && result[1].lastName == "Петров") &&
        (result[2].firstName == "Иван" && result[2].lastName == "Сидоров") &&
        (result[3].firstName == "Олег" && result[3].lastName == "Сидоров")) {
        return true;
    }
    return false;
}

bool SorterTests::test3()
{
    Sorter sorter(static_cast<SORTING_METHOD>(3), "../../tests/test1.txt");
    auto result = sorter.sorting();
    if ((result[0].firstName == "Иван" && result[0].lastName == "Сидоров") &&
        (result[1].firstName == "Иван" && result[1].lastName == "Иванов") &&
        (result[2].firstName == "Иван" && result[2].lastName == "Петров") &&
        (result[3].firstName == "Олег" && result[3].lastName == "Сидоров")) {
        return true;
    }
    return false;
}
