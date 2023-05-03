/*
 * @Author:
 * @Date:   2023-04-06 09:10:12
 * @Last Modified by:
 * @Last Modified time: 2023-04-06 10:49:29
 * @Function:
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
    auto add = [](int a, int b)
    {
        return a + b;
    };
    cout << add(3, 5) << endl;
    int cur = 9;
    auto add1 = [=](int a)
    {
        return cur + a;
    };
    cout << add1(2) << endl;
    return 0;
}
