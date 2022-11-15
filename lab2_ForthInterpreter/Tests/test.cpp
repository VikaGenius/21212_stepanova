#include "gtest/gtest.h"
#include "Forth.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(ForthTests, ValueOnTheStack) {
	std::stack<int> stack1;
	std::string filename = "test1.txt"; //тест на арифметические операции, иф, иф элсе, некоторые махинации со стеком
	int isFile = 1;
	Executor(isFile, stack1, filename);
	int top = stack1.top();
	EXPECT_EQ(top, 8);
	stack1.pop();
	top = stack1.top();
	EXPECT_EQ(top, 7);
	stack1.pop();
}

TEST(ForthTests, ThrowOnTheStack) {
//тесты на исключения, связанные с размером стека и делением на ноль
 	int isFile = 0;
 	std::stack<int> stack1;

	std::string str = "+";
	EXPECT_ANY_THROW(Executor(isFile, stack1, str));
 	str = "7 *";
 	EXPECT_ANY_THROW(Executor(isFile, stack1, str));
 	str = "5 0 /";
 	EXPECT_ANY_THROW(Executor(isFile, stack1, str));
	str = "2147483647 5 +";
	EXPECT_ANY_THROW(Executor(isFile, stack1, str));
	str = "-2147483647 7 -";
	EXPECT_ANY_THROW(Executor(isFile, stack1, str));
	str = "2147483647 2 *";
	EXPECT_ANY_THROW(Executor(isFile, stack1, str));
	str = "7 swap";
	EXPECT_ANY_THROW(Executor(isFile, stack1, str));
	str = "7 rot";
	EXPECT_ANY_THROW(Executor(isFile, stack1, str));
	str = "7 7 rot";
	EXPECT_ANY_THROW(Executor(isFile, stack1, str));
	str = "7 drop swap";
	EXPECT_ANY_THROW(Executor(isFile, stack1, str));
	str = ".\" hahahahahahahahahhahahahaha";
	EXPECT_ANY_THROW(Executor(isFile, stack1, str));
	str = "4 if 5 if then ;";
	EXPECT_ANY_THROW(Executor(isFile, stack1, str));
	stack1.pop();
	str = "5 if drop 0 if 5 else 4 then ;";
	EXPECT_ANY_THROW(Executor(isFile, stack1, str));
	stack1.pop();
	str = "0 if";
	EXPECT_ANY_THROW(Executor(isFile, stack1, str));
	stack1.pop();
	str = "5 if 7 then";
	EXPECT_ANY_THROW(Executor(isFile, stack1, str));
	stack1.pop();
	str = "5 if drop if else then ;";
	EXPECT_ANY_THROW(Executor(isFile, stack1, str));
	stack1.pop();
	str = "5 >";
	EXPECT_ANY_THROW(Executor(isFile, stack1, str));
	str = "=";
	EXPECT_ANY_THROW(Executor(isFile, stack1, str));
	//str = "10 0 do";
	//EXPECT_ANY_THROW(Executor(isFile, stack1, str));
	// str = "10 0 do 5 loop";
	// EXPECT_ANY_THROW(Executor(isFile, stack1, str));
	// str = "0 10 do 5 loop ;";
	// EXPECT_ANY_THROW(Executor(isFile, stack1, str));
	// str = "do 5 loop ;";
	// EXPECT_ANY_THROW(Executor(isFile, stack1, str));
}


int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}