#include <iostream>
#include <list>

// так как в задании не указан тип элементов,
// которые хранятся в списке, то давайте сделаем
// эту функцию шаблонной
// Параметр It — это тип итератора
template<class It>
size_t max_increasing_len(It p, It q)
{
    int maxLenght = 0;
    int count = 1;
    auto prev = p;
    for (; p != q; ++p){
        if (*p > *prev) {
            prev = p;
            count++;
            if (count > maxLenght) {
                maxLenght = count;
            }
            continue;
        }
        if (count > maxLenght) {
            maxLenght = count;
        }
        prev = p;
        count = 1;
    }
    return maxLenght;
}

