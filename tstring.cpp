#include "tstring.h"
tstring& tstring::operator+=(const char& c) {
    data.push_back(c);
    return *this;
}
char tstring::operator[](const int &i) const {
    return data[i];
}

bool tstring::operator==(const tstring& _str) const {
    if (len() != _str.len()) return false;
    for (int i = 0; i < len(); i++)
        if (data[i] != _str[i]) return false;
    return true;
}
bool tstring::operator!=(const tstring& _str) const {
    return !(*this == _str);
}
int tstring::len() const {
    return data.len();
}

ostream & operator<<(ostream& out, const tstring& _str) {
    for (int i = 0; i < _str.len(); i++)
        out << _str.data[i];
    return out;
}

tstring& tstring::operator=(const tstring& other) {
    if (this != &other) {
        data = other.data;
    }
    return *this;
}

tstring& tstring::operator=(tstring&& other) noexcept {
    if (this != &other) {
        data = std::move(other.data);
    }
    return *this;
}

tstring::tstring(const tstring &other) {
    data = other.data;
}

tstring::tstring(tstring &&other) noexcept {
    data = std::move(other.data);
}
