#include <iostream>
using namespace std;
template <class BeingCounted>
class Counted
{
public:
    class TooManyObjects
    {
    };
    static int objectCount() { return numObjects; }

protected:
    Counted();
    Counted(const Counted &rhs);
    ~Counted() { --numObjects; }

private:
    static int numObjects;
    static const size_t maxObjects = 10; // 必须初始化由用户完成
    void init();
};
template <class BeingCounted>
Counted<BeingCounted>::Counted()
{
    init();
}
template <class BeingCounted>
Counted<BeingCounted>::Counted(const Counted<BeingCounted> &)
{
    init();
}
template <class BeingCounted>
void Counted<BeingCounted>::init()
{
    if (numObjects >= maxObjects)
    {
        throw TooManyObjects();
    }
    ++numObjects;
    cout << numObjects << endl;
}
template <class BeingCounted> // 定义numObjects
int Counted<BeingCounted>::numObjects = 0;
class PrintJob
{
};
class Printer;
class Printer : private Counted<Printer>
{
public:
    static Printer *makePrinter();
    static Printer *makePrinter(const Printer &rhs);
    //     ~Printer();
    //     void submitJob(const PrintJob &job);
    //     void reset();
    //     void performSelfTest();
    //     using Counted<Printer>::objectCount; // 开放接口
    //     using Counted<Printer>::TooManyObjects;

private:
    Printer() = default;
    Printer(const Printer &rhs) = default;
};
Printer *Printer::makePrinter()
{
    return new Printer;
}
Printer *Printer::makePrinter(const Printer &rhs)
{
    return new Printer(rhs);
}
int main()
{
    Printer *printer1 = Printer::makePrinter();
    Printer *printer2 = Printer::makePrinter();
    Printer *printer3 = Printer::makePrinter();
    Printer *printer4 = Printer::makePrinter();
    Printer *printer5 = Printer::makePrinter();
    Printer *printer6 = Printer::makePrinter();
    Printer *printer7 = Printer::makePrinter();
    Printer *printer8 = Printer::makePrinter();
    Printer *printer9 = Printer::makePrinter();
    Printer *printer10 = Printer::makePrinter();
    Printer *printer11 = Printer::makePrinter();
    // Printer *printer1 = new Printer();
}