/*
 По аналогии с функцией printf с предыдущего степа напишите функцию print_values с переменным числом аргументов, которая для каждого аргумента выводит его тип и значение в поток std::ostream, который ей передан в качестве первого аргумента. Функция должна работать с произвольным числом аргументов.
Указание: для вывода имени типа нужно использовать std::type_info::name.
Например, вызов функции

print_values(std::cout, 0, 3.5, "Hello");

должен вывести на стандартный вывод примерно следующее (таким будет вывод на g++).

i: 0
d: 3.5
PKc: Hello
*/

#include <ostream>
#include <typeinfo>

//void print_values(std::ostream& os){}

template<typename T>
void print_values(std::ostream & os, T arg)
{
    os << typeid(arg).name() << ": " << arg << std::endl;
}

// принимает произвольное число аргументов
template<typename T, typename... Args>
void print_values(std::ostream & os, T value, Args... args)
{
    os << typeid(value).name() << ": " << value<< std::endl;
    print_values(os, args...);
}



//print_values(std::cout, 0, 3.5, "Hello");
