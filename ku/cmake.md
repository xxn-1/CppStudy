---
在当前目录下编写CMakeLists.txt文件解析
---

#### 创建生成文件夹

```cmake
mkdir build
cd build
cmake .. // 编译
cmake --build . // 生成可执行文件
```



#### 语法

内容初始格式：

```cmake
project(本工程名)

```

##### 注释

`#`

##### 变量

`set`

设置值

```cmake
set(变量名 "daw")
set(变量名 ON)
set(变量名 OFF)
set(变量名 1)
# ON/OFF是布尔
# 列表设置，使用分号分割的多个值
set(变量名 V1;V2)

```

**使用变量：**`${<variable>}`

###### 缓存变量

```text
# set(<variable> <value>  CACHE <type> <docstring> [FORCE])
type为：STRING/INT等等
引用CACHE变量：$CACHE{<varialbe>}。
Cache变量会被保存在构建目录下的CMakeCache.txt中，缓存起来之后是不变的，除非重新配置更新
```

###### 环境变量

```c
set(ENV{ENV_VAR} "$ENV{PATH}")
要引用环境变量，格式为：$ENV{<variable>}
```

##### 内置变量

```c
CMake常见内置变量及环境变量
1、CMAKE_C_COMPILER:指定C编译器；
2、CMAKE_CXX_COMPILER:指定C++编译器；
3、CMAKE_C_FLAGS:指定编译C文件时的编译选项，如-g，也能够通过add_ditions加入编译选项；
4、CMAKE_CXX_FLAGS:设置C++编译选项。
6、CMAKE_COMMAND:也就是CMake可运行文件本身的全路径；
7、CMAKE_DEBUG_POSTFIX：Debug版本号生成目标的后缀，通常能够设置为”d”字符；
8、CMAKE_GENERATOR:编译器名称。比如”UnixMakefiles”, “Visual Studio 7”等；
9、CMAKE_INSTALL_PREFIX:project安装文件夹。全部生成和调用所需的可运行程序。库文件，头文件都会安装到该路径下，Unix/Linux下默觉得/usr/local, windows下默觉得C:\Program Files;
10、CMAKE_MODULE_PATH:设置搜索CMakeModules模块(.cmake)的额外路径。用来定义自己的cmake模块所在的路径；
11、CMAKE_CURRENT_SOURCE_DIR:指的是当前处理的CMakeLists.txt所在的路径。
12、CMAKE_CURRENT_BINARY_DIR:假设是in-source编译。则跟CMAKE_CURRENT_SOURCE_DIR一致。假设是out-of-source，指的是target编译文件夹；
13、CMAKE_CURRENT_LIST_FILE:输出调用这个变量的CMakeLists.txt的完整路径；
14、CMAKE_CURRENT_LIST_LINE:输出这个变量所在的行；
15、CMAKE_INCLUDE_CURRENT_DIR:自己主动加入CMAKE_CURRENT_BINARY_DIR和CMAKE_CURRENT_SOURCE_DIR到当前处理的CMakeLists.txt;
16、CMAKE_INCLUDE_DIRECTORIES_PROJECT_EFORE:将project提供的头文件文件夹始终至于系统头文件文件夹的前面，当你定义的头文件确定跟系统发生冲突时能够提供一些帮助。
17、EXECUTABLE_OUTPUT_PATH:指定可运行文件的存放路径。终于结果的存放文件夹；
18、LIBRARY_OUTPUT_PATH:指定库文件存放路径，终于结果的存放文件夹；
19、BUILD_SHARED_LIBS:指定编译成静态库还是动态库；
20、PROJECT_BINARY_DIR(CMAKE_BINARY_DIR):假设是内部构建(in-sourcebuild),指的就是project顶层文件夹；假设是外部构建(out-of-source build)。指的是project编译发生的文件夹；
21、PROJECT_NAME:project名称。即使用PROJECT命令设置的名称；
22、PROJECT_SOURCE_DIR(CMAKE_SOURCE_DIR):project源码文件所在的文件夹。指的是project顶层文件夹；
23、CYGWIN:标识当前系统是否为Cygwin；
24、MSVC:标识当前系统是否使用MicrosoftVisual C。
25、UNIX:标识当前系统是否为Unix系列(包含Linux、Cygwin和Apple);
26、WIN32：标识当前系统是否为Windows及Win64;

```



##### **条件语句**

支持的语法有：

1. 字符串比较，比如：**STREQUAL、STRLESS、STRGREATER**等；
2. 数值比较，比如：**EQUAL、LESS、GREATER**等；
3. 布尔运算，**AND、OR、NOT**；
4. 路径判断，比如：**EXISTS、IS_DIRECTORY、IS_ABSOLUTE**等；
5. 版本号判断；等等；
6. 使用小括号可以组合多个条件语句，比如：**(cond1) AND (cond2 OR (cond3))**。

对于**常量**：

1. ON、YES、TRUE、Y和非0值均被视为`True`；
2. 0、OFF、NO、FALSE、N、IGNORE、空字符串、NOTFOUND、及以"-NOTFOUND"结尾的字符串均视为`False`。

