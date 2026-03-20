// main.cpp
#include <iostream>
#include "largeIntegers.h"

void testFixedNumbers() {
    largeIntegers a("123456789987654321");
    largeIntegers b("987654321123456789");

    std::cout << "Testing with fixed numbers:\n";
    std::cout << "A = ";
    a.print();
    std::cout << "\nB = ";
    b.print();
    std::cout << "\n\n";

    largeIntegers sum = a.add(b);
    largeIntegers diff1 = a.subtract(b);
    largeIntegers diff2 = b.subtract(a);
    largeIntegers prod = a.multiply(b);

    std::cout << "A + B = ";
    sum.print();
    std::cout << "\n";

    std::cout << "A - B = ";
    diff1.print();
    std::cout << "\n";

    std::cout << "B - A = ";
    diff2.print();
    std::cout << "\n";

    std::cout << "A * B = ";
    prod.print();
    std::cout << "\n\n";

    std::cout << "Comparisons:\n";
    std::cout << "A == B? " << (a == b ? "true" : "false") << "\n";
    std::cout << "A <  B? " << (a <  b ? "true" : "false") << "\n";
    std::cout << "A >  B? " << (a >  b ? "true" : "false") << "\n\n";
}

void interactiveMenu() {
    while (true) {
        std::cout << "-----------------------------\n";
        std::cout << "Large Integers Calculator\n";
        std::cout << "1. Add\n";
        std::cout << "2. Subtract\n";
        std::cout << "3. Multiply\n";
        std::cout << "4. Compare\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Exiting.\n";
            return;
        }

        if (choice == 5) {
            std::cout << "Exiting program.\n";
            break;
        }

        std::string s1, s2;
        std::cout << "Enter first large integer: ";
        std::cin >> s1;
        std::cout << "Enter second large integer: ";
        std::cin >> s2;

        largeIntegers x(s1), y(s2);

        switch (choice) {
        case 1: {
            largeIntegers r = x + y;
            std::cout << "Result (x + y) = ";
            r.print();
            std::cout << "\n";
            break;
        }
        case 2: {
            largeIntegers r = x - y;
            std::cout << "Result (x - y) = ";
            r.print();
            std::cout << "\n";
            break;
        }
        case 3: {
            largeIntegers r = x * y;
            std::cout << "Result (x * y) = ";
            r.print();
            std::cout << "\n";
            break;
        }
        case 4: {
            std::cout << "x == y? " << (x == y ? "true" : "false") << "\n";
            std::cout << "x <  y? " << (x <  y ? "true" : "false") << "\n";
            std::cout << "x >  y? " << (x >  y ? "true" : "false") << "\n";
            break;
        }
        default:
            std::cout << "Invalid choice.\n";
            break;
        }

        std::cout << "\n";
    }
}

int main() {
    // Required test with given numbers
    testFixedNumbers();

    // Optional interactive part (good for screenshots / grading)
    interactiveMenu();

    return 0;
}
