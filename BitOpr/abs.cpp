/*
* @Author:
* @Date:   2023-05-08 16:33:29
* @Last Modified by:
* @Last Modified time: 2023-05-08 16:42:18
* @Function:
*/
#include <cstdint>
#include <iostream>
using namespace std;
// 补码表示，对于正数，k >> 31后即为0000 0000 0000 0000 0000 0000 0000 0000，而对于负数，k >> 31后即为1111 1111 1111 1111 1111 1111 1111 1111；
uint64_t getAbs(int64_t num) {
    int size = sizeof(num) * 8 - 1;
    return (num ^ (num >> size)) - (num >> size);
}
// 取绝对值
int main() {
    cout << getAbs(-3) << endl;
}
