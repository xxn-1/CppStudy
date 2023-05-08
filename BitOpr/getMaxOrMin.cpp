/*
 * @Author:
 * @Date:   2023-05-08 16:47:25
 * @Last Modified by:
 * @Last Modified time: 2023-05-08 16:49:06
 * @Function:
 */
#include <iostream>
using namespace std;

// 得到最大值
inline int64_t getMax(int64_t n, int64_t m)
{
    return (n ^ (n ^ m) & -(n < m)); // 取最大值
}

// 得到最小值
inline int64_t getMin(int64_t n, int64_t m)
{
    return (m ^ (n ^ m) & -(n < m)); // 取最小值
}
// 得到当前类型最大值
inline int getMaxInt()
{
    int size = sizeof((int)1);
    return (int)(1 << (size * 8 - 1)) - 1;
}
inline int getMinInt()
{
    int size = sizeof((int)1);
    return (int)(1 << (size * 8 - 1));
}
int main(int argc, char const *argv[])
{
    cout << getMax(-1, -2) << endl;
    cout << getMin(-1, -2) << endl;
    cout << getMaxInt() << endl;
    cout << getMinInt() << endl;
    return 0;
}
