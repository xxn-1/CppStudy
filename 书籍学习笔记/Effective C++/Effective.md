#### 以constexpr代替

使用编译器代替运行时，是更有效率的。

#### 使用enum、inline、const

更多地使用这三者，可在编译时代替运行时，提高效率

对于一些类似于简单宏的函数，要使用inline标注。

为了多个文件获取单例变量，应使用
```c
Mytype& get() {
    static Mytype t;
    return t;
}
```

在c++17以后，可以使用`inline constexpr`定义一个变量，在被多个文件包含时也能正常编译

**尽量使用const引用代替值传递**

**将inline限制在小型、会被频繁调用的函数身上**

#### const和non-const成员函数

在成员函数中，**当non const成员函数和const成员函数有同样的实现时**，可以通过已经实现的`const`成员函数来完成`non const`成员函数。

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



#### 在析构函数中不应处理异常

而是再封装时让用户决定

#### operator=处理自赋值

```c
Mytype& operator=(const Mytype& e) {
    Mytype tmp = e;
    swap(*this,e);
    return *this;
}
```

#### Swap特例化

对于swap来说，某些情况下仅仅需要交换二者内的数据指针，而不需要实际的交换数据空间。我们需要特例化swap，**一般而言，在类中Public定义`swap`函数，然后定义非成员函数的特例化swap调用成员函数swap完成实际工作**

```c++
// 注意要限定非成员函数swap在自己的命名域中而不是std中。
namespace my{
class xxx{
    public:
    void swap(xxx& other) noexcept {
		using std::swap;
        // 进交换指针
        swap(...);
    }
}

    template<> 
    void swap<xxx>(xxx &a,xxx &b) noexcept {
        a.swap(b);
    }
}
```

如果想要在标准库中特化某一类型的swap操作，**需要在std中单独声明特化版本**：

```cpp
namespace std {
    void swap(N::C& lhs, N::C& rhs) noexcept {
        lhs.swap(rhs);
    }
}
```

一般来说，不允许直接在std标准库中的声明自定义函数或类。然而，标准对于某些模板函数可以进行显试实例化定义（即特化，swap算是其中的一个）。

注意，标准允许我们使用模板实例化扩展std命名空间，但不能使用其他模板重载来扩展它。

#### operator=

赋值要返回引用，**同时要注意在`operator=`中处理自赋值，copy and swap**

#### 使用类管理资源

在资源类中要提供对原始资源的访问接口。



#### 以类型代替

在设计如`date`类时，可以通过先定义`Year、Month、Day`三个类让用户正确的传递参数。在类中对参数进行限制。可以使用多个静态函数，或者`enum`

#### 函数中避免引用和指针到一个函数中的局部堆变量，用返回值代替

类似于二元运算，并不需要返回一个引用。**若是返回一个引用，则该对象是栈对象，类似于`a*b*c`这样的运算的，其中`a*b`创建的栈变量是无法delete的，所以我们必须返回值对象是最好的**

#### 若在运算符中运算的对象前或后都需要类型转换

**使用非成员函数替代成员函数完成。**

#### 派生类调用基类的函数

```c++
void xxx() {
    base::xxx()
}
```

#### 避免成员函数返回一个指针、引用指向类的私有成员

#### copy and swap

该策略是对对象状态“全有或全无”改变的一个很好办法。

#### 异常安全函数

带有异常安全的函数要求有两个条件：1）不泄露任何资源；2）不允许数据败坏；

异常安全函数提供以下三个保证：

    1）基本承诺：如果异常被抛出，程序内的任何事物仍然保持在有效状态下，没有任何对象或数据结构会因此而败坏，所有对象都处于一种内部前后一致的状态。
    2）强烈保证：如果异常被抛出，程序状态不改变。换句话说，如果函数成功，就是完全成功，如果失败，程序会回到“调用函数之前”的状态。可以借助copy and swap。
    3）不抛掷保证：承诺绝不抛出异常，因为它们总是能够完成它们原先承诺的功能。

#### 继承关系

##### **is-a**

**public继承：**

这样的继承表示**派生类**与**基类**之间的关系是`is a`的关系，凡是派生类的对象同时也属于基类，但凡是基类对象所属的不一定是个派生类对象。**派生类是一般化，基类是特殊化。由此得出，在考虑public继承时，一定要考虑是否对基类的特性派生类是否都拥有**

##### **has-a**

复合关系。例如人这个类，每个人都拥有名字，人和名字之间就是`has-a`的关系，像这样的关系实现的方式就是：**将其被包含的类定义在人的内部作为变量。**

##### **has-a**

**private继承：**其行为表现类似于将某个变量定义为其私有成员。通过私有继承的方式继承某个类，在特殊情况下很有用，一般而言，我们都可以使用将其定为变量的方式实现。**私有继承可以造成empty类最优化**

