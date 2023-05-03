/*
 * @Author:
 * @Date:   2023-03-29 10:57:40
 * @Last Modified by:
 * @Last Modified time: 2023-03-29 11:01:04
 * @Function:
 */
#include <iostream>
#include <stdexcept>
using namespace std;
int main(int argc, char const *argv[])
{
    int a = 3;
    int b = 0;

    try
    {
        if (b == 0)
            throw runtime_error("分母为0!");
        else
        {
            int c = a / b;
        }
    }
    catch (runtime_error e)
    {
        cout << e.what();
    }
    return 0;
}
