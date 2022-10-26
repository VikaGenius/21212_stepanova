// Forth.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Factory.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>

bool IsNumber(const std::string& str) {
    return std::all_of(str.begin(), str.end(), [](const char& ch) { return isdigit(ch); });
}


void IfOperator(std::stringstream& stream, std::stack <int>& stack1, Factory& factory, std::string& str, std::string& word);
void Cycle(std::stack <int>& stack1, Factory& factory, std::string& str);

void Parser(std::stringstream& stream, std::stack <int>& stack1, Factory& factory, std::string& str, std::string& word) {
    if (IsNumber(word)) {
        stack1.push(std::stoi(word));
    }
    else if (word == "if") {
        IfOperator(stream, stack1, factory, str, word);
    }
    else if (word == "do") {
        Cycle(stack1, factory, str);
    }
    else {
        factory.createCommandByName(word)->Operation(word, stack1);
    }
}

void IfOperator(std::stringstream& stream, std::stack <int>& stack1, Factory& factory, std::string& str, std::string& word) {
    if (str.substr(str.size()-6) != "then ;") { 
        throw std::invalid_argument("Error: unknown command"); 
    }
    str.erase(str.size() - 6);
    if (stack1.top() != 0) {
        while (stream >> word && word != "else") {
            //    if (IsNumber(word)) {
            //        stack1.push(std::stoi(word));
            //    }
            //    else if (word == "if") {
            //        IfOperator(stream, stack1, factory, str, word);
            //        break;
            //    }
            //    //ду луп
            //    else {
            //        factory.createCommandByName(word)->Operation(word, stack1);
            //    }
            //}
            Parser(stream, stack1, factory, str, word);
        }
    }
    else {
        int countIf = 0;
        while (stream >> word && word != "else") {
            if (word == "if") {
                countIf++;
            }
            if (word == "then") {
                stream >> word;
                if (word == ";") {
                    countIf--;
                }
                else {
                    throw std::invalid_argument("Error: unknown command");
                }
            }
            if (word == "else" && countIf == 0) {
                while (stream >> word) {
                    Parser(stream, stack1, factory, str, word);
                }
            }
        }

    }
    
}

void Cycle(std::stack <int>& stack1, Factory& factory, std::string& str) {
    if (str.substr(str.size() - 6) != "loop ;") {
        throw std::invalid_argument("Error: unknown command");
    }
    str.erase(str.size() - 6);
    int i = stack1.top();
    stack1.pop();
    int end = stack1.top();
    stack1.pop();
    std::string str1;
    std::stringstream stream1;
    std::string word;
    for (i; i < end; i++) {
        str1 = str;
        stream1 << str1;
        while(stream1 >> word) {
            Parser(stream1, stack1, factory, str, word);
        }
    }

}

int main()
{
    std::cout << "Hello World!\n";

    std::ifstream file("file.txt");
    std::string str, word;
    std::stringstream stream;

    std::stack <int> stack1;
    Factory factory;

    while (std::getline(file, str)) {
        stream << str;
        while (stream >> word) {
            if (IsNumber(word)) {
                stack1.push(std::stoi(word));
            }
        
            else if (word == "if") {
                IfOperator(stream, stack1, factory, str, word);
                continue;
            }
            else if (word == "do") {
                Cycle(stack1, factory, str);
                continue;
            }
            //принтстринг
            else {
                factory.createCommandByName(word)->Operation(word, stack1);
            }
        }
    }

    return 0;
}