```c++
//这种情况下使用private是一种很好的方案
#include <iostream>
using namespace std;
struct empty{};
struct test1{
    int a;
    empty b;
};
struct test2:private empty{
    int a;
};
struct test3{
    int a;
};
int main() {
    cout << sizeof(empty) << endl;
    cout << sizeof(test1) << endl;
    cout << sizeof(test2) << endl;
    cout << sizeof(test3) << endl;

}
结果：
1
8
4
4
```



#### 虚函数的替代方案

* NVI模式
* 策略模式

#### 模板中的typename

template内出现的名称如果相依于某个模板参数，称之为**从属名称**。类似于`C::iterator iter`

对于从属名称，**若是一个类型，我们必须显式声明，通过在其前标注：`typename`，`typename C::iterator iter;`**

> ​			特殊的是，在继承的基类列表中不能使用typename标注，在构造函数初始化列表中也不能使用typename标注。

#### 模板获取容器类型的内部值类型

```c++
template <class T> // T是一个迭代器
void get(T t) {
    typename std::iterator_traits<T>::value_type temp(*t);
}
```

#### 对模板类定义一些额外的特殊类型是有用的

* 迭代器：

  ```c++
  using iterator_category = std::forward_iterator_tag; // 这里选择类型
  using difference_type = std::ptrdiff_t;
  using size_type = size_t;
  using value_type = T;
  using reference = T &;
  using pointer = T *;
  ```

* 一般：

  ```c++
  using iterator = Iterator<T>;
  using const_iterator = Iterator<const T>;
  using type = XXX<T>
  using value_type = T;
  using size_type = ...
  ```

  





#### 模板 -- 派生类调用积累模板成员名称

在**派生类模板**中通过`this->`明确指涉调用获取**基类模板**内的成员名称

- 在模板类中，如果一个派生类在其方法中调用了基类的方法，那么这段代码可能无法编译通过
- **备注（重点）：**
  - 这一现象是与编译器有关的，Effective C++的作者编译的时候出错
  - 本人使用VS编译的时候没有出错
  - 因此这个问题是与编译器有关

**解决的三种办法：**

- **使用this指针：**使用this指针调用这些函数，实现先告诉编译器这些函数是属于自身类的（在编译之后它们会从基类中继承而来）

- **使用using声明式**：

  ```cpp
  template<typename Company>
  class LoggingMsgSender:public MsgSender<Company>{
  public:
      using MsgSender<Company>::sendClearMsg;
      using MsgSender<Company>::sendSecretMsg;
  ```

- **明确指出被调用的函数位于base class中**

  **这种方法不太建议，因为：**被调用的函数可能是virtual函数，这种修饰符会关闭“virtual绑定行为”

#### 模板 -- 代码膨胀

使用 模板 会导致代码**膨胀**

编写模板时也是做这样的分析以避免重复。小窍门：在 非模板 代码中，重复十分明确，即你可以”看“到两个函数或两个类之间有重复。但在 模板代码 中，重复是**隐晦**的：毕竟只存在一份 模版源码 ，所以你必须训练自己去感受当 模板 被具现化多次时可能发生的重复。

1. **因非类型模板参数（non-type template parameters）而造成的代码膨胀，往往可以消除，做法是以函数参数或 class 成员变量替换 template 参数。**
2. **因类型参数（type parameters）而造成的代码膨胀，往往可以降低，做法是让带有完全相同二进制表述（binary representations）的具现类型（instantiation types）共享实现码。**

技巧如下：

- 当我们设计类模板时，很自然的将其所有的成员函数都在类模板内实现。这样，所有成员函数都为函数模板。每当类模板生成新实例时，其成员函数都有可能相应的生产新的模板实例。
- 但是如果仔细分析，会发现不会所有的成员函数的操作都与新类型有关，有些类型无关的操作，完全不必写成模板。如能将这些操作提取出来，就可以成比例的降低函数模板所生成的目标代码量，从而显著减少目标文件尺寸和编译时间
- 那么该怎么提取呢？具体做法是为目标设计一个与模板参数无关的基类，再将模板类中与模板参数无关的成员变量以及函数都提升到基类中实现。这样，各个类模板实例所调用的都是共同基类中的成员函数，就不会重复生成等价的函数实例。

```c++
template<typename T>   //与尺寸无关的base class
class SquareMatrixBase {
protected:
	void invert(size_t matrixSize);  //以给定的尺寸求逆矩阵
    SquareMatrixBase(size_t n, T* pMem) : size(n), pData(pMem) {}
	void setDataPtr(T* ptr) {
		pData = ptr;
	}

    // 变量

private:
	size_t size;
	T* pData;  
    // ...
};
 
template<typename T, size_t n>
class SquareMatrix : private SquareMatrixBase<T> {
private:
	using SquareMatrixBase<T>::invert;  //避免遮掩base版的invert
public:
	void invert() {
		this->invert(n);  //制造一个inline调用，用this->为了不被derived classes的函数名称掩盖
	}
public:
	SquareMatrix() : SquareMatrixBase(n, data) {}
private:
	T data[n*n]    
};
// 其中派生类模板的invert将操作完全托管给基类实现
```

