// largeIntegers.cpp
#include "largeIntegers.h"
#include <cctype>
#include <stdexcept>

// ---------- Private helpers ----------

void largeIntegers::normalize() {
    // Remove leading zeros in internal representation
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
    if (digits.size() == 1 && digits[0] == 0) {
        isNegative = false; // zero is not negative
    }
}

void largeIntegers::fromString(const std::string& value) {
    digits.clear();
    isNegative = false;

    if (value.empty()) {
        digits.push_back(0);
        isNegative = false;
        return;
    }

    std::size_t start = 0;
    if (value[0] == '-') {
        isNegative = true;
        start = 1;
    } else if (value[0] == '+') {
        start = 1;
    }

    for (std::size_t i = value.size(); i > start; --i) {
        char c = value[i - 1];
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            throw std::invalid_argument("Invalid character in number string");
        }
        digits.push_back(c - '0');
    }

    if (digits.empty()) {
        digits.push_back(0);
        isNegative = false;
    }

    normalize();
}

std::string largeIntegers::toString() const {
    if (digits.empty()) {
        return "0";
    }

    std::string result;
    if (isNegative) {
        result.push_back('-');
    }

    for (std::size_t i = digits.size(); i > 0; --i) {
        result.push_back(static_cast<char>('0' + digits[i - 1]));
    }

    return result;
}

int largeIntegers::compareAbs(const largeIntegers& a, const largeIntegers& b) {
    if (a.digits.size() < b.digits.size()) return -1;
    if (a.digits.size() > b.digits.size()) return 1;

    for (std::size_t i = a.digits.size(); i > 0; --i) {
        if (a.digits[i - 1] < b.digits[i - 1]) return -1;
        if (a.digits[i - 1] > b.digits[i - 1]) return 1;
    }
    return 0;
}

largeIntegers largeIntegers::addAbs(const largeIntegers& a, const largeIntegers& b) {
    largeIntegers result;
    result.isNegative = false;
    result.digits.clear();

    int carry = 0;
    std::size_t maxSize = std::max(a.digits.size(), b.digits.size());
    for (std::size_t i = 0; i < maxSize || carry; ++i) {
        int da = (i < a.digits.size()) ? a.digits[i] : 0;
        int db = (i < b.digits.size()) ? b.digits[i] : 0;
        int sum = da + db + carry;
        result.digits.push_back(sum % 10);
        carry = sum / 10;
    }

    result.normalize();
    return result;
}

largeIntegers largeIntegers::subAbs(const largeIntegers& a, const largeIntegers& b) {
    // assumes |a| >= |b|
    largeIntegers result;
    result.isNegative = false;
    result.digits.clear();

    int borrow = 0;
    for (std::size_t i = 0; i < a.digits.size(); ++i) {
        int da = a.digits[i];
        int db = (i < b.digits.size()) ? b.digits[i] : 0;
        int diff = da - db - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits.push_back(diff);
    }

    result.normalize();
    return result;
}

// ---------- Public interface ----------

largeIntegers::largeIntegers() : digits(1, 0), isNegative(false) {}

largeIntegers::largeIntegers(const std::string& value) {
    fromString(value);
}

largeIntegers::largeIntegers(long long value) {
    if (value < 0) {
        isNegative = true;
        value = -value;
    } else {
        isNegative = false;
    }

    if (value == 0) {
        digits.push_back(0);
    } else {
        while (value > 0) {
            digits.push_back(static_cast<int>(value % 10));
            value /= 10;
        }
    }
    normalize();
}

void largeIntegers::setValue(const std::string& value) {
    fromString(value);
}

std::string largeIntegers::getValue() const {
    return toString();
}

largeIntegers largeIntegers::add(const largeIntegers& other) const {
    largeIntegers result;

    if (this->isNegative == other.isNegative) {
        result = addAbs(*this, other);
        result.isNegative = this->isNegative;
    } else {
        int cmp = compareAbs(*this, other);
        if (cmp == 0) {
            result = largeIntegers("0");
        } else if (cmp > 0) {
            result = subAbs(*this, other);
            result.isNegative = this->isNegative;
        } else {
            result = subAbs(other, *this);
            result.isNegative = other.isNegative;
        }
    }

    result.normalize();
    return result;
}

largeIntegers largeIntegers::subtract(const largeIntegers& other) const {
    largeIntegers negOther = other;
    negOther.isNegative = !other.isNegative;
    return this->add(negOther);
}

largeIntegers largeIntegers::multiply(const largeIntegers& other) const {
    largeIntegers result;
    result.digits.assign(this->digits.size() + other.digits.size(), 0);
    result.isNegative = (this->isNegative != other.isNegative);

    for (std::size_t i = 0; i < this->digits.size(); ++i) {
        int carry = 0;
        for (std::size_t j = 0; j < other.digits.size() || carry; ++j) {
            long long cur = result.digits[i + j] +
                            static_cast<long long>(this->digits[i]) *
                            (j < other.digits.size() ? other.digits[j] : 0) +
                            carry;
            result.digits[i + j] = static_cast<int>(cur % 10);
            carry = static_cast<int>(cur / 10);
        }
    }

    result.normalize();
    return result;
}

// Operator overloads

largeIntegers largeIntegers::operator+(const largeIntegers& other) const {
    return add(other);
}

largeIntegers largeIntegers::operator-(const largeIntegers& other) const {
    return subtract(other);
}

largeIntegers largeIntegers::operator*(const largeIntegers& other) const {
    return multiply(other);
}

bool largeIntegers::operator==(const largeIntegers& other) const {
    return isNegative == other.isNegative && digits == other.digits;
}

bool largeIntegers::operator!=(const largeIntegers& other) const {
    return !(*this == other);
}

bool largeIntegers::operator<(const largeIntegers& other) const {
    if (isNegative != other.isNegative) {
        return isNegative && !other.isNegative;
    }

    int cmp = compareAbs(*this, other);
    if (!isNegative) {
        return cmp < 0;
    } else {
        return cmp > 0;
    }
}

bool largeIntegers::operator>(const largeIntegers& other) const {
    return other < *this;
}

bool largeIntegers::operator<=(const largeIntegers& other) const {
    return !(*this > other);
}

bool largeIntegers::operator>=(const largeIntegers& other) const {
    return !(*this < other);
}

void largeIntegers::print(std::ostream& os) const {
    os << toString();
}
