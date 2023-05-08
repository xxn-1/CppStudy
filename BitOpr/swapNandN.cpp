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
// https://www.zhihu.com/question/38206659
//http://www.matrix67.com/blog/archives/263
//https://blog.csdn.net/lmhacm/article/details/77287571
//https://zhuanlan.zhihu.com/p/539924958
//https://blog.csdn.net/m0_64183293/article/details/122519405
//https://cloud.tencent.com/developer/beta/article/1967368?areaSource=&traceId=
//https://blog.csdn.net/qq_45709460/article/details/104617456
//https://blog.csdn.net/abcSunl/article/details/69500121
