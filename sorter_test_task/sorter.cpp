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
#include "sorter.h"
#include <sstream>
#include <algorithm>
#include <iostream>


Sorter::Sorter(SORTING_METHOD sortingMethod, std::string fileName) {
    setSortingMethod(sortingMethod);
    setFileName(fileName);
}

void Sorter::setSortingMethod(SORTING_METHOD newMethod) {
    m_sorting_method = newMethod;
}

void Sorter::setFileName(std::string fileName) {
    m_file.open(fileName);
    if(!m_file.is_open()) {
        std::cerr << "Ошибка чтения файла" << std::endl;
        return;
    }
    std::cout << "Файл успешно открыт" << std::endl;
}

std::vector<Sorter::Person> Sorter::sorting() {
    std::string line;
    while(std::getline(m_file, line)) {
        std::istringstream stream(line);
        std::string firstName, lastName, number;
        std::getline(stream, lastName, ' ');
        std::getline(stream, firstName, ':');
        std::getline(stream, number);
        number.erase(0,1);
        m_person.push_back({firstName, lastName, number});
    }

    bool (Sorter::*sortingFoo)(const Person& first, const Person& second);

    switch (m_sorting_method) {

    case SORTING_METHOD::FIRST_NAME:
        sortingFoo = &Sorter::sortByFirstName;
        break;
    case SORTING_METHOD::NUMBER:
        sortingFoo = &Sorter::sortByNumber;
        break;
    case SORTING_METHOD::SECOND_NAME:
    default:
        sortingFoo = &Sorter::sortByLastName;
        break;
    }

    std::sort(m_person.begin(), m_person.end(),
              [this, sortingFoo](const Person& first, const Person& second) {
                  return (this->*sortingFoo)(first, second);
              }
              );

    m_file.close();
    return m_person;
}

bool Sorter::sortByFirstName(const Person &first, const Person &second) {
    if (first.firstName == second.firstName) {
        //return first.lastName < second.lastName;
    }
    return first.firstName < second.firstName;
}

bool Sorter::sortByLastName(const Person &first, const Person &second) {
    if (first.lastName == second.lastName) {
        //return first.firstName < second.firstName;
    }
    return first.lastName < second.lastName;
}

bool Sorter::sortByNumber(const Person &first, const Person &second) {
    return std::stoi(first.number) < std::stoi(second.number);
}
