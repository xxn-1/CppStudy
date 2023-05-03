/*
 * @Author: xu
 * @Date:   2023-03-30 08:44:25
 * @Last Modified by:
 * @Last Modified time: 2023-03-30 09:40:32
 * @Function: 测试流
 */
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
using namespace std;
int main(int argc, char const *argv[])
{
    // int a;
    // cin >> a;
    // cin.tie(nullptr);
    // cout << 1;

    // cin >> a;
    // ///////////////////////////////
    ifstream a("./data.txt");
    ofstream b("./out.txt");
    string data;
    while (a >> data)
    {
        b << data << endl;
        cout << data << endl;
    }
    return 0;
}
