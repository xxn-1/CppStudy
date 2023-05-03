/*
 * @Author: xu
 * @Date:   2023-03-28 16:17:51
 * @Last Modified by:
 * @Last Modified time: 2023-03-28 16:19:19
 * @Function:
 */
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
int main()
{
    string a = "abcde";
    for (auto &tmp : a) {
        tmp = toupper(tmp);
    }
    cout << a << endl;
}
