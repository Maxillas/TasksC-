#include "task1_2_4.cpp"
#include "task1_2_10.cpp"
#include "task2_1.cpp"
#include "task3_2.cpp"
#include "task3_3.cpp"

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
    return 0;
}

