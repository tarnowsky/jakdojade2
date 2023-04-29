#ifndef JAKDOJADE2_HASHMAP_H
#define JAKDOJADE2_HASHMAP_H

#include "Town.h"

struct Pair {
    City* city = nullptr;
    int id = -1;
};

class HashMap {
private:
    const int capacity = 7873;
    list<Pair> *table;
public:
    HashMap();
    explicit HashMap(int _size);

    // Hash funkcja
    int hash(const tstring& _cityName) const;

    // Metoda dodająca parę do mapy
    void put(City* _city, int _id);

    // Metoda zwracająca wartość dla danego klucza
    int get(const tstring& _cityName);

    // Metoda usuwająca parę z mapy

    ~HashMap();
};


#endif //JAKDOJADE2_HASHMAP_H
