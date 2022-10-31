#include "FlatMap.cpp"
#include <gtest/gtest.h>

//#include "pch.h"
//#include "FlatMap.h"


TEST(FlatMapTest, Swap) {
	FlatMap a;
	FlatMap b;

	Key key = "Vika";
	Value val(18, 57);

	Key key1 = "Armina";
	Value val1(19, 47);

	Key key2 = "Kate";
	Value val2(14, 80);

	a.insert(key, val);
	b.insert(key1, val1);
	a.insert(key2, val2);
	b.insert(key2, val2);

	a.swap(b);
	EXPECT_EQ(a.at(key1).age, 19);
	EXPECT_EQ(a.contains(key1), true);
	EXPECT_EQ(a.contains(key2), true);
	EXPECT_EQ(b.contains(key1), false);

	a = b;
	EXPECT_EQ(a.contains(key), true);
	EXPECT_EQ(a.contains(key1), false);
	EXPECT_EQ(a.contains(key2), true);

}

TEST(FlatMapTest, Clear) {
	FlatMap a;
	Key key = "Vika";
	Value val(18, 57);

	Key key1 = "Armina";
	Value val1(19, 47);

	Key key2 = "Yana";
	Value val2(90, 50);

	a.insert(key, val);
	a.insert(key1, val1);
	a.insert(key2, val2);
	FlatMap b(a);

	EXPECT_EQ(a, b);

	a.clear();

	EXPECT_EQ(b.erase(key), true);
	EXPECT_EQ(b.at(key1).age, 19);
	EXPECT_EQ(a.erase(key), false);
	EXPECT_ANY_THROW(a.at(key1));
	EXPECT_EQ(a.empty(), true);
}

