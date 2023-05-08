#include <iostream>
using namespace std;
// 以下操作基本都仅限于无符号，但是函数参数使用了int，这是错误没修改。
int getPosNBit(int a, int n)
{
    return (a >> (n - 1)) & 1;
}
void setPosN_1_Bit(int &a, int n)
{
    a | (1 << (n - 1));
}
void setPosN_0_Bit(int &a, int n)
{
    a & ~(1 << (n - 1)); // 将n的二进制的第m位改为0
}
void setReversePosN(int &a, int n)
{
    a ^ (1 << (n - 1)); // 取反第n位
}
int getPos1ToN(int &a, int n)
{
    return a & ((1 << n) - 1);
} // 取出后n位
void setReverse1ToN(int &a, int n) // 后N位取反
{
    a ^ ((1 << n) - 1);
}
void set1ToN_1_Bit(int &a, int n) // 后N位设1
{
    a | ((1 << n) - 1);
}
void set1TO0(int &a) // 把右边连续的1设为0 100101111->100100000
{
    a &(a + 1);
}
void set0TO1(int &a) // 把右边连续的0设为1
{
    a | (a - 1);
}
void theFirst0To1(int &a) // 右起的第1个0设1
{
    a | (a + 1);
}
int getLianxu1Right(int &a) // (100101111->1111)
{
    return (a ^ (a + 1)) >> 1;
}
void removeTheFirst1Left(int &a) // 去掉右起第一个1的左边
{
    a &(a ^ (a - 1));
}
int main()
{
}