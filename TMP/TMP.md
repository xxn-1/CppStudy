---
模板元编程
---



**最大的优点：可将工作由运行期移至编译期**

使用示例：

* 确保度量单位正确
* 优化矩阵运算
* 可以生成客户定制之设计模式实现品

例子1：

```c++
template<typename IterT, typename DisT>
void doAdvance(IterT& iter, Dist d, std::random_access_iterator_tag) {	//随机访问迭代器
    iter += d;
}

template<typename IterT, typename DisT>
void doAdvance(IterT& iter, Dist d, std::bidirectional_iterator_tag) {	//双向迭代器
    if(d >= 0)
        while(d--) ++iter;
    else 
        while(d++) --iter;
}

template<typename IterT, typename DisT>
void doAdvance(IterT& iter, Dist d, std::input_iterator_tag) {			//输入迭代器
    if(d < 0)
        throw std::out_of_range("Negative distance");
    while(d++) --iter;
}
//在advance中调用doAdvance，实际的工作委托给doAdvance
template<typename IterT,typename DistT>
void advance(IterT& iter,DistT d) {
    doAdvance(iter,d,typename std::iterator_traits<IterT>::iterator_category());
}

```

例子2：

```c++
template <unsigned n>
struct Factorial {
    enum {value = n*Factorial<n-1>::value};
}
template <>
struct Factorial<0> {
    enum {value = 1};
}
cout << Factorial<10>::value << endl;
```

