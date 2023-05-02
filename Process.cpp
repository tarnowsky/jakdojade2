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
    adj = new list<Pair>[cityArrLen];
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
                cityHashMap.put(&(cityArr[map[i][j].id]), map[i][j].id);
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
                        adj[i].push_back({poss_neighb->id, node->cost + 1});
                    }
                    else if (poss_neighb->type == '#') {
                        poss_neighb->visitor = cityArr[i].getId();
                        poss_neighb->cost = node->cost + 1;
                        queue.push_front(poss_neighb);
                    }
                } else throw logic_error("Found no possible direction for neighbour");
            }
        }
    }
}

void Process::addFlights() {
    int flightNum, cost;
    cin >> flightNum;
    getchar();
    while(flightNum--) {
        tstring from, to;
        bool flightAdded = false;

        addAirport(from);
        addAirport(to);
        cin >> cost;
        getchar();

        int fromId = cityHashMap.get(from);
        int toId = cityHashMap.get(to);

        for (int i = 0; i < adj[fromId].len(); i++) {
            if ((adj[fromId][i].city == toId) && (adj[fromId][i].cost > cost)) {
                adj[fromId][i].cost = cost;
                flightAdded = true;
                break;
            }
        }
        if (!flightAdded) adj[fromId].push_back({toId, cost});

    }
}

void Process::addAirport(tstring& _city) {
    int c;
    while((c = getchar()) != ' ') _city += (char)c;
}

int Process::findPath(const int& start, const int& target, list<int>& path) {
    list<int> parent(cityArrLen, -1);
    list<int> dist(cityArrLen, INF);
    list<bool> visited(cityArrLen, false);
    list<Pair> pq;

    dist[start] = 0;
    pq.push_back({start, 0});

    while(!pq.is_empty()) {
        int u = pq.pop().city;
        if (visited[u]) continue;
        if (u == target) break;
        for (int i = 0; i < adj[u].len(); i++) {
            int neighbour = adj[u][i].city;
            int cost = adj[u][i].cost;
            int alt = dist[u] + cost;
            if (alt < dist[neighbour]) {
                dist[neighbour] = alt;
                parent[neighbour] = u;
                pq.insert({neighbour, dist[neighbour]}, findPlaceForPath(dist[neighbour], pq));
            }
        }
    }
    if (dist[target] != INF) {
        int current = parent[target];
        while (current != start) {
            path.push_back(current);
            current = parent[current];
        }
    }
    return dist[target];

}



int Process::findPlaceForPath(int _cost, list<Pair>& queue) {
    int s, p = 0, k = queue.len();
    while (p<k) {
        s = (p + k - 1) / 2;
        if (queue[s].cost >= _cost) p = s + 1;
        if (queue[s].cost < _cost) k = s;
    }
    return k;
}

void Process::exeCommands() {
    int commandsNum, mode;
    cin >> commandsNum;
    getchar();
    while (commandsNum--) {
        tstring from, to;
        list<int> path; // do przechowywania drogi start -> target

        addAirport(from);
        addAirport(to);
        cin >> mode;
        getchar();

        if (from == to) cout << 0;
        else {
            int start = cityHashMap.get(from);
            int target = cityHashMap.get(to);

            int cost = findPath(start, target, path);

            cout << cost;
            if (mode)
                for (int i = path.len() - 1; i >= 0 ; i--)
                    cout << " " << cityArr[path[i]].getName();
        }
        cout << endl;
    }
}

Process::~Process() {
    for (int i = 0; i < rows; i++)
        delete[] map[i];
    delete[] map;

    delete[] cityArr;
    delete[] adj;

}









