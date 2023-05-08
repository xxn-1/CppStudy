#### 要点

对于sinks，以 mt 后缀结尾的是线程安全的，比如：`daily_file_sink_mt`，以st 后缀结尾的是非线程安全的，比如：`daily_file_sink_st`

#### 输出格式

类似于Python



#### 初始

常用初始化头文件使用：`<spdlog/spdlog.h>`

使用一些文件相关的：`<spdlog/sinks/xxx.h>`

命名域：`spdlog`

##### 常用方法

* `spdlog::get("日志名")`获取已创建日志名对象的指针，**返回的对象线程安全**

  ```c++
  // 手动创建的logger对象需要全局注册日志对象使得可以spdlog::get(logger_name)
  spdlog::register_logger(日志对象);
  
  ```

  

* `日志对象->set_level(spdlog::level::等级)`只输出某个等级以上的数据到日志对象

* `日志对象->set_pattern("输出格式")`：

  ```c
  模式大全：每个模式可以预先添加一个宽度标记来对齐，最大128：
  左对齐	%-数字<模式标志>
  右对齐 %数字<模式标志>
  中心对齐 %=数字<模式标志>
  如：%=3v
  -------------------
  %v 日志内容
  %t 线程ID
  %P 进程ID
  %n 记录器Logger名
  %l 日志级别
  %L 日志级别简称
  %a 星期几（简称）
  %A 星期几
  %b 月份简称
  %B 月份
  %c 日期时间
  %C 年（两位）
  %Y 年
  %D %x 日期简写
  %m 月份（数字）
  %d 日（数组）
  %H 小时（24制）
  %I 小时（12制）
  %M 分钟
  %S 秒
  %e 毫秒
  %f 微秒
  %F 纳秒
  %p AM/PM
  %r 时间（12制）
  %R 时分（24制）
  %T %X 时间（24制）
  %z 时区（偏移）
  %E epoch（秒）
  %% 百分号
  %+ 默认格式
  %^ start color range (can be used only once)
  %$ end color range (for example %^[+++]%$ %v) (can be used only once)
  %@ 文件名与行数
  %s 文件名
  %g 文件名（含路径）
  %# 行数
  %! 函数名
  %o 相对上一条记录的时间间隔（毫秒）
  %i 相对上一条记录的时间间隔（微秒）
  %u 相对上一条记录的时间间隔（纳秒）
  %O 相对上一条记录的时间间隔（秒）
  ////////////////////////////////
  其中几个模式需要调用宏才能开启：
  在使用<%@>、<%s>、<%#>、<%!> 不是直接写上就可以，需要调用相对应的函数宏才可实现日志输出中要携带文件名、行数或函数名时，必须使用SPDLOG_LOGGER_*宏，且要激活对应的级别（哪些级别以上的日志会被记录）：例子
  SPDLOG_LOGGER_INFO(日志对象,"将要打印的消息内容，不带模式，模式在设置模式方法中设置"); 
  ```

* 用上面的方法输出的日志仅在程序正常退出时才写入。但有时候，我们希望在程序不正常退出时查看日志以帮助我们锁定错误所在位置，由此可以加入下方代码：**实时刷新日志，会按照指定的等级以上刷新**

  ```ada
  my_logger->flush_on(spdlog::level::trace);
  spdlog::flush_every(std::chrono::seconds(5)); // 间隔刷新
  
  
  
  
  ```

##### 输出到

###### 控制台

* `spdlog::stdout_color_mt("日志名")`创建一个控制台带颜色等级输出对象

###### 文件

* `spdlog::daily_logger_mt[/st]("日志名","文件路径",时,分,...)`**会在每天这个时间点新建一个日志文件**
* `spdlog::basic_logger_mt`日志文件会一直被写入，不断变大
* `spdlog::rotating_logger_mt(日志名,文件路径,文件最大大小，文件最多个数)`滚动日志，当日志文件超出规定大小后，会根据文件最多个数参数决定当前文件，可能会更名当前文件，然后创建新文件写入

###### 流

* `spdlog::ostream_sink_mt`

###### 丢弃

* `spdlog::null_sink_st`丢弃所有到它的日志

###### 分发器

将日志消息分发到它的接收器列表

```c++
#include "spdlog/sinks/syslog_sink.h"
...
auto dist_sink = make_shared<spdlog::sinks::dist_sink_st>();
auto sink1 = make_shared<spdlog::sinks::stdout_sink_st>();
auto sink2 = make_shared<spdlog::sinks::simple_file_sink_st>("mylog.log");

dist_sink->add_sink(sink1);
dist_sink->add_sink(sink2);
```



##### 多对一/一对多

###### 多对一

多个日志对象输出后，输出到同一个输出对象

```c++
 auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logfile", 23, 59);
        // create synchronous  loggers
auto net_logger = std::make_shared<spdlog::logger>("net", daily_sink);
auto hw_logger  = std::make_shared<spdlog::logger>("hw",  daily_sink);
auto db_logger  = std::make_shared<spdlog::logger>("db",  daily_sink);      


```

###### 一对多

一个日志对象输出后，输出到不同输出对象(如：同时输出到控制台和文件)

```c++
std::vector<spdlog::sink_ptr> sinks;
sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_st>("logfile", 23, 59));
auto combined_logger = std::make_shared<spdlog::logger>("name", begin(sinks), end(sinks));
//register it if you need to access it globally
spdlog::register_logger(combined_logger);
```

##### 默认全局logger对象

默认情况下，已经有一个全局记录日志对象：`spdlog::info/debug...`，可以使用其他对象替换：`spdlog::set_default_logger(日志对象)`

##### 删除所有日志对象

* `spdlog::drop_all()`
* `spdlog::drop("日志对象名")`

##### 打印日志中出现错误的处理方法

全局

```c++
spdlog::set_error_handler([](const std::string& msg) {
        std::cerr << "my err handler: " << msg << std::endl;
});
```

局部对象

```c++
critical_logger->set_error_handler([](const std::string& msg) {
        throw std::runtime_error(msg);
});
```



#### 异步特性

`#include <spdlog/asynch.h>`

异步就一定需要线程或线程池+日志队列，这将会销毁之前的全局线程池对象tp，并创建一个新的线程池–这也意味着所有使用旧的线程池tp的loggers都将停止工作，因此建议在任何`async loggers`被创建之前调用该函数

* `spdlog::init_thread_pool(日志队列字节数,线程个数)`

异步类型日志，例子：

`spdlog::rotating_logger_mt<spdlog::async_factory>(初始化)`

##### VS上bug

**一定要确保在main()函数退出时调用`spdlog::shutdown()`函数**