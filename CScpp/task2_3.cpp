/*
Напишите шаблонную функцию to_pair, которая принимает произвольный std::tuple и два индекса внутри и возвращает std::pair, содержащий элементы переданного std::tuple с соответствующими индексами.

Пример:

auto t = std::make_tuple(0, 3.5, "Hello");
std::pair<double, char const *> p = to_pair<1,2>(t);
// p содержит 3.5 и "Hello"
 */

#include <iostream>
#include <functional>
#include <tuple>

template<int firstIndex, int secondIndex, typename... Tup>
auto to_pair(std::tuple<Tup...> tpl)->decltype(std::make_pair(std::get<firstIndex>(tpl), std::get<secondIndex>(tpl))) {
    return std::make_pair(std::get<firstIndex>(tpl), std::get<secondIndex>(tpl));
}
auto t = std::make_tuple(0, 3.5, "Hello");
std::pair<double, char const *> p = to_pair<1,2>(t);


/*Напишите constexpr бинарные операторы +, - и * (скалярное произведение) для структуры Point.

Пример использования:

constexpr size_t size = static_cast<size_t>(Point(2,4) * Point(4,3));
int m[size]; // массив из 20 элементов */

// определение структуры Point уже подключено
struct Point
{
    constexpr Point(double x, double y)
        : x(x), y(y)
    {}

    double x = 0;
    double y = 0;
};

// сложение
constexpr Point operator+(const Point &a, const Point &b)
{
    return Point(a.x + b.x, a.y + b.y);
}

// вычитание
constexpr Point operator-(const Point &a, const Point &b)
{
    return Point(a.x - b.x, a.y - b.y);
};

// скалярное произведение
constexpr double operator*(const Point &a, const Point &b)
{
    return a.x * b.x + a.y * b.y;
}

/*

Рассмотрим следующую функцию for_each.

Определите переменную square_fun, хранящую безымянную функцию, которая возводит переданное число в квадрат.

Пример:
*/

template<class F>
void for_each_int(int * p, int * q, F f)
{
    for ( ; p != q; ++p )
        f(*p);
}

// определение переменной
auto square_fun = [](int & num){ num *= num;};

/*Рассмотрим следующую функцию find_if:

template<class F>
int * find_if(int * p, int * q, F f)
{
    for ( ; p != q; ++p )
        if (f(*p))
            return p;
    return q;
}

Определите переменную gen_finder, хранящую безымянную функцию, которая принимает массив значений типа int через два указателя и
возвращает безымянную функцию, которая в свою очередь принимает значение типа int и проверяет, есть ли это значение в переданном массиве.

Пример:

int primes[5] = {2,3,5,7,11};

int m[10] = {0,0,1,1,4,6,7,8,9,10};

// first_prime будет указывать на число 7
int * first_prime = find_if(m, m + 10, gen_finder(primes, primes + 5));
*/

template<class F>
int * find_if(int * p, int * q, F f)
{
    for ( ; p != q; ++p )
        if (f(*p))
            return p;
    return q;
}

auto gen_finder = [](int* arrayStart, int* arrayEnd){
    auto foo = [arrayStart, arrayEnd](int inputNum){
        int* start = arrayStart;
        int* end = arrayEnd;
        for (; start != end; ++start) {
            if(inputNum == *start) {
                return true;
            }
        }
        return false;
    };

    return foo;};

int primes[5] = {2,3,5,7,11};

int m[10] = {0,0,1,1,4,6,7,8,9,10};

// first_prime будет указывать на число 7
int * first_prime = find_if(m, m + 10, gen_finder(primes, primes + 5));







