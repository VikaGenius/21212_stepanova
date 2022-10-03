#pragma once
typedef std::string Key;

struct Value {
	unsigned age = 0;
	unsigned weight = 0;
	Value() = default;
	Value(unsigned a, unsigned w);
	~Value() = default;
};

struct Container {
	Key key;
	Value value;
};

class FlatMap
{
public:
	FlatMap();
	~FlatMap();

	FlatMap(const FlatMap& b);
	FlatMap(FlatMap&& b) noexcept;

	// Обменивает значения двух флетмап.
	// Подумайте, зачем нужен этот метод, при наличии стандартной функции
	// std::swap.
	void swap(FlatMap& b);

	void memoryExpansion();

	size_t binarySearch(const Key& k) const;

	FlatMap& operator=(const FlatMap& b);
	FlatMap& operator=(FlatMap&& b) noexcept;

	// Очищает контейнер.
	void clear();

	// Удаляет элемент по заданному ключу.
	bool erase(const Key& k);

	// Вставка в контейнер. Возвращаемое значение - успешность вставки.
	bool insert(const Key& k, const Value& v);

	// Проверка наличия значения по заданному ключу.
	bool contains(const Key& k) const;

	// Возвращает значение по ключу. Небезопасный метод.
	// В случае отсутствия ключа в контейнере, следует вставить в контейнер
	// значение, созданное конструктором по умолчанию и вернуть ссылку на него. 
	Value& operator[](const Key& k);

	// Возвращает значение по ключу. Бросает исключение при неудаче.
	Value& at(const Key& k);
	const Value& at(const Key& k) const;

	size_t size() const;

	bool empty() const;

	friend bool operator==(const FlatMap& a, const FlatMap& b);
	friend bool operator!=(const FlatMap& a, const FlatMap& b);

private:
	Container* container = nullptr;
	size_t size_c = 0ull;
	size_t capacity = 0ull;
};


