/*
 * @Author: xu
 * @Date:   2023-03-28 15:02:24
 * @Last Modified by:
 * @Last Modified time: 2023-03-28 15:04:38
 * @Function:
 */
#include <iostream>
using namespace std;
constexpr int getNum(int u)
{
    return u == 2 ? u : u % 2;
}
int main()
{
    constexpr int a = 3;
    constexpr int b = getNum(5);
    cout << a << endl << b << endl;
}
