#include <iostream>
#include <ostream>
using namespace std;
template < typename T > ostream &print(ostream &os, const T &t)
{
    return os << t;
}
template < typename T, typename... Args >
ostream &print(ostream &os, const T &t, const Args... args)
{
    os << t << ends;
    cout << sizeof...(args) << endl;
    return print(os, args...);
}
int main()
{
    print(cout, 21, 42, 1212, 121111, 45);
}
