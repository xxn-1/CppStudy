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