对于**变量**，只要**其值不是常量中为`False`的情形，则均视为`True`**。

##### 消息打印

`message`

```text
message([<mode>] "message text" ...)
```

其中`mode`就相当于打印的等级，常用的有这几个选项：

1. 空或者`NOTICE`：比较重要的信息，如前面演示中的格式
2. DEBUG：调试信息，主要针对开发者
3. STATUS：项目使用者可能比较关心的信息，比如提示当前使用的编译器
4. WARNING：CMake警告，不会打断进程
5. SEND_ERROR：CMake错误，会继续执行，但是会跳过生成构建系统
6. FATAL_ERROR：CMake致命错误，会终止进程

##### 分支控制

`if()/elseif()/else()/endif()`举个例子，for/while循环也是类似的：

```text
set(EMPTY_STR "")
if (NOT EMPTY_STR AND FLAG AND NUM LESS 50 AND NOT NOT_DEFINE_VAR)
    message("The first if branch...")
elseif (EMPTY_STR)
    message("EMPTY_STR is not empty")
else ()
    message("All other case")
endif()
```

##### 列表操作

`list`也是CMake的一个命令，有很多有用的子命令，比较常用的有：

1. `APPEND`，往列表中添加元素；
2. `LENGTH`，获取列表元素个数；
3. `JOIN`，将列表元素用指定的分隔符连接起来；

示例如下：

```text
set(SLOGAN_ARR To be)   # Saved as "To;be"
set(SLOGAN_ARR To;be)
set(SLOGAN_ARR "To;be")
set(WECHAT_ID_ARR Real Cool Eengineer)
list(APPEND SLOGAN_ARR a)                # APPEND sub command
list(APPEND SLOGAN_ARR ${WECHAT_ID_ARR}) # Can append another list
list(LENGTH SLOGAN_ARR SLOGAN_ARR_LEN)   # LENGTH sub command
# Convert list "To;be;a;Real;Cool;Engineer"
# To string "To be a Real Cool Engineer"
list(JOIN SLOGAN_ARR " " SLOGEN_STR)
message("Slogen list length: ${SLOGAN_ARR_LEN}")
message("Slogen list: ${SLOGAN_ARR}")
message("Slogen list to string: ${SLOGEN_STR}\n")
```

##### 文件操作

CMake的`file`命令支持的操作比较多，可以**读写、创建或复制文件和目录、计算文件hash、下载文件、压缩文件**等等。 使用的语法都比较类似，以笔者常用的递归遍历文件为例，下面是获取src目录下两个子目录内所有c文件的列表的示例：

```cmake
file(GLOB_RECURSE ALL_SRC
        src/module1/*.c
        src/module2/*.c
        )
        #GLOB_RECURSE表示执行递归查找，查找目录下所有符合指定正则表达式的文件。
```

##### 配置文件生成

`configure_file`命令可以将配置文件模板中的特定内容替换，生成目标文件。 将输入文件中的内容`@VAR@`或者`${VAR}`在输出文件中将被对应的变量值替换，将input文件中的`#cmakedefine var`关键字替换成`#define var`或者`#undef var`。 使用方式为：

```cmake
set(VERSION 1.0.0)
configure_file(version.h.in # 输入文件，输入文件中对应变量名被自动替换成指定值，如输入文件中包含：#define VERSION @VERSION@，被自动替换
"${PROJECT_SOURCE_DIR}/version.h")
```

假设`version.h.in`的内容为：

```text
#define VERSION "@VERSION@"
```

那么生成的`version.h`的内容为：

```text
#define VERSION "1.0.0"
```

##### 执行系统命令

使用`execute_process`命令可以执行一条或者顺序执行多条系统命令，对于需要使用系统命令获取一些变量值是有用的。比如获取当前仓库最新提交的commit的commit id：

```text
execute_process(COMMAND bash "-c" "git rev-parse --short HEAD" OUTPUT_VARIABLE COMMIT_ID
```

##### 查找库文件

通过find_library在指定的路径和相关默认路径下查找指定名字的库，常用的格式如下：

`find_library (<VAR> name1 [path1 path2 ...])`

##### 引入其他模块

`include`命令将cmake文件或者模块加载并执行。比如：

```text
include(CPack) # 开启打包功能
include(CTest) # 开启测试相关功能
```

---

#### CMakeLists.txt写法

