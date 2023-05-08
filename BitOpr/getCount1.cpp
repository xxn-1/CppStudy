/*
* @Author:
* @Date:   2023-05-08 16:50:45
* @Last Modified by:
* @Last Modified time: 2023-05-08 17:11:06
* @Function:
*/
#include <iostream>
using namespace std;
// 求1出现的次数
//https://cloud.tencent.com/developer/beta/article/1967368?areaSource=&traceId=
int count_one(int n) {
    int count = 0;
    while(n) {
        n = n&(n-1);
        count++;
    }
    return count;
}
inline unsigned count_bits(uint64_t v)
{
    v = (v & 0x5555555555555555) + ((v >> 1) & 0x5555555555555555);
    v = (v & 0x3333333333333333) + ((v >> 2) & 0x3333333333333333);
    v = (v & 0x0f0f0f0f0f0f0f0f) + ((v >> 4) & 0x0f0f0f0f0f0f0f0f);
    v = (v & 0x00ff00ff00ff00ff) + ((v >> 8) & 0x00ff00ff00ff00ff);
    v = (v & 0x0000ffff0000ffff) + ((v >> 16) & 0x0000ffff0000ffff);
    v = (v & 0x00000000ffffffff) + ((v >> 32) & 0x00000000ffffffff);
    return v;
}

inline unsigned count_bits(uint32_t v)
{
    v = (v & 0x55555555) + ((v >> 1) & 0x55555555);
    v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
    v = (v & 0x0f0f0f0f) + ((v >> 4) & 0x0f0f0f0f);
    v = (v & 0x00ff00ff) + ((v >> 8) & 0x00ff00ff);
    v = (v & 0x0000ffff) + ((v >> 16) & 0x0000ffff);
    return v;
}

inline unsigned count_bits(uint16_t v)
{
    v = (v & 0x5555) + ((v >> 1) & 0x5555);
    v = (v & 0x3333) + ((v >> 2) & 0x3333);
    v = (v & 0x0f0f) + ((v >> 4) & 0x0f0f);
    v = (v & 0x00ff) + ((v >> 8) & 0x00ff);
    return v;
}

inline unsigned count_bits(uint8_t v)
{
    v = (v & 0x55) + ((v >> 1) & 0x55);
    v = (v & 0x33) + ((v >> 2) & 0x33);
    v = (v & 0x0f) + ((v >> 4) & 0x0f);
    return v;
}
int main() {
    cout << count_bits(3u);
}
