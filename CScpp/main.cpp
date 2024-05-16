#include "task1_2_4.cpp"
#include "task1_2_10.cpp"

using namespace std;

void * foog(size_t a, char const* b) {return 0;};

int main()
{
    Base * base = new D1;
    D1BaseToD2Base(base);
    delete base;

    auto *f = &foog;


    std::cout << typeid(foog).name();




    return 0;
}