#### 成员函数模板

* 使用成员函数模板，生成“可接受所有兼容类型”的函数
* 如果声明成员模板用于“泛化copy"构造或”泛化赋值操作“，**注意在声明模板的泛化类型成员函数之外，还要定义普通的拷贝构造函数和拷贝赋值运算符。**

#### 模板 -- 模板函数需要类型转换时需要定义非成员函数

```c++
template<typename T>
const Rational<T> operator*(const Rational<T>& lhs,
                                             const Rational<T>& rhs){
    ...
}
// 在非模板类中这段函数是可以编译成功的，但是模板函数这段代码错误
```

**正确做法：**

```c++
template<typename T>
const Rational<T> doMultiply(const Rational& lhs,
                                             const Rational& rhs){
    ...
        return Rational(相×);
}
// 做实际乘法，下面这个函数要在类中定义
friend Rational operator*(const Rational& lhs,
                                           const Rational& rhs){
        doMultiply(lhs,rhs);
    ...
```

#### traits机制

**通过该机制获取迭代器表现类型信息**

```c++
//用于标记迭代器的类型
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag :public input_iterator_tag {};
struct bidirectional_iterator_tag :public forward_iterator_tag {};
struct random_access_iterator_tag :public bidirectional_iterator_tag {};
// 通过别名实现iterator_category
template< ... >		//略而未写 template参数
class deque{		//deque的迭代器
public:
    class iterator{
    public:
        typedef random_access_iterator_tag iterator_category;
        ...
    };
    ...
};

template< ... >
class list{			//list的迭代器
public:
    class iterator{
    public:
        typedef bidirectional_iterator_tag iterator_category;
        ...
    };
    ...
};

template<typename IterT>//IterT的iterator_category就是用来表现IterT说自己是什么
struct iterator_traits{
    //typedef typename的使用，见条款42
    typedef typename IterT::iterator_category iterator_category;
    ...
};
...
```



通过`iterator_traits`类实现，该类是一个模板，`iterator_traits<T>`中一定有`iterator_category`成员用来获取迭代器tag类型。

**自定义trait类：**

在简单的迭代器中, 通过内嵌类型申明很好的隐藏了所指对象的内部细节, 实现了数据和算法的分离, 但是STL要求支持迭代器的算法, 应该也要支持原生指针，这里存在的一个难题就是原生指针不能内嵌类型申明, 于是这里就需要多一层的封装,萃取编译技术应运而生. 萃取(traits)编程技术，归纳成四个字就是：特性萃取。在迭代器的上下文中, 就是萃取出迭代器的value type, 可以概念上认为迭代器所指对象的类型(value type)就是该迭代器的一个特性(traits)

```c++
template <class Iterator>
struct iterator_traits {
    typedef typename Iterator::value_type value_type;
    //...
};
// 针对指针，特例化版本：
template <class T>
struct iterator_traits<T*> {
    typedef T value_type;
};
 
template <class T>
struct iterator_traits<const T*> {
    typedef T value_type;
};
```



例子：`typeid(typename std::iterator_traits<IterT>::iterator_category)
        == typeid(std::random_access_iterator_tag)`

---

标准库还定义了其他特性：

* `char_traits`
* `numeric_limits`

#### 重载替代If语句

重载在编译期间完成，if语句在运行期间完成

**注意，if语句运行时才会确定，通常我们可以重载多个模板函数，使得当前模板函数通过这些重载的模板函数完成实际功能，而不需要通过if判断完成**

例子：

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

#### 模板元编程(TMP)

使用TMP可将工作从运行期转移到编译期。

一个“酷”的例子：

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

#### 模板中别名的利用+偏特化(特化)的巧妙用处

###### 实现约束

```c++
// 基础判断降级为helper
template <typename>
struct is_floating_point_helper : false_type {};
template <>
struct is_floating_point_helper<float> : true_type {};
template <>
struct is_floating_point_helper<double> : true_type {};
template <>
struct is_floating_point_helper<long double> : true_type {};
// remove_reference和remove_const的声明
template <typename>
struct remove_const;
template <typename>
struct remove_reference;
// 实际的is_floating_point
template <typename T>
struct is_floating_point : is_floating_point_helper<typename remove_const<typename remove_reference<T>::type>::type> {};
```

###### 实现去除引用

```c++
template <typename T>
struct remove_reference {
    using type = T;
};
template <typename T>
struct remove_reference<T &> {
    using type = T;
};
template <typename T>
struct remove_reference<T &&> {
    using type = T;
};
```

