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

