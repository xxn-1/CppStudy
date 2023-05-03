/*
* @Author:
* @Date:   2023-04-06 10:06:39
* @Last Modified by:
* @Last Modified time: 2023-04-06 10:12:04
* @Function:
*/
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
    vector<int> num;
    auto biter = back_inserter(num);
    *biter = 3;
    *biter = 4;


    auto iiter = inserter(num,num.begin()+2);
    *iiter = 333;
    for_each(num.begin(),num.end(),[](int t){cout << t << endl;});
    return 0;
}
