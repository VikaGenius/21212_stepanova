// FlatMap.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*#include <algorithm>
#include <iostream>
#include <cassert>
#include <stdlib.h>*/
#include "FlatMap.h"


typedef std::string Key;


 //Value::Value() = default;
Value::Value(unsigned a, unsigned w): age(a), weight(w) {}
 //Value::~Value() = default;


/*struct Container {
    Key key;
    Value value;
};*/


 FlatMap::FlatMap() {
    capacity = 10;
    container = new Container[capacity]; 
  }
FlatMap::~FlatMap() {
    delete[] container;
}

FlatMap::FlatMap(const FlatMap & b) {
    *this = b;
}
FlatMap::FlatMap(FlatMap&& b) noexcept {
    *this = b;
}

// Обменивает значения двух флетмап.
// Подумайте, зачем нужен этот метод, при наличии стандартной функции
// std::swap.
void FlatMap::swap(FlatMap& b) {
    FlatMap tmp = std::move(b);
    b = std::move(*this);
    *this = std::move(tmp);
}

FlatMap& FlatMap::operator=(const FlatMap& b) {
    size_c = b.size_c;
    capacity = b.capacity;
    if (container != nullptr) {
        delete[] container;
    }
    container = new Container[capacity];
    std::copy_n(b.container, capacity, container);
    return *this;
}

FlatMap& FlatMap::operator=(FlatMap&& b) noexcept {
    size_c = b.size_c;
    capacity = b.capacity;
    if (container != nullptr) {
        delete[] container;
    }
    container = new Container[capacity];
    std::copy_n(b.container, size_c, container);
    return *this; 
}

// Очищает контейнер.
void FlatMap::clear() {
    if (container != nullptr) {
        delete[] container;
    }
    size_c = 0;
    capacity = 10;
    container = new Container[capacity];
}

void FlatMap::memoryExpansion() {
    Container* tmp = new Container[size_c];
    std::copy_n(container, size_c, tmp);
    delete[] container;
    container = new Container[capacity];
    std::copy_n(tmp, size_c, container);
}

size_t FlatMap::binarySearch(const Key& k) const {
    long long left = -1;
    long long right = size_c;
    long long middle = 0;
    while (right - left > 1) {
        middle = left + (right - left) / 2; 
        if (container[middle].key == k) {
            return middle;
        }
        if (container[middle].key < k) {
            left = middle;
        }
        else {
            right = middle;
        }
    }
    return right;
}

// Удаляет элемент по заданному ключу.
bool FlatMap::erase(const Key& k) {
    size_t ind = binarySearch(k);
    if (container[ind].key == k) {
        std::copy_n(&container[ind + 1], size_c - ind, &container[ind]);
        size_c--;
        return true;
    }
    else {
        return false;
    }
}
   
// Вставка в контейнер. Возвращаемое значение - успешность вставки.
bool FlatMap::insert(const Key& k, const Value& v) {
    if (container == nullptr) {
        std::cout << "Container does not exist";
        return false;
    }
    if (size_c > 0) {
        if (size_c == capacity) {
            capacity *= 2;
            memoryExpansion();
        }
        size_t index = binarySearch(k);
        if (index == size_c) {
            container[index].key = k;
            container[index].value.age = v.age;
            container[index].value.weight = v.weight;
            size_c++;
            return true;
        }
        if (container[index].key == k) {
            std::cout << "There is already an element with this key";
            return false;
        }
        else {
            std::copy_n(&container[index], size_c - index, &container[index + 1]);
            container[index].key = k;
            container[index].value.age = v.age;
            container[index].value.weight = v.weight;
            size_c++;
            return true;
        }
    }
    else {
        container[0].key = k;
        container[0].value.age = v.age;
        container[0].value.weight = v.weight;
        size_c++;
        return true;
            
    }
}
// Проверка наличия значения по заданному ключу.
bool FlatMap::contains(const Key& k) const {
    if (container[binarySearch(k)].key == k) {
        return true;
    }
    else {
        return false;
    }
}

// Возвращает значение по ключу. Небезопасный метод.
// В случае отсутствия ключа в контейнере, следует вставить в контейнер
// значение, созданное конструктором по умолчанию и вернуть ссылку на него. 
Value& FlatMap::operator[](const Key& k) {
    size_t ind = binarySearch(k);
    if (container[ind].key == k) {
        return container[ind].value;
    }
    else {
        insert(k, Value());
        return container[ind].value;
    }
}

// Возвращает значение по ключу. Бросает исключение при неудаче.
Value& FlatMap::at(const Key& k) {
    size_t ind = binarySearch(k);
    if (container[ind].key == k) {
        return container[ind].value;
    }
    else {
        throw "No value found for this key";
    }
}
const Value& FlatMap::at(const Key& k) const {
    size_t ind = binarySearch(k);
    if (container[ind].key == k) {
        return container[ind].value;
    }
    else {
        throw "No value found for this key";
    }
}

size_t FlatMap::size() const {
    return size_c;
}

bool FlatMap::empty() const {
    if (size_c == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool operator==(const FlatMap& a, const FlatMap& b) {
    if (a.size_c == b.size_c) {
        for (size_t i = 0; i < a.size_c; i++) {
            if (a.container[i].key == b.container[i].key &&
                a.container[i].value.age == b.container[i].value.age &&
                a.container[i].value.weight == b.container[i].value.weight) {
                return true;
                }
            else {
                return false;
            }
        }
    }
    else {
        return false;
    }
}
bool operator!=(const FlatMap& a, const FlatMap& b) {
    if (!(a == b)) {
        return true;
    }
    else {
        return false;
    }
}




int main()
{
    /*FlatMap a;

    Key key = "Vika";
    Value value(18, 57);
    a.insert(key, value);
 
    Key key1 = "Armina";
    Value value1(19, 47);
    a.insert(key1, value1);

    Key key2 = "Yana";
    Value value2(90, 50);
    a.insert(key2, value2);

    Value v3 = a.at(key2);*/
    //std::cout << v3.age;
    /*if (a.erase(key) == true) {
        std::cout << a.size();
    }
    else {
        std::cout << "loh";
        }*/
    


}

