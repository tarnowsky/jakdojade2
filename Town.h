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
    int visitor = -1;
    mutable tstring name;
    Point position;
    mutable list<Neighbour> neighbours;
private:
    int findPlaceForNeighbour(int neighbId);
public:
    int getNeighbourId(int cityId);
    int getVisitor() const;
    void setVisitor(int _visitor);
    void setName(tstring&& _name);
    void setId(int _id);
    void setPosition(Point&& _position);
    void addNeighbour(Neighbour&& _neighbour);
    void setPathCost(int neighbId, int _cost);

    Point getPosition() const;
    int getId() const;
    list<Neighbour>& getNeighbours() const;

    tstring& getName() const;
};

struct Neighbour {
    int cityId;
    int cost;
    void setCost(int _cost) {cost = _cost;}
};

#endif //JAKDOJADE2_TOWN_H
