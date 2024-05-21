/*
Дополните класс Array перемещающим конструктором и перемещающим оператором присваивания.

Замечание: все объявленные методы класса Array уже реализованы.
*/

#include <iostream>
#include <utility>

template<class T>
struct Array
{
    // все объявленные ниже методы уже реализованы
    explicit Array(size_t size = 0);
    Array(Array const& a);
    Array & operator=(Array const& a);
    ~Array();

    size_t size() const;
    T &         operator[](size_t i);
    T const&    operator[](size_t i) const;

    void swap(Array & ar){
        std::swap(data_, ar.data_);
        std::swap(size_, ar.size_);
    }
    // реализуйте перемещающий конструктор
    Array(Array && ar) : Array() {
        swap(ar);
    }
    // реализуйте перемещающий оператор присваивания
    Array & operator = (Array && ar) {
        swap(ar);
        return *this;
    }


private:
    size_t  size_;
    T *     data_;
};

