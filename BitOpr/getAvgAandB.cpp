/*
* @Author:
* @Date:   2023-05-08 16:56:31
* @Last Modified by:
* @Last Modified time: 2023-05-08 16:59:57
* @Function:
*/
#include <iostream>
using namespace std;
// 求平均数
// 第一步：x,y对应位均为1，相加后再除以2还是原来的数，如两个00001111相加后除以2仍得00001111。
// 第二步，对应位有且只有一位为1，用“异或”运算提取出来，然后>>1(右移一位，相当于除以2），即到到第二部分的平均值。
// 第三步，对应位均为零，因为相加后再除以二还是0，所以不用计算。
// 三部分汇总之后就是(x&y)+((x^y)>>1)
int64_t getAvgAandB(int64_t a,int64_t b) {
    return (a&b) + ((a^b) >> 1);
}
int main() {
    cout << getAvgAandB(-2, -6);
}
