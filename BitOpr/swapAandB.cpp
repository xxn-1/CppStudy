/*
* @Author:
* @Date:   2023-05-08 17:12:06
* @Last Modified by:
* @Last Modified time: 2023-05-08 17:14:01
* @Function:
*/
#include <iostream>
using namespace std;
inline void swap(int64_t &a,int64_t &b) {
    a^=b,b^=a,a^=b;
}

int main() {
    int64_t a = 3;
    int64_t b = -4;
    swap(a,b);
    cout << a << " " << b << endl;
}
