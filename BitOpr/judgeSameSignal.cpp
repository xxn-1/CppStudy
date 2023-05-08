#include <iostream>
bool judge(int n, int m)
{
    return (n ^ m) >= 0;
}
int main()
{
    std::cout << judge(-1, -2);
}