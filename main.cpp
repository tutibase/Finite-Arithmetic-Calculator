#include <iostream>
#include "myArithmetic.h"

int main()
{
    std::string s;
    char sign;
    bool flag = 1;

    while (flag) {
        s = stringInput("First num: ");
        myNum a(s);
        s = stringInput("Second num: ");
        myNum b(s);
        sign = signInput("Sing: ");
        std::cout << "\nAnswer: ";
        switch (sign) {
        case '+':
            std::cout << (a + b).getNum() << "\n\n";
            break;

        case '-':
            std::cout << (a - b).getNum() << "\n\n";
            break;

        case '*':
            std::cout << (a * b).getNum() << "\n\n";
            break;

        case '/':
            std::cout << (a / b).getNum() << "\n\n";
            break;

        case '^':
            std::cout << (a.Pow(b)).getNum() << "\n\n";
            break;

        default:
            break;
        }

        std::cout << "----------------------\n\n";
        sign = continueInput("Continue? [y]/[n]: ");
        if (sign == 'n') flag = 0;
    }
}
