/*
 * @Author:
 * @Date:   2023-03-30 11:03:35
 * @Last Modified by:
 * @Last Modified time: 2023-03-30 11:04:50
 * @Function: 探究vector的空间分配策略
 */
#include <iostream>
#include <vector>
using namespace std;
int main(int argc, char const *argv[])
{
    vector< int > num;
    num.push_back(1);
    cout << num.capacity() << endl;
    num.push_back(1);
    cout << num.capacity() << endl;
    num.push_back(1);
    cout << num.capacity() << endl;

    return 0;
}
