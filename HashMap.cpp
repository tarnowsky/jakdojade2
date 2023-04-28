#include "HashMap.h"
HashMap::HashMap() {
    table = new Pair*[capacity];
    for (int i = 0; i < capacity; i++)
        table[i] = nullptr;
}

// Hash funkcja
int HashMap::hash(const tstring& _city) {
    int hashVal = 0;
    for (int i = 0; i < _city.len(); i++) {
        hashVal += _city[i];
    }
    return hashVal % capacity;
}

// Metoda dodająca parę do mapy
void HashMap::put(City* _city, int _id) {
    Pair* p = new Pair(_city, _id);
    int index = hash(_city->getName());
    if (table[index] == nullptr) {
        table[index] = p;
    }
    else {
        Pair* curr = table[index];
        while (curr->city->getName() != _city->getName() && curr->next != nullptr)
            curr = curr->next;
        if (curr->city->getName() == _city->getName())
            curr->id = _id;
        else curr->next = p;
    }
}

// Metoda zwracająca wartość dla danego klucza
int HashMap::get(const tstring& _city) {
    int index = hash(_city);
    Pair* curr = table[index];
    while (curr != nullptr) {
        if (curr->city->getName() == _city) {
            return curr->id;
        }
        curr = curr->next;
    }
    return -1; // klucz nieznaleziony
}

// Metoda usuwająca parę z mapy
void HashMap::remove(const tstring& _city) {
    int index = hash(_city);
    Pair* curr = table[index];
    Pair* prev = nullptr;
    while (curr != nullptr) {
        if (curr->city->getName() == _city) {
            if (prev == nullptr) {
                table[index] = curr->next;
            }
            else {
                prev->next = curr->next;
            }
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}