###### 判断类型相同

```c++
template <typename, typename>
struct is_same : false_type {};
template <typename T>
struct is_same<T, T> : true_type {};
```

###### ...

#### new/delete Handler

标准库`<new>`头文件中针对内存管理有几个Handler函数

* `set_new_handler(函数指针)`当分配内存不够时会**无限调用**该函数回调**直到分配成功**。

  通常在该函数中做以下事情：

  * 如果该handler无法获取更多内存，会替换新的handler
  * 卸除该handler
  * 抛出bad_alloc异常
  * 不返回，调用`abort()||exit()`

**为每个类定制自己的handler**

```c++
 class Widget{
    public:
        static std::new_handler set_new_handler(std::new_handler p) throw();
        static void* operator new(std::size_t size) throw(std::bad_alloc);
    private:
        static std::new_handler currentHandler;
    };
    std::new_handler Widget::currentHandler=0;
    std::new_handler Widget::set_new_handler(std::new_handler p) throw()
    {
        std::new_handler oldHandler=currentHandler;
        currentHandler=p;
        reutrn oldHandler;
    }
}
    void* Widget::operator new(std::size_t size) throw(std::bad_alloc)
    {
        NewHandlerHolder h(std::set_new_handler(currentHandler));//安装Widget的new-handler
        return ::operator new(size);
    }
class NewHandlerHolder{
public:
    explicit NewHandlerHolder(std::new_handler nh)
    :handlere(nh){}
    ~NewHandlerHolder()
    { std::set_new_handler(handler); }
private:
    std::new_handler handler;
    NewHandlerHolder&(const NewHandlerHolder&);//防止copying
    NewHandlerHolder& operator-(const NewHandlerHolder&);
};
```

#### 自定义new/delete

使用场景：

* 自定义一些协议时候可以在new中创建头尾等\
* 为了检测运行错误
* 为了收集动态分配内存中统计信息
* 为了降低缺省new/delete中带来的额外空间分配开销
* 为了弥补缺省分配器中非最佳齐伟
* 为了将相关对象成簇集中
* 为了获得非传统的行为，如delete后将归还内容覆盖为0

规范例子：

```c++
void* operator new(std::size_t size) throw(std::bad_alloc) {
    using namespace std;
    if(size == 0)	//处理0-byte申请,将它视为 1 byte 申请
        size = 1;
    
    while(true) {
        尝试分配size bytes;
        if(分配成功）
            return 指向分配得来的内存的指针;
           
        //分配失败，找到当前的 new-handling 函数
        new_handler globalHandler = set_new_handler(0);
        set_new_handler(globalHandler);

        if(globalHandler) 
           (*globalHandler)();	//执行函数指针globalHandler指向的函数
        else 
           throw std::bad_alloc();
    }
}
void operator delete(void* rawMemory) throw(){
    if(rawMemory == 0) return;	//如果被删除的是个 null 指针，那就什么都不做

   现在， 归还 rawMemory 所指内存;
}
           
// 假设上述new是一个类的new，针对该类的派生类的new只需要判断其分配的大小
void* Base::operator new(std::size_t size) throw(std::bad_alloc) {
    if(size != sizeof(Base))			//如果大小错误
        return ::operator new(size);	//使用标准的 operator new
    ...									//否则在这处理
}
          
           
// 派生类的delete
void Base::operator delete(void rawMemory, std::size_t size) throw() {
    if(rawMemory == 0) 					//检测是否为 null 指针
        return;
    if(size != sizeof(Base)) {				//如果大小错误，让标准 operator delete 处理此一申请
        ::operator delete(rawMemory);
        return;
    }
    现在，归还rawMemory所指内存;
    return ;
}           
```

#### 如果声明了一个带额外参数的new，那麽同时必须声明一个同样额外参数的delete与之对应，并且还要声明一个不带额外参数的delete

这意味着若声明带参数的new需要同时声明3个函数

#### 通过引用捕获异常

#### 多考虑使用懒惰计算

将一些繁琐的运算直到真正需要时才进行计算。

#### 协助编译器完成返回值优化

**某些情况下返回值是不可避免地，这种情况下会产生临时对象(构造和析构)。使用以下这种方法优化：**

```c++
string s(string a,string b) {
    return string(a+b);
}

不要使用下面的代码，会产生临时对象
string s(string a,string b) {
    string t = a+b;
    return t;
}    
```

#### 某些情况下可以重载多个运算符避免隐式构造临时对象

类似下列重载，重载后针对`UPInt upi3 = 10 + upi1`对于10就不会隐式转换为UPInt了，**仅针对程序中含有大量转变的情况下使用这种方法**

