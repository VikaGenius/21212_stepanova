#include <algorithm>
#include <cassert>
#include <string>
#include "FlatMap.h"
#include <stdexcept>

Value::Value(unsigned a, unsigned w) : age(a), weight(w) {}

namespace {
    constexpr size_t kDefaultSize = 10;
}

FlatMap::FlatMap(): capacity(kDefaultSize) {
    container = new Container[capacity];
}
FlatMap::~FlatMap() {
    delete[] container;
}

FlatMap::FlatMap(const FlatMap& b) {
    *this = b;
}
FlatMap::FlatMap(FlatMap&& b) noexcept {
    *this = std::move(b);
}

void FlatMap::swap(FlatMap& b) {
    FlatMap tmp = std::move(b);
    b = std::move(*this);
    *this = std::move(tmp);
}

FlatMap& FlatMap::operator=(const FlatMap& b) {
    if (this != &b) {
        size_c = b.size_c;
        capacity = b.capacity;
        if (container != nullptr) {
            delete[] container;
        }
        container = new Container[capacity];
        std::copy_n(b.container, size_c, container);
    }
    return *this;
}

FlatMap& FlatMap::operator=(FlatMap&& b) noexcept {
    if (this != &b) {
        size_c = b.size_c;
        capacity = b.capacity;
        if (container != nullptr) {
            delete[] container;
        }
        container = b.container;
        b.container = nullptr;
    }
    return *this;
}

void FlatMap::clear() {
    assert(container);
    delete[] container;
    size_c = 0;
    capacity = kDefaultSize;
    container = new Container[capacity];
}

void FlatMap::memoryExpansion() {
    Container* tmp = new Container[capacity];
    std::copy_n(container, size_c, tmp);
    delete[] container;
    container = tmp;
}

size_t FlatMap::binarySearch(const Key& k) const{
    size_t left = 0;
    size_t right = size_c;
    size_t middle = 0;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (container[middle].key == k) {
            return middle;
        }
        if (container[middle].key > k) {
            right = middle;
        }
        else {
            left = middle + 1;
        }
    }
    return right;
}

bool FlatMap::erase(const Key& k) {
    size_t ind = binarySearch(k);
    if (ind == size_c - 1) {
        container[ind] = { "", {0, 0} };
        size_c--;
        return true;
    }
    if (container[ind].key == k) {
        std::copy_n(&container[ind + 1], size_c - ind - 1, &container[ind]);
        size_c--;
        return true;
    }

    return false;
}

bool FlatMap::insert(const Key& k, const Value& v) {
    if (size_c > 0) {
        if (size_c == capacity) {
            capacity *= 2;
            memoryExpansion();
        }
        size_t index = binarySearch(k);
        if (container[index].key == k) {
            return false;
        }
        if (index == size_c) {
            container[index] = { k, {v.age, v.weight} };
            size_c++;
            return true;
        }

        else {
            std::copy_backward(container + index, container + size_c, container + size_c + 1);
            container[index] = { k, {v.age, v.weight} };
            size_c++;
            return true;
        }
    }
    else {
        container[0] = { k, {v.age, v.weight} };
        size_c++;
        return true;

    }
}
bool FlatMap::contains(const Key& k) const {
    if (container[binarySearch(k)].key == k) {
        return true;
    }

    return false;
}

Value& FlatMap::operator[](const Key& k) {
    size_t ind = binarySearch(k);
    if (container[ind].key == k) {
        return container[ind].value;
    }
    insert(k, Value());
    return container[ind].value;
}

Value& FlatMap::at(const Key& k) {
    size_t ind = binarySearch(k);
    if (container[ind].key == k) {
        return container[ind].value;
    }

    throw std::invalid_argument("No value found for this key");
}
const Value& FlatMap::at(const Key& k) const {
    const size_t ind = binarySearch(k);
    if (container[ind].key == k) {
        return container[ind].value;
    }

    throw std::invalid_argument("No value found for this key");
}

size_t FlatMap::size() const {
    return size_c;
}

bool FlatMap::empty() const {
    return size_c == 0;
}

bool operator==(const Value& a, const Value& b) {
    if (a.age == b.age && a.weight == b.weight) {
        return true;
    }
    return false;
}

bool operator==(const Container& a, const Container& b) {
    if (a.key == b.key && a.value == b.value) {
        return true;
    }
    return false;
}

bool operator==(const FlatMap& a, const FlatMap& b) {
    if (a.size_c == b.size_c) {
        return std::equal(a.container, a.container + a.size_c, b.container);
    }
    return false;
}

bool operator!=(const FlatMap& a, const FlatMap& b) {
    return !(a == b);
}

