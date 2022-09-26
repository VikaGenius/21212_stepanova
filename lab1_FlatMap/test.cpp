#include "pch.h"
#include "FlatMap.h"


TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(FlatMapTest, Insert) {
	FlatMap map;
	Key key = "Vika";
	Value val(18, 57);

	Key key1 = "Armina";
	Value val1(19, 47);

	Key key2 = "Yana";
	Value val2(90, 50);
	Key key3(key);

	ASSERT_EQ(map.insert(key, val), true);
	ASSERT_EQ(map.insert(key3, map.at(key3)), false);
	ASSERT_EQ(map.insert(key1, val1), true);
	ASSERT_EQ(map.insert(key2, val2), true);
	ASSERT_TRUE(map.contains(key2));
	ASSERT_FALSE(map.contains("Maria"));
}

TEST(FlatMapTest, Swap) {
	FlatMap a;
	FlatMap b;

	Key key = "Vika";
	Value val(18, 57);

	Key key1 = "Armina";
	Value val1(19, 47);

	a.insert(key, val);
	b.insert(key1, val1);

	a.swap(b);
	ASSERT_TRUE(a.at(key1).age == 19);
	ASSERT_FALSE(b.contains(key1));
}

TEST(FlatMapTest, Clear) {
	FlatMap a;
	Key key = "Vika";
	Value val(18, 57);

	Key key1 = "Armina";
	Value val1(19, 47);

	a.insert(key, val);
	a.insert(key1, val1);

	FlatMap b(a);
	a.clear();

	ASSERT_TRUE(b.erase(key));
	ASSERT_TRUE(b.at(key1).age == 19);
	ASSERT_TRUE(a.erase(key) == false);
	ASSERT_FALSE(a.at(key1).age == 19);
	ASSERT_TRUE(a.empty());
}







