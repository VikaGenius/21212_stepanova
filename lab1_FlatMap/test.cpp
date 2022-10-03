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
	ASSERT_TRUE(a == b);
	ASSERT_FALSE(a != b);
	a.clear();

	ASSERT_TRUE(b.erase(key));
	ASSERT_TRUE(b.at(key1).age == 19);
	ASSERT_TRUE(a.erase(key) == false);
	ASSERT_ANY_THROW(a.at(key1));
	ASSERT_TRUE(a.empty());
}

TEST(FlatMapTest, Memory) {
	FlatMap a;
	Key key = "Vika";
	Value val(18, 57);
	a.insert(key, val);

	Key key1 = "Armina";
	Value val1(19, 47);
	a.insert(key1, val1);

	Key key2 = "Yana";
	Value val2(90, 50);
	a.insert(key2, val2);

	Key key3 = "Maria";
	Value val3(10, 52);
	a.insert(key3, val3);

	Key key4 = "Kate";
	Value val4(14, 80);
	a.insert(key4, val4);

	Key key5 = "Kira";
	Value val5(16, 50);
	a.insert(key5, val5);

	Key key6 = "Maksim";
	Value val6(35, 80);
	a.insert(key6, val6);

	Key key7 = "Lena";
	Value val7(40, 52);
	a.insert(key7, val7);

	Key key8 = "Dasha";
	Value val8(27, 90);
	a.insert(key8, val8);

	Key key9 = "Mark";
	Value val9(12, 32);
	a.insert(key9, val9);

	Key key10 = "Sveta";
	Value val10(10, 20);
	a.insert(key10, val10);

	Key key11 = "Lera";
	Value val11(50, 72);
	a.insert(key11, val11);

	ASSERT_TRUE(a.size() == 12);
	ASSERT_TRUE(a.at(key11).age == 50);
	ASSERT_TRUE(a.erase(key11));
	ASSERT_TRUE(a.contains(key10));
	ASSERT_ANY_THROW(a.at(key11));
	ASSERT_TRUE(a.erase(key1));
	ASSERT_ANY_THROW(a.at(key1));
	ASSERT_TRUE(a.erase(key2));
	ASSERT_ANY_THROW(a.at(key2));
	ASSERT_FALSE(a.contains(key2));
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}





