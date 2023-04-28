#ifndef JAKDOJADE2_HASHMAP_H
#define JAKDOJADE2_HASHMAP_H

#include "Town.h"

struct Pair {
    City* city;
    int id;
    Pair* next = nullptr;
    Pair(City *_city, int _id) : city(_city), id(_id), next(nullptr) {}
};

class HashMap {
private:
    static const int capacity = 10000;
    Pair** table;
public:
    HashMap();

    // Hash funkcja
    static int hash(const tstring& _cityName);

    // Metoda dodająca parę do mapy
    void put(City* _city, int _id);

    // Metoda zwracająca wartość dla danego klucza
    int get(const tstring& _cityName);

    // Metoda usuwająca parę z mapy
    void remove(const tstring& _cityName);
};


#endif //JAKDOJADE2_HASHMAP_H
