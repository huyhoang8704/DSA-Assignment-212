#include <iostream>
#include <typeinfo>

using namespace std;
// Hàm ép kiểu từ int sang float
float intToFloat(int num) {
    return static_cast<float>(num);
}
struct frame {
    int type;
    float data;
};

int main() {
    frame c;
    float a = 5.2;
    int b = 4;
    c.data = int (a-b); 
    // cout <<typeid(c.data).name() << " " << c.data;
    cout << 2000.39 * 72;
    return 0;
}
