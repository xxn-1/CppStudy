---
QT
---

[TOC]

#### QT概况

QT将所有内容分为3部分：

1. QT基本模块：定义了适用于所有平台的基础功能，是QT核心。基本模块的基础是QT Core模块，其他模块都依赖于该模块。基本模块包括：

   ​	![](https://pic.imgdb.cn/item/642e6f41a682492fccbfc495.png)

2. QT扩展模块

   ​	![](https://pic.imgdb.cn/item/642e7036a682492fccc123be.png)

   ​	![](https://pic.imgdb.cn/item/642e7036a682492fccc123f6.png)

3. QT开发工具

#### 项目组成

##### 项目管理文件

后缀`.pro`是项目的管理文件，文件名就是项目的名称。

```C
QT	+= core gui // 表示项目中加入core gui模块，用于GUI设计的类库模块
// 如果要用sql模块，就要加QT	+= sql
greaterThan(QT_MAJOR_VERSION,4):QT += widgets // 表示QT主版本大于4时才加入widgets模块
TARGET = 文件名 // 表示生成可执行文件为--文件名.exe

```

#### 组件

对需要访问的组件要修改其`objectName`，以便进行区分，不访问的则不用修改。