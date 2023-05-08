/*
* @Author:
* @Date:   2023-05-08 16:52:10
* @Last Modified by:
* @Last Modified time: 2023-05-08 16:54:21
* @Function:
*/
#include <iostream>
using namespace std;
// 消除最右边的1
inline int64_t eraseRight1(int64_t num) {
    return num & (num - 1);
}
int main() {
    cout << eraseRight1(3) << endl;
}
