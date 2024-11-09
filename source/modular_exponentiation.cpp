#include"BigInteger.h"

using namespace std;

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