/*
* @Author:
* @Date:   2023-04-06 09:44:43
* @Last Modified by:
* @Last Modified time: 2023-04-06 09:48:34
* @Function:
*/
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
using namespace std;
bool isLen(const string & s) {
    return s.length() >= 6;
}
int main() {
    vector< string > s = {"213213", "dko", "fjeniiwe", "0e32", "jdiein", ",m"};
    cout << count_if(s.begin(), s.end(), isLen) << endl;
}
