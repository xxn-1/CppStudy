#include <iostream>
#include <memory>
using namespace std;
void ref(shared_ptr<int> tmp) noexcept
{
    int d;
    cout << tmp.use_count() << endl;

    return;
}
int main()
{
    // shared_ptr<int> p = make_shared<int>(32);
    // cout << *p << endl;
    // shared_ptr<int> pp(new int(4));
    // cout << *pp << endl;
    // cout << pp.use_count() << endl;
    // shared_ptr<int> tmp = pp;
    // cout << pp.use_count() << endl;
    // ref(pp);
    // cout << pp.use_count() << endl;
    shared_ptr<int> p(new int[3]{2, 4, 5}, [](int *t)
                      { delete[] t; cout<<"delete"<<endl ; });
    for (int i = 0; i < 3; i++)
    {
        cout << *(p.get() + i) << " ";
    }
    cout << endl;
}