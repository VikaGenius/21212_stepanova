#pragma once
#include <algorithm>
#include <iostream>
#include <cassert>
#include <stdlib.h>

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

	void swap(FlatMap& b);

	void memoryExpansion();

	size_t binarySearch(const Key& k) const;

	FlatMap& operator=(const FlatMap& b);
	FlatMap& operator=(FlatMap&& b) noexcept;

	void clear();
	bool erase(const Key& k);

	bool insert(const Key& k, const Value& v);
	bool contains(const Key& k) const;

	Value& operator[](const Key& k);
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


