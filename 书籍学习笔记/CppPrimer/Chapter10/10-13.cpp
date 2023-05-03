/*
 * @Author:
 * @Date:   2023-04-06 08:48:50
 * @Last Modified by:
 * @Last Modified time: 2023-04-06 08:59:43
 * @Function:
 * 测试谓词，接受一个string，返回一个bool，指出string是否有5个或更多字符
 */
#include "algorithm"
#include "iostream"
#include "string"
#include "vector"
#include <algorithm>
#include <vector>

using namespace std;

bool isCfive(string tmp)
{
    return tmp.size() >= 5;
}
int main()
{
    vector< string > s = {"213213", "dko", "fjeniiwe", "0e32", "jdiein", ",m"};
    // partition(s.begin(), s.end(), isCfive);
    partition(s.begin(), s.end(),
              [](string str) -> bool
              {
                  return str.length() >= 5;
              });
    for (auto str : s)
    {
        cout << str << endl;
    }
}
