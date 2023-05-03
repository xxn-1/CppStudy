#include <iostream>
#include <windows.h>
using namespace std;
template <unsigned n>
struct Factorial
{
    enum
    {
        value = n * Factorial<n - 1>::value
    };
};
template <>
struct Factorial<0>
{
    enum
    {
        value = 1

        
    };
};
// template <unsigned n>
// struct Factorial
// {

//         const static int value = n * Factorial<n - 1>::value;

// };
// template <>
// struct Factorial<0>
// {

//         const static int value = 1;
// };
int main()
{
    cout << Factorial<10>::value << endl;
}