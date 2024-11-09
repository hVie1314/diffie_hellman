#include "generate_private_key.h"
#include <random>

// tạo khóa riêng ngẫu nhiên nằm trong khoảng [2, p - 2]
BigInteger generate_private_key(BigInteger p)
{
    // kiểm tra xem có khả thi để tạo khóa cho số nguyên tố p không
    BigInteger temp("3");
    if (p <= temp)
    {
        cout << "Can not generate private key for this prime number" << endl;
    }
    // khởi tạo các tham số cần thiết
    string primeNum = p.getValue();
    char maxNum = primeNum[0];
    bool isSmaller = false;
    string strResult = "";
    random_device rd;
    mt19937 gen(rd());

    // thực hiện random số ngẫu nhiên từ [0, p]
    for (int i = 0; i < primeNum.length(); i++)
    {
        // kiểm tra xem số hiện tại đã nhỏ hơn p chưa
        if (!isSmaller)
        {
            maxNum = primeNum[i];
        }
        uniform_int_distribution<int> distribution(0, maxNum - '0');
        char ranValue = distribution(gen) + '0';
        strResult.push_back(ranValue);
        if (ranValue < maxNum)
        {
            isSmaller = true;
            maxNum = '9';
        }
    }

    size_t non_zero_pos = strResult.find_first_not_of('0');
    if (non_zero_pos == std::string::npos)
    {
        strResult = "0";
    }
    else
    {
        strResult.erase(0, non_zero_pos);
    }
    // Kiểm tra để đảm bảo khóa nằm trong khoảng từ [2, p - 2]
    BigInteger result(strResult);
    temp.setValue("2");
    if (result >= temp && result <= p - temp)
    {
        // nếu result nằm trong khoảng [2, p -2] thì trả về p
        return result;
    }
    else
    {
        // nếu result nằm ngoài khoảng [2, p - 2] thì ta cộng 2 vào và mod cho p - 2
        result = result + temp;
        result = result % (p - temp);
        return result;
    }
}
