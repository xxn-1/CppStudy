/*
* @Author:
* @Date:   2023-05-08 16:18:04
* @Last Modified by:
* @Last Modified time: 2023-05-08 16:26:57
* @Function:
*/
#include <cstdint>
#include <iostream>
using namespace std;
inline uint64_t get2N(int n) {
    return 1 << n;;
}
int main(int argc, char const *argv[])
{
    /* code */
    cout << get2N(3) << endl;
    return 0;
}
