/*
* @Author:
* @Date:   2023-05-08 17:14:33
* @Last Modified by:
* @Last Modified time: 2023-05-08 17:16:17
* @Function:
*/
#include <iostream>
using namespace std;
// 正数变负数，负数变整数
//
int reversal(int a) {
  return ~a + 1;
}
int main() {
    cout << reversal(3);
}
