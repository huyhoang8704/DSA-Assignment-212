#include <iostream>
using namespace std;
// Hàm ép kiểu từ int sang float
float intToFloat(int num) {
    return static_cast<float>(num);
}

int main() {
    // float a = 42.0;
    // float b = intToFloat(a);
    // std::cout << "Giá trị nguyên: " << a << std::endl;
    // std::cout << "Giá trị sau khi ép kiểu sang float: " << b << std::endl;
    int result;
    result = 4 < 5 ;
    cout <<result;
    return 0;
}
