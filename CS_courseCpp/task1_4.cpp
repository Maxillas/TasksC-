#include <typeinfo>
#include <iostream>

/* 1.4.4 */
/* Вам требуется реализовать функцию, которая принимает на вход два указателя на базовый класс Expression, и возвращает true, если оба указателя указывают на самом деле на объекты одного и того же класса, и false в противном случае (т.е. если оба указателя указывают на BinaryOperation, то возвращается true, а если один из них указывает на Number, а второй на BinaryOperation, то false).

Реализуйте её при помощи typeid.

Требования к реализации: Использовать dynamic_cast и вызывать методы по переданным указателям запрещено.
*/

class Expression{};

bool check_equals(Expression const *left, Expression const *right)
{
    if(typeid(*left) == typeid(*right)) {
        return true;
    }
    return false;
}

/* 1.4.7 */
/* Предположим, что вам даётся два указателя на объект некоторого сложного полиморфного класса, который использует множественное наследование. Оба указателя имеют один и тот же тип, но могут ссылаться на разные однотипные базы внутри одного объекта.

Напишите шаблонную функцию, которая по двум однотипным указателям проверяет, указывают ли они на один объект.
*/

template<class T>
bool isSameObject(T const * p, T const * q)
{
    if (dynamic_cast<void const *>(p) == dynamic_cast<void const *>(q)) {
        return true;
    }
    return false;
}
