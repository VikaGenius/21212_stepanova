#include "gtest/gtest.h"
#include "interpreter.h"

#include <fstream>

TEST(ForthTests, ValueOnTheStack) {
	std::ifstream input("test1.txt");          
    std::ofstream output("out.txt");
	Interpreter a(input, output);
	EXPECT_NO_THROW(a.Executor());
	output.close();
	std::ifstream out("out.txt");
	std::string str;
    std::getline(out, str);
	EXPECT_EQ(str == "1C8754", true);
}

TEST(ForthTests, LogicOperations) {
	std::stringstream str;
	std::ofstream output;
	output.open("out.txt", std::ofstream::out | std::ofstream::trunc);
	str << "3 2 = . 3 3 = . 4 3 > . 3 4 < . 9 5 < . 2 10 > .";
	Interpreter a(str, output);
	EXPECT_NO_THROW(a.Executor());
	output.close();
	std::ifstream out("out.txt");
	std::string str1;
    std::getline(out, str1);
	EXPECT_EQ(str1 == "011100", true);
}

TEST(ForthTests, InternalOperations) {
	std::stringstream str;
	std::ofstream output;
	output.open("out.txt", std::ofstream::out | std::ofstream::trunc);
	str << "5 dup . . 4 6 drop . 8 7 swap . . 4 1 2 3 rot . . . . 3 2 over . . . 66 emit 100 200 . cr ."; 
	Interpreter a(str, output);
	EXPECT_NO_THROW(a.Executor());
	output.close();
	std::ifstream out("out.txt");
	std::string str1;
    std::getline(out, str1);
	EXPECT_EQ(str1 == "554872134323B200", true); 
	std::getline(out, str1);
	EXPECT_EQ(str1 == "100", true);
}

TEST(ForthTests, PrintString) {
	std::stringstream str;
	std::ofstream output;
	output.open("out.txt", std::ofstream::out | std::ofstream::trunc);
	str << ".\" You can handle it!\" 5 ."; 
	Interpreter a(str, output);
	EXPECT_NO_THROW(a.Executor());
	output.close();
	std::ifstream out("out.txt");
	std::string str1;
    std::getline(out, str1);
	EXPECT_EQ(str1 == "You can handle it! ", true); 
	std::getline(out, str1);
	EXPECT_EQ(str1 == "5", true);
}

TEST(ForthTests, NestingIf) {
	std::stringstream str;
	std::ofstream output;
	output.open("out.txt", std::ofstream::out | std::ofstream::trunc);
	str << "1 if 1 . if 1 . if 1 . if 1 . then ; then ; then ; then ;";
	Interpreter a(str, output);
	EXPECT_NO_THROW(a.Executor());
	output.close();
	std::ifstream out("out.txt");
	std::string str1;
    std::getline(out, str1);
	EXPECT_EQ(str1 == "1111", true);
}

TEST(ForthTests, IfElse) {
	std::stringstream str;
	std::ofstream output;
	output.open("out.txt", std::ofstream::out | std::ofstream::trunc);
	str << "0 if 1 else 2 . then ;";
	Interpreter a(str, output);
	EXPECT_NO_THROW(a.Executor());
	output.close();
	std::ifstream out("out.txt");
	std::string str1;
    std::getline(out, str1);
	EXPECT_EQ(str1 == "2", true);
}

TEST(ForthTests, IfElse2) {
	std::stringstream str;
	std::ofstream output;
	output.open("out.txt", std::ofstream::out | std::ofstream::trunc);
	str << "0 if 1 else 2 if 5 . then ; . then ;";
	Interpreter a(str, output);
	EXPECT_NO_THROW(a.Executor());
	output.close();
	std::ifstream out("out.txt");
	std::string str1;
    std::getline(out, str1);
	EXPECT_EQ(str1 == "52", true);
}

TEST(ForthTests, NestingDo) {
	std::stringstream str;
	//std::ofstream output("out1.txt");
	std::ofstream output;
	output.open("out.txt", std::ofstream::out | std::ofstream::trunc);
	str << "2 0 do 5 . 3 0 do 2 . loop ; loop ;";
	Interpreter a(str, output);
	EXPECT_NO_THROW(a.Executor());
	output.close();
	std::ifstream out("out.txt");
	std::string str1;
    std::getline(out, str1);
	EXPECT_EQ(str1 == "52225222", true);
}

