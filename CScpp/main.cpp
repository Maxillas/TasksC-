#include <iostream>

using namespace std;

/* ***************** */
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

/* ***************** */
/* 1.2 step 10 */
struct Unit
{
    explicit Unit(size_t id)
        : id_(id)
    {}

    size_t id() const { return id_; }

private:
    size_t id_;
};

// базовый класс для животных
struct Animal : virtual Unit
{
    // name хранит название животного
    // "bear" для медведя
    // "pig" для свиньи
    Animal(std::string const & name, size_t id)
        : Unit(id)
        , name_(name) {}

    std::string const& name() const { return name_; }
private:
    std::string name_;
};

// класс для человека
struct Man : virtual Unit
{
    explicit Man(size_t id)
        : Unit(id) {}
};

// класс для медведя
struct Bear : Animal
{
    explicit Bear(size_t id)
        : Unit(id)
        , Animal("bear", id) {}
};

// класс для свиньи
struct Pig : Animal
{
    explicit Pig(size_t id)
        : Unit(id)
        , Animal("pig", id) {}
};

// класс для челмедведосвина
struct ManBearPig : Man, Bear, Pig
{
    ManBearPig(size_t id)
        : Unit(id)
        , Man(id)
        , Bear(id)
        , Pig(id) {}

};
/* end */

int main()
{
    Base * base = new D1;
    D1BaseToD2Base(base);
    delete base;
    return 0;
}
