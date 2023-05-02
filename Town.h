#ifndef JAKDOJADE2_TOWN_H
#define JAKDOJADE2_TOWN_H
#include "tstring.h"

struct Point {
    int x, y;
    friend ostream& operator<<(ostream& out, const Point& p) {
        return out << "(" << p.x << ", " << p.y << ")";
    }
};

class City {
private:
    int id;
    mutable tstring name;
    Point position;
public:
    void setName(tstring&& _name);
    void setId(int _id);
    void setPosition(Point&& _position);

    Point getPosition() const;
    int getId() const;
    tstring& getName() const;
};



#endif //JAKDOJADE2_TOWN_H
