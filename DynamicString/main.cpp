#include <iostream>
#include <cstring>
#include <set>

class String
{
public:

    //конструктор
    String(const char *str = "") :
        m_size(strlen(str)),
        m_pstr(new char[m_size + 1])
    {
        strncpy(m_pstr, str, m_size + 1);
    };

    //конструктор копирования
    String(const String& otherStr) :
        m_size(otherStr.m_size),
        m_pstr(new char[m_size + 1])
    {
        strncpy(m_pstr, otherStr.m_pstr, m_size + 1);
    };

    //деструктор
    ~String() {
        delete[] m_pstr;
    }

    //конструктор перемещения
    String(String&& otherStr) :
        String()
    {
        std::swap(m_pstr, otherStr.m_pstr);
        std::swap(m_size, otherStr.m_size);
    };

    //оператор присваивания String
    String& operator= (const String& otherStr) {
        if(this == &otherStr) {return *this;}
        delete [] this->m_pstr;
        m_size = otherStr.m_size;
        m_pstr = new char[m_size + 1];
        strncpy(m_pstr, otherStr.m_pstr, m_size + 1);
        return *this;
    };

    //перемещающий оператор присваивания
    String& operator= (String&& otherStr) {
        if(this == &otherStr) {return *this;}
        std::swap(m_pstr, otherStr.m_pstr);
        std::swap(m_size, otherStr.m_size);
        return *this;
    };

    //оператор присваивания char*
    String& operator= (const char* otherStr) {
        if(m_pstr == otherStr) {return *this;}
        delete [] this->m_pstr;
        m_size = strlen(otherStr);
        m_pstr = new char[m_size + 1];
        strncpy(m_pstr, otherStr, m_size + 1);
        return *this;
    };

    //оператор += String
    String& operator+= (const String& otherStr) {
        size_t newSize = m_size + otherStr.m_size;
        char* newStr = new char[newSize + 1];
        std::strncpy(newStr, m_pstr, m_size);
        std::strncat(newStr, otherStr.m_pstr, otherStr.m_size + 1);

        delete[] m_pstr;
        m_pstr = newStr;
        m_size = newSize;

        return *this;
    };

    //оператор += char*
    String& operator+= (const char* otherStr) {
        size_t newSize = m_size + strlen(otherStr);
        char* newStr = new char[newSize + 1];
        std::strncpy(newStr, m_pstr, m_size);
        std::strncat(newStr, otherStr, strlen(otherStr) + 1);

        delete[] m_pstr;
        m_pstr = newStr;
        m_size = newSize;

        return *this;
    };

    //оператор + String
    String operator+ (const String& otherStr) const {
        size_t newSize = m_size + otherStr.m_size;
        char* newStr = new char[newSize + 1];

        std::strncpy(newStr, m_pstr, m_size);
        std::strncat(newStr, otherStr.m_pstr, otherStr.m_size + 1);

        String result(newStr);
        delete[] newStr;
        return result;
    };

    //оператор + char*
    String operator+ (const char* otherStr) const {
        size_t newSize = m_size + strlen(otherStr);
        char* newStr = new char[newSize + 1];

        std::strncpy(newStr, m_pstr, m_size);
        std::strncat(newStr, otherStr, strlen(otherStr) + 1);

        String result(newStr);
        delete[] newStr;
        return result;
    };

    //оператор >
    bool operator> (const String& otherStr) const {
        return std::tolower(*m_pstr) > std::tolower(*otherStr.m_pstr);
    };

    void print() const {
        for(size_t i = 0; i < m_size; ++i) {
            std::cout << m_pstr[i];
        }
        std::cout << std::endl;
    }


private:
    size_t m_size;
    char *m_pstr;


};


int main()
{
    size_t count = 0;
    std::cout << "Введите количество строк" << std::endl;
    std::cin >> count;

    std::multiset<String, std::greater<String>> container;
    size_t maxLengh = 100;

    for (size_t i = 0; i != count; ++i) {
        std::cout << "Введите строку" << std::endl;
        char inputStr[maxLengh];
        std::cin >> inputStr;
        String str(inputStr);
        container.emplace(str);
    }

    std::cout << "Результат: " << container.size() << std::endl;
    for (auto it = container.begin(); it != container.end(); ++it) {
        (*it).print();
    }

    return 0;
}
