#include <typeinfo>
#include <typeindex>
#include <map>
#include <functional>
#include <iostream>

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
    void addImpl(std::type_info const &t1,
                 std::type_info const &t2,
                 std::function<Result(Base* a, Base* b)> foo)
                 //Result (*foo)(Base* a, Base* b))
    {
        std::pair<std::type_index, std::type_index> pair = std::make_pair(std::type_index(t1), std::type_index(t2));
        m_fooContainer.emplace(pair, foo);
    }

    // проверяет, есть ли реализация мультиметода
    // для типов объектов a и b
    bool hasImpl(Base * a, Base * b) const
    {
        std::pair<std::type_index, std::type_index> pair_A =
        std::make_pair(std::type_index(typeid(*a)),
                       std::type_index(typeid(*b)));


        if(Commutative) {
            std::pair<std::type_index, std::type_index> pair_B =
            std::make_pair(std::type_index(typeid(*b)),
                           std::type_index(typeid(*a)));

            if(m_fooContainer.find(pair_A) != m_fooContainer.end() ||
               m_fooContainer.find(pair_B) != m_fooContainer.end()) {
                return true;
            }
            return false;
        }
        if(m_fooContainer.find(pair_A) != m_fooContainer.end()){
            return true;
        }
        return false;
        // здесь проверить на комутативность. если ЕСТЬ пара нужная, то збс, если нет, то нет
        // возвращает true, если реализация есть
        // если операция коммутативная, то нужно
        // проверить есть ли реализация для b и а
    }

    // Применяет мультиметод к объектам
    // по указателям a и b
    Result call(Base * a, Base * b) const
    {
        std::pair<std::type_index, std::type_index> pair_A =
        std::make_pair(std::type_index(typeid(*a)),
                       std::type_index(typeid(*b)));


        std::pair<std::type_index, std::type_index> pair_B =
        std::make_pair(std::type_index(typeid(*b)),
                       std::type_index(typeid(*a)));

        if(m_fooContainer.find(pair_A) != m_fooContainer.end()) {
            return m_fooContainer.at(pair_A)(a, b);
        } else if (m_fooContainer.find(pair_B) != m_fooContainer.end() && Commutative) {
            return m_fooContainer.at(pair_B)(b, a);
        }
        // возвращает результат применения реализации
        // мультиметод
    }

private:
    std::map<std::pair<std::type_index, std::type_index>, std::function<Result(Base*, Base*)>> m_fooContainer;

    //Result (*)(Base* a, Base* b)
    //std::function<Result(Base* a, Base* b)>
};
