#include "HashMap.h"
HashMap::HashMap() {
    table = new list<Pair>[capacity];
}

// Hash funkcja
int HashMap::hash(const tstring& _cityName) const {
    int hashVal = 1;
    int prime = 2137;
    for (int i = 0; i < _cityName.len(); i++) {
        hashVal = (hashVal * prime + _cityName[i]) % capacity;
    }
    return hashVal % capacity;
}

// Metoda dodająca parę do mapy
void HashMap::put(City* _city, int _id) {
    int index = hash(_city->getName());
    table[index].push_back({_city, _id});
}

// Metoda zwracająca wartość dla danego klucza
int HashMap::get(const tstring& _cityName) {
    int index = hash(_cityName);
    for (int i = 0; i < table[index].len(); i++)
        if (table[index][i].city->getName() == _cityName)
            return table[index][i].id;
    return -1; // klucz nieznaleziony
}

HashMap::~HashMap() {
    delete[] table;
}

HashMap::HashMap(int _size) : capacity(_size){
    table = new list<Pair>[capacity];
}
