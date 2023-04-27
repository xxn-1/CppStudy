#### 以constexpr代替

使用编译器代替运行时，是更有效率的。

#### 使用enum、inline、const

更多地使用这三者，可在编译时代替运行时，提高效率

对于一些类似于简单宏的函数，要使用inline标注。

#### const和non-const成员函数

为了更好地避免代码重复，可以通过在nonconst中调用const函数的技术。**我们可以通过已经定义的const来实现non-const函数。在non-const中实际调用const函数来完成。**

> 注意，在调用const函数时，必须将对象本身转换成const类型修饰的，否则会发生递归。
>
> 同时反向用const调用non-const是错误的，有风险的。

```c++
// 假如const函数定义如下
const T& func()const{
    ...
}
T& func(){
    return const_cast<T&>(static_cast<const MyClass类型>(*this));
}
```



学到04了。