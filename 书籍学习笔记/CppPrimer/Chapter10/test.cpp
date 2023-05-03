/*
 * @Author:
 * @Date:   2023-03-30 15:22:00
 * @Last Modified by:
 * @Last Modified time: 2023-03-30 15:34:23
 * @Function: 测试algorithm头文件
 */
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;
int main(int argc, char const *argv[])
{
    /* code */
    vector< string > ss = {"21321312ads", "0=-=-=!2@(#*@"};
    cout << accumulate(ss.begin(), ss.end(), string("")) << endl;
    return 0;
}
