#include <stdlib.h>
#include <cstring>
#include <iostream>

class Array {
public:
    // конструктор
    // Array();
    Array (size_t initial_capacity) {
        capacity = initial_capacity;
        arr = (int*)malloc(capacity * sizeof(*arr));
    }

    Array() {
        capacity = 12;
        arr = (int*)malloc(capacity * sizeof(*arr));
    }

    // деструктор
    ~Array() {
        free(arr);
    }

    Array& operator=(const Array& firstArr) {
        if (arr != nullptr) {
            free(arr);
        }
        size = firstArr.size;
        capacity = firstArr.capacity;
        arr = (int*)malloc(size * sizeof(*arr));
        memmove(arr, firstArr.arr, size);
        return *this;
    }

    Array(const Array& copy) {
        *this = copy;
    }

    void push_back(int num) {
        if (size == capacity) {
            capacity *= 2;
            int* tmp = (int*)realloc(arr, capacity);
            if (tmp == nullptr) {
                std::cout << "Memory allocation error";
                return;
            }
            // if ...
            arr = tmp;
        }
        arr[size] = num;
        size++;
    }

    void insert(int index, const int num) {
        if (size == capacity) {
            capacity *= 2;
            int* tmp = (int*)realloc(arr, capacity);
            if (tmp == nullptr) {
                std::cout << "Memory allocation error";
                return;
            }
        }
        memmove(arr + index + 1, arr + index, (size - index) * sizeof(int));
        arr[index] = num;
        size++;
    }

    int at(const int index) {
        return arr[index];
    }

    int& operator[](const int index) {
        return arr[index];
    }

    int pop(const int index) {
        int popEl = arr[index];
        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
        return popEl;
    }

    int min() {
        int minEl = INT_MAX;
        for (int i = 0; i < size; i++) {
            if (arr[i] < minEl) {
                minEl = arr[i];
            }
        }
        return minEl;
    }

    int max() {
        int maxEl = 0;
        for (int i = 0; i < size; i++) {
            if (arr[i] > maxEl) {
                maxEl = arr[i];
            }
        }
        return maxEl;
    }

private:
    int* arr = nullptr;
    size_t size = 0ull;
    size_t capacity = 0ull;
};

int main() {
    Array a(10);
    a.push_back( /*&a,*/ 21212);
    a.push_back(11);
    a.push_back(130);
    a.push_back(12);
    a.push_back(15);
    a.insert(2, 4);
    for (int i = 0; i < 6; i++) {
        std::cout << a.at(i) << "\n";
    }
   
}