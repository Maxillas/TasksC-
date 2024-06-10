#include <iostream>
#include <algorithm>

// алгоритм должен работать с forward итераторами
// и возвращать итератор, который потом будет передан
// в метод erase соответствующего контейнера
template<class FwdIt>
FwdIt remove_nth(FwdIt p, FwdIt q, size_t n)
{

    if(std::distance(p,q) <= 1 || std::distance(p,q) < n)
        return q;

    int i = 0;
    FwdIt it = p;
    FwdIt output;
    //FwdIt itEnd = q;
    while (i != n) {
        it++;
        i++;
    }
    for(; it != q; ++it) {
        FwdIt nextIt = std::next(it, 1);
        std::swap(*it, *nextIt);
        if (nextIt == q) {
            output = it;
        }
    }

    return output;
}





//Напишите алгоритм remove_nth, который удаляет элемент из последовательности по номеру этого элемента.
