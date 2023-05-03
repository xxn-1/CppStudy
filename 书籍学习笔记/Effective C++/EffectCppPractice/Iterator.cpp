#include <iostream>
#include <iterator>
#include <cstring>
using namespace std;
template <typename T>
class Iterator; // Template type declaration
// Defines a numeric range
template <typename T>
class Numeric
{
public:
    friend class Iterator<T>;
    using iterator = Iterator<T>;
    using const_iterator = Iterator<const T>;

    using size_type = size_t;
    // Return the begin iterator for the range
    iterator begin() { return iterator(*this, (size_type)0); }
    // Return the end iterator for the range
    iterator end()
    {
        return iterator(*this, length);
    }
    // const iterator begin() const { return const_iterator(*this, 0); }
    // const iterator end() const { return const_iterator(*this, length); }

    Numeric(char *tmp) : data(new T[1024]), capycity(1024), length(2) // 修改
    {
        strcpy(data, tmp);
    };
    // static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value,
    //               "Numeric_Range type argument must be numeric.");
    ~Numeric()
    {
        delete[] data;
    }

private:
    T *data;
    size_type capycity;
    size_type length;
};
// Iterator class template- it's a forward iterator
template <typename T>
class Iterator : public std::iterator<std::forward_iterator_tag, T>
{
    friend class Numeric<T>;

public:
    // using iterator = Iterator<T>;
    using iterator_category = std::forward_iterator_tag; // 这里选择类型
    using difference_type = std::ptrdiff_t;
    using size_type = size_t;
    using value_type = T;
    using reference = T &;
    using pointer = T *;

private:
    Numeric<T> &num; // 对容器的引用
    size_type length;

public:
    explicit Iterator(Numeric<T> &data_, size_type length_) : num{data_}, length(length_){};

    // Assignment operator
    Iterator &operator=(const Iterator &src)
    {
        num = src.numdata;
    }

    // Dereference an iterator
    T &operator*()
    {
        // When the value is one step more than the last, it's an end iterator

        return *(num.data + length);
    }

    // Prefix increment operator
    Iterator &operator++()
    {
        // When the value is one step more than the last, it's an end iterator
        // 判断length<capacity
        length = length + 1;
        return *this;
    }

    // Postfix increment operator
    Iterator operator++(int)
    {
        // When the value is one step more than the last, it's an end iterator
        Iterator temp = *this;
        length += 1;
        return temp; // The iterator before it's incremented
    }

    // Comparisons
    // bool operator<(const Numeric_Iterator &iter) const { return value < iter.value; }
    bool operator==(const Iterator &iter) const { return length == iter.length; }
    bool operator!=(const Iterator &iter) const { return length != iter.length; }
    // bool operator>(const Numeric_Iterator &iter) const { return value > iter.value; }
    // bool operator<=(const Numeric_Iterator &iter) const { return *this < iter || *this == iter; }
    // bool operator>=(const Numeric_Iterator &iter) const { return *this > iter || *this == iter; }
};
// 常量迭代器

//...

//
int main()
{
    char tmp[3] = "13";
    // cout << *(tmp+2);
    Numeric<char> n(tmp);
    // cout << *(n.end()) << endl;
    // cout << *(++n.begin()) << endl;
    // cout << *(n.end()) << endl;
    for (auto x : n)
    {
        cout << x << endl;
    }
}