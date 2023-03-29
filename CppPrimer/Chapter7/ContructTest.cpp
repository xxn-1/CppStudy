/*
* @Author: xu
* @Date:   2023-03-29 16:15:02
* @Last Modified by:
* @Last Modified time: 2023-03-29 16:33:25
* @Function: 测试构造顺序
*/
#include <iostream>
using namespace std;
class X{
    // int i;
    int j; // i要定义在j后
    int i;
public:
    X(int val):j(val),i(j){};
    void show(){
        cout << i << " " << j << endl;
    }
};
int main(){
    X x(2);
    x.show();
    cerr << "22" << endl;
    return 0;
}
