/*
 * @Author:
 * @Date:   2023-03-28 16:39:16
 * @Last Modified by:
 * @Last Modified time: 2023-03-29 08:32:40
 * @Function:
 */
#include <iostream>
#include <vector>
using namespace std;
using as = vector< int >;
int main()
{
    as v{1, 4, 19, 30, 232, 42, -21, 932, 412, 12, 1032, 12, -1, 23, -4};
    // 相邻整数输出
    int sum = v[0];
    for (decltype(v.size()) i = 1; i < v.size(); i++)
    {
        sum += v[i];
        cout << sum << endl;
        sum = v[i];
    }
    cout << "=======================================" << endl;
    // task2
    for (decltype(v.size()) i = 0; i <= v.size() / 2; i++)
    {
        if (i != v.size() - 1 - i)
            cout << v[i] + v[v.size() - 1 - i] << endl;
        else
            cout << v[i] << endl;
    }
}
