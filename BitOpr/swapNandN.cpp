/*
* @Author:
* @Date:   2023-05-08 17:17:00
* @Last Modified by:
* @Last Modified time: 2023-05-08 17:20:19
* @Function:
*/
#include <iostream>
using namespace std;
// 交换高n位和低n位。
int swaps(int a) {
    int size = sizeof(a)/2;
    return  (a >> size) | (a << size);

}
int main() {
    cout << swaps(3);
}
//https://blog.csdn.net/m0_64183293/article/details/122519405
