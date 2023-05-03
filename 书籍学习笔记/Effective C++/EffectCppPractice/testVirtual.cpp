#include <iostream>
using namespace std;
struct testVirtual
{
    // virtual void init();
    virtual void init() {
        cout << 1;
    };
    virtual void init1() {
        cout << 1;
    };
    int b;
    /* data */
};
int main() {
    cout << sizeof(testVirtual);
}
