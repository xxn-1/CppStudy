/*
 * @Author: xu
 * @Date:   2023-03-28 16:17:51
 * @Last Modified by:
 * @Last Modified time: 2023-03-28 16:25:52
 * @Function:
 */
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
int main()
{
    string a = "a,bc..d.e";
    for (size_t i = 0; i < a.size(); i++)
    {
        if (ispunct(a[i]))
        {
            a = a.erase(i--,1);
        }
    }
    cout << a << endl;
}
