/*
 * @Author: xu
 * @Date:   2023-03-29 08:35:56
 * @Last Modified by:
 * @Last Modified time: 2023-03-29 10:14:01
 * @Function: 迭代器版本3-20
 */
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;
using as = vector< int >;

int main()
{
    as v{1, 4, 19, 30, 232, 42, -21, 932, 412, 12, 1032, 12, -1, 23, -4};
    // 相邻整数输出
    int sum = *v.begin();
    for (auto i = v.begin() + 1; i != v.end(); i++)
    {
        sum += *i;
        cout << sum << endl;
        sum = *i;
    }
    cout << "=======================================" << endl;
    // task2
    //
    const decltype(v.size()) len = v.size();
    for (auto i = v.begin(); i <= v.begin() + (len / 2); i++)
    {
        if (i != v.begin() + (len - (i - v.begin()) - 1))
            cout << *i + *(v.begin() + (len - (i - v.begin()) - 1)) << endl;
        else
            cout << *i << endl;
    }
    return 0;
}