TEST(ForthTests, Throw) {
//тесты на исключения, связанные с размером стека и делением на ноль, неправильным вводом команд
	std::stringstream str;
	str << "+";
	Interpreter a(str);
	EXPECT_ANY_THROW(a.Executor());

	std::stringstream str1;
 	str1 << "7 *";
	Interpreter a1(str1);
 	EXPECT_ANY_THROW(a1.Executor());

	std::stringstream str2;
 	str2 << "5 0 /";
	Interpreter a2(str2);
 	EXPECT_ANY_THROW(a2.Executor());

	std::stringstream str3;
	str3 << "2147483647 5 +";
	Interpreter a3(str3);
	EXPECT_ANY_THROW(a3.Executor());

	std::stringstream str4;
	str4 << "-2147483647 7 -";
	Interpreter a4(str4);
	EXPECT_ANY_THROW(a4.Executor());

	std::stringstream str5;
	str5 << "2147483647 2 *";
	Interpreter a5(str5);
	EXPECT_ANY_THROW(a5.Executor());

	std::stringstream str6;
	str6 << "7 swap";
	Interpreter a6(str6);
	EXPECT_ANY_THROW(a6.Executor());

	std::stringstream str7;
	str7 << "7 rot";
	Interpreter a7(str7);
	EXPECT_ANY_THROW(a7.Executor());

	std::stringstream str8;
	str8 << "7 7 rot";
	Interpreter a8(str8);
	EXPECT_ANY_THROW(a8.Executor());

	std::stringstream str9;
	str9 << "7 drop swap";
	Interpreter a9(str9);
	EXPECT_ANY_THROW(a9.Executor());

	std::stringstream str10;
	str10 << ".\" hahahahahahahahahhahahahaha";
	Interpreter a10(str10);
	EXPECT_ANY_THROW(a10.Executor());

	std::stringstream str11;
	str11 << "4 if 5 if then ;";
	Interpreter a11(str11);
	EXPECT_ANY_THROW(a11.Executor());

	std::stringstream str12;
	str12 << "5 if drop 0 if 5 else 4 then ;";
	Interpreter a12(str12);
	EXPECT_ANY_THROW(a12.Executor());

	std::stringstream str13;
	str13 << "0 if";
	Interpreter a13(str13);
	EXPECT_ANY_THROW(a13.Executor());

	std::stringstream str14;
	str14 << "5 if 7 then";
	Interpreter a14(str14);
	EXPECT_ANY_THROW(a14.Executor());

	std::stringstream str15;
	str15 << "5 if drop if else then ;";
	Interpreter a15(str15);
	EXPECT_ANY_THROW(a15.Executor());

	std::stringstream str16;
	str16 << "5 >";
	Interpreter a16(str16);
	EXPECT_ANY_THROW(a16.Executor());

	std::stringstream str17;
	str17 << "=";
	Interpreter a17(str17);
	EXPECT_ANY_THROW(a17.Executor());
	
	std::stringstream str18;
	str18 << "10 0 do";
	Interpreter a18(str18);
	EXPECT_ANY_THROW(a18.Executor());
	
	std::stringstream str19;
	str19 << "10 0 do 5 loop";
	Interpreter a19(str19);
	EXPECT_ANY_THROW(a19.Executor());

	std::stringstream str20;
	str20 << "0 10 do 5 loop ;";
	Interpreter a20(str20);
	EXPECT_ANY_THROW(a20.Executor());

	std::stringstream str21;
	str21 << "do 5 loop ;";
	Interpreter a21(str21);
	EXPECT_ANY_THROW(a21.Executor());

	std::stringstream str22;
	str22 << "if then ;";
	Interpreter a22(str22);
	EXPECT_ANY_THROW(a22.Executor());

	std::stringstream str23;
	str23 << "meow";
	Interpreter a23(str23);
	EXPECT_ANY_THROW(a23.Executor());

	std::stringstream str24;
 	str24 << "5 /";
	Interpreter a24(str24);
 	EXPECT_ANY_THROW(a24.Executor());

	std::stringstream str25;
 	str25 << "/";
	Interpreter a25(str25);
 	EXPECT_ANY_THROW(a25.Executor());
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}