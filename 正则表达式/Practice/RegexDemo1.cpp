#include <iostream>
#include <regex>
#include <string>
using namespace std;
int main()
{
    cout << regex_match("123", regex("\\d")) << endl;  // 结果为0
    smatch result;
    string str = "foo foo";
    regex regex(R"(([a-z]*)\s?\1)");
    if (regex_match(str, result, regex))
    {
        cout << result[0] << endl;
    }

    cout << regex_replace(str, regex, "$0") << endl;
}
