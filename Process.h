#ifndef JAKDOJADE2_PROCESS_H
#define JAKDOJADE2_PROCESS_H
#include <iostream>
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

struct Point {
    int x, y;
    friend ostream& operator<<(ostream& out, const Point& p) {
        return out << "(" << p.x << ", " << p.y << ")";
    }
};

struct Node {
    char type = 0;
    int visitor = 0;
    int id = -1;
};

class Process {
public:
    Process();
    void addCitiesToArr();
    ~Process();
private:
    Node** map;
    int rows, cols;
    City* cityArr;
private:
    tstring getCityName(Point cityPos);
    Point findLetterPos(Point cityPos);
    inline Point findFirstLetterPos(Point letterPos);
    inline tstring parseCityName(Point firstLetterPos);
    static inline bool canBeInName(char c);
    friend ostream& operator<<(ostream& out, const Process& p);
};


#endif //JAKDOJADE2_PROCESS_H
