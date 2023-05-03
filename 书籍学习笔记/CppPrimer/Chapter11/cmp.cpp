/*
 * @Author:
 * @Date:   2023-04-06 11:12:26
 * @Last Modified by:
 * @Last Modified time: 2023-04-06 13:58:30
 * @Function:
 */
#include "iostream"
#include "set"
#include "unordered_set"
#include <ostream>
#include <system_error>
#include <vector>
using namespace std;
typedef struct Student
{
    Student(int a_, int b_) : a(a_), b(b_){};
    int a;
    int b;
    friend ostream &operator<<(ostream &os, const Student &e)
    {
        os << e.a << ends << e.b << endl;
        return os;
    };
} Student;
ostream &operator<<(ostream &os, const Student &e);

bool compareIs(const int &a, const int &b)
{
    return a > b;
}
bool compareStu(const Student &a_, const Student &b_)
{
    return a_.a == b_.a ? a_.b < b_.b : a_.a < b_.a;
}
bool op(const Student &a_, const Student &b_)
{
    return a_.a == b_.a;
}
size_t hasher(const Student &stu)
{
    return hash< int >()(stu.a);
}
int main(int argc, char const *argv[])
{
    /* code */
    Student a(123, 3232);
    Student b(922, 12);
    Student c(124, 5344);
    Student d(122, 3234);
    Student e(123, 5344);
    Student f(123, 1);

    vector< int > vs = {421, 12, 4321, 23, 5241, 211, 53532, 121};
    vector< Student > students = {a, b, c, d, e, f};
    set< int, decltype(compareIs) * > nums(vs.begin(), vs.end(), compareIs);
    // set< Student, decltype(compareStu) * > stus(students.begin(),
    // students.end(), compareStu);
    // for (auto x : nums)
    // {
    //     cout << x << " ";
    // }
    unordered_set< Student, decltype(hasher) *, decltype(op) * > stus(3, hasher, op);
    cout << stus.bucket_count() << endl;
    for (auto s : stus)
    {
        cout << s;
    }
    cout << endl;
    return 0;
}
