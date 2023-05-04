#include <iostream>
#include <string>
#include <ext/rope>
using namespace __gnu_cxx;
using namespace std;
rope<int>rp;
int main()
{
    rp.append(3);
    rp.append(1);
    rp.append(2);
    rp.append(1);
    rp = rp.substr(1, 3);//从1开始截3个数字，注意rope是从0开始的，所有的容器都是从0开始的
    for(int i = 0; i < rp.size(); ++ i)
        cout << rp[i] << " ";
    puts("");
    return 0;
}
