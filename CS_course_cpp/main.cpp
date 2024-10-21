#include "task1_2_4.cpp"
#include "task1_2_10.cpp"
#include "task2_1.cpp"
#include "task3_2.cpp"
#include "task3_3.cpp"
#include "task3_4.cpp"
#include "task3_5.cpp"

#include <cassert>
#include <iostream>
#include <cstdint>


using namespace std;

void * foog(size_t a, char const* b) {return 0;};

/* Write your code here */



struct Shape {
    int32_t shape_;
    constexpr Shape(int32_t shape) : shape_(shape) {}
    virtual int32_t shapenum() { return this->shape_; };
    virtual ~Shape() = default;
};

struct Point {
    double x_;
    double y_;
    constexpr Point(double x, double y) : x_(x), y_(y) {}
};


struct Rectangle : Shape {
    Point leftbottom_, righttop_;
    constexpr Rectangle(double x1 = 0, double y1 = 0, double x2 = 1, double y2 = 1)
        : Shape(4), leftbottom_(x1, y1), righttop_(x2, y2) {};
};


struct Triangle : Shape {
    Point first_, second_, third_;
    constexpr Triangle(double x1 = 0, double y1 = 0, double x2 = 6, double y2 = 6, double x3 = 12, double y3 = 0)
        : Shape(3), first_(x1, y1), second_(x2, y2), third_(x3, y3) {}

};

bool is_both_same_shape(Shape* a, Shape* b) {
    return( a->shapenum() == b->shapenum()) ? true : false;
}


bool is_both_rectangle(Shape* a, Shape* b) {
    return (a->shapenum() == 4 && b->shapenum() == 4) ? true : false;
}

bool is_both_triangle(Shape* a, Shape* b) {
    return (a->shapenum() == 3 && b->shapenum() == 3 )? true : false;
}

bool is_first_triangle_second_rectangle(Shape* a, Shape* b) {
    return ((a->shapenum() == 3) && (b->shapenum() == 4)) ? true : false;
}

bool is_first_rectangle_second_triangle(Shape* a, Shape* b) {
    return (a->shapenum() == 4 && b->shapenum() == 3 )? true : false;
}


bool is_one_triangle_another_rectangle(Shape* a, Shape* b) {
    return ((a->shapenum() == 3 && b->shapenum() == 4) || ( a->shapenum() == 4 && b->shapenum() == 3 )) ? true : false;
}

bool test_defaultctor() {
    std::cout << __FUNCTION__ << " result: ";
    Shape* trg = static_cast<Shape*>(new Triangle());
    Shape* rct = static_cast<Shape*>(new Rectangle());
    delete trg;
    delete rct;
    return true;
}





bool test_multimethod_comm_one_triangle_another_rectangle() {

    std::cout << __FUNCTION__ << ' ';
    Multimethod2<Shape, bool, true> multimethod_obj;

    multimethod_obj.addImpl(typeid(Rectangle), typeid(Triangle), is_one_triangle_another_rectangle);


    Shape* s1 = new Triangle();
    Shape* s2 = new Rectangle();


    bool is_done[4] = { false,false,false,false };
    bool res[4] = { false, false, false, false };
    if (multimethod_obj.hasImpl(s1, s1))
    {

        res[0] = false; res[0]  = multimethod_obj.call(s1, s1);

        is_done[0] = true;

    }
    std::cout << std::endl << '\t' << "Triangle  &  Triangle: " << multimethod_obj.hasImpl(s1, s1) << " ;is called: "  << is_done[0] << " ;result: " << res[0] << std::endl;
    if (multimethod_obj.hasImpl(s1, s2))
    {

        res[1] = false; res[1]  = multimethod_obj.call(s1, s2);

        is_done[1] = true;

    }
    std::cout << '\t' << "Triangle  & Rectangle: " << multimethod_obj.hasImpl(s1, s2) << " ;is called: "  << is_done[1] << " ;result: " << res[1] << std::endl;
    if (multimethod_obj.hasImpl(s2, s1))
    {

        res[2] = false; res[2]  = multimethod_obj.call(s2, s1);

        is_done[2] = true;

    }
    std::cout << '\t' << "Rectangle &  Triangle: " << multimethod_obj.hasImpl(s2, s1) << " ;is called: " << is_done[2] << " ;result: " << res[2] << std::endl;
    if (multimethod_obj.hasImpl(s2, s2))
    {

        res[3] = false; res[3]= multimethod_obj.call(s2, s2);

        is_done[3] = true;

    }
    std::cout << '\t' << "Rectangle & Rectangle: " << multimethod_obj.hasImpl(s2, s2) << " ;is called: " << is_done[3] << " ;result: " << res[3] << std::endl;
    delete s1;
    delete s2;
    return !is_done[0] && is_done[1] && is_done[2] && !is_done[3] && !res[0] && res[1] && res[2] && !res[3];
}

