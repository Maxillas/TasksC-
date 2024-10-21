#include <iostream>
#include <algorithm>

// алгоритм должен работать с forward итераторами
// и возвращать итератор, который потом будет передан
// в метод erase соответствующего контейнера
template<class FwdIt>
FwdIt remove_nth(FwdIt p, FwdIt q, size_t n)
{
    auto a = std::distance(p,q);

    if((a == 1 && n == 0)) {
        return p;
    }
    if (n >= a || a == 0) {
        return q;
    }
    int i = 0;
    FwdIt it = p;
    FwdIt output;
   // FwdIt itEnd = q;
    while (i != n) {
        it++;
        i++;
    }
    for(; it != q; ++it) {
        FwdIt nextIt = std::next(it);
        if (nextIt == q) {
            return it;
        }
        std::swap(*it, *nextIt);

    }
    return output;
}





//Напишите алгоритм remove_nth, который удаляет элемент из последовательности по номеру этого элемента.
