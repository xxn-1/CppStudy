#### 结构

[GLFW介绍 - 简书 (jianshu.com)](https://www.jianshu.com/p/5ac964bb4a03)

**窗口初始化：**

* `glfwWindowHintString()：`单独设置字符串值提示，这个函数为下一次glfwCreateWindow函数的调用设置**hints**

* `glfwWindowHint()`：单独设置整数值提示。

* `glfwDefaultWindowHints()：`一次将所有提示重置为默认值。

* `glfwInit()`：初始化GLFW库。

  这些提示分为窗口相关提示（Window related hints），帧缓冲区相关提示（Framebuffer related hints），显示器相关提示（Framebuffer related hints），以及上下文相关提示（Context related hints）。常用的Hint：

  ![img](https://img-blog.csdnimg.cn/20181219203459264.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM2MzgzNjIz,size_16,color_FFFFFF,t_70)

  ```
  	GLFW_RESIZABLE----------------用户能否调节窗口大小
  	GLFW_VISIBLE------------------窗口是否可见
  	GLFW_DECORATED----------------窗口边框的小部件是否可见
  	GLFW_FOCUSED------------------窗口是否具有输入焦点
  	GLFW_AUTO_ICONIFY-------------全屏窗口是否在焦点丢失,关闭窗口小部件等图标化
  	GLFW_FLOATING-----------------置顶
  	GLFW_MAXIMIZED----------------窗口最大化
  	GLFW_CENTER_CURSOR------------光标是否在新创建的全屏窗口上居中
  	GLFW_TRANSPARENT_FRAMEBUFFER--窗口透明
  	GLFW_FOCUS_ON_SHOW------------获得输入焦点时glfwShowWindow是否被调用
  	GLFW_SCALE_TO_MONITOR---------根据监视器内容比例调整窗口内容区域的大小
  	GLFW_REFRESH_RATE-------------全屏时指定刷新率
  	GLFW_RED_BITS-----------------颜色缓冲区中红色深度
  	GLFW_GREEN_BITS---------------颜色缓冲区绿色深度
  	GLFW_BLUE_BITS----------------颜色缓冲区蓝色深度
  	GLFW_ALPHA_BITS---------------颜色缓冲区混合深度
  	GLFW_DEPTH_BITS---------------深度缓冲区深度
  	GLFW_STENCIL_BITS-------------模板缓冲区深度
  	GLFW_ACCUM_RED_BITS-----------累积缓冲区中红色深度
  	GLFW_ACCUM_GREEN_BITS---------累积缓冲区中绿色深度
  	GLFW_STEREO	------------------OpenGL立体渲染
  	GLFW_DOUBLEBUFFER-------------双缓冲区
  	GLFW_ACCUM_BLUE_BITS----------累计缓冲区中蓝色深度
  	GLFW_ACCUM_ALPHA_BITS---------累计缓冲区中混合深度
  	GLFW_AUX_BUFFERS--------------辅助缓冲区
  	GLFW_SAMPLES------------------多重采样的样本数
  	GLFW_SRGB_CAPABLE-------------缓冲区是否支持sRGB
  	GLFW_CONTEXT_VERSION_MAJOR---设置主版本号
  	GLFW_CONTEXT_VERSION_MINOR---设置次版本号
  	GLFW_CLIENT_API--------------设置OpenGL版本
  	GLFW_CONTEXT_CREATION_API----创建上下文的API
  	GLFW_OPENGL_FORWARD_COMPAT---是否向之前版本兼容
  	GLFW_OPENGL_DEBUG_CONTEXT----是否创建调试上下文
  	GLFW_OPENGL_PROFILE----------指定OpenGL上下文的配置文件
  	GLFW_CONTEXT_ROBUSTNESS------指定上下文的健壮性策略
  	GLFW_CONTEXT_RELEASE_BEHAVIOR-指定上下文要使用的发布行为
  	GLFW_CONTEXT_NO_ERROR--------是否应由上下文生成错误
  
  ```

  

**窗口创建：**

* `GLFWwindow* window = glfwCreateWindow(640(宽), 480(高),  “My Title”(标题), NULL, NuLL);`

* 全屏窗口：`GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", glfwGetPrimaryMonitor(), GLFWwindow * 	share(NULL));`第四个参数用于全屏模式得显式，最后一个值share表示要与其共享资源得上下文窗口，值为NULL表示不共享

  ```
  返回值:
  	成功返回窗口的句柄否则返回NULL
  	可能的错误包括:
  		GLFW_NOT_INITIALIZED -------------------没有初始化
  		GLFW_INVALID_ENUM-----------------------无效的枚举
  		GLFW_INVALID_VALUE----------------------无效的数值
  		GLFW_API_UNAVAILABLE--------------------api不可用
  		GLFW_VERSION_UNAVAILABLE-----------------版本不可用
  		GLFW_FORMAT_UNAVAILABLE------------------格式错误
  		GLFW_PLATFORM_ERROR----------------------平台错误
  ```

  

**窗口销毁：**`glfwDestroyWindow(window);glfwTerminate();`



#### 渲染循环

保证主动关闭应用程序之前，它能够不断绘制图像并能够接受用户输入。

```c++
 while (!glfwWindowShouldClose(window))//glfwWindowShouldClose函数在每次循环开始前检查一次GLFW是否被要求退出，如果是的话该函数返回true，渲染循环结束。
    {
        //渲染指令
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//清除颜色设置为X色
        // glClear(GL_COLOR_BUFFER_BIT);//执行清除
        //检查并调用事件，交换缓冲
        // glfwSwapBuffers(window);//glfwSwapBuffers函数会交换颜色缓冲（储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
        glfwPollEvents(回调函数，在窗口设置好后调用);//glfwPollEvents函数检查是否触发事件（比如键盘输入、鼠标移动）、更新窗口状态，并调用对应地回调函数（可以通过回调方法手动设置）
    }
```

##### 双缓冲

应用程序使用单缓冲绘图时可能会存在图像闪烁的问题。 这是因为生成的图像不是一下子被绘制出来的，而是按照从左到右，由上而下逐像素地绘制而成的。最终图像不是在瞬间显示给用户，而是通过一步一步生成的，这会导致渲染的结果很不真实。为了规避这些问题，我们应用双缓冲渲染窗口应用程序。**前**缓冲保存着最终输出的图像，它会在屏幕上显示；而所有的的渲染指令都会在**后**缓冲上绘制。当所有的渲染指令执行完毕后，我们**交换**(Swap)前缓冲和后缓冲，这样图像就立即呈显出来，之前提到的不真实感就消除了。

`void glfwSwapBuffers(GLFWwindow* window);`



#### 输入控制

* `glfwGetKey(window对象,按键)`返回值：GLFW_PRESS/GLFW_RELEASE

```c++
voidprocessInput(GLFWwindow *window){    
 if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)        // 中间 
 glfwSetWindowShouldClose(window, true); //按下ESC，关闭GLFW
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
glfwSetKeyCallback(window, key_callback); // 设置回调函数

```

#### 常用函数

**初始化并创建窗口**：常用接口如下：

1. int glfwInit(void)：必须在其他任何GLFW函数之前被调用，因为它负责初始化整个GLFW库。如果成功的话，该接口将返回GL_TRUE，否则就会返回GL_FALSE。
2. GLFWwindow* glfwCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)：负责创建一个新的OpenGL环境和窗口。
   monitor非NULL的话，窗口会被全屏创建到指定的监视器上，分辨率由width和height来指定。否则窗口会被创建到桌面上，并且尺寸由width和height来指定。
   title是一个UTF-8字符串的指针，可以用来创建窗口的初始标题。
   share非NULL的话，新创建的窗口所关联的OpenGL环境将与share所给定的关联环境共享资源。
3. void glfwMakeContextCurrent(GLFWwindow* window)：设置参数window中的窗口所关联的OpenGL环境为当前环境。这个环境在当前线程中会一直保持为当前环境，直到另一个环境被设置为当前环境，或者窗口被删除为止。
4. int glfwWindowShouldClose(GLFWwindow* window)：如果用户准备关闭参数window所指定的窗口，那么此接口将会返回GL_TRUE，否则将会返回GL_FALSE。
5. void glfwSwapBuffers(GLFWwindow* window)：请求窗口系统将参数window关联的后缓存画面呈现给用户。通常这一步是通过窗口的前后缓存的交换完成的。也可能是在一个“预备显示”的帧缓存队列中进行截取，窗口系统可能需要等待一次垂直刷新事件完成，再显示帧的内容。
6. void glfwPollEvents(void)：告诉GLFW检查所有等待处理的事件和消息，包括操作系统和窗口系统中应当处理的消息。如果有消息正在等待，它会先处理这些消息再返回；否则该函数会立即返回。
7. void glfwWaitEvents(void)：等待一个或多个事件传递到应用程序，并且处理它们再返回。对应的调用线程在事件到达之前会保持睡眠状态。

**处理用户输入**：主要是对键盘和鼠标的用户输入进行处理。常见接口如下：

1. GLFWkeyfun glfwSetKeyCallback(GLFWwindow* window, GLFWkeyfun cbfun)：设置一个新的键盘消息回调函数cbfun给指定的窗口window。如果按下或者放开键盘按键，系统会调用这个函数。它的返回值是前一个回调函数的返回值，从而用来恢复之前的回调函数。
   其中键盘消息回调函数的声明如下所示：
   void ExampleGLFWkeyfun(GLFWwindow* window, int key, int scancode, int action, int mods)：
   window就是接受到键盘消息的窗口句柄。
   key是按下或者松开的键盘按键。
   scancode是一个系统平台相关的键位扫描码信息。
   action可以是GLFW_PRESS（按下键），GLFW_RELEASE（松开键），GLFW_REPEAT（连续输入模式）中的一个。
   mods对应着辅助键的设置，例如shift和ctrl是否同时被按下。
2. int glfwGetKey(GLFWwindow* window, int key)：返回指定窗口window中指定按键key的状态，可以是GLFW_PRESS（按下键），GLFW_RELEASE（松开键），GLFW_REPEAT（连续输入模式）中的一个。
3. GLFWcursorposfun glfwSetCursorPosCallback(GLFWwindow* window, GLFWcursorposfun cbfun)：设置一个新的鼠标光标位置回调函数cbfun给指定窗口window。每当鼠标光标位置发生变化的时候，这个回调函数就会被触发。它的返回值是前一个回调函数的返回值，从而用来恢复之前的回调函数。
   其中鼠标光标位置回调函数的声明如下所示：
   void GLFWcursorposfun(GLFWwindow* window, double x, double y)：
   window就是接受到鼠标光标消息的窗口句柄。
   x和y就是鼠标光标相对于窗口左上角的新位置。
4. GLFWwindowsizefun glfwSetWindowSizeCallback(GLFWwindow* window, GLFWwindowsizefun cbfun)：设置一个新的鼠标按键回调函数cbfun给指定窗口window。当用户按下或者松开鼠标按键时，这个回调函数将会被触发。它的返回值是前一个回调函数的返回值，从而用来恢复之前的回调函数。
   其中鼠标按键回调函数的声明如下所示：
   void GLFWmousebuttonfun(GLFWwindow* window, int button, int action, int mods)：
   window就是接受到鼠标按键消息的窗口句柄。
   button就是当前的鼠标键。其中button可以是GLFW_MOUSE_BUTTON_1到GLFW_MOUSE_BUTTON_8中的一个值。
   action就是可以是GLFW_PRESS（按下键），GLFW_RELEASE（松开键），GLFW_REPEAT（连续输入模式）中的一个。
   mods对应着辅助键的设置，例如shift和ctrl是否同时被按下。
5. int glfwGetMouseButton(GLFWwindow* window, int button)：返回指定窗口window中指定鼠标键button的状态。
6. GLFWscrollfun glfwSetScrollCallback(GLFWwindow* window, GLFWscrollfun cbfun)：设置一个新的鼠标滚轮回调函数cbfun给指定窗口window。当用户滚动鼠标滚轮时，这个回调函数将会被触发。它的返回值是前一个回调函数的返回值，从而用来恢复之前的回调函数。
   其中鼠标滚轮回调函数的声明如下所示：
   void GLFWscrollfun(GLFWwindow* window, double xoffset, double yoffset)：
   window就是接受到鼠标滚轮消息的窗口句柄。
   xoffset和yoffset对应滚轮在x和y两个方向的运动。

**控制窗口属性**：可以在创建窗口时进行指定，也可以在程序中进行指定。常用接口如下：

1. void glfwWindowHint(int hint, int value)：设置窗口提示参数。设置以后就会影响之后创建的所有窗口。
   hint表示GLFW内部定义的状态。
   value表示状态值。
2. void glfwDefaultWindowHints(void)：恢复所有提示参数到默认值。建议在每次设置窗口提示参数之前都调用一次这个函数，这样才能保证提示参数设置值不发生混乱。
3. void glfwSetWindowSize(GLFWwindow* window, int width, int height)：设置窗口的尺寸大小。
   window表示操作的窗口句柄。
   width和height表示窗口的宽高大小。
4. void glfwGetWindowSize(GLFWwindow* window, int* width, int* height)：获取窗口当前的尺寸大小。
   window表示操作的窗口句柄。
   width和height表示保存窗口宽高大小的地址。
5. GLFWwindowsizefun glfwSetWindowSizeCallback(GLFWwindow* window, GLFWwindowsizefun cbfun)：设置一个新的窗口大小回调函数cbfun给指定窗口window。当窗口大小发生变化时，这个回调函数将会被触发。它的返回值是前一个回调函数的返回值，从而用来恢复之前的回调函数。
   其中窗口大小回调函数的声明如下所示：
   void GLFWwindowsizefun(GLFWwindow* window, int width, int height)：
   window表示操作的窗口句柄。
   width和height表示窗口的宽高大小。
6. void glfwSetWindowPos(GLFWwindow* window, int xpos, int ypos)：设置窗口的坐标位置。
   window表示操作的窗口句柄。
   xpos和ypos表示窗口的横纵坐标。
7. void glfwGetWindowPos(GLFWwindow* window, int* xpos, int* ypos)：获取窗口当前位置。
   window表示操作的窗口句柄。
   xpos和ypos表示保存窗口横纵坐标的地址。
8. GLFWwindowposfun glfwSetWindowPosCallback(GLFWwindow* window, GLFWwindowposfun cbfun)：设置一个新的窗口坐标回调函数cbfun给指定窗口window。当窗口位置发生变化时，这个回调函数将会被触发。它的返回值是前一个回调函数的返回值，从而用来恢复之前的回调函数。
   其中窗口坐标回调函数的声明如下所示：
   void GLFWwindowposfun(GLFWwindow* window, int xpos, int ypos)：
   window表示操作的窗口句柄。
   xpos和ypos表示窗口的横纵坐标。
9. void glfwGetFramebufferSize(GLFWwindow* window, int* width, int* height)：获取窗口帧缓存尺寸大小。
   window表示操作的窗口句柄。
   width和height表示保存窗口帧缓存宽高大小的地址。
10. GLFWframebuffersizefun glfwSetFramebufferSizeCallback(GLFWwindow* window, GLFWframebuffersizefun cbfun)：设置一个新的窗口帧缓存大小回调函数cbfun给指定窗口window。当窗口帧缓存大小发生变化时，这个回调函数将会被触发。它的返回值是前一个回调函数的返回值，从而用来恢复之前的回调函数。
    其中窗口帧缓存大小回调函数的声明如下所示：
    void GLFWframebuffersizefun(GLFWwindow* window, int width, int height)：
    window表示操作的窗口句柄。
    width和height表示窗口帧缓存的宽高大小。
11. void glfwSetWindowUserPointer(GLFWwindow* window, void* pointer)：设置窗口关联的用户数据指针。这里GLFW仅做存储，不做任何的特殊处理和应用。
    window表示操作的窗口句柄。
    pointer表示用户数据指针。
12. void* glfwGetWindowUserPointer(GLFWwindow* window)：获取窗口关联的用户数据指针。
    window表示操作的窗口句柄。

**清理和关闭程序**：通常用在退出GLFW时进行的操作。常用接口如下：
1.void glfwDestroyWindow(GLFWwindow* window)：销毁窗口对象以及关联的OpenGL环境。
window表示操作的窗口句柄。

2.void glfwTerminate(void)：关闭glfw库本身。