#include <string>
#include <sstream>
#include <exception>
class bad_from_string : public std::exception
{
    std::string info;
public:
    bad_from_string(std::string e ="from_string except") : info(e){}
    const char* what() const noexcept{
        return info.c_str();
    }
};

// функция from_string
template<class T>
T from_string(std::string const& s)
{
    std::istringstream is(s);
        T t;
        is >> std::noskipws >> t;
        if (is.fail())
            throw bad_from_string("conversion error");
        is.get();
        if(is.good())
            throw bad_from_string("conversion error");
        return t;
}