bool test_multimethod_comm_first_triangle_second_rectangle() {

    std::cout << __FUNCTION__ << ' ';
    Multimethod2<Shape, bool, true> multimethod_obj;
    auto a_foo_stdfunction = std::function<bool(Shape*, Shape*)>(is_first_triangle_second_rectangle);


    multimethod_obj.addImpl(typeid(Rectangle), typeid(Triangle), a_foo_stdfunction);


    Shape* s1 = new Triangle();
    Shape* s2 = new Rectangle();


    bool is_done[4] = { false,false,false,false };
    bool res[4] = { false, false, false, false };
    if (multimethod_obj.hasImpl(s1, s1))
    {

        res[0] = false; res[0] = multimethod_obj.call(s1, s1);

        is_done[0] = true;

    }
    std::cout << std::endl << '\t' << "Triangle  &  Triangle: " << multimethod_obj.hasImpl(s1, s1) << " ;is called: " << is_done[0] << " ;result: " << res[0] << std::endl;
    if (multimethod_obj.hasImpl(s1, s2))
    {

        res[1] = false; res[1] = multimethod_obj.call(s1, s2);

        is_done[1] = true;

    }
    std::cout << '\t' << "Triangle  & Rectangle: " << multimethod_obj.hasImpl(s1, s2) << " ;is called: " << is_done[1] << " ;result: " << res[1] << std::endl;
    if (multimethod_obj.hasImpl(s2, s1))
    {

        res[2] = false; res[2] = multimethod_obj.call(s2, s1);

        is_done[2] = true;

    }
    std::cout << '\t' << "Rectangle &  Triangle: " << multimethod_obj.hasImpl(s2, s1) << " ;is called: " << is_done[2] << " ;result: " << res[2] << std::endl;
    if (multimethod_obj.hasImpl(s2, s2))
    {

        res[3] = false; res[3] = multimethod_obj.call(s2, s2);

        is_done[3] = true;

    }
    std::cout << '\t' << "Rectangle & Rectangle: " << multimethod_obj.hasImpl(s2, s2) << " ;is called: " << is_done[3] << " ;result: " << res[3] << std::endl;
    delete s1;
    delete s2;
    return !is_done[0] && is_done[1] && is_done[2] && !is_done[3] && !res[0] && !res[1] && !res[2] && !res[3];
}

bool test_multimethod_comm_both_rectangle() {

    std::cout << __FUNCTION__ << ' ';
    Multimethod2<Shape, bool, true> multimethod_obj;

    multimethod_obj.addImpl(typeid(Rectangle), typeid(Rectangle), is_both_rectangle);

    Shape* s1 = new Triangle();
    Shape* s2 = new Rectangle();

    bool is_done[4] = { false,false,false,false };
    bool res[4] = { false, false, false, false };
    if (multimethod_obj.hasImpl(s1, s1))
    {

        res[0] = false; res[0] = multimethod_obj.call(s1, s1);

        is_done[0] = true;

    }
    std::cout << std::endl << '\t' << "Triangle  &  Triangle: " << multimethod_obj.hasImpl(s1, s1) << " ;is called: " << is_done[0] << " ;result: " << res[0] << std::endl;
    if (multimethod_obj.hasImpl(s1, s2))
    {

        res[1] = false; res[1] = multimethod_obj.call(s1, s2);

        is_done[1] = true;

    }
    std::cout << '\t' << "Triangle  & Rectangle: " << multimethod_obj.hasImpl(s1, s2) << " ;is called: " << is_done[1] << " ;result: " << res[1] << std::endl;
    if (multimethod_obj.hasImpl(s2, s1))
    {

        res[2] = false; res[2] = multimethod_obj.call(s2, s1);

        is_done[2] = true;

    }
    std::cout << '\t' << "Rectangle &  Triangle: " << multimethod_obj.hasImpl(s2, s1) << " ;is called: " << is_done[2] << " ;result: " << res[2] << std::endl;
    if (multimethod_obj.hasImpl(s2, s2))
    {

        res[3] = false; res[3] = multimethod_obj.call(s2, s2);

        is_done[3] = true;

    }
    std::cout << '\t' << "Rectangle & Rectangle: " << multimethod_obj.hasImpl(s2, s2) << " ;is called: " << is_done[3] << " ;result: " << res[3] << std::endl;
    delete s1;
    delete s2;
    return !is_done[0] && !is_done[1] && !is_done[2] && is_done[3] && !res[0] && !res[1] && !res[2] && res[3];
}

