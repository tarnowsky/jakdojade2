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

    list(int num, T value) {
        capacity = num;
        data = new T[capacity];
        size = 0;
        for (int i = 0; i < capacity; i++) push_back(value);
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

    void insert(const T& value, int id) {
        // znajdz miejsce
        if (id == 0) push_front(value);
        else {
            push_back(value);
            for (int i = size - 1; i > id; i--)
                swap(data[i], data[i - 1]);
        }
    }

    void push_back(const T& value) {
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

    void push_front(const T& value) {
        push_back(value);
        for (int i = size - 1; i > 0; i--)
            swap(data[i], data[i - 1]);

    }

    T& operator[](int index) const {
        return data[index];
    }

    [[nodiscard]] int len() const{
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
