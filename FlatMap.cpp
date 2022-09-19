// FlatMap.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <algorithm>

typedef std::string Key;

struct Value {
    unsigned age;
    unsigned weight;
};

struct Container {
    Key key;
    Value* value;
};

class FlatMap
{
public:
    FlatMap() {
        capacity = 10;
        container = new Container[capacity]; 
    }
    ~FlatMap() {
        delete[] container;
    }

    FlatMap(const FlatMap& b) {
        *this = b;
    }
    FlatMap(FlatMap&& b);
    //разберись!


    // Обменивает значения двух флетмап.
    // Подумайте, зачем нужен этот метод, при наличии стандартной функции
    // std::swap.
    void swap(FlatMap& b) {
        FlatMap tmp = b;
        b = *this;
        *this = tmp;
    }

    FlatMap& operator=(const FlatMap& b) {
        size = b.size;
        capacity = b.capacity;
        if (container != nullptr) {
            delete[] container;
        }
        container = new Container[capacity];
        std::copy_n(b.container, capacity, container);
        return *this;
    }

    FlatMap&& operator=(FlatMap&& b) {
        size = b.size;
        capacity = b.capacity;
        if (container != nullptr) {
            delete[] container;
        }
        container = new Container[capacity];
        std::copy_n(b.container, size, container);
        //return *this; 
        //ану разберись с этим тряпка
    }

    // Очищает контейнер.
    void clear() {
        if (container != nullptr) {
            delete[] container;
        }
        size = 0;
        capacity = 10;
        container = new Container[capacity];
    }

    void memoryExpansion() {
        Container* tmp = container;
        delete[] container;
        container = new Container[capacity];
        std::copy_n(tmp, size, container);
    }


    // Удаляет элемент по заданному ключу.
    bool erase(const Key& k);
    // Вставка в контейнер. Возвращаемое значение - успешность вставки.
    bool insert(const Key& k, const Value& v) {
        if (container == nullptr) {
            return false;
        }
        if (size > 0) {
            if (size == capacity) {
                capacity *= 2;
                memoryExpansion();
            }
            //по поиску бинарному вставка
            size++;
        }
        else {
            container->key = k;
            container->value->age = v.age;
            container->value->weight = v.weight;
            size++;
            
        }
    }

    // Проверка наличия значения по заданному ключу.
    bool contains(const Key& k) const;

    // Возвращает значение по ключу. Небезопасный метод.
    // В случае отсутствия ключа в контейнере, следует вставить в контейнер
    // значение, созданное конструктором по умолчанию и вернуть ссылку на него. 
    Value& operator[](const Key& k);

    // Возвращает значение по ключу. Бросает исключение при неудаче.
    Value& at(const Key& k);
    const Value& at(const Key& k) const;

    //size_t size() const;
    bool empty() const;

    friend bool operator==(const FlatMap& a, const FlatMap& b);
    friend bool operator!=(const FlatMap& a, const FlatMap& b);

private:
    Container* container = nullptr;
    size_t size = 0ull;
    size_t capacity = 0ull;
};

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}

