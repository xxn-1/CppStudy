#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    string str = "hello@world@how@are@you@";
    stringstream ss(str);
    string token;
    while (getline(ss, token, '@'))
    {  // 使用getline函数按照'@'分割字符串
        cout << token << endl;
    }
    return 0;
}