bool test_multimethod_noncomm_both_rectangle() {

    std::cout << __FUNCTION__ << ' ';
    Multimethod2<Shape, bool, false> multimethod_obj;

    multimethod_obj.addImpl(typeid(Rectangle), typeid(Rectangle), is_both_rectangle);

    Shape* s1 = new Triangle();
    Shape* s2 = new Rectangle();


    bool is_done[4] = { false,false,false,false };
    bool res[4] = { false, false, false, false };
    if (multimethod_obj.hasImpl(s1, s1))
    {

        res[0] = false; res[0] = multimethod_obj.call(s1, s1);

        is_done[0] = true;

    }
    std::cout << std::endl << '\t' << "Triangle  &  Triangle: " << multimethod_obj.hasImpl(s1, s1) << " ;is called: " << is_done[0] << " ;result: " << res[0] << std::endl;
    if (multimethod_obj.hasImpl(s1, s2))
    {

        res[1] = false; res[1] = multimethod_obj.call(s1, s2);

        is_done[1] = true;

    }
    std::cout << '\t' << "Triangle  & Rectangle: " << multimethod_obj.hasImpl(s1, s2) << " ;is called: " << is_done[1] << " ;result: " << res[1] << std::endl;
    if (multimethod_obj.hasImpl(s2, s1))
    {

        res[2] = false; res[2] = multimethod_obj.call(s2, s1);

        is_done[2] = true;

    }
    std::cout << '\t' << "Rectangle &  Triangle: " << multimethod_obj.hasImpl(s2, s1) << " ;is called: " << is_done[2] << " ;result: " << res[2] << std::endl;
    if (multimethod_obj.hasImpl(s2, s2))
    {

        res[3] = false; res[3] = multimethod_obj.call(s2, s2);

        is_done[3] = true;

    }
    std::cout << '\t' << "Rectangle & Rectangle: " << multimethod_obj.hasImpl(s2, s2) << " ;is called: " << is_done[3] << " ;result: " << res[3] << std::endl;
    delete s1;
    delete s2;
    return !is_done[0] && !is_done[1] && !is_done[2] && is_done[3] && !res[0] && !res[1] && !res[2] && res[3];
}

bool test_multimethod_noncomm_first_rectangle_second_triangle_twoinjections() {

    std::cout << __FUNCTION__ << ' ';
    Multimethod2<Shape, bool, false> multimethod_obj;



    multimethod_obj.addImpl(typeid(Triangle), typeid(Rectangle), is_first_rectangle_second_triangle);
    multimethod_obj.addImpl(typeid(Rectangle), typeid(Triangle), is_first_rectangle_second_triangle);

    Shape* s1 = new Triangle();
    Shape* s2 = new Rectangle();


    bool is_done[4] = { false,false,false,false };
    bool res[4] = { false, false, false, false };
    if (multimethod_obj.hasImpl(s1, s1))
    {

        res[0] = false; res[0] = multimethod_obj.call(s1, s1);

        is_done[0] = true;

    }
    std::cout << std::endl << '\t' << "Triangle  &  Triangle: " << multimethod_obj.hasImpl(s1, s1) << " ;is called: " << is_done[0] << " ;result: " << res[0] << std::endl;
    if (multimethod_obj.hasImpl(s1, s2))
    {

        res[1] = false; res[1] = multimethod_obj.call(s1, s2);

        is_done[1] = true;

    }
    std::cout << '\t' << "Triangle  & Rectangle: " << multimethod_obj.hasImpl(s1, s2) << " ;is called: " << is_done[1] << " ;result: " << res[1] << std::endl;
    if (multimethod_obj.hasImpl(s2, s1))
    {

        res[2] = false; res[2] = multimethod_obj.call(s2, s1);

        is_done[2] = true;

    }
    std::cout << '\t' << "Rectangle &  Triangle: " << multimethod_obj.hasImpl(s2, s1) << " ;is called: " << is_done[2] << " ;result: " << res[2] << std::endl;
    if (multimethod_obj.hasImpl(s2, s2))
    {

        res[3] = false; res[3] = multimethod_obj.call(s2, s2);

        is_done[3] = true;

    }
    std::cout << '\t' << "Rectangle & Rectangle: " << multimethod_obj.hasImpl(s2, s2) << " ;is called: " << is_done[3] << " ;result: " << res[3] << std::endl;
    delete s1;
    delete s2;
    return !is_done[0] && is_done[1] && is_done[2] && !is_done[3] && !res[0] && !res[1] && res[2] && !res[3];
}

