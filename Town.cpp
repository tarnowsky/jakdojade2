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

void City::setPosition(Point&& _position) {
    position = _position;
}

Point City::getPosition() const {
    return position;
}

int City::getId() const {
    return id;
}
