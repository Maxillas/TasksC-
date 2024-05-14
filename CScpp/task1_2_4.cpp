/* *****************
Вам дана следующая иерархия классов:

struct Base { ... };

struct D1 : Base { ... };

struct D2 : Base { ... };

struct D3 : D1, D2 { ... };

Напишите функцию D1BaseToD2Base, которая преобразует указатель типа Base на объект типа D3, который ссылается на экземпляр Base, соответствующий D1, в указатель, ссылающийся на экземпляр Base соответствующий D2.
*/

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