bool test_multimethod_noncomm_first_rectangle_second_triangle() {

    std::cout << __FUNCTION__ << ' ';
    Multimethod2<Shape, bool, false> multimethod_obj;


    multimethod_obj.addImpl(typeid(Rectangle), typeid(Triangle), is_first_rectangle_second_triangle);

    Shape* s1 = new Triangle();
    Shape* s2 = new Rectangle();

    bool is_done[4] = { false,false,false,false };
    bool res[4] = { false, false, false, false };
    if (multimethod_obj.hasImpl(s1, s1))
    {

        res[0] = false; res[0] = multimethod_obj.call(s1, s1);

        is_done[0] = true;

    }
    std::cout << std::endl << '\t' << "Triangle  &  Triangle: " << multimethod_obj.hasImpl(s1, s1) << " ;is called: " << is_done[0] << " ;result: " << res[0] << std::endl;
    if (multimethod_obj.hasImpl(s1, s2))
    {

        res[1] = false; res[1] = multimethod_obj.call(s1, s2);

        is_done[1] = true;

    }
    std::cout << '\t' << "Triangle  & Rectangle: " << multimethod_obj.hasImpl(s1, s2) << " ;is called: " << is_done[1] << " ;result: " << res[1] << std::endl;
    if (multimethod_obj.hasImpl(s2, s1))
    {

        res[2] = false; res[2] = multimethod_obj.call(s2, s1);

        is_done[2] = true;

    }
    std::cout << '\t' << "Rectangle &  Triangle: " << multimethod_obj.hasImpl(s2, s1) << " ;is called: " << is_done[2] << " ;result: " << res[2] << std::endl;
    if (multimethod_obj.hasImpl(s2, s2))
    {

        res[3] = false; res[3] = multimethod_obj.call(s2, s2);

        is_done[3] = true;

    }
    std::cout << '\t' << "Rectangle & Rectangle: " << multimethod_obj.hasImpl(s2, s2) << " ;is called: " << is_done[3] << " ;result: " << res[3] << std::endl;
    delete s1;
    delete s2;
    return !is_done[0] && !is_done[1] && is_done[2] && !is_done[3] && !res[0] && !res[1] && res[2] && !res[3];
}

bool test_multimethod_comm_first_triangle_second_rectangleAND_first_rectangle_second_triangle() {

    std::cout << __FUNCTION__ << ' ';
    Multimethod2<Shape, bool, true> multimethod_obj;

    multimethod_obj.addImpl(typeid(Triangle), typeid(Rectangle), is_first_triangle_second_rectangle);
    multimethod_obj.addImpl(typeid(Rectangle), typeid(Triangle), is_first_rectangle_second_triangle);

    Shape* s1 = new Triangle();
    Shape* s2 = new Rectangle();

    bool is_done[4] = { false,false,false,false };
    bool res[4] = { false, false, false, false };
    if (multimethod_obj.hasImpl(s1, s1))
    {

        res[0] = false; res[0] = multimethod_obj.call(s1, s1);

        is_done[0] = true;

    }
    std::cout << std::endl << '\t' << "Triangle  &  Triangle: " << multimethod_obj.hasImpl(s1, s1) << " ;is called: " << is_done[0] << " ;result: " << res[0] << std::endl;
    if (multimethod_obj.hasImpl(s1, s2))
    {

        res[1] = false; res[1] = multimethod_obj.call(s1, s2);

        is_done[1] = true;

    }
    std::cout << '\t' << "Triangle  & Rectangle: " << multimethod_obj.hasImpl(s1, s2) << " ;is called: " << is_done[1] << " ;result: " << res[1] << std::endl;
    if (multimethod_obj.hasImpl(s2, s1))
    {

        res[2] = false; res[2] = multimethod_obj.call(s2, s1);

        is_done[2] = true;

    }
    std::cout << '\t' << "Rectangle &  Triangle: " << multimethod_obj.hasImpl(s2, s1) << " ;is called: " << is_done[2] << " ;result: " << res[2] << std::endl;
    if (multimethod_obj.hasImpl(s2, s2))
    {

        res[3] = false; res[3] = multimethod_obj.call(s2, s2);

        is_done[3] = true;

    }
    std::cout << '\t' << "Rectangle & Rectangle: " << multimethod_obj.hasImpl(s2, s2) << " ;is called: " << is_done[3] << " ;result: " << res[3] << std::endl;
    delete s1;
    delete s2;
    return !is_done[0] && is_done[1] && is_done[2] && !is_done[3] && !res[0] && res[1] && res[2] && !res[3];
}


