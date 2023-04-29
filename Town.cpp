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

void City::addNeighbour(Neighbour &&_neighbour) {
    neighbours.insert(_neighbour, findPlaceForNeighbour(_neighbour.cityId));
}

int City::findPlaceForNeighbour(int neighbId) {
    int s, p = 0, k = neighbours.len();
    while (p<k) {
        s = (p + k - 1) / 2;
        if (neighbours[s].cityId > neighbId) k = s;
        if (neighbours[s].cityId < neighbId) p = s + 1;
    }
    return p;
}

list<Neighbour> &City::getNeighbours() const {
    return neighbours;
}

int City::getNeighbourId(int cityId) {
    int s, p = 0, k = neighbours.len();
    while (p<k) {
        s = (p + k - 1) / 2;
        if (neighbours[s].cityId == cityId) return s;

        if (neighbours[s].cityId > cityId) k = s - 1;
        if (neighbours[s].cityId < cityId) p = s + 1;
    }
    if (p < neighbours.len()) if (neighbours[p].cityId == cityId) return p;
    return -1;
}

void City::setVisitor(int _visitor) {
    visitor = _visitor;
}

int City::getVisitor() const{
    return visitor;
}

void City::setPathCost(int neighbId, int _cost) {
    neighbours[neighbId].setCost(_cost);
}
