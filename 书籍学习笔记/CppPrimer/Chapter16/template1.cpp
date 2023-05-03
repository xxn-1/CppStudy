#include "iostream"
using namespace std;
template <typename T,size_t N>
void getSum(const T (&a)[N])
{
    cout << N << endl;
    T sum;
    for(auto x:a){
        sum += x;
    }
    cout << sum << endl;
}
int main() {
    int a[2] = {2,3};
    getSum(a);
    string b[2] = {"dfwsefd","fre222"};
    getSum(b);
}