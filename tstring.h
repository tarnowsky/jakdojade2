#ifndef JAKDOJADE2_TSTRING_H
#define JAKDOJADE2_TSTRING_H
#include "list.h"
using namespace std;

class tstring {
public:
    tstring() = default;

    tstring(const tstring& other);
    tstring(tstring&& other) noexcept ;

    tstring& operator+=(const char& c);
    char operator[](const int& i) const;
    bool operator==(const tstring& _str) const;
    bool operator!=(const tstring& _str) const;

    tstring& operator=(const tstring& other);
    tstring& operator=(tstring&& other) noexcept;

    int len() const;

private:
    list<char> data;
    friend ostream & operator<<(ostream& out, const tstring& _str);
};


#endif //JAKDOJADE2_TSTRING_H
