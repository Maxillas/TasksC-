#include "task1_2_4.cpp"
#include "task1_2_10.cpp"

using namespace std;

int main()
{
    Base * base = new D1;
    D1BaseToD2Base(base);
    delete base;
    return 0;
}
