---

---

#### 非标准容器

* `<hash_set>|<hash_map>`头文件包含`hash_set|hash_map|hash_multiset|hash_multimap`容器

* 非标准序列容器：

  * `slist`单向列表

  * `rope`一个平衡树

    ```c++
    #include<ext/rope>
    using namespace __gnu_cxx;
    ```

#### 使用容器时要封装

封装使得我们如果发现此容器不是最好的选择时，可以方便的替换

```
通常为其起一个别名
typedef 容器类型<Myclass> MyVecClass;
typedef MyVecClass::iterator MyIterator;
```



#### 多使用empty()而不是size()==0

---

#### 利用插入迭代器操作的方式几乎都使用容器内的区间成员函数替代

如：

```c++
前：
v1.clear();
copy(v2,begin(),v2.end(),back_iterator(v1));
使用以下代码替换效率更高
v1.assign(v2.begin(),v2.end());
```

**使用单元素版本函数和区间操作函数区别：**

* 调用函数次数不同，单元素版本开销大
* 单元素版本会影响其他位置的元素，可能导致其他元素依次移位。**由此导致了赋值或拷贝构造的开销**
* 减少了容器动态扩充内存的次数，区间函数可以明确知道元素的个数来使得扩充一步到位。

#### 记住析构容器中对象

如果容器中存储的对象是指针类型，而且是new出来的指针对象，那么在析构容器对象前，那么必须首先delete指针。

**注意，最好不要直接传入指针，而是使用智能指针，因为遍历析构容器中指针过程可能发生异常会崩溃。**

#### 容器适配器

语法：`stack<类型T,底层容器<T>>`适配器的底层构造容器决定了它的结构是如何组织的(链表 or 数组)

* `stack`容器支持：
  * `vector`
  * `deque`
  * `list`
* `queue`
  * `deque`
  * `list`
* `priority_queue`
  * `vector`
  * `deque`



#### 容器分配器

定义容器分配内存的策略。也就是自定义`allocator`

适用于自定义分配器的情景：

* 想把容器分配到一块特定的内存空间中，或者想把容器本身和容器存储的对象放到同一块内存空间中。

  可以有一个函数专门用来返回这样的内存空间。new一块空间使用placement new放置容器，容器中对象使用分配器在调用该函数分配空间。

* 

```c++
/*
 * @Author:
 * @Date:   2023-05-10 10:19:29
 * @Last Modified by:
 * @Last Modified time: 2023-05-10 11:09:51
 * @Function:
 */
// 自定义分配器
//
#include <corecrt.h>
#include <cstdio>
#include <iostream>
#include <memory>
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
    pointer allocate(size_type _size)
    {
        curSize += _size;
        STD cout << "MyAllocator::allocate,内存分配:"
                 << sizeof(value_type) * _size << "B" << std::endl;
        return static_cast< pointer >(operator new(sizeof(value_type) * _size));
    }
    void deallocate(pointer p, size_type _size)
    {
        STD cout << "MyAllocator::deallocate,内存释放:"
                 << sizeof(value_type) * _size << "B" << STD endl;
        curSize -= _size;
        operator delete(p);
        STD cout << "MyAllocator remind:" << curSize * sizeof(value_type) << "B"
                 << STD endl;
    }
    // inline bool operator==(const MyAllocator< T > &, const MyAllocator< T > &);
    // inline bool operator!=(const MyAllocator< T > &, const MyAllocator< T > &);
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
    size_type curSize;
};
int main()
{
    STD vector< int, MyAllocator< int > > v;
    v.reserve(6);
    v.reserve(7);
    STD cout << v.get_allocator().getAllocations() << STD endl;

    getchar();
}
```



#### String和Vector

##### string实现策略

引用计数实现方式：

* 为普通指针数据成员
* 为静态成员变量
* 放置在string内一个嵌套结构体中。

**引用计数就放到数据字符前(char*)的最前面(放在后面会拦住'\0')，申请内存时多申请一个计数类型的大小**

1. 深拷贝：无论什么时候都深拷贝

2. COW写时复制：string成员仅保存一个指针指向一块string数据成员的内存。再加以通过引用计数实现。读时仅递增引用计数，复制指针。当写时才真正的

3. SSO短字符串优化：数据保存在string内，当数据字符小于16时保存在栈中，当大于等于16时，通过堆存放数据字符。

   ```c++
   union {
       char *pointer;
       char _local[16];
   }
   ```

   

##### **注意点：**

1. string类在某些标准库的实现中是引用计数的，引用计数在**多线程**环境下效率很低，我们需要使用非引用计数版本，**或者考虑vector<char>替换。**
2. 频繁拷贝时，推荐使用引用计数策略。
3. 在不同平台上string的实现大不相同，如果应用要考虑不同平台时，需要考虑不同平台上的String实现策略。
4. 若我们已经知道容器元素最终个数大小，提前调用`reserve`分配足量的空间。

#### SWAP策略在容器中使用

* **缩减容器的`capacity`**：

  `vector<int>v;v.reserve(2);v.clear();vector<int>().swap(v);`v被清空了。

#### 特殊的vector<bool>

在类型中，`bool`占用一个字节。

但是在<vector>中的bool是一个假的容器，为了节省空间存储了bool的紧凑表示，每个bit表示一个bool。**只是一个仿容器，而不是真正的容器，没有真正容器的一些功能实现。**

#### 顺序关联容器的相等和等价

**针对所有顺序关联容器：**

关联容器的`find`函数是基于相等的，需要实现`==`运算符比较相等

关联容器的`insert`函数决定是否插入某个键（判断其是否已存在）是基于等价的，需要实现`<`运算符判别键是否重复和排序。可以自定义该行为。**注意其中不需要`<=`这会使得相等的键重复插入**

---

**在排序容器的比较中，需要注意，默认的比较行为不能区分是指针/迭代器/智能指针还是值，如果想按set中存储的指针对象所指的值排序，需要自己定义排序行为。**



##### 强制转化到引用

有些STL中的`set`实现通过迭代器获取对象时，得到的对象是一个原来对象的`const Type&`，**如果我们通过强制转化，只转化为`Type`这会导致这个对象并没有指向原先那个set中的对象，而是创建一个临时变量，所以一定要强制转化到`Type `**

#### 考虑用排序的Vector代替关联容器

**对于大部分应用程序处理数据结构只分为三个阶段：**

1. 一系列插入数据
2. 查找数据：
3. 更新删除数据：此操作结束后转为第二阶段。

关联容器针对每个对象都额外添加了几个指针(其数据结构二叉树本身造成的)，因此关联容器存储的对象会显著的增加内存消耗，尤其是在存储的对象特别大量时。消耗是Vector的近三倍。**系统显著变慢。**另外，关联容器是分散存储的地址，与Vector连续空间不同。

**但是Vector在插入删除时非常低效，因此仅当查找操作与插入删除操作分离时，才考虑使用排序的Vector数据结构。而特殊的，vector替换map类型时，内部要存储`pair`组织的对象。**

#### map的插入操作

**插入时：** 使用`insert`代替下标插入会省去临时对象的创建析构消耗。

- [x] `m.insert(1,2)`
- [ ] `m[1]=2`

**更新时：**使用下标操作代替`insert`，`insert`操作会导致`pair`和`Type`两个类型构造和析构，而下标没有任何代价。

- [x] `m[1]=2`

**可以实现一个addAndUpdate函数模板来代替实现上面两个函数**



#### istreambuf_iterator

和`istream_iterator`的区别：

该流可以原封不动的把输入的字符输出，包括空白字符

而`istream_iterato`会忽略空白。
