#include <iostream>
using namespace std;
extern "C"
{
    int Sum(int i, int j)
    {
        return i + j;
    }
}
int main() {
//sum.cpp
    cout << Sum(1,2) << endl;

}