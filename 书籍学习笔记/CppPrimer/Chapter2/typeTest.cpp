/* xu
 * @Author:
 * @Date:   2023-03-28 15:28:12
 * @Last Modified by:
 * @Last Modified time: 2023-03-28 15:49:50
 * @Function: 测试auto/decltype
 */
#include <iostream>
#include <typeinfo>
using namespace std;
int getNum()
{
    return 3;
}


int main()
{
    auto a = 2;
    const auto b = "aa";
    decltype(getNum()) c = getNum();
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    int &d = a;
    decltype(d) e = a;  // e是引用int类型，所以此时为int &类型。
    decltype(d + 0) f;  // f是int类型
    cout << typeid(e).name() << endl;
    cout << typeid(b).name() << endl;
}
