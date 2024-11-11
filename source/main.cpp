#include "modular_exponentiation.h" // Đã bao gồm BigInteger và hàm modular_exponentiation
#include "generate_safe_prime.h"     // Đã bao gồm hàm generateSafePrime và generate_private_key
#include "generate_private_key.h"
#include <iostream>

using namespace std;

int main() {
    // Tạo một số nguyên tố an toàn (safe prime) p và một số nguyên g là căn nguyên thủy của p
    BigInteger p = generateSafePrime(512); // Sử dụng 512-bit số nguyên tố an toàn
    BigInteger g("2"); // Căn nguyên thủy, giả sử g = 2

    // Bên A và B sẽ tạo khóa riêng tư ngẫu nhiên trong khoảng [2, p-2]
    BigInteger private_key_A = generate_private_key(p);
    BigInteger private_key_B = generate_private_key(p);

    // Tính khóa công khai của A và B dựa trên khóa riêng và số nguyên căn thủy
    BigInteger public_key_A = modular_exponentiation(g, private_key_A, p);
    BigInteger public_key_B = modular_exponentiation(g, private_key_B, p);

    // Tính khóa chung mà mỗi bên sẽ có
    BigInteger shared_secret_A = modular_exponentiation(public_key_B, private_key_A, p);
    BigInteger shared_secret_B = modular_exponentiation(public_key_A, private_key_B, p);

    cout << "Shared secret that Alice can solve: " << shared_secret_A << endl;
    cout << "Shared secret that Bob can solve " << shared_secret_B << endl;

    // Kiểm tra tính hợp lệ của khóa chung
    std::cout << "Does the process correct? " << (shared_secret_A == shared_secret_B) << "\n";

    return 0;
}
