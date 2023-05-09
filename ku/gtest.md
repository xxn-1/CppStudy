---
头文件gtest/gtest.h，链接库gtest_main.lib,gtest.lib,gmock.lib,gmock_main.lib
https://blog.csdn.net/jkddf9h8xd9j646x798t/article/details/105964161?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-105964161-blog-129078358.235%5Ev32%5Epc_relevant_default_base3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-105964161-blog-129078358.235%5Ev32%5Epc_relevant_default_base3&utm_relevant_index=2
---

main函数中写套路化：

```c++
int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

```



#### 测试

##### 自定义消息

每个宏也可以使用 << 运算符在测试失败时输出自定义信息，如：

```c
ASSERT_EQ(M[i], N[j]) << "i = " << i << ", j = " << j;

```

##### 简单测试

```c++
TEST(分类名, 测试名) { // 分类名和测试名也可使用中文
    测试代码
}


```

在类中添加：

```c++
FRIEND_TEST(分类名, 测试名);
// 声明该测试为该类的友元
```

##### 复杂测试

**需要自定义测试类，其中要包含测试主体，同时要继承测试类：**

![img](https://img-blog.csdnimg.cn/img_convert/ac1d3faecd3c66b0eaf549aef985c4f5.png)

```c
从::testing::Test派生自定义测试类后, 有以下类函数可重载.

void SetUp(); 在测试创建时被调用
void TearDown(); 在测试结束时被调用
static void SetUpTestSuite() 在进程启动时调用一次
static void TearDownTestSuite() 在进程退出时调用一次

```



```c++
TEST_F(类名, 测试名) { // 这里的类名为上述CalculationTest
    测试代码 // 直接使用p
}
// 类内可以通过静态变量共享对象
```



##### 全局共享对象

```c
自定义类public继承 ::testing::Environment.
定义并实现 void SetUp().
定义并实现 void TearDown()
在 RUN_ALL_TESTS()前用new为本类生成一个实例, 然后用 ::testing::AddGlobalTestEnvironment 注册为全局共享对象.

```

##### 自定义测试模板

```c
自定义测试类public继承 testing::TestWithParam<T>
在函数外用 INSTANTIATE_TEST_SUITE_P(数据注释, 类名, 数据生成器1, 数据生成器2...) 定义测试数据.
使用TEST_P取代TEST_F或TEST定义测试模板.
```



##### 异常测试

|     ASSERT宏     |     EXPECT宏     |                     功能                     |
| :--------------: | :--------------: | :------------------------------------------: |
| ASSERT_NO_THROW  | EXPECT_NO_THROW  |        不抛出异常，参数为 (statement)        |
| ASSERT_ANY_THROW | EXPECT_ANY_THROW |         抛出异常，参数为 (statement)         |
|   ASSERT_THROW   |   EXPECT_THROW   | 抛出特定类型的异常，参数为 (statement, type) |

##### 值参数化测试

值参数化测试即为为被测对象带入大量随机值进行测试，类似于在for循环内使用函数。gtest中的定位是用来使用大量随机值来检验算法实现的正确性，或比较同一个接口的不同实现之间的差别。gtest把“集中输入测试参数”的需求抽象出来提供支持，称为值参数化测试（Value Parameterized Test)。
值参数化测试包括4个步骤：

1. 自定义测试类public继承 `testing::TestWithParam<T>`
2. 在此类中，可实现SetUp、TearDown等方法。测试参数由TestWithParam实现的GetParam()方法依次返回。
3. 使用TEST_P(而不是TEST_F)定义测试。
4. 在函数外用 `INSTANTIATE_TEST_SUITE_P(数据注释, 类名, 数据生成器1, 数据生成器2...)` 定义测试数据.

数据生成器：

| 生成器名 | 参数        | 生成数据                                                     |
| -------- | ----------- | ------------------------------------------------------------ |
| Range    | (b, e, s=1) | 以s为步长生成[b, e)区间内的的数据                            |
| Values   | (v1, v2, …) | 简单枚举数据v1, v2, …                                        |
| ValuesIn | (a)         | 枚举C数组a内的数据                                           |
| ValuesIn | ©           | 枚举STL容器c内的数据                                         |
| ValuesIn | (b, e)      | 枚举迭代器b到e的数据                                         |
| Bool     | ()          | 枚举true和false                                              |
| Combine  | (g1, g2, …) | 枚举生成器g1, g2, …等的<br/>所有数据的所有组合(笛卡尔积)<br/>并用std::tuple捆绑输出 |
|          |             |                                                              |

