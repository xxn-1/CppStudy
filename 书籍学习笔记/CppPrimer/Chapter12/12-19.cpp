#include <vector>
#include <string>
#include <iostream>
#include <memory>
using namespace std;
// begin/end/size/empty/push_back/pop_back/front()/back
class numsptr;
typedef class nums
{
public:
    typedef vector<string>::size_type size_type;
    friend class numsptr;
    nums()
    {
        if (!vs)
            vs.reset(new vector<string>);
    };
    nums(initializer_list<string> strs)
    {
        if (!vs)
            vs.reset(new vector<string>);
        vs->insert(vs->end(), strs.begin(), strs.end());
    };
    string front()
    {
        if (check(0))
            return vs->at(0);
        return string();
    };
    const string front() const
    {
        return vs->at(0);
    };
    string back()
    {
        if (check(0))
            return vs->at(size() - 1);
        return string();
    };
    const string back() const
    {
        return vs->at(size() - 1);
    }
    bool empty()
    {
        return size() == 0;
    };
    size_type size()
    {
        return vs->size();
    };
    const size_type size() const
    {
        return vs->size();
    }
    void push_back(string s)
    {
        vs->push_back(s);
    };
    string pop_back()
    {
        if (size() - 1)
        {
            string tmp = vs->at(size() - 1);
            vs->erase(vs->end() - 1);
            return tmp;
        }
        else
            throw runtime_error("out of range");
    };
    numsptr begin();
    numsptr end();
    nums &operator=(const nums &num)
    {
        vs = num.vs;
        return *this;
    }

private:
    shared_ptr<vector<string>> vs;
    bool check(int pos)
    {
        return size() != 0 && pos >= 0 && pos < size();
    }
} nums;

typedef class numsptr
{
public:
    typedef vector<string>::size_type size_type;
    numsptr(shared_ptr<vector<string>> tmp, size_type size_ = 0, size_type cur_ = 0) : p(tmp), size(size_), cur(cur_){};
    numsptr();
    numsptr &incr()
    {
        auto s = p.lock();
        if (!s)
            throw runtime_error("nullptr");
        if (cur + 1 > size)
        {
            throw runtime_error("out of range");
        }
        cur++;
        return *this;
    }
    string get()
    {
        auto s = p.lock();
        if (!s)
            throw runtime_error("nullptr");
        if (cur >= size)
        {
            throw runtime_error("out of range");
        }
        return (*s)[cur];
    }

private:
    weak_ptr<vector<string>> p;
    size_type cur = 0;
    size_type size;

} numsptr;
numsptr nums::begin()
{
    return numsptr(vs, size(), 0);
}
numsptr nums::end()
{
    return numsptr(vs, size(), size());
}
int main()
{
    nums num{"fesfe", "feew"};
    cout << num.size() << endl;

    // num.pop_back();
    // cout << num.size() << endl;

    numsptr p = num.begin();
    cout << p.get() << endl;
    p.incr();
    cout << p.get() << endl;
    p.incr();
    cout << p.get() << endl;
}