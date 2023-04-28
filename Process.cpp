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
            map[i][j].position = {j, i};
            if (c == '*')
                map[i][j].id = id++;
        }
        getchar();
    }
    cityArrLen = id;
    cityArr = new City[cityArrLen];
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
                cityArr[map[i][j].id].setName(getCityName({j, i}));
                cityArr[map[i][j].id].setId(map[i][j].id);
                cityArr[map[i][j].id].setPosition({j, i});
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

void Process::addNeighbours() {
    for (int i = 0; i < cityArrLen; i++) {
        list<Node*> queue;
        map[cityArr[i].getPosition().y][cityArr[i].getPosition().x].visitor = cityArr[i].getId();
        queue.push_front(&(map[cityArr[i].getPosition().y][cityArr[i].getPosition().x]));
        while (!queue.is_empty()) {
            Node *node = queue.pop();

            for (int j = 0; j < 4; j++) {
                if (node->position.y == 0 && j == UP) continue;
                if (node->position.y == rows - 1 && j == DOWN) continue;
                if (node->position.x == 0 && j == LEFT) continue;
                if (node->position.x == cols - 1 && j == RIGHT) continue;

                Node* poss_neighb = nullptr;
                switch(j) {
                    case UP:
                        poss_neighb = &(map[node->position.y - 1][node->position.x]);
                        break;
                    case DOWN:
                        poss_neighb = &(map[node->position.y + 1][node->position.x]);
                        break;
                    case RIGHT:
                        poss_neighb = &(map[node->position.y][node->position.x + 1]);
                        break;
                    case LEFT:
                        poss_neighb = &(map[node->position.y][node->position.x - 1]);
                        break;
                    default: break;
                }
                if (poss_neighb) {
                    if (poss_neighb->visitor == cityArr[i].getId()) continue;
                    if (poss_neighb->type == '*') {
                        poss_neighb->visitor = cityArr[i].getId();
                        cityArr[i].addNeighbour({poss_neighb->id,node->cost + 1});
                    }
                    else if (poss_neighb->type == '#') {
                        poss_neighb->visitor = cityArr[i].getId();
                        poss_neighb->cost = node->cost + 1;
                        queue.push_front(poss_neighb);
                    }
                } else throw logic_error("Found no possible direction for neighbour");
            }
        }
//        // print neighbours
//        cout << cityArr[i].getName() << endl;
//        for (int j = 0; j < cityArr[i].getNeighbours().len(); j++) {
//            cout << "\t" << cityArr[cityArr[i].getNeighbours()[j].cityId].getName();
//            cout << " cost: " << cityArr[i].getNeighbours()[j].cost << endl;
//        }
    }
}







Process::~Process() {
    for (int i = 0; i < rows; i++)
        delete[] map[i];
    delete[] map;

    delete[] cityArr;
}







