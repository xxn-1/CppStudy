#include "Base.h"
using namespace std;
class BaseOver : public Base
{
public:
    Base *clone() & override
    {
        cout << "copy";
        return new BaseOver(*this);
    }
    Base *clone() && override
    {
        cout << "move";
        return new BaseOver(std::move(*this));
    }
    void show() override
    {
        cout << "nnnnn";
    }
};
