/*
 * @Author: xu
 * @Date:   2023-03-29 13:24:12
 * @Last Modified by:
 * @Last Modified time: 2023-03-29 13:34:27
 * @Function: 测试可变形参
 */
#include <initializer_list>
#include <iostream>
using namespace std;
void func(initializer_list< int > t)
{
    for (auto x : t)
    {
        cout << x << " ";
    }
    cout << endl;
}
int main(int argc, char const *argv[])
{
    /* code */
    func({1,2,3,4});
    cout << __FILE__ << endl;
    return 0;
}
