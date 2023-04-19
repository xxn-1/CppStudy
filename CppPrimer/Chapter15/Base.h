#include <iostream>
using namespace std;
class Base
{
public:
    virtual Base *clone() &
    {
        cout << "copy";
        return new Base(*this);
    }
    virtual Base *clone() &&
    {
        cout <<"move";
        return new Base(std::move(*this));
    }
    virtual void show()
    {
        cout << "nihao";
    }
};