```c++
const UPInt operator+(const UPInt& lhs,  // add UPInt

  const UPInt& rhs);  // and UPInt

 

const UPInt operator+(const UPInt& lhs,  // add UPInt

  int rhs);  // and int

 

const UPInt operator+(int lhs,  // add int and

  const UPInt& rhs);  // UPInt

// 对于两个参数都是int的重载是错误地，参数类型必须含有一个用户自定义类型。
```

#### 针对运算符的定义

通常通过其他运算符的实现来完成，形成依赖关系



#### 虚函数的代价

在定义了虚函数`virtual`的类中，必须额外存储一个`vptr`指针，**这意味着虚函数的类会为此付出额外的代价。**虚函数指针的大小跟普通指针大小等同，这意味着类要在保持齐位的情况下维持类的大小。

#### Union联合ENUM

#### 虚拟拷贝函数

借助

```c++
virtual Base* clone() const = 0;
...
virtual Base* clone() const {
    return new MyType(*this)
}    
```

#### 非成员函数虚拟化

有些函数必须定义为非成员函数，希望让这样的函数实现虚拟化。如`ostream<<`

可以为类定义一个虚成员函数来完成真正的工作，在非成员函数中调用成员函数

```c++
class NLComponent
{
public:
    virtual ostream& print(ostream& s) const = 0;
    ...
};
class TextBlock:public NLComponent
{
public:
    virtual ostream& print(ostream& s) const;
    ...
};
class Graphic:public NLComponent
{
public:
    virtual ostream& print(ostream& s) const;
    ...
};
inline ostream& operator<<(ostream& s,const NLComponent& c)
{
    return c.print(s);
}
```

#### 尽可能用函数中的静态变量替换类中的静态成员变量

好处：

* 直到函数被真正调用时才初始化

**注意，返回静态变量的函数不要使用内联**

#### 限制类对象的数目

将类构造函数和拷贝构造函数都删除，然后使用静态的函数来完成，并且类中需要定义限制的标志数量

```c++
class Printer {
public:
    class TooManyObjects{};
    static Printer * makePrinter();
    static Printer * makePrinter(const Printer& rhs);
    ...
private:
    static size_t numObjects;
    static const size_t maxObjects = 10; // 对象的数目限制,也可以使用枚举
    Printer();
    Printer(const Printer& rhs);
};
size_t Printer::numObjects = 0;
const size_t Printer::maxObjects;
Printer::Printer(){
    if (numObjects >= maxObjects) {
        throw TooManyObjects();
    }
    ...
}
Printer::Printer(const Printer& rhs){
    if (numObjects >= maxObjects) {
        throw TooManyObjects();
    }
     ...
}
Printer * Printer::makePrinter(){ 
    return new Printer; 
}
Printer * Printer::makePrinter(const Printer& rhs){ 
    return new Printer(rhs); 
}
```

将这种限制抽象为模板

```c++
template<class BeingCounted>
class Counted {
public:
    class TooManyObjects{}; 
    static int objectCount() { return numObjects; }
protected:
    Counted();
    Counted(const Counted& rhs);
    ~Counted() { --numObjects; }
private:
    static int numObjects;
    static const size_t maxObjects = 10; // 必须初始化由用户完成
    void init(); 
}; 
template<class BeingCounted>
Counted<BeingCounted>::Counted(){ 
    init(); 
}
template<class BeingCounted>
Counted<BeingCounted>::Counted(const Counted<BeingCounted>&){ 
    init(); 
}
template<class BeingCounted>
void Counted<BeingCounted>::init(){
    if (numObjects >= maxObjects) throw TooManyObjects()
        ++numObjects;
}
template<class BeingCounted>                 // 定义numObjects
int Counted<BeingCounted>::numObjects = 0; 
```

使用时：

```c++
class Printer: private Counted<Printer> {
public:
    static Printer * makePrinter();
    static Printer * makePrinter(const Printer& rhs);
    ~Printer();
    void submitJob(const PrintJob& job);
    void reset();
    void performSelfTest();
    ...
using Counted<Printer>::objectCount;  // 开放接口
using Counted<Printer>::TooManyObjects;
private:
    Printer();
    Printer(const Printer& rhs);
};

由于Counted<Printer>是Printer的基类,因此构造Printer之前一定会发生Counted<Printer>的构造,这样就把限制对象个数的任务交由基类Counted<Printer>来完成.此外,由于Printer只继承Counted的实现而不继承接口,因此使用private继承.如果要使开放Counted的部分接口,可以使用using declaration:
```

---

l例子：

```c++
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
```

#### 要求或禁止堆中建立对象

程序的栈从地址空间的顶部向下扩展，堆则从底部向上扩展

##### 强制类只能在堆中建立对象

在new中追踪其分配的地址到list中，delete中删除，我们如果要定义一个类判断对象指针是否是堆对象就继承该类就可以查询

