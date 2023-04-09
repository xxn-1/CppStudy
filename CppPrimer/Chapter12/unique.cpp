#include <memory>
#include <iostream>
using namespace std;
void mydelete(int *temp)
{
    cout << "my delete" << endl;
    delete temp;
}
int main()
{
    // unique_ptr<int, decltype(mydelete) *> p(new int(4), mydelete);
    unique_ptr<int[], decltype(mydelete) *> up(new int[10]{1, 4, 7, 5, 2, 6, 8, 56, 4, 3}, mydelete);
    for (int i = 0; i < 10; i++)
    {
        cout << up[i] << " ";
    }
    up.reset();
    cout << endl;
} // main end