#ifndef JAKDOJADE2_TOWN_H
#define JAKDOJADE2_TOWN_H
#include "tstring.h"

struct Point {
    int x, y;
    friend ostream& operator<<(ostream& out, const Point& p) {
        return out << "(" << p.x << ", " << p.y << ")";
    }
};

struct Neighbour;

class City {
private:
    int id;
    mutable tstring name;
    Point position;
    mutable list<Neighbour> neighbours;
public:
    void setName(tstring&& _name);
    void setId(int _id);
    void setPosition(Point&& _position);
    void addNeighbour(Neighbour&& _neighbour);

    Point getPosition() const;
    int getId() const;
    list<Neighbour>& getNeighbours() const;

    tstring& getName() const;
};

struct Neighbour {
    int cityId;
    int cost;
};

#endif //JAKDOJADE2_TOWN_H