```c++
class HeapTracked {                  // 混合类; 跟踪
public:                              // 从operator new返回的ptr
  class MissingAddress{};            // 异常类，见下面代码
  virtual ~HeapTracked() = 0;
  static void *operator new(size_t size);
  static void operator delete(void *ptr);
  bool isOnHeap() const;
private:
  typedef const void* RawAddress;
  static list<RawAddress> addresses;
};
// mandatory definition of static class member
list<RawAddress> HeapTracked::addresses;
// HeapTracked的析构函数是纯虚函数，使得该类变为抽象类。
// (参见Effective C++条款14). 然而析构函数必须被定义，
//所以我们做了一个空定义。.
HeapTracked::~HeapTracked() {}
void * HeapTracked::operator new(size_t size)
{
  void *memPtr = ::operator new(size);  // 获得内存
  addresses.push_front(memPtr);         // 把地址放到list的前端
  return memPtr;
}
void HeapTracked::operator delete(void *ptr)
{
  //得到一个 "iterator"，用来识别list元素包含的ptr；
  //有关细节参见条款35
  list<RawAddress>::iterator it =
    find(addresses.begin(), addresses.end(), ptr);
  if (it != addresses.end()) {       // 如果发现一个元素
    addresses.erase(it);             //则删除该元素
    ::operator delete(ptr);          // 释放内存
  } else {                           // 否则
    throw MissingAddress();          // ptr就不是用operator new
  }                                  // 分配的，所以抛出一个异常
} 
bool HeapTracked::isOnHeap() const
{
  // 得到一个指针，指向*this占据的内存空间的起始处，
  // 有关细节参见下面的讨论
  const void *rawAddress = dynamic_cast<const void*>(this);
  // 在operator new返回的地址list中查到指针
  list<RawAddress>::iterator it =
    find(addresses.begin(), addresses.end(), rawAddress);
  return it != addresses.end();      // 返回it是否被找到
} 


-===================================使用============================
class Asset: public HeapTracked {
private:
  UPNumber value;
  ...
};
我们能够这样查询Assert*指针，如下所示：
void inventoryAsset(const Asset *ap)
{
  if (ap->isOnHeap()) {
    ap is a heap-based asset — inventory it as such;
  }
  else {
    ap is a non-heap-based asset — record it that way;
  }
}
```



##### 禁止类在堆中建立对象

只需要将需要禁止的类中重载new/delete，将其定义为private即可。

```c++
class UPNumber {
private:
  static void *operator new(size_t size);
  static void operator delete(void *ptr);
  ...
};

```

#### 智能指针

智能指针的拷贝赋值通常有三种实现：

* 不允许对象共享。调用时转移所有权
* 不允许对象共享。调用时进行深拷贝
* 允许共享。使用引用计数

#### 引用计数

实现手法：**需要将数据变量也放入内嵌的类中**

```c++
class xxx {
    struct ref_data{
        数据变量
        引用计数变量
    }
}
```

#### 自定义迭代器

**注意，迭代器不等于指针**

针对几种类型：

* 若自定义的类使用**STL容器**作为数据成员，则迭代器的实现委托给STL容器

  ```c++
  class CourseList {
  private:
  	  typedef vector<Student> StudentList;
  	  StudentList students;
      
  public:
  	  typedef StudentList::iterator   iterator;
  	  typedef StudentList::const_iterator 	const_iterator;
      
  	  iterator begin() { return students.begin(); }
  	  iterator end() { return students.end(); }
    ...
  };
  
  只需要typedef重命名即可
  ```

* 若自定义的类使用了数组类型作为数据成员，则需要返回指针即可

  ```c++
  class CourseList {
  private:
    typedef Student  StudentList[100];
    StudentList  students; 
      
  public:
  	  typedef Student *  iterator; 
  	  typedef const Student *  const_iterator; 
      
  	 iterator begin() { return &students[0]; } //
   	 iterator end() { return &students[100]; } //
  };
  
  ```

* 有时候需要一个普通容器的迭代器的变体，比如该迭代器可以计数，或者迭代器可以检查是否在一个合法范围

  定义这种特殊的迭代器通常需要使用**委托模式**，新迭代器的构造函数要初始化某种存在的迭代器，以及其它所需要的信息，并将某种已有的迭代器作为私有成员变量，然后这个自定义的迭代器的operator++ operator* 只是添加一些额外的功能然后调用那个已有的迭代器变量的++ 与* 操作符

* 新型容器 -- 定义新迭代器

  基本迭代器操作符支持：`*|++|!=|`

  **实现迭代器通常需要保存：指针的首地址、元素个数**

```c++
容器要和其迭代器建立联系：

1. 在容器的begin() end()方法中，需要构造并返回迭代器
2. 在迭代器中，要有一个数据成员是对容器的引用
出于这些原因，可归纳处定义容器和其迭代器的典型模式：
1. 将迭代器的声明前置
2. 定义容器类
3. 在容器中将迭代器类声明为友元类
4. 定义迭代器类    
```

