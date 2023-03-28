/*
* @Author: CGSW057
* @Date:   2023-03-28 08:49:31
* @Last Modified by:   CGSW057
* @Last Modified time: 2023-03-28 09:59:23
* @Function: 计算某个类型的字节数
*/
#include "iostream"
#include <cstdint>
using namespace std;
int main() {
    // 计算uint16_t位数
    // uint16_t i1 = ~0; // 2字节
    // uint32_t i1 = ~0; // 4字节
    uint64_t i1 = ~0; // 8字节
    //
    int count = 0;
    while(i1) {
        i1 >>= 8;
        count++;
    }
    cerr << count << endl;
    return -1;
}
