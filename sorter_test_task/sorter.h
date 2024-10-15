#ifndef SORTER_H
#define SORTER_H

#include <fstream>
#include <vector>

enum class SORTING_METHOD {
    FIRST_NAME = 1,
    SECOND_NAME,
    NUMBER
};

class Sorter {

    struct Person {
        std::string firstName;
        std::string lastName;
        std::string number;
    };

public:
    Sorter(SORTING_METHOD sortingMethod, std::string fileName);
    void setSortingMethod (SORTING_METHOD newMethod);
    void setFileName(std::string fileName);
    std::vector<Person> sorting();
private:
    SORTING_METHOD m_sorting_method;
    std::ifstream m_file;
    std::vector<Person> m_person;
    bool sortByFirstName(const Person& first, const Person& second);
    bool sortByLastName(const Person& first, const Person& second);
    bool sortByNumber (const Person& first, const Person& second);
};

#endif // SORTER_H
