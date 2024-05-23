/*
Напишите шаблонную функцию to_pair, которая принимает произвольный std::tuple и два индекса внутри и возвращает std::pair, содержащий элементы переданного std::tuple с соответствующими индексами.

Пример:

auto t = std::make_tuple(0, 3.5, "Hello");
std::pair<double, char const *> p = to_pair<1,2>(t);
// p содержит 3.5 и "Hello"
 */

#include <iostream>
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