```c++
// 例子
// addupto.h  
#pragma once  
 
inline unsigned NaiveAddUpTo(unsigned n) {  
    unsigned sum = 0;  
    for(unsigned i = 1; i <= n; ++i) sum += i;  
    return sum;  
}  
 
inline unsigned FastAddUpTo(unsigned n) {  
    return n*(n+1)/2;  
} 
 
// addupto_test.cpp
//参数化测试  
#include <gtest/gtest.h>  
#include "addupto.h"  
 
class AddUpToTest : public testing::TestWithParam<unsigned>//继承此类进行值参数化测试
{  
public:  
AddUpToTest() { n_ = GetParam(); }  //测试参数由此返回
protected:  
unsigned n_;  
};  
 
TEST_P(AddUpToTest, Calibration) {  
    EXPECT_EQ(NaiveAddUpTo(n_), FastAddUpTo(n_));  //期望a和b相等，不中断
}  
 
INSTANTIATE_TEST_CASE_P(  
    NaiveAndFast, // prefix  前缀，自定义
    AddUpToTest,   // test case name  测试用例名称，自定义
    testing::Range(1u, 1000u) // parameters  参数，u表示unsigned，必需严谨，否则编译错误，
    					//也可以使用 testing::Range<unsigned>(1, 1000)，产生的参数会传入类中对应的参数
    ); 
```

##### 类型测试

##### 自省/反射

使用以下代码获取当前测试的信息对象

```
const ::testing::TestInfo* const test_info =
::testing::UnitTest::GetInstance()->current_test_info();
```

#### 测试方法

给出测试的接口，和实际期望值

- ASSERT_ XXX: 断言, 不通过检查则中断测试, 当在测试外使用时要求函数返回void.
- EXPECT_XXX : 期望, 不通过检查并不中断测试.

|       后缀        |   参数    |       通过条件       |
| :---------------: | :-------: | :------------------: |
|       TRUE        |     ©     |      c == true       |
|       FALSE       |     ©     |      c == false      |
|        EQ         |   (a,b)   |        a == b        |
|        NE         |   (a,b)   |        a != b        |
|        LT         |   (a,b)   |        a < b         |
|        LE         |   (a,b)   |        a <= b        |
|        GT         |    GT     |        a > b         |
|        GE         |  (a, b)   |        a >= b        |
|     FLOAT_EQ      |  (a, b)   |    float型 a ≈ b     |
|     DOUBLE_EQ     |  (a, b)   |    double型 a ≈ b    |
|       NEAR        | (a, b, e) |   abs(a - b) <= e    |
| HRESULT_SUCCEEDED |    (h)    | SUCCEEDED(h) == true |
|  HRESULT_FAILED   |    (h)    |  FAILED(h) == true   |

浮点数的大小比较未直接提供, gtest提供了3型检查函数

 EXPECT_PRED_FORMAT2(::testing::FloatLE, v1, v2); 

- `::testing::FloatLE`
- `::testing::DoubleLE`

对字符串的检查后缀：

|   STREQ   | (a, b) |       C字符串相等       |
| :-------: | :----: | :---------------------: |
|   STRNE   | (a, b) |      C字符串不相等      |
| STRCASEEQ | (a, b) |  C字符串忽略大小写相等  |
| STRCASENE | (a, b) | C字符串忽略大小写不相等 |

##### 自定义值检查

1型检查函数要求返回值能隐式转为bool.

| 后缀  |        参数        |            通过条件            |
| :---: | :----------------: | :----------------------------: |
| PRED1 |       (f, v)       |       bool(f(v)) == true       |
| PRED2 |     (f, v, w)      |     bool(f(v, w)) == true      |
| PRED3 |    (f, v, w, x)    |    bool(f(v, w, x)) == true    |
| PRED4 |  (f, v, w, x, y)   |  bool(f(v, w, x, y)) == true   |
| PRED5 | (f, v, w, x, y, z) | bool(f(v, w, x, y, z)) == true |


​		
​		自定义值检查2 2型检查函数

1. 定义返回值为 ::testing::AssertResult 的检查函数.

2. 在检查通过的地方返回 ::testing::AssertionSuccess().

3. 在检查不通过的地方返回 ::testing::AssertionFailure(), 返回前可对其使用 << 输出注释.

4. 现可使用 EXPECT_TURE(f(v)) 和 ASSERT_TRUE(f(v)) 做自定义检查.
   ```c++
   ::testing::AssertionResult IsEven(int n) {
       if((n % 2) == 0) {
           return ::testing::AssertionSuccess();
       } else {
           return ::testing::AssertFailure() << n << "为奇数";
       }
   }
   EXPECT_TRUE(IsEven(4 + 3))
   
   ```

    

自定义值检查3 3型检查函数