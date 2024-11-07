#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // For reverse
#include <stdexcept>

using namespace std;

class BigInteger {
private:
    string value; // Attribute để lưu giá trị chuỗi số lớn

public:
    // Constructor để khởi tạo đối tượng BigInteger với giá trị chuỗi
    BigInteger(string val) : value(val) {}

    // Định nghĩa toán tử cộng
    BigInteger operator+(const BigInteger& other) {
        return BigInteger(add(this->value, other.value));
    }

    BigInteger& operator=(const BigInteger& other) {
        if (this != &other) { // Kiểm tra nếu không phải là gán chính nó
            this->value = other.value;
        }
        return *this;
    }

    bool operator==(const BigInteger& other) const {
        return this->value == other.value;
    }

    bool operator!=(const BigInteger& other) const {
        return this->value != other.value;
    }

    bool operator>=(const BigInteger& other) const {
        return this->value >= other.value;
    }
    
    bool operator<=(const BigInteger& other) const {
        return this->value <= other.value;
    }

    // Định nghĩa toán tử trừ
    BigInteger operator-(const BigInteger& other) {
        return BigInteger(subtract(this->value, other.value));
    }

    // Định nghĩa toán tử nhân
    BigInteger operator*(const BigInteger& other) {
        return BigInteger(multiply(this->value, other.value));
    }

    // Định nghĩa toán tử chia (chia cho 2)
    BigInteger operator/(int divisor) {
        if (divisor == 2) {
            return BigInteger(divideBy2(this->value));
        }
        throw invalid_argument("Only division by 2 is implemented.");
    }

    // Định nghĩa toán tử chia lấy dư
    BigInteger operator%(const BigInteger& other) {
        return BigInteger(mod(this->value, other.value));
    }

    friend ostream& operator<<(ostream& os, const BigInteger& bigInt) {
        os << bigInt.value;
        return os;
    }

    // Phương thức để cộng hai số lớn dưới dạng chuỗi
    string add(string num1, string num2) {
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

    // Phương thức để trừ hai số lớn dưới dạng chuỗi
    string subtract(string num1, string num2) {
        if (!isGreaterOrEqual(num1, num2))
            return "0"; // Giới hạn nếu num1 < num2 (đơn giản hóa)

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
            }
            else {
                carry = 0;
            }
            result.push_back(sub + '0');
        }

        for (int i = n2; i < n1; i++) {
            int sub = (num1[i] - '0') - carry;
            if (sub < 0) {
                sub += 10;
                carry = 1;
            }
            else {
                carry = 0;
            }
            result.push_back(sub + '0');
        }

        reverse(result.begin(), result.end());
        result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
        return result;
    }

    // Phương thức kiểm tra nếu num1 >= num2
    bool isGreaterOrEqual(string num1, string num2) {
        if (num1.size() > num2.size()) return true;
        if (num1.size() < num2.size()) return false;
        for (int i = 0; i < num1.size(); ++i) {
            if (num1[i] > num2[i]) return true;
            if (num1[i] < num2[i]) return false;
        }
        return true;
    }

    // Phương thức nhân hai số lớn dưới dạng chuỗi
    string multiply(string num1, string num2) {
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

    // Phương thức chia một số lớn dưới dạng chuỗi cho 2
    string divideBy2(string num) {
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

    // Phương thức tính num % a dưới dạng chuỗi
    string mod(string num, string a) {
        string result = "0";
        for (char digit : num) {
            result = multiply(result, "10");
            result = add(result, string(1, digit));
            result = modInternal(result, a);
        }
        return result;
    }

    // Phương thức tính phần dư (num % a) bằng cách chia thủ công
    string modInternal(string num, string a) {
        string remainder = num;
        while (isGreaterOrEqual(remainder, a)) {
            remainder = subtract(remainder, a);
        }
        return remainder;
    }

    // Getter để lấy giá trị chuỗi số lớn
    string getValue() const {
        return value;
    }

    // Setter để cập nhật giá trị chuỗi số lớn
    void setValue(string val) {
        value = val;
    }
};


BigInteger modular_exponentiation(BigInteger x, BigInteger y, BigInteger p) {
    BigInteger res("1"); // Khởi tạo kết quả là "1"
    x = x % p;           // Modulo x với p

    if (x == BigInteger("0")) return BigInteger("0"); // Nếu x chia hết cho p, trả về "0"

    while (y != BigInteger("0")) {
        // Nếu y là số lẻ, nhân res với x và lấy mod với p
        if ((y.getValue().back() - '0') % 2 != 0)
            res = (res * x) % p;

        // y bây giờ phải là số chẵn, chia y cho 2
        y = y / 2;
        x = (x * x) % p; // Thay x thành x^2 và lấy mod với p
    }

    return res;
}

// Hàm main để kiểm tra
int main() {
    BigInteger x("2");
    BigInteger y("5125");
    BigInteger p("58905897777877889755588822222254895359858835");

    cout << "Power is " << modular_exponentiation(x, y, p) << endl;
    return 0;
}