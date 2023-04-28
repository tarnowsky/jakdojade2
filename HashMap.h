#ifndef JAKDOJADE2_HASHMAP_H
#define JAKDOJADE2_HASHMAP_H

#include "Town.h"

struct Pair {
    City* city = nullptr;
    int id = -1;
};

class HashMap {
private:
    static const int capacity = 10000;
    list<Pair> *table;
public:
    HashMap();

    // Hash funkcja
    static int hash(const tstring& _cityName);

    // Metoda dodająca parę do mapy
    void put(City* _city, int _id);

    // Metoda zwracająca wartość dla danego klucza
    int get(const tstring& _cityName);

    // Metoda usuwająca parę z mapy

    ~HashMap();
};


#endif //JAKDOJADE2_HASHMAP_H
