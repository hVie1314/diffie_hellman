#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <string>
#include <iostream>

using namespace std;

class BigInteger {
private:
    string value;

    // Phương thức private
    string add(string num1, string num2) const;
    string subtract(string num1, string num2) const;
    bool isGreaterOrEqual(string num1, string num2) const;
    string multiply(string num1, string num2) const;
    string divideBy2(string num) const;
    string mod(string num, string a) const;
    string modInternal(string num, string a) const;

public:
    // Constructor
    BigInteger(string val);

    // Toán tử cơ bản
    BigInteger operator+(const BigInteger& other) const;
    BigInteger& operator=(const BigInteger& other);
    bool operator==(const BigInteger& other) const;
    bool operator!=(const BigInteger& other) const;
    bool operator>=(const BigInteger& other) const;
    bool operator<=(const BigInteger& other) const;
    BigInteger operator-(const BigInteger& other) const;
    BigInteger operator*(const BigInteger& other) const;
    BigInteger operator/(int divisor) const;
    BigInteger operator%(const BigInteger& other) const;

    // Hàm xuất
    friend ostream& operator<<(ostream& os, const BigInteger& bigInt);

    // Getter và Setter
    string getValue() const;
    void setValue(string val);
};


#endif
