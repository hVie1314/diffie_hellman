#include "BigInteger.h"
#include <vector>
#include<string>
#include <algorithm> // reverse
#include <stdexcept>

BigInteger::BigInteger(string val) : value(val) {}

BigInteger BigInteger::operator+(const BigInteger& other) const {
    return BigInteger(add(this->value, other.value));
}

BigInteger& BigInteger::operator=(const BigInteger& other) {
    if (this != &other) {
        this->value = other.value;
    }
    return *this;
}

bool BigInteger::operator==(const BigInteger& other) const {
    return this->value == other.value;
}

bool BigInteger::operator!=(const BigInteger& other) const {
    return this->value != other.value;
}

bool BigInteger::operator>=(const BigInteger& other) const {
    return this->value >= other.value;
}

bool BigInteger::operator<=(const BigInteger& other) const {
    return this->value <= other.value;
}

BigInteger BigInteger::operator-(const BigInteger& other) const {
    return BigInteger(subtract(this->value, other.value));
}

BigInteger BigInteger::operator*(const BigInteger& other) const {
    return BigInteger(multiply(this->value, other.value));
}

BigInteger BigInteger::operator/(int divisor) const {
    if (divisor == 2) {
        return BigInteger(divideBy2(this->value));
    }
    throw invalid_argument("Only division by 2 is implemented.");
}

BigInteger BigInteger::operator%(const BigInteger& other) const {
    return BigInteger(mod(this->value, other.value));
}

ostream& operator<<(ostream& os, const BigInteger& bigInt) {
    os << bigInt.value;
    return os;
}

string BigInteger::add(string num1, string num2) const {
    string result = "";
    int carry = 0;
    int n1 = num1.size(), n2 = num2.size();
    int i = n1 - 1, j = n2 - 1;

    // Cộng từ phải sang trái
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += num1[i--] - '0';
        if (j >= 0) sum += num2[j--] - '0';

        carry = sum / 10;
        result.push_back(sum % 10 + '0');
    }

    reverse(result.begin(), result.end());
    return result;
}

string BigInteger::subtract(string num1, string num2) const {
    bool negativeResult = false;
    
    // Đảm bảo num1 luôn là số lớn hơn hoặc bằng num2
    if (!isGreaterOrEqual(num1, num2)) {
        swap(num1, num2);  // Đổi chỗ nếu num1 < num2
        negativeResult = true; // Đánh dấu kết quả là âm
    }

    string result = "";
    int n1 = num1.size(), n2 = num2.size();
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());

    int carry = 0;
    for (int i = 0; i < n2; i++) {
        int sub = (num1[i] - '0') - (num2[i] - '0') - carry;
        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        result.push_back(sub + '0');
    }

    for (int i = n2; i < n1; i++) {
        int sub = (num1[i] - '0') - carry;
        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        result.push_back(sub + '0');
    }

    reverse(result.begin(), result.end());
    result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));

    // Thêm dấu âm nếu kết quả là âm
    if (negativeResult) {
        result = "-" + result;
    }
    return result;
}


bool BigInteger::isGreaterOrEqual(string num1, string num2) const {
    if (num1.size() > num2.size()) return true;
    if (num1.size() < num2.size()) return false;
    for (int i = 0; i < num1.size(); ++i) {
        if (num1[i] > num2[i]) return true;
        if (num1[i] < num2[i]) return false;
    }
    return true;
}

string BigInteger::multiply(string num1, string num2) const {
    if (num1 == "0" || num2 == "0") return "0";

    vector<int> result(num1.size() + num2.size(), 0);
    for (int i = num1.size() - 1; i >= 0; i--) {
        for (int j = num2.size() - 1; j >= 0; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = result[i + j + 1] + mul;
            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }

    string product;
    for (int num : result)
        if (!(product.empty() && num == 0))
            product.push_back(num + '0');

    return product.empty() ? "0" : product;
}

string BigInteger::divideBy2(string num) const {
    string result;
    int carry = 0;
    for (char digit : num) {
        int current = carry * 10 + (digit - '0');
        result.push_back(current / 2 + '0');
        carry = current % 2;
    }
    while (result.size() > 1 && result[0] == '0')
        result.erase(result.begin());
    return result;
}

string BigInteger::mod(string num, string a) const {
    string result = "0";
    for (char digit : num) {
        result = multiply(result, "10");
        result = add(result, string(1, digit));
        result = modInternal(result, a);
    }
    return result;
}

string BigInteger::modInternal(string num, string a) const {
    string remainder = num;
    while (isGreaterOrEqual(remainder, a)) {
        remainder = subtract(remainder, a);
    }
    return remainder;
}

string BigInteger::getValue() const {
    return value;
}

void BigInteger::setValue(string val) {
    value = val;
}