int main() {
    //std::cout << test_defaultctor() << std::endl;
    std::cout << "Is it has to be like this: " << test_multimethod_comm_one_triangle_another_rectangle() << std::endl << std::endl;
    std::cout << "Is it has to be like this: " << test_multimethod_comm_first_triangle_second_rectangle() << std::endl << std::endl;
    std::cout << "Is it has to be like this: " << test_multimethod_comm_both_rectangle() << std::endl << std::endl;
    std::cout << "Is it has to be like this: " << test_multimethod_noncomm_both_rectangle() << std::endl << std::endl;
    std::cout << "Is it has to be like this: " << test_multimethod_noncomm_first_rectangle_second_triangle_twoinjections() << std::endl << std::endl;
    std::cout << "Is it has to be like this: " << test_multimethod_noncomm_first_rectangle_second_triangle() << std::endl << std::endl;
    std::cout << std::endl << "check order test, because test on the site guessed only one implementation, and guess, that you can have different functions for different shape even with commutative." << std::endl;
    std::cout << "Is it has to be like this: " << test_multimethod_comm_first_triangle_second_rectangleAND_first_rectangle_second_triangle() << std::endl << std::endl;

    std::cout << "ended" << std::endl;

    std::cout << "_________________________________" << std::endl;


#if 1

    const VectorList<int> check_const_compile;
    auto check_const_equals_compile = check_const_compile.begin();

    VectorList<std::vector<int>> check_arrow_vl;
    std::vector<int> vint1 = {1, 2, 3};
    std::vector<int> vint2 = {4, 5, 6};
    std::vector<std::vector<int>> vecs;
    vecs.push_back(vint1);
    vecs.push_back(vint2);
    check_arrow_vl.append(vecs.begin(), vecs.end());
    auto it_f = check_arrow_vl.begin();
    assert(it_f->size() == 3);
#endif

#if 1
    VectorList<char> vec_list;

    std::vector<char> v1;
    v1.push_back('A');
    v1.push_back('B');
    v1.push_back('C');
    vec_list.append(v1.begin(), v1.end());
    assert(std::distance(v1.begin(), v1.end()) == 3);
    std::cout << "vec elem = " << *(--(v1.end())) << std::endl;

    std::vector<char> v2;
    v2.push_back('D');
    v2.push_back('E');
    v2.push_back('F');
    v2.push_back('G');
    vec_list.append(v2.begin(), v2.end());

    // assert(vec_list.size() == 7);
    // std::cout << "begin = " << *((vec_list.begin())) << std::endl;
    // auto ggg = --vec_list.end();
    // std::cout << "USUKA BLA 5" << std::endl;
    // std::cout << "end = " << *(ggg) << std::endl;

    // for (auto it = vec_list.begin(); it != vec_list.end(); ++it) {
    //     std::cout << *it << std::endl;
    // }
    // for (auto a = vec_list.begin(); a != vec_list.end(); a++) {
    //     std::cout << "222222" << std::endl;
    // }
    // std::cout << "AUF  = " << std::distance(vec_list.begin(), vec_list.end()) << std::endl;


    assert(std::distance(vec_list.begin(), vec_list.end()) == 7);


    auto ra = vec_list.rbegin();
    ++ra;
    ++ra;
    auto a = ra.base();
#endif

#if 1
    auto it = vec_list.begin();
    assert(*it == 'A'); ++it;
    assert(*it == 'B'); ++it;
    assert(*it == 'C'); ++it;
    assert(*it == 'D'); ++it;
    assert(*it == 'E'); ++it;
    assert(*it == 'F'); ++it;
    assert(*it == 'G'); ++it;
    assert(it == vec_list.end());
#endif

#if 1
    it = vec_list.begin();
    assert(*it == 'A'); it++;
    assert(*it == 'B'); it++;
    assert(*it == 'C'); it++;
    assert(*it == 'D'); it++;
    assert(*it == 'E'); it++;
    assert(*it == 'F'); it++;
    assert(*it == 'G'); it++;
    assert(it == vec_list.end());
#endif

#if 1
    it = vec_list.end(); --it;
    assert(*it == 'G'); --it;
    assert(*it == 'F'); --it;
    assert(*it == 'E'); --it;
    assert(*it == 'D'); --it;
    assert(*it == 'C'); --it;
    assert(*it == 'B'); --it;
    assert(*it == 'A');
    assert(it == vec_list.begin());
#endif

#if 1
    it = vec_list.end(); it--;
    assert(*it == 'G'); it--;
    assert(*it == 'F'); it--;
    assert(*it == 'E'); it--;
    assert(*it == 'D'); it--;
    assert(*it == 'C'); it--;
    assert(*it == 'B'); it--;
    assert(*it == 'A');
#endif

#if 1
    auto r_it = vec_list.rbegin();
    assert(*r_it == 'G'); ++r_it;
    assert(*r_it == 'F'); ++r_it;
    assert(*r_it == 'E'); ++r_it;
    assert(*r_it == 'D'); ++r_it;
    assert(*r_it == 'C'); ++r_it;
    assert(*r_it == 'B'); ++r_it;
    assert(*r_it == 'A'); ++r_it;
    assert(r_it == vec_list.rend());
#endif

#if 1
    r_it = vec_list.rbegin();
    assert(*r_it == 'G'); r_it++;
    assert(*r_it == 'F'); r_it++;
    assert(*r_it == 'E'); r_it++;
    assert(*r_it == 'D'); r_it++;
    assert(*r_it == 'C'); r_it++;
    assert(*r_it == 'B'); r_it++;
    assert(*r_it == 'A'); r_it++;
    assert(r_it == vec_list.rend());
#endif


#if 1
    r_it = vec_list.rend(); --r_it;
    assert(*r_it == 'A'); --r_it;
    assert(*r_it == 'B'); --r_it;
    assert(*r_it == 'C'); --r_it;
    assert(*r_it == 'D'); --r_it;
    assert(*r_it == 'E'); --r_it;
    assert(*r_it == 'F'); --r_it;
    assert(*r_it == 'G');
#endif

#if 1
    r_it = vec_list.rend(); r_it--;
    assert(*r_it == 'A'); r_it--;
    assert(*r_it == 'B'); r_it--;
    assert(*r_it == 'C'); r_it--;
    assert(*r_it == 'D'); r_it--;
    assert(*r_it == 'E'); r_it--;
    assert(*r_it == 'F'); r_it--;
    assert(*r_it == 'G');
#endif

// #if 1 //test convertations
//     it = vec_list.begin();
//     ++it;
//     ++it;
//     assert(*it == 'C');
//     r_it = it;
//     assert(*r_it == 'B');
//     auto new_it = r_it.base();
//     assert(*new_it == 'C');
// #endif

#if 1
    VectorList<char>::const_iterator def;
    auto dit = vec_list.end(); --dit;
    def = dit;

    VectorList<char>::const_reverse_iterator rdef;
    auto rdit = vec_list.rend(); --dit;
    rdef = rdit;
#endif

#if 1
    VectorList<int> check_empty;
    assert(check_empty.size() == 0);
    assert(check_empty.begin() == check_empty.end());
    assert(check_empty.rbegin() == check_empty.rend());
#endif

#if 1
    typedef VectorList<std::string> VL;

    static_assert(std::is_same<std::iterator_traits<VL::const_iterator>::reference, std::string const&>::value, "Incorrect iterator value_type");
    static_assert(std::is_same<std::iterator_traits<VL::const_iterator>::iterator_category, std::bidirectional_iterator_tag>::value, "FFF");
#endif

    // VectorList<int> vlist;
    // std::vector<int> v1 = {1,2,3};
    // std::vector<int> v2 = {4,5,6,7};

    // vlist.append(v1.begin(), v1.end());
    // vlist.append(v2.begin(), v2.end());

    // // vlist.begin() - указывает на первый элемент первого вектора, т.е. на цифру '1'
    // // --vlist.end() - указывает на последний элемент последнего вектора, т.е. на цифру '7'
    // // vlist.size() - вернет 7



    // auto A = vlist.begin();
    // auto B = &A;

    // bool result = (A.m_VectorIt == B->m_VectorIt);
    // std::cout << "Test * and -> = " << result << std::endl;
    // std::cout << std::endl;



    // std::cout << "size = " << vlist.size() << std::endl;
    // auto a = vlist.begin();
    // std::cout << "first element = " << *a << std::endl;
    // auto b = vlist.end();
    // std::cout << "last element = " << *(--b) << std::endl;

    // auto c = vlist.rbegin();
    // for (c; c != vlist.begin(); c++) {

    // }
    // std::cout << "first revers element = " << *c << std::endl;
    // // auto d = vlist.rend();
    // // std::cout << "last element = " << *b << std::endl;


    // std::cout << "Test ++i" << std::endl;
    // for (auto i = vlist.begin(); i != vlist.end(); ++i)
    //     std::cout << *i << " ";
    // std::cout << std::endl;
    // std::cout << std::endl;

    // std::cout << "Test i++" << std::endl;
    // for (auto i = vlist.begin(); i != vlist.end(); i++)
    //     std::cout << *i << " ";
    // std::cout << std::endl;
    // std::cout << std::endl;

    // // std::cout << "Test --i" << std::endl;
    // // for (auto i = vlist.end(); i != vlist.begin(); ){
    // //     std::cout << *--i << " ";
    // // }
    // // std::cout << std::endl;

    // std::cout << "Test i--" << std::endl;
    // for (auto i = vlist.end(); i != vlist.begin(); ) {
    //     i--;
    //     std::cout << *i << " ";
    // }

    // std::cout << std::endl;

    // std::cout << "Test --i" << std::endl;
    // for (auto i = vlist.end(); i != vlist.begin(); ) {
    //     std::cout << *--i << " ";
    // }

    // std::cout << std::endl;

    std::cout << "____________________" << std::endl;
    std::vector<int> v = {0,1,2,3,4,5,6,7,8,9,10};
    for(auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    v.erase(remove_nth(v.begin(), v.end(), 5), v.end());

    //remove_nth(v.begin(), v.end(), 5);

    for(auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    //теперь в v = {0,1,2,3,4,6,7,8,9,10};
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    {
        std::vector<int> v = {0,1,2,3,4,5,6,7,8,9,10};
        v.erase(remove_nth(v.begin(), v.end(), 5), v.end());
        std::cout << "Test #1 = 0 1 2 3 4 6 7 8 9 10" << std::endl;
        for(const auto& val : v) {
            std::cout << val << ' ';
        }
        std::cout << std::endl;
    }

    {
        std::vector<int> v = {};
        v.erase(remove_nth(v.begin(), v.end(), 5), v.end());
        std::cout << "Test #2 = []" << std::endl;
        for(const auto& val : v) {
            std::cout << val << ' ';
        }
        std::cout << std::endl;
    }

    {
        std::vector<int> v = {1};
        v.erase(remove_nth(v.begin(), v.end(), 5), v.end());
        std::cout << "Test #3 = 1" << std::endl;
        for(const auto& val : v) {
            std::cout << val << ' ';
        }
        std::cout << std::endl;
    }

    {
        std::vector<int> v = {1};
        v.erase(remove_nth(v.begin(), v.end(), 0), v.end());
        std::cout << "Test #4 = []" << std::endl;
        for(const auto& val : v) {
            std::cout << val << ' ';
        }
        std::cout << std::endl;
    }

    {
        std::vector<int> v = {1, 2};
        v.erase(remove_nth(v.begin(), v.end(), 5), v.end());
        std::cout << "Test #5 = [1, 2]" << std::endl;
        for(const auto& val : v) {
            std::cout << val << ' ';
        }
        std::cout << std::endl;
    }

    {
        std::vector<int> v = {1, 2};
        v.erase(remove_nth(v.begin(), v.end(), 0), v.end());
        std::cout << "Test #6 = [2]" << std::endl;
        for(const auto& val : v) {
            std::cout << val << ' ';
        }
        std::cout << std::endl;
    }

    {
        std::vector<int> v = {1, 2};
        v.erase(remove_nth(v.begin(), v.end(), 1), v.end());
        std::cout << "Test #7 = [1]" << std::endl;
        for(const auto& val : v) {
            std::cout << val << ' ';
        }
        std::cout << std::endl;
    }

    {
        std::vector<int> v = { 0,1,1,1,1,1,1,1,1,1 };
        v.erase(remove_nth(v.begin(), v.end(), 5), v.end());
        std::cout << "Test #8 = [1]" << std::endl;
        for(const auto& val : v) {
            std::cout << val << ' ';
        }
        std::cout << std::endl;
        v.erase(remove_nth(v.begin(), v.end(), 5), v.end());
        std::cout << "Test #9 = [1]" << std::endl;
        for(const auto& val : v) {
            std::cout << val << ' ';
        }
        std::cout << std::endl;
        v.erase(remove_nth(v.begin(), v.end(), 5), v.end());
        std::cout << "Test #10 = [1]" << std::endl;
        for(const auto& val : v) {
            std::cout << val << ' ';
        }
        std::cout << std::endl;
        v.erase(remove_nth(v.begin(), v.end(), 5), v.end());
        std::cout << "Test #11 = [1]" << std::endl;
        for(const auto& val : v) {
            std::cout << val << ' ';
        }
        std::cout << std::endl;
        v.erase(remove_nth(v.begin(), v.end(), 5), v.end());
        std::cout << "Test #12 = [1]" << std::endl;
        for(const auto& val : v) {
            std::cout << val << ' ';
        }
        std::cout << std::endl;
        v.erase(remove_nth(v.begin(), v.end(), 5), v.end());
        std::cout << "Test #13 = [1]" << std::endl;
        for(const auto& val : v) {
            std::cout << val << ' ';
        }
        std::cout << std::endl;

        v.erase(remove_nth(v.begin(), v.end(), 5), v.end());
        std::cout << "Test #14 = [1]" << std::endl;
        for(const auto& val : v) {
            std::cout << val << ' ';
        }
        std::cout << std::endl;

       // std::cout << "" << std::endl;
    {
//        std::vector<int> v{10,11,11,12,13,11,11,11,14};
//        v.erase(remove_nth(v.begin(), v.end(), 5), v.end());
//        std::cout << "Test #15 = [1]" << std::endl;
//        for(const auto& val : v) {
//            std::cout << val << ' ';
//        }
//        v.erase(remove_nth(v.begin(), v.end(), 5), v.end());
//        std::cout << "Test #16 = [1]" << std::endl;
//        for(const auto& val : v) {
//            std::cout << val << ' ';
//        }
//        v.erase(remove_nth(v.begin(), v.end(), 5), v.end());
//        std::cout << "Test #17 = [1]" << std::endl;
//        for(const auto& val : v) {
//            std::cout << val << ' ';
//        }
//        v.erase(remove_nth(v.begin(), v.end(), 5), v.end());
//        std::cout << "Test #18 = [1]" << std::endl;
//        for(const auto& val : v) {
//            std::cout << val << ' ';
//        }
//        v.erase(remove_nth(v.begin(), v.end(), 4), v.end());
//        std::cout << "Test #19 = [1]" << std::endl;
//        for(const auto& val : v) {
//            std::cout << val << ' ';
//        }
//        v.erase(remove_nth(v.begin(), v.end(), 0), v.end());
//        std::cout << "Test #20 = [1]" << std::endl;
//        for(const auto& val : v) {
//            std::cout << val << ' ';
//        }
//        v.erase(remove_nth(v.begin(), v.end(), 1), v.end());
//        std::cout << "Test #21 = [1]" << std::endl;
//        for(const auto& val : v) {
//            std::cout << val << ' ';
//        }
//        v.erase(remove_nth(v.begin(), v.end(), 1), v.end());
//        std::cout << "Test #22 = [1]" << std::endl;
//        for(const auto& val : v) {
//            std::cout << val << ' ';
//        }

    }

    }


    return 0;
}

