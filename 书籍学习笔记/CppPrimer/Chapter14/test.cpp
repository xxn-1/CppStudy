#include <functional>
#include <utility>
#include <iostream>
using namespace std;
int main()
{
    plus<int> add;
    cout << add(1,2) << endl;
}