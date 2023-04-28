#ifndef JAKDOJADE2_TOWN_H
#define JAKDOJADE2_TOWN_H
#include "tstring.h"

struct Neighbour;

class City {
private:
    int id;
    mutable tstring name;
    list<Neighbour> neighbours;
public:
    void setName(tstring&& _name);
    void setId(int _id);

    tstring& getName() const;
};

struct Neighbour {
    int cityId;
    int cost;
};

#endif //JAKDOJADE2_TOWN_H
