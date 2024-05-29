#include <typeinfo>
#include <typeindex>
#include <map>
#include <iostream>

// базовый класс фигуры (полиморфный)
struct Shape {  };

// прямоугольник
struct Rectangle : Shape {  };

// треугольник
struct Triangle : Shape {  };

// Base - базовый класс иерархии
// Result - тип возвращаемого значения мультиметода
// Commutative - флаг, который показывает, что
// мультиметод коммутативный (т.е. f(x,y) = f(y,x)).
template<class Base, class Result, bool Commutative>
struct Multimethod2
{
    // устанавливает реализацию мультиметода
    // для типов t1 и t2 заданных через typeid
    // f - это функция или функциональный объект
    // принимающий два указателя на Base
    // и возвращающий значение типа Result
    void addImpl(std::type_info const &t1, std::type_info const &t2, Result (*foo)(Base* a, Base* b))
    {
        std::pair<std::type_index, std::type_index> pair = std::make_pair(std::type_index(t1), std::type_index(t2));
        m_fooContainer.emplace(pair, foo);
    }

    // проверяет, есть ли реализация мультиметода
    // для типов объектов a и b
    bool hasImpl(Base * a, Base * b) const
    {
        // здесь проверить на комутативность. если ЕСТЬ пара нужная, то збс, если нет, то нет
        // возвращает true, если реализация есть
        // если операция коммутативная, то нужно
        // проверить есть ли реализация для b и а
       // return ...;
        return true;
    }

    // Применяет мультиметод к объектам
    // по указателям a и b
    Result call(Base * a, Base * b) const
    {
        // возвращает результат применения реализации
        // мультиметода к a и b
       // return ...;
        return true;
    }

private:
    std::map<std::pair<std::type_index, std::type_index>, Result (*)(Base* a, Base* b)> m_fooContainer;

};