TEST(FlatMapTest, Insert) {
	FlatMap map;

	Key key = "Vika";
	Value val(18, 57);
	EXPECT_EQ(map.insert(key, val), true);
	EXPECT_EQ(map.contains(key), true);

	Key key1 = "Armina";
	Value val1(19, 47);
	EXPECT_EQ(map.insert(key, val), false);
	EXPECT_EQ(map.insert(key1, val1), true);
	EXPECT_EQ(map.contains(key), true);
	EXPECT_EQ(map.contains(key1), true);

	Key key2 = "Yana";
	Value val2(90, 50);
	EXPECT_EQ(map.insert(key2, val2), true);
	EXPECT_EQ(map.contains(key), true);
	EXPECT_EQ(map.contains(key1), true);
	EXPECT_EQ(map.contains(key2), true);

	Key key3 = "Maria";
	Value val3(10, 52);
	EXPECT_EQ(map.insert(key3, val3), true);
	EXPECT_EQ(map.contains(key), true);
	EXPECT_EQ(map.contains(key1), true);
	EXPECT_EQ(map.contains(key2), true);
	EXPECT_EQ(map.contains(key3), true);

	Key key4 = "Kate";
	Value val4(14, 80);
	EXPECT_EQ(map.insert(key4, val4), true);
	EXPECT_EQ(map.contains(key), true);
	EXPECT_EQ(map.contains(key1), true);
	EXPECT_EQ(map.contains(key2), true);
	EXPECT_EQ(map.contains(key3), true);
	EXPECT_EQ(map.contains(key4), true);

	Key key5 = "Kira";
	Value val5(16, 50);
	EXPECT_EQ(map.insert(key5, val5), true);
	EXPECT_EQ(map.contains(key), true);
	EXPECT_EQ(map.contains(key1), true);
	EXPECT_EQ(map.contains(key2), true);
	EXPECT_EQ(map.contains(key3), true);
	EXPECT_EQ(map.contains(key4), true);
	EXPECT_EQ(map.contains(key5), true);

	Key key6 = "Maksim";
	Value val6(35, 80);
	EXPECT_EQ(map.insert(key6, val6), true);
	EXPECT_EQ(map.contains(key), true);
	EXPECT_EQ(map.contains(key1), true);
	EXPECT_EQ(map.contains(key2), true);
	EXPECT_EQ(map.contains(key3), true);
	EXPECT_EQ(map.contains(key4), true);
	EXPECT_EQ(map.contains(key5), true);
	EXPECT_EQ(map.contains(key6), true);

	Key key7 = "Lena";
	Value val7(40, 52);
	EXPECT_EQ(map.insert(key7, val7), true);
	EXPECT_EQ(map.contains(key), true);
	EXPECT_EQ(map.contains(key1), true);
	EXPECT_EQ(map.contains(key2), true);
	EXPECT_EQ(map.contains(key3), true);
	EXPECT_EQ(map.contains(key4), true);
	EXPECT_EQ(map.contains(key5), true);
	EXPECT_EQ(map.contains(key6), true);
	EXPECT_EQ(map.contains(key7), true);

	Key key8 = "Dasha";
	Value val8(27, 90);
	EXPECT_EQ(map.insert(key8, val8), true);
	EXPECT_EQ(map.contains(key), true);
	EXPECT_EQ(map.contains(key1), true);
	EXPECT_EQ(map.contains(key2), true);
	EXPECT_EQ(map.contains(key3), true);
	EXPECT_EQ(map.contains(key4), true);
	EXPECT_EQ(map.contains(key5), true);
	EXPECT_EQ(map.contains(key6), true);
	EXPECT_EQ(map.contains(key7), true);
	EXPECT_EQ(map.contains(key8), true);


	Key key9 = "Mark";
	Value val9(12, 32);
	EXPECT_EQ(map.insert(key9, val9), true);
	EXPECT_EQ(map.contains(key), true);
	EXPECT_EQ(map.contains(key1), true);
	EXPECT_EQ(map.contains(key2), true);
	EXPECT_EQ(map.contains(key3), true);
	EXPECT_EQ(map.contains(key4), true);
	EXPECT_EQ(map.contains(key5), true);
	EXPECT_EQ(map.contains(key6), true);
	EXPECT_EQ(map.contains(key7), true);
	EXPECT_EQ(map.contains(key8), true);
	EXPECT_EQ(map.contains(key9), true);

	Key key10 = "Sveta";
	Value val10(10, 20);
	EXPECT_EQ(map.insert(key10, val10), true);
	EXPECT_EQ(map.contains(key), true);
	EXPECT_EQ(map.contains(key1), true);
	EXPECT_EQ(map.contains(key2), true);
	EXPECT_EQ(map.contains(key3), true);
	EXPECT_EQ(map.contains(key4), true);
	EXPECT_EQ(map.contains(key5), true);
	EXPECT_EQ(map.contains(key6), true);
	EXPECT_EQ(map.contains(key7), true);
	EXPECT_EQ(map.contains(key8), true);
	EXPECT_EQ(map.contains(key9), true);
	EXPECT_EQ(map.contains(key10), true);

	Key key11 = "Lera";
	Value val11(50, 72);
	EXPECT_EQ(map.insert(key11, val11), true);
	EXPECT_EQ(map.contains(key), true);
	EXPECT_EQ(map.contains(key1), true);
	EXPECT_EQ(map.contains(key2), true);
	EXPECT_EQ(map.contains(key3), true);
	EXPECT_EQ(map.contains(key4), true);
	EXPECT_EQ(map.contains(key5), true);
	EXPECT_EQ(map.contains(key6), true);
	EXPECT_EQ(map.contains(key7), true);
	EXPECT_EQ(map.contains(key8), true);
	EXPECT_EQ(map.contains(key9), true);
	EXPECT_EQ(map.contains(key10), true);
	EXPECT_EQ(map.contains(key11), true);

	EXPECT_EQ(map.size(), 12);
	EXPECT_EQ(map.at(key11), val11);

	EXPECT_EQ(map.empty(), false);

	EXPECT_EQ(map.erase(key), true);
	EXPECT_EQ(map.erase(key1), true);
	EXPECT_EQ(map.erase(key2), true);
	EXPECT_EQ(map.erase(key3), true);
	EXPECT_EQ(map.erase(key4), true);
	EXPECT_EQ(map.erase(key5), true);
	EXPECT_EQ(map.erase(key6), true);
	EXPECT_EQ(map.erase(key7), true);
	EXPECT_EQ(map.erase(key8), true);
	EXPECT_EQ(map.erase(key9), true);
	EXPECT_EQ(map.erase(key10), true);
	EXPECT_EQ(map.erase(key11), true);

	EXPECT_EQ(map.empty(), true);

	EXPECT_EQ(map.contains(key), false);
	EXPECT_EQ(map.contains(key1), false);
	EXPECT_EQ(map.contains(key2), false);

	EXPECT_ANY_THROW(map.at(key11));
	EXPECT_ANY_THROW(map.at(key1));
	EXPECT_ANY_THROW(map.at(key2));


}

TEST(FlatMapTest, Operators) {
	FlatMap a;

	Key key = "RandomName";
	Value val(139, 199);
	a.insert(key, val);

	Key key1 = "Lena";
	Value val1(40, 52);
	a.insert(key1, val1);

	Key key2 = "Dasha";
	Value val2(27, 90);
	a.insert(key2, val2);

	FlatMap b;
	b.insert(key1, val1);
	ASSERT_FALSE(a == b);
	b = a;
	ASSERT_TRUE(a == b);
	ASSERT_FALSE(a != b);
	b.clear();
	ASSERT_FALSE(a == b);
	ASSERT_TRUE(a[key] == val);

}

TEST(FlatMapTest, ConstAt) {
	FlatMap a;

	Key key = "ab";
	Value val(1, 5);

	Key key1 = "av";
	Value val2(3, 9);

	a.insert(key, val);
	a.insert(key1, val2);

	const FlatMap b(a);

	EXPECT_EQ(b.at(key).age, 1);
	EXPECT_ANY_THROW(b.at("lalala"));
	EXPECT_EQ(b.at(key1).weight, 9);
	EXPECT_EQ(b.at(key) == val2, false);

}


int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}






