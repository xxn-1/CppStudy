/*
 * @Author:
 * @Date:   2023-05-08 16:39:15
 * @Last Modified by:
 * @Last Modified time: 2023-05-08 16:40:51
 * @Function:
 */
#include <cstdint>
#include <iostream>
using namespace std;
// 取反码
// 补码表示，对于正数，k >> 31后即为0000 0000 0000 0000 0000 0000 0000
// 0000，而对于负数，k >> 31后即为1111 1111 1111 1111 1111 1111 1111 1111；

int64_t getReverse(int64_t num)
{
    int size = sizeof(num) * 8 - 1;
    return num^ (num >> size);
}
int main(int argc, char const *argv[])
{
    cout << getReverse(-3);
    return 0;
}