当定义一个表示迭代器的类时，可以使用以迭代器模板为基类生成的实例，这样会添加类需要的类型别名。例如：

```c++
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
```

#### 代理手法

**通常情况下，要使得proxy对象的行为和他们所扮演的对象一致，必须重载可作用于实际对象的每一个函数，这极大增加了负担，同时构建代理对象时也需要额外的负担**

##### 例子1：通过内部代理实现了二维数组的访问。

```c++
template<class T>
class Array2D {
public:
    //代理类
    class Array1D {
    public:
        T& operator[](int index);
        const T& operator[](int index) const;
    ...
    };
    Array1D operator[](int index);
    const Array1D operator[](int index) const;
    ...
};
```

##### 例子2：使用proxy class便可以做到区分non-const operator[]用于读还是写操作

```c++
class String {
public:
    //代理类用于区分operator[]的读写操作
    class CharProxy { // proxies for string chars
    public:
        CharProxy(String& str, int index); // creation
        CharProxy& operator=(const CharProxy& rhs); // lvalue
        CharProxy& operator=(char c); // uses
        operator char() const; 
    private:
        String& theString; //用于操作String,并在适当时机开辟新内存并复制
        int charIndex;
    };
    const CharProxy operator[](int index) const; // for const Strings
    CharProxy operator[](int index); // for non-const Strings
    ...
    friend class CharProxy;
private:
    RCPtr<StringValue> value;//见条款29
};

String::CharProxy& String::CharProxy::operator=(const CharProxy& rhs)
{
    if (theString.value->isShared()) {
        theString.value = new StringValue(theString.value->data);
    }
    theString.value->data[charIndex] = rhs.theString.value->data[rhs.charIndex];
    return *this;
}
String::CharProxy& String::CharProxy::operator=(char c)
{
    if (theString.value->isShared()) {
        theString.value = new StringValue(theString.value->data);
    }
    theString.value->data[charIndex] = c;
    return *this;
}
//以上来那个函数的代码部分有重复,可考虑将重复部分提取成一个函数
const String::CharProxy String::operator[](int index) const
{
    return CharProxy(const_cast<String&>(*this), index);
}
String::CharProxy String::operator[](int index)
{
    return CharProxy(*this, index);
}
String::CharProxy::CharProxy(String& str, int index): theString(str), charIndex(index) {}
String::CharProxy::operator char() const
{
return theString.value->data[charIndex];
}
```

#### 函数动态绑定时参数存在多个需要决定的对象

如：需要检测两个游戏组件的碰撞，这两个组件都继承了抽象基类。但是作为成员函数，调用时只能`component1.Collide(component2)`这样的方法中，两个参数都需要决定如何绑定，**但是我们只能决定一个对象的动态绑定，即参数中的对象**

**通过模拟虚函数表解决这样的二重调度问题：**

