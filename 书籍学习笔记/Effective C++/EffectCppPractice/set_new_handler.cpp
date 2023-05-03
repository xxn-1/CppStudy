#include <new>
#include <string>
#include <iostream>
#include <locale>
#include <wchar.h>
#include <cstdio>
using namespace std;
void handler()
{
    cout << "error" << endl;
}
int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ios_base::sync_with_stdio(false); // 缺少的话，wcout wchar_t 会漏掉中文
    wcin.imbue(locale(""));
    wcout.imbue(locale(""));

    wstring s;

    wchar_t t[] = L"wprtinf 中文\n";

    wstring u = L"wout 中文";

    wprintf(t);
    wcin >> s;
    wcout << "wcin " << s << endl;
    wcout << u << endl;

    return 0;
}
