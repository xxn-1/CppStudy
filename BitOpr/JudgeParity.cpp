/*
 * @Author:
 * @Date:   2023-03-30 10:41:00
 * @Last Modified by:
 * @Last Modified time: 2023-03-30 10:42:30
 * @Function: 判断奇偶数
 */
#include <iostream>
using namespace std;
bool judge(int x)
{
    return x & 1 ? true : false;
}
int main(int argc, char const *argv[])
{
    cout << judge(0);
    return 0;
}
