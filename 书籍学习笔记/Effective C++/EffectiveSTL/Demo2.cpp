/*
 * @Author:
 * @Date:   2023-05-10 10:19:29
 * @Last Modified by:
 * @Last Modified time: 2023-05-10 15:08:26
 * @Function:
 */
// 自定义分配器
//
#include <corecrt.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <pthread.h>
#include <string>
#include <thread>
#include <vector>
#define STD ::std::
template < class T > class MyAllocator
{
public:
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using const_pointer = const T *;
    using const_reference = const T &;
    using size_type = size_t;
    using void_pointer = void *;
    using const_void_pointer = const void *;
    using difference = STD ptrdiff_t;

    template < class U > struct rebind
    {
        using other = MyAllocator< U >;
    };
    MyAllocator() = default;
    ~MyAllocator() = default;
    // 分配内存
    pointer allocate(size_type _size = 0)
    {
        curSize += _size;
        STD cout << "MyAllocator::allocate,内存分配:"
                 << sizeof(value_type) * _size << "B" << std::endl;
        return static_cast< pointer >(operator new(sizeof(value_type) * _size));
    }
    void deallocate(pointer p, size_type _size = 0)
    {
        STD cout << "MyAllocator::deallocate,内存释放:"
                 << sizeof(value_type) * _size << "B" << STD endl;
        curSize -= _size;
        operator delete(p);
        STD cout << "MyAllocator remind:" << curSize * sizeof(value_type) << "B"
                 << STD endl;
    }
    // 分配内存
    pointer allocate(size_type numObjects, const_void_pointer hint)
    {
        return allocate(numObjects);
    }
    pointer address(reference x) const
    {
        return &x;
    }
    const_pointer address(const_reference x) const
    {
        return &x;
    }

    friend inline bool operator==(const MyAllocator< T > &l,
                                  const MyAllocator< T > &r)
    {
        return l.getAllocations() == r.getAllocations();
    };
    friend inline bool operator!=(const MyAllocator< T > &l,
                                  const MyAllocator< T > &r)
    {
        return !(l == r);
    };

    size_type max_size() const
    {
        return static_cast< size_type >(-1) / sizeof(value_type);
    }
    // 构造函数
    template < class U > void destroy(U *p)
    {
        STD cout << "destory" << STD endl;
        p->~U();
    }
    // //构造对象
    template < class U, class... Args > void construct(U *p, Args &&...args)
    {
        STD cout << "construct" << STD endl;
        new (p) U(std::forward< Args >(args)...);
    }
    // 返回每次分配/删除的内存数
    const size_type getAllocations() const
    {
        return curSize * sizeof(value_type);
    }
private:
    size_type curSize = 0;
};
int main()
{
    STD vector< int, MyAllocator< int > > v;
    v.reserve(6);
    STD vector<int,MyAllocator< int > >().swap(v);
    STD cout << v.get_allocator().getAllocations() << STD endl;
}
