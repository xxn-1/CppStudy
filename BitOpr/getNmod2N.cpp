/*
* @Author:
* @Date:   2023-05-08 16:28:10
* @Last Modified by:
* @Last Modified time: 2023-05-08 16:33:12
* @Function:
*/
// n求对2的m次方的取余
#include <cstdint>
#include <iostream>
// m是表示2的m次方
inline uint64_t getNMod2N(uint64_t n,int m) {
    return n & ((1<<m)-1);
}
int main(int argc, char const *argv[])
{
    std::cout << getNMod2N(5, 2);
    return 0;
}
