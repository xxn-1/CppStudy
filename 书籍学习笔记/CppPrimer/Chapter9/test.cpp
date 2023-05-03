/*
 * @Author:
 * @Date:   2023-03-30 10:25:14
 * @Last Modified by:
 * @Last Modified time: 2023-03-30 10:30:02
 * @Function:
 */
#include <array>
#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
    array< int, 32 > a = {2, 3, 4, 5};
    for (auto x : a)
    {
        cout << x << ends;
    }
    cout << endl;
    a.fill(3);
    for (auto x : a)
    {
        cout << x << ends;
    }
    return 0;
}
