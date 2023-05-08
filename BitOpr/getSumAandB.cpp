/*
* @Author:
* @Date:   2023-05-08 16:56:31
* @Last Modified by:
* @Last Modified time: 2023-05-08 17:06:49
* @Function:
*/
#include <iostream>
using namespace std;
// 求和
int64_t getSumAandB(int64_t a,int64_t b) {
    if(b==0)return a;
    else if(a==0)return b;
    int sum = a^b,carry =(a&b)<<1;
    return getSumAandB(sum, carry);
}
int main() {
    cout << getSumAandB(-2, -6);
}
