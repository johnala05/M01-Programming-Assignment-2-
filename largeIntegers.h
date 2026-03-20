// largeIntegers.h
#ifndef LARGEINTEGERS_H
#define LARGEINTEGERS_H

#include <iostream>
#include <vector>
#include <string>

class largeIntegers {
private:
    std::vector<int> digits; // least significant digit at index 0
    bool isNegative;

    void fromString(const std::string& value);
    std::string toString() const;
    void normalize(); // remove leading zeros, fix sign

    static int compareAbs(const largeIntegers& a, const largeIntegers& b);
    static largeIntegers addAbs(const largeIntegers& a, const largeIntegers& b);
    static largeIntegers subAbs(const largeIntegers& a, const largeIntegers& b); // |a| >= |b|

public:
    // Constructors
    largeIntegers();                         // default 0
    largeIntegers(const std::string& value); // from string
    largeIntegers(long long value);          // from built-in integer (optional convenience)

    // Set and get
    void setValue(const std::string& value);
    std::string getValue() const;

    // Arithmetic operations (member style)
    largeIntegers add(const largeIntegers& other) const;
    largeIntegers subtract(const largeIntegers& other) const;
    largeIntegers multiply(const largeIntegers& other) const;

    // Operator overloads (syntactic sugar)
    largeIntegers operator+(const largeIntegers& other) const;
    largeIntegers operator-(const largeIntegers& other) const;
    largeIntegers operator*(const largeIntegers& other) const;

    bool operator==(const largeIntegers& other) const;
    bool operator!=(const largeIntegers& other) const;
    bool operator<(const largeIntegers& other) const;
    bool operator>(const largeIntegers& other) const;
    bool operator<=(const largeIntegers& other) const;
    bool operator>=(const largeIntegers& other) const;

    // Print
    void print(std::ostream& os = std::cout) const;
};

#endif // LARGEINTEGERS_H
