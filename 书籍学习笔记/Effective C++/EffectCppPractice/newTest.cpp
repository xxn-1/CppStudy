#include <iostream>
using namespace std;
struct newTest
{
private:
    void* operator new(size_t size);
    void operator delete(void *ptr);

};
struct newTTest:public newTest{};
int main() {
    newTest n1;
    newTTest nn1;
    // newTTest *nn2 = new newTTest;
}