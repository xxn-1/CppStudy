#include <iostream>
using namespace std;
template<class T>
class Array2D {
public:
    class Array1D {
    public:
        T& operator[](int index);
        const T& operator[](int index) const;
    ...
    };
    Array1D operator[](int index);
    const Array1D operator[](int index) const;
    ...
};
int main() {

}