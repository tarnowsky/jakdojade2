#ifndef JAKDOJADE2_PROCESS_H
#define JAKDOJADE2_PROCESS_H
#include <iostream>
#include "HashMap.h"
#include "Town.h"
using namespace std;


enum Directions {
    UP,
    DOWN,
    RIGHT,
    LEFT,
    TOP_RIGHT,
    BOTTOM_RIGHT,
    TOP_LEFT,
    BOTTOM_LEFT,
};



struct Node {
    char type = 0;
    int visitor = -1;
    int cost = 0;
    Point position{};
    int id = -1;
};

class Process {
public:
    Process();
    void addCitiesToArr();
    void addNeighbours();

    HashMap& getCityHashMap() const;
    City* getCityArr() const;
    int** getNeighbours() const;

    ~Process();
private:
    Node** map;
    int rows, cols;
    City* cityArr;
    int** neighbours;
    mutable HashMap cityHashMap;
    int cityArrLen;
private:
    tstring getCityName(Point cityPos);
    Point findLetterPos(Point cityPos);
    inline Point findFirstLetterPos(Point letterPos);
    inline tstring parseCityName(Point firstLetterPos);
    static inline bool canBeInName(char c);
    friend ostream& operator<<(ostream& out, const Process& p);
};


#endif //JAKDOJADE2_PROCESS_H