```c++
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <typeinfo>
#include <typeinfo.h>
class GameObject {
public:
    virtual ~GameObject() {} //基类里面有虚函数，派生类继承后，使用typeid().name才能取得对应的class name

};
class SpaceShip : public GameObject {};
class SpaceStation : public GameObject {};
class Asteroid : public GameObject {};

//匿名namespace
namespace {
    using std::string;
    using std::map;
    using std::make_pair;
    using std::pair;
    using std::cout;
    using std::endl;
    // 增加
    void shipAsteroid(GameObject& spaceShip, GameObject& asteroid) { cout << "spaceShip collide with asteroid" << endl; };
    void shipStation(GameObject& spaceShip, GameObject& spaceStation) { cout << "spaceShip collide with spaceStation" << endl; };
    void asteroidStation(GameObject& asteroid, GameObject& spaceStation) { cout << "asteroid collide with spaceStation" << endl; };

    void asteroidShip(GameObject& asteroid, GameObject& spaceShip) { shipAsteroid(spaceShip, asteroid); };
    void stationShip(GameObject& spaceStation, GameObject& spaceShip) { shipStation(spaceShip, spaceStation); };
    void stationAsteroid(GameObject& spaceStation, GameObject& asteroid) { asteroidStation(asteroid, spaceStation); };
}

//碰撞map
class CollisionMap {
public:
    //这里使用单例
    static CollisionMap* theCollisionMap() {
        static CollisionMap CM;
        return &CM;
    };

    typedef void (*HitFunctionPtr)(GameObject&, GameObject&);

    //这里添加新的碰撞处理函数，成对处理
    void addEntry(const string& type1, const string& type2, HitFunctionPtr collisionFunction)
    {
        if (collisionMap.find(std::make_pair(type1, type2)) != collisionMap.end()) return;
        //成对添加
                // printf("%p\n",collisionFunction);

        collisionMap[std::make_pair(type1, type2)] = collisionFunction;
        collisionMap[std::make_pair(type2, type1)] = collisionFunction;
        
    }

    //这里移除碰撞函数
    void removeEntry(const string& type1, const string& type2) {
        if (collisionMap.find(std::make_pair(type1, type2)) != collisionMap.end()) return;

        //成对移除
        collisionMap.erase(std::make_pair(type1, type2));
        collisionMap.erase(std::make_pair(type2, type1));
    }

    //查找有没有对应的碰撞函数
    HitFunctionPtr lookup(const string& class1, const string& class2) {
        HitMap::iterator it = collisionMap.find(make_pair(class1, class2));
        
        if (it == collisionMap.end()) {
            return 0;
        }

        return (*it).second;
    }
private:
    typedef map<pair<string, string>, HitFunctionPtr> HitMap;
    HitMap collisionMap;

    CollisionMap() { initializeCollisionMap(); };
    CollisionMap(const CollisionMap&);

    // 这里可以内部初始化，也可以改为一个函数，来注册一下函数
    void initializeCollisionMap() {
        collisionMap.clear();
        // 增加
        addEntry("9SpaceShip", "8Asteroid", &shipAsteroid);
        addEntry("9SpaceShip", "12SpaceStation", &shipStation);
        // ...
    }
};

//匿名namespace
namespace
{
    //这里处理碰撞，会查找碰撞map，如果有函数就执行，没有的话就抛出异常
    void processCollision(GameObject& object1, GameObject& object2) {  
        CollisionMap* CM = CollisionMap::theCollisionMap();
        CollisionMap::HitFunctionPtr phf = CM->lookup(typeid(object1).name(), typeid(object2).name());
        if (phf) phf(object1, object2);
        else cout << "UnkowCollision! " << typeid(object1).name() << " - " << typeid(object2).name() << endl;
    }
}

int main() {
    SpaceShip spaceShip;
    Asteroid asteroid;
    SpaceStation spaceStation;

    processCollision(spaceShip, asteroid);  //spaceShip collide with asteroid
    processCollision(asteroid, spaceShip);  //UnkowCollision! class Asteroid - class SpaceShip
    processCollision(spaceShip, spaceStation); //spaceShip collide with spaceStation
    processCollision(asteroid, spaceStation); //UnkowCollision! class Asteroid - class SpaceStation

    return 0;
}
```

#### 避免异形赋值

我们需要定义

```c++
class Animal {
public:
    virtual Animal& operator=(const Animal& rhs);
    ...
};
class Lizard: public Animal {
public:
    virtual Lizard& operator=(const Animal& rhs);

    ...
};
class Chicken: public Animal {
public:
    virtual Chicken& operator=(const Animal& rhs);
    ...
};
```

针对上述代码的继承体系，会导致以下异形赋值代码成功：

```c++
Animal *a1 = new Lizard;
Animal *a2 = new Chicken;
*a1 = *a2;
```

**因此，一般而言，我们的最根处的类一定要定义为纯虚函数，修改后的继承体系为：**

```c++
class AbstractAnimal {
protected:
    AbstractAnimal& operator=(const AbstractAnimal& rhs);
    ...
public:
    virtual ~AbstractAnimal() = 0;
    ...
}

class Animal : public AbstractAnimal {
public:
    Animal& operator=(const Animal& rhs);
    ...
}

class Lizard : public AbstractAnimal {
public:
    Lizard& operator=(const Lizard& rhs);
    ...
}

class Chicken : public AbstractAnimal {
public:
    Chicken& operator=(const Chicken& rhs);
    ...
}
```

#### 关于要引进类的功能的地位选择

* 继承其功能
* 将其定为成员变量来调用它的某些函数完成本类功能

**需要进行权衡取舍**

#### 静态初始化

类似结构

```c++
int main() {
	init();
    ...
    destory();
}
```



##### 借助流迭代器初始化

使用流可以直接把一个文件或者一些列输出初始化到一个容器中

`istream_iterator`



#### 几个模板的使用

* `function`包装函数

* `mem_fn`传入类成员函数的地址，将类的成员函数转变成一个普通函数，返回一个新的函数句柄，该函数句柄的第一个参数需要传入一个该类类型对象的地址。

  ```c++
  Foo f;
  auto greet = std::mem_fn(&Foo::display_greeting);
  greet(&f);
  void Foo::display_greeting() {
         std::cout << "Hello, world.\n";
  }
  ```

  

* `result_of`可以在编译时获取函数返回类型。

  ```c++
  result <函数名(函数参数类型列表)>::type //这是一个类型
  ```

  

  

* `enable_if`

* `bind`：将某些参数绑定到函数上形成新的函数句柄

* `std::not1`将一元谓词结果取反

* `std::not2`将二元谓词结果取反

#### ref函数包装

某些情况下要传递引用时，不能直接传递，必须使用`ref`包装
