#include "Process.h"
using namespace std;
Process::Process() : map(nullptr), rows(0), cols(0) {
    int id = 0;
    cin >> cols >> rows;
    getchar();
    map = new Node*[rows];
    for (int i = 0; i < rows; i++) {
        map[i] = new Node[cols];
        for (int j = 0; j < cols; j++) {
            int c = getchar();
            map[i][j].type = (char)c;
            if (c == '*')
                map[i][j].id = id++;
        }
        getchar();
    }
    cityArr = new City[id];
}

ostream &operator<<(ostream &out, const Process& p) {
    for (int i = 0; i < p.rows; i++) {
        for (int j = 0; j < p.cols; j++)
            out << p.map[i][j].type;
        out << endl;
    }
    return out;
}


void Process::addCitiesToArr() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (map[i][j].type == '*') {
                tstring cityName = getCityName({j, i});
                cityArr[map[i][j].id].setName(std::move(cityName));
                cityArr[map[i][j].id].setId(map[i][j].id);
            }
        }
    }
}

tstring Process::getCityName(Point cityPos) {
    return parseCityName(findFirstLetterPos(findLetterPos(cityPos)));
}


Point Process::findLetterPos(Point cityPos) {
    for (int i = 0; i < 8; i++) {
        if ((cityPos.y == 0) && (i == UP || i == TOP_LEFT || i == TOP_RIGHT)) continue;
        if ((cityPos.y == rows - 1) && (i == DOWN || i == BOTTOM_LEFT || i == BOTTOM_RIGHT)) continue;
        if ((cityPos.x == 0) && (i == LEFT || i == TOP_LEFT || i == BOTTOM_LEFT)) continue;
        if ((cityPos.x == cols - 1) && (i == RIGHT || i == TOP_RIGHT || i == BOTTOM_RIGHT)) continue;

        switch(i) {
            case UP:
                if (canBeInName(map[cityPos.y - 1][cityPos.x].type)) return {cityPos.x, cityPos.y - 1};
                break;
            case DOWN:
                if (canBeInName(map[cityPos.y + 1][cityPos.x].type)) return {cityPos.x, cityPos.y + 1};
                break;
            case LEFT:
                if (canBeInName(map[cityPos.y][cityPos.x - 1].type)) return {cityPos.x - 1, cityPos.y};
                break;
            case RIGHT:
                if (canBeInName(map[cityPos.y][cityPos.x + 1].type)) return {cityPos.x + 1, cityPos.y};
                break;
            case TOP_LEFT:
                if (canBeInName(map[cityPos.y - 1][cityPos.x - 1].type)) return {cityPos.x - 1, cityPos.y - 1};
                break;
            case TOP_RIGHT:
                if (canBeInName(map[cityPos.y - 1][cityPos.x + 1].type)) return {cityPos.x + 1, cityPos.y - 1};
                break;
            case BOTTOM_LEFT:
                if (canBeInName(map[cityPos.y + 1][cityPos.x - 1].type)) return {cityPos.x - 1, cityPos.y + 1};
                break;
            case BOTTOM_RIGHT:
                if (canBeInName(map[cityPos.y + 1][cityPos.x + 1].type)) return {cityPos.x + 1, cityPos.y + 1};
                break;
            default: break;
        }
    }
    return {-1, -1};
}

bool Process::canBeInName(char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

Point Process::findFirstLetterPos(Point letterPos) {
    while (letterPos.x-- > 0 && canBeInName(map[letterPos.y][letterPos.x].type));
    ++letterPos.x;
    return letterPos;
}

tstring Process::parseCityName(Point firstLetterPos) {
    tstring cityName;
    do {
        cityName += map[firstLetterPos.y][firstLetterPos.x].type;
    } while (firstLetterPos.x++ < cols-1 && canBeInName(map[firstLetterPos.y][firstLetterPos.x].type));
    return cityName;
}









Process::~Process() {
    for (int i = 0; i < rows; i++)
        delete[] map[i];
    delete[] map;

    delete[] cityArr;
}





