/*
 * @Author:
 * @Date:   2023-03-30 11:12:44
 * @Last Modified by:
 * @Last Modified time: 2023-03-30 13:27:53
 * @Function:
 */
#include <iostream>
#include <string>
using namespace std;
string replace(string s, string old_, string new_)
{
    auto pos = 0;
    while (pos != string::npos)
    {
        pos = s.find(old_, pos);
        if (pos != string::npos)
        {
            s.erase(pos, old_.size());
            s.insert(pos, new_);
        }
    }
    return s;
}
string replace_(string s, string old_, string new_)
{
    auto pos = 0;
    while (pos != string::npos)
    {
        pos = s.find(old_, pos);
        if (pos != string::npos)
        {
            s.replace(pos,old_.size(),new_);
        }
    }
    return s;
}
int main(int argc, char const *argv[])
{
    string str = "afaefeasufofes,pwqfo,wf,~,eow!ufo,ofe.ufoew!";
    cout << replace_(str, "ufo", "==d==") << endl;
    cout << replace(str, "ufo", "==d==");

    return 0;
}
