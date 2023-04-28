#include "Town.h"

void City::setName(tstring &&_name) {
    name = _name;
}

void City::setId(int _id) {
    id = _id;
}

tstring &City::getName() const {
    return name;
}
