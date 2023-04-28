#ifndef JAKDOJADE2_LIST_H
#define JAKDOJADE2_LIST_H
#include <iostream>
using namespace std;


template <class T>
class list {
public:
    list() {
        data = new T[capacity];
        size = 0;
    }

    list(const list& other) : size(other.size), data(new T[other.size]) {
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    list& operator=(const list& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new T[size];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    list(list&& other) noexcept : size(other.size), data(other.data) {
        other.size = 0;
        other.data = nullptr;
    }

    list& operator=(list&& other) noexcept {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = other.data;
            other.size = 0;
            other.data = nullptr;
        }
        return *this;
    }

    void push_back(T value) {
        if (size == capacity) {
            T* new_data = new T[capacity * 2];
            for (int i = 0; i < size; i++)
                new_data[i] = data[i];
            delete[] data;
            data = new_data;
            capacity *= 2;
        }
        data[size++] = value;
    }

    T operator[](int index) const {
        if (index < size) {
            return data[index];
        } else {
            throw out_of_range("Index out of range");
        }
    }

    int len() const{
        return size;
    }

    bool is_empty() {
        return size == 0;
    }

    T pop() {
        if (size == 0)
            throw out_of_range("Trying to pop out of empty list");
        return data[--size];
    }

    ~list() {
        delete[] data;
    }

private:
    T *data;
    int size;
    int capacity = 1;
};

#endif //JAKDOJADE2_LIST_H
