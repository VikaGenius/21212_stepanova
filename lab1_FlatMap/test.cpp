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

TEST(FlatMapTest, Memory) {
	FlatMap a;
	Key key = "Vika";
	Value val(18, 57);

	Key key1 = "Armina";
	Value val1(19, 47);

	Key key2 = "Yana";
	Value val2(90, 50);

	Key key3 = "Maria";
	Value val3(10, 52);

	Key key4 = "Kate";
	Value val4(14, 80);

	Key key5 = "Maria";
	Value val5(16, 50);

	Key key6 = "Maksim";
	Value val6(35, 80);

	Key key7 = "Lena";
	Value val7(40, 52);

	Key key8 = "Dasha";
	Value val8(27, 90);

	Key key9 = "Mark";
	Value val9(12, 32);

	Key key10 = "Sveta";
	Value val10(10, 20);

	Key key11 = "Lera";
	Value val11(50, 72);

	a.insert(key, val);
	a.insert(key1, val1);
	a.insert(key2, val2);
	a.insert(key3, val3);
	a.insert(key4, val4);
	a.insert(key5, val5);
	a.insert(key6, val6);
	a.insert(key7, val7);
	a.insert(key8, val8);
	a.insert(key9, val9);
	a.insert(key10, val10);
	a.insert(key11, val11);

	ASSERT_TRUE(a.size() == 12);
	ASSERT_TRUE(a.erase(key10));
	ASSERT_TRUE(a.contains(key10) == false);
	ASSERT_TRUE(a.at(key11).age == 50);
}







