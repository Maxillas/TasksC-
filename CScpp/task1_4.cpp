#include <typeinfo>
#include <iostream>

/* 1.4.4 */
class Expression{};

bool check_equals(Expression const *left, Expression const *right)
{
    if(typeid(*left) == typeid(*right)) {
        return true;
    }
    return false;
}

/* 1.4.7 */

template<class T>
bool isSameObject(T const * p, T const * q)
{
    if (dynamic_cast<void const *>(p) == dynamic_cast<void const *>(q)) {
        return true;
    }
    return false;
}
