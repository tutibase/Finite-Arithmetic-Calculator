#include "myArithmetic.h"

myNum::myNum() {
	zeroing();
	is_positive = 1;
}

myNum::myNum(std::string num) : myNum() {
	bool flag = 0;
	if (num[0] == '-') {
		is_positive = 0;
		flag = 1;
	}
	for (int i = 0; i < num.size() - flag; i++) {
		this->num[this->num.size() - 1 - i] = num[num.size() - 1 - i];
	}
}

void myNum::zeroing() {
	num.resize(8);
	for (int i = 0; i < 8; i++) {
		num[i] = 'a';
	}
}

myNum myNum::operator + (const myNum& other) const {
	myNum result;
	if (!this->is_positive and !other.is_positive) result.is_positive = 0;
	if (this->is_positive and !other.is_positive) return *this - other.abs();
	if (!this->is_positive and other.is_positive) return other - this->abs();

	char inShift = 'a';
	char outShift = 'a';
	char tmp = 'a';

	for (int i = num.size() - 1; i > -1; i--) {
		inShift = outShift;
		outShift = 'a';
		result.num[i] = this->num[i];

		while (inShift != 'a') {
			if (result.num[i] == 'e') {
				result.num[i] = 'a';
				outShift = 'b';
				inShift = digits[index(inShift) - 1];
				continue;
			}
			result.num[i] = digits[index(result.num[i]) + 1];
			inShift = digits[index(inShift) - 1];
		}

		tmp = other.num[i];
		while (tmp != 'a') {
			if (result.num[i] == 'e') {
				result.num[i] = 'a';
				outShift = 'b';
				tmp = digits[index(tmp) - 1];
				continue;
			}
			result.num[i] = digits[index(result.num[i]) + 1];
			tmp = digits[index(tmp) - 1];
		}
	}
	if (outShift != 'a') result.num = "overflow";
	return result;
}

myNum myNum::operator - (const myNum& other) const {
	myNum result;
	if (this->is_positive and !other.is_positive) return *this + other.abs();
	if (!this->is_positive and other.is_positive) {
		result = this->abs() + other.abs();
		result.is_positive = 0;
		return result;
	}
	if (!this->is_positive and !other.is_positive) return other.abs() - this->abs();

	if (other.absCmp(*this)) {
		result = other - *this;
		result.is_positive = 0;
		return result;
	}

	char inShift = 'a';
	char outShift = 'a';
	char tmp = 'a';

	for (int i = num.size() - 1; i > -1; i--) {
		inShift = outShift;
		outShift = 'a';
		result.num[i] = this->num[i];

		if (inShift != 'a') {
			if (result.num[i] == 'a') {
				result.num[i] = 'e';
				outShift = 'b';
			}
			else {
				result.num[i] = digits[index(result.num[i]) - 1];
			}
		}

		tmp = other.num[i];
		while (tmp != 'a') {
			if (result.num[i] == 'a') {
				result.num[i] = 'e';
				outShift = 'b';
				tmp = digits[index(tmp) - 1];
				continue;
			}
			result.num[i] = digits[index(result.num[i]) - 1];
			tmp = digits[index(tmp) - 1];
		}
	}
	return result;
}

myNum myNum::operator * (const myNum& other) const {
	myNum result;
	for (myNum i; i != other.abs(); i = i + myNum("b")) {
		result = result + *this;
		if (result.num == "overflow") return result;
	}
	result.is_positive = (result.is_positive == other.is_positive);
	return result;
}

myNum myNum::operator / (const myNum& other) const {
	myNum result;
	myNum remainder(*this);
	myNum i("b");
	if (other == myNum("a").getNum()) {
		if (this->abs() == other.abs())
			result.num = "[-eeeeeeee; eeeeeeee]";
		else
			result.num = "empty set";
		goto stop;
	}

	if (other.is_positive != this->is_positive) i.is_positive = 0;

	while ((remainder.absCmp(other)) or (remainder.num == other.num) or (!remainder.is_positive)) {
		result = result + i;
		if (other.is_positive != remainder.is_positive)
			remainder = remainder + other;
		else
			remainder = remainder - other;
	}
	if (remainder.getNum() != "a")
		result.num = result.getNum() + '(' + remainder.getNum() + ')';
	else result.num = result.getNum();
stop:
	result.is_positive = 1; // для корректного вывода (строчкой выше в result.num уже попадает знак)
	return result;
}

myNum myNum::Pow(const myNum& other) const {
	myNum result("b");
	for (myNum i; i != other.abs(); i = i + myNum("b")) {
		if (result.num == "overflow") return result.getNum();
		result = result * (*this);
	}
	if (!other.is_positive) result = myNum("b") / result;
	return result;
}

bool myNum::operator != (const myNum& other) const {
	return (this->num != other.num or this->is_positive != other.is_positive);
}

bool myNum::operator == (const myNum& other) const {
	return !(*this != other);
}


bool myNum::absCmp(const myNum& other) const {
	for (int i = 0; i < this->num.size(); i++) {
		if (index(this->num[i]) > index(other.num[i])) return 1;
		if (index(this->num[i]) < index(other.num[i])) return 0;
	}
	return 0;
}

myNum myNum::abs() const {
	myNum result(this->num);
	result.is_positive = 1;
	return result;
}

std::string myNum::getNum() const {
	if (num == "aaaaaaaa") return "a";
	bool start = 0;
	std::string result;
	for (int i = 0; i < num.size(); i++) {
		if (num[i] != 'a') start = 1;
		if (start) result += num[i];
	}
	if (!this->is_positive) return "-" + result;
	return result;
}


int index(char c) {
	auto itr = std::find(digits.begin(), digits.end(), c);

	if (itr != digits.cend()) {
		return std::distance(digits.begin(), itr);
	}
	else {
		std::cout << "\n\nElement not found!\n\n";
		return -1;
	}
}

std::string stringInput(const char* msg) {
	std::cout << msg;
	std::string val;
	bool flag = 0;
	while (true) {
		std::cin >> val;
		flag = 0;
		for (int i = 0; i < val.size(); i++) {
			if ((val[i] < 'a' or val[i] > 'h') and !(i == 0 and val[i] == '-')) flag = 1;
		}
		if (std::cin.peek() != '\n' or flag or
			(val.size() > 8 and val[0] != '-') or
			(val.size() > 9 and val[0] == '-') or
			(val == "-"))
		{
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			printf("\nIncorrect input!\n");
		}
		else break;
	}
	return val;
}

char signInput(const char* msg) {
	std::cout << msg;
	char val;
	while (true) {
		std::cin >> val;

		if (std::cin.peek() != '\n' or (val != '+' and val != '-' and val != '*' and val != '/' and val != '^')) {
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			printf("\nIncorrect input!\n");
		}
		else break;
	}
	return val;
}

char continueInput(const char* msg) {
	std::cout << msg;
	char val;
	while (true) {
		std::cin >> val;
		if (std::cin.peek() != '\n' or (val != 'y' and val != 'n')) {
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			printf("\nIncorrect input!\n");
		}
		else break;
	}
	return val;
}