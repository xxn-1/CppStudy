#include <iostream>
#include <memory>
#include <vector>
using namespace std;

int main()
{
    vector<int> v{1, 23, 4, 2, 1, 2};
    allocator<int> alloc;

    auto p = alloc.allocate(10);
    auto q = uninitialized_copy(v.begin(), v.end(), p);
    auto c = uninitialized_fill_n(q, 10 - v.size(), 99);

    cout << "===============" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << *(p + i) << endl;
        alloc.destroy(p);
    }
    alloc.deallocate(p, 10);
}