```cmake
cmake_minimum_required(VERSION 3.4.1)
# 指定 cmake 的最小版本
project(demo VERSION 版本号格式为major.minor.patch.tweak LANGUAGES C CXX)
# 设置项目名称,这个命令不是强制性的，它会引入两个变量 demo_BINARY_DIR 和 demo_SOURCE_DIR，同时，cmake 自动定义了两个等价的变量 PROJECT_BINARY_DIR 和 PROJECT_SOURCE_DIR。
# 通过VERSION指定版本号，格式为major.minor.patch.tweak，并且CMake会将对应的值分别赋值给以下变量（如果没有设置，则为空字符串）：

# PROJECT_VERSION, <PROJECT-NAME>_VERSION
# PROJECT_VERSION_MAJOR, <PROJECT-NAME>_VERSION_MAJOR
# PROJECT_VERSION_MINOR, <PROJECT-NAME>_VERSION_MINOR
# PROJECT_VERSION_PATCH, <PROJECT-NAME>_VERSION_PATCH
# PROJECT_VERSION_TWEAK, <PROJECT-NAME>_VERSION_TWEAK
add_executable(demo demo.cpp) # 生成可执行文件
add_library(common STATIC util.cpp) # 生成静态库
add_library(common SHARED util.cpp) # 生成动态库或共享库


# 设置编译类型add_library 默认生成是静态库，通过以上命令生成文件名字，
# 在 Linux 下是：
# demo
# libcommon.a
# libcommon.so
# 在 Windows 下是：
# demo.exe
# common.lib
# common.dll
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
# 指定编程语言版本，CMAKE_、_CMAKE或者以下划线开头后面加上任意CMake命令的变量名都是CMake保留的内置变量
add_compile_options(-Wall -Wextra -pedantic -Werror)
# 针对所有编译器配置
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pipe -std=c99")
# 仅针对C编译器配置
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -std=c++11")
还可针对具体编译类型：
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

# 仅针对C++编译器配置
set(CMAKE_BUILD_TYPE Debug)
# 配置编译类型，可设置为：Debug、Release、RelWithDebInfo、MinSizeRel等
add_definitions(-DDEBUG -DREAL_COOL_ENGINEER=1) 
# 添加全局宏定义，等同于C中#define，定义后C中相当于定义了对应的#define，每个变量都以-D开头，实际名字为-D之后的，有值宏只需要加=号。
add_library(<name> [STATIC | SHARED | MODULE]
            [EXCLUDE_FROM_ALL]
            [source1] [source2 ...])
# 生成库name属性必须全局唯一，生成的library名会根据STATIC或SHARED成为name.a或name.lib。STATIC(静态库)/SHARED(动态库)/MODULE(模块库)
add_library(<name> <SHARED|STATIC|MODULE|OBJECT|UNKNOWN> IMPORTED [GLOBAL])
# 添加已存在的库
include_directories(...)
# 设置头文件搜索的目录

include(file)
# 在当前文件里包含还有一个CMake脚本文件的内容,用来加载CMakeLists.txt文件，也用于加载提前定义的cmake模块。
message
# 打印消息。在控制台或者对话框输出一行或多行调试信息；
find_library(${var} NAMES name1[name2 …] PATHS path1 [path2 …] PATH_SUFFIXES suffix1 [uffix2 …])
# 搜索一个外部的链接库文件,并将结果的全部路径保存到var变量中
find_path(<VAR> name1[path1 path2 …])
# 该命令在參数path*指示的文件夹中查找文件name1并将查找到的路径保存在变量VAR中(当中使用”[…]”包含的项表示可忽略项，使用”…|…”切割的项表示仅仅能选择当中一项)。
set_target_properties
# 用来设置输出的名称，对于动态库，还能够用来指定动态库版本号和API版本号；
option(${var} “text” value)
# 向用户提供一个可选项。提示信息为text。初始值为value，并将终于的结果传递到var变量中。
install
# 安装目标project到指定的文件夹,此命令用于定义安装规则，安装的内容能够包含目标二进制、动态库、静态库以及文件、文件夹、脚本等；
target_link_libraries(可执行文件名即add_executable的变量名 依赖库的名字即addlibrary的名字)
# 能够用来为target加入须要链接的共享库。指定project所用的依赖库，加入链接库，加入动态库或静态库，相当于指定-l參数；
```





#### 例子

```
./cmake-template
├── CMakeLists.txt
├── src
│   └── c
│       ├── cmake_template_version.h
│       ├── cmake_template_version.h.in
│       ├── main.c
│       └── math
│           ├── add.c
│           ├── add.h
│           ├── minus.c
│           └── minus.h
└── test
    └── c
        ├── test_add.c
        └── test_minus.
```

项目的构建任务为：

1. 将math目录编译成静态库，命名为math

   ```c
   file(GLOB_RECURSE MATH_LIB_SRC
           src/c/math/*.c
           )
   add_library(math STATIC ${MATH_LIB_SRC})
   ```

   

2. 编译main.c为可执行文件demo，依赖math静态库

   ```
   add_executable(demo src/c/main.c)
   target_link_libraries(demo math)
   ```

   

3. 编译test目录下的测试程序，可以通过命令执行所有的测试

4. 支持通过命令将编译产物安装及打包

   ```c
   install(TARGETS math demo // TARGETS后跟需要安装的列表
           RUNTIME DESTINATION xxx 
           LIBRARY DESTINATION xxx
           ARCHIVE DESTINATION xxx)
   // 参数RUNTIME DESTINATION、LIBRARY DESTINATION、ARCHIVE DESTINATION分别指定可执行文件、库文件、归档文件分别应该安装到安装目录下个哪个子目录。
   ```

   