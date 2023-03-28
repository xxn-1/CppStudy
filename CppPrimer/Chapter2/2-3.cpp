/*
 * @Author: xu
 * @Date:   2023-03-28 11:42:27
 * @Last Modified by: xu
 * @Last Modified time: 2023-03-28 13:42:23
 * @Function:计算各种类型数据
 */
#include <iostream>
using namespace std;
int main()
{
    uint8_t u = 10, u2 = 42;
    uint8_t u_ = u - u2;
    cout << u_ << endl;
    // cout << u2 - u << endl;
    int8_t i1 = -2;
    uint8_t i2 = 2;
    cout << i1 + i2 << endl;
    // 值为0
    //
    float f1 = 1.3e3f;
    cout << f1 << endl;

}
