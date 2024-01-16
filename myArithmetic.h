#pragma once
#include <string>
#include <vector>
#include <iostream>

const std::vector<char> digits = { 'a', 'b', 'g', 'c', 'h', 'f', 'd', 'e' };

class myNum {

private:
	std::string num;
	bool is_positive;

public:
	myNum();
	myNum(std::string num);
	void zeroing();
	std::string getNum() const;
	bool absCmp(const myNum& other) const;
	myNum abs() const;

	bool operator != (const myNum& other) const;
	bool operator == (const myNum& other) const;
	myNum operator + (const myNum& other) const;
	myNum operator - (const myNum& other) const;
	myNum operator * (const myNum& other) const;
	myNum operator / (const myNum& other) const;
	myNum Pow(const myNum& other) const;
	
};

int index(char c);
std::string stringInput(const char* msg = "");
char signInput(const char* msg = "");
char continueInput(const char* msg = "");