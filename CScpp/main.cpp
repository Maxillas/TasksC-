#include <iostream>

using namespace std;

/* 1.2 step 4 */
class Base {};
class D1 : public Base {};
class D2 : public Base {};
class D3 : public D1, public D2 {};

Base const * D1BaseToD2Base( Base const * base )
{
    D1 const* d1 = (D1 const*)base;
    D3 const* d3 = (D3 const*)d1;
    D2 const* d2 = (D2 const*)d3;
    return d2;
}
/* end */

int main()
{
    Base * base = new D1;
    D1BaseToD2Base(base);
    delete base;
    return 0;
}
