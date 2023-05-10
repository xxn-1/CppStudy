## 概述

Vulkan公开一个或多个设备，每个设备都公开一个或者多个队列，这些队列可以彼此异步处理工作。设备支持的队列集被划分为多个族。每个系列都支持一种或多种类型的功能，并且可以包含具有类似特征的多个队列。单个队列族中的队列被认为是相互兼容的，并且为队列族生成的工作可以在该族中的任何队列上执行。本规范定义了队列可能支持的以下类型的功能：图形、计算、视频解码、视频编码、传输和稀疏内存管理。

### 执行类型

Vulkan为设备的执行引擎提供了一个接口，这些执行引擎的命令在执行时间之前被记录到命令缓冲区内，然后提交到队列中执行，一旦提交到队列中，命令缓冲区将在没有进一步应用程序干预的情况下完成执行。一旦提交队列操作后，队列提交命令会将控制权返回应用程序。这些队列间没有隐式的排序，所有可以按任意顺序执行不同队列上的操作，若要显示排序，**需要使用信号量和栅栏**。(创建来自`vkQueue*`)

### 函数调用

* **创建、实例化相关函数类型遵循定义：**Vulkan中创建、实例化相关的函数参数一般遵循如下原则定义:  使用有关creation info 的结构体指针提供自定义信息 使用自定义分配器回调的指针 使用保存新对象句柄的指针将对象创建在这里。例子：

  `VkResult result = vkCreateInstance(&createInfo, nullptr, &instance); `

  第二个参数

  ```c++
  typedef struct VkAllocationCallbacks {
  	void* pUserData;
  	PFN_vkAllocationFunction pfnAllocation;
  	PFN_vkReallocationFunction pfnReallocation;
  	PFN_vkFreeFunction pfnFree;
  	PFN_vkInternalAllocationNotification pfnInternalAllocation;
  	PFN_vkInternalFreeNotification pfnInternalFree;
  } VkAllocationCallbacks;
  
  ```

  

### 对象类型

Vulkan中的设备、队列和其他实体都由Vulkan对象表示。

**API级别中**，所有对象都由句柄引用，有两类句柄：

* 可调度(分派)句柄：指向不透明类型的指针，该指针可以作为拦截API命令的一部分使用，因此每个API命令都将一个可分派类型作为第一个参数。**可分派类型的每个对象在其生存期内必须就有唯一的句柄值**
* 不可调度(不可分派)句柄：是一个**64位**整数类型，**含义依赖于实现。**从`VkDevice`创建或分派的所有对象，即以`VkDevice`作为第一个参数都是该设备的私有对象，不得在其他设备上使用。

对象分别由`vkCreate*`和`vkAllocation`命令创建或分配。一旦创建“结构”就不可更改，使用`vkDestory*`和`vkFree*`销毁。

当下列对象类型被传递到`Vulkan命令`而不再被用于创建的对象进一步访问时，它们将被使用，**它们不能在传递到任何API命令期间被销毁：**

* `VkShaderModule`
* `VkPipelineCache`
* `VkValidationCacheEXT`

---



当使用以下Vulkan对象的任何命令缓冲区处于挂起状态时，不得销毁该对象：

* `VkEvent`
* `VkQueryPool`
* `VkBuffer`
* `VkBufferView`
* `VkImage`
* `VkImageView`
* `VkPipeline`
* `VkSampler`
* `VkSamplerYcbcrConversion`
* `VkDescriptorPool`
* `VkFramebuffer`
* `VkCommandPool`
* `VkDeviceMemory`
* `VkDescriptorSet`
* `VkIndirectCommandsLayoutNV`
* `VkAccelerationStructureNV`
* `VkAccelerationStructureKHR`
* `VkVideoSessionKHR`
* `VkVideoSessionParameterKHR`

---



当任何队列正在执行使用以下对象的命令时，不得销毁该对象：

* `VkFence`
* `VkSemaphone`
* `VkCommandBuffer`
* `VkCommandPool`

---

对象销毁顺序一般而言是无限制的，**除非两者存在父子关系**，那么要注意必须先销毁子对象再销毁父对象(**除非明确定义销毁父对象时连带自动销毁其子对象**)

---

以下对象有特殊的销毁规则

* `VkQueue`：该对象无法显式销毁，只有用来检索它们的`VkDevice`对象被销毁时，他们会被隐式销毁
* 销毁**池类**对象，那麽对应用它分配的所有对象将被自动销毁。
* `VkPhysicalDevice`：无法被显示销毁，当用来检索它们的`VkInstance`对象被销毁后，其被显式销毁
* `VkInstance`：通过它检索到的所有`VkPhysicalDevice`对象处于空闲，且`VkPhysicalDevice`中被创建的所有`VkDevice`对象被销毁后，就可以销毁`VkInstance`对象
* `VkDevice`：当通过它检索到的所有的`VkQueue`对象都处于空闲，并且队列所创建的所有对象已经被销毁后，可以销毁`VkDevice`对象，其中所创建的对象类型包括：
  * `VkFence`
  * `VkSemaphore`
  * `VkEvent`
  * `VkBuffer`
  * `VkBufferView`
  * `VkImage`
  * `VkImageView`
  * `VkShaderModule`
  * `VkPipelineCache`
  * `VkPipeline`
  * `VkPipelineLayout`
  * `VkSampler`
  * `VkSamplerYcbcrConversion`
  * `VkDescriptorSetLayout`
  * `VkDescriptorPool`
  * `VkFramebuffer`
  * `VkRenderPass`
  * `VkCommandPool`
  * `VkCommandBuffer`
  * `VkDeviceMemory`
  * `VkValidationCacheEXT`
  * `VkAccelerationStructorNV`
  * `VkAccelerationStructorKHR`
  * `VkVideoSessionKHR`
  * `VkVideoSessionParameterKHR`

---

从`VkDevice`创建的对象句柄范围仅作用于该逻辑设备，不在范围内的对象称为外部对象，要将外部对象引入该`VkDevice`作用域，必须从**源作用域**中的对象到处外部句柄，然后将其导入目标作用域。

#### 语法规定

Vulkan使用C99描述函数。

基本类型使用C的类型作为基本类型，**除了bool类型，因为C没有一个足够可移植的内置布尔值类型。**

---

Vulkan常使用一些类型：

*  `VkBool32`： ` typedef uint32_t VkBool32;`作为bool类型，使用以下两个常量值作为bool值

   * `#define VK_TRUE 1U`

   * `#define VK_FALSE 0U`

*  `VkDeviceSize`： ` Vulkan使用：typedef uint64_t VkDeviceSize`作为**表示设备内存大小和偏移值**。

*  `VkDeviceAddress`：表示设备缓冲区地址值，真实类型为`uint64_t`



### 线程行为

Vulkan所有命令都支持从多个线程并发调用，**但是命令中使用的某些参数或参数的组件被定义为外部同步**。这表示必须使用互斥机制通过锁来调用同步这些参数。

对于不可变类型对象是不需要进行同步的。

一些需要外部同步的场景：

* 命令可以接受用户分配的列表，列表内容是外部同步的参数，由此必须保证命令中最多一个线程使用列表中的给定元素
* 当`commandBuffer`参数需要外部同步时，意味着缓冲区的`commandPool`也需要外部同步



### 有效调用

**句柄的有效使用**

当在规范中显式调用时，可以使用保留值`VK_NULL_HANDLER`代替有效的不可调用句柄，使用`NULL`代替可调度句柄，任何成功创建对象的命令都不能返回这些值，将这些值传递给`vkDestory*||vkFree*`是有效的，他们会自动忽略这些值

---



**char的有效使用：**

在规范中显式调用，可以为`NULL`

---



**枚举类型的有效使用：**通过switch处理枚举值时推荐添加`default`，枚举值有效使用符合以下条件的为有效

* 枚举数被定义为枚举类型的一部分
* 枚举数不是后缀为`_MAX_ENUM`，这个数的存在只是确保C枚举类型的大小为32位，不能被应用程序使用
* 如果枚举值被用在将`VkInstance`作为第一个参数的函数，其满足以下条件之一即可：
  * 枚举值是由支持的核心版本添加的如：`vkEnumerateInstanceVersion`，且`VkApplicationInfo::apiVersion`值大于或等于添加他的版本
  * 由第一个支持该实例的实力扩展添加的
* 如果枚举值被用在将`VkPhysicalDevice`作为第一个参数的函数，其满足以下条件之一即可：
  * 它是由该设备支持的和新版本添加
  * 为实例启用的实力扩展添加
  * 由该设备支持的设备扩展添加
* 如果枚举值用于具有其他可调度对象作为第一个参数的函数，并满足以下条件之一
  * 有设备支持的核心版本添加
  * 由为设备启用的设备扩展添加

---



**标志的有效使用**

标志类型：`VkFlags|VkFlags64`。只有低位31位可用作标志位

其中针对单个位标志的位类型定义，在类型替换为：`VkXXXBitsXXX`

---

**结构的有效使用**

任何包含`sType`成员的结构都必须具有`sType`值，该值是与结构类型匹配的有效`VkStructureType`

结构体指针中的`pNext`成员引起的`pNext`结构链在运行时必须由以下任一方面定义：

* 支持的核心版本
* 支持的扩展
* 在设备扩展添加物理设备级功能的情况下支持的设备扩展每种类型的扩展结构

为了方便需要迭代结构指针链的实现，VulkanAPI提供了两个基本结构供其函数使用，分别对通用输入和输出进行操作：

![image-20230507144931819](https://github.com/xxn-1/image/blob/main/img/202305071449885.png)

![image-20230507144945405](https://github.com/xxn-1/image/blob/main/img/202305071449433.png)

---

**扩展的有效使用**

* 除非`vkEnumerateInstanceExtensionProperties`确定的实例支持该扩展，并且该扩展在`VkInstanceCreateInfo`中启用，否则不得使用实例扩展添加到API的实例级功能或行为。
* 除非`vkEnumerateInstanceExtensionProperties`确定的实例支持该扩展，并且该扩展在`VkInstanceCreateInfo`中启用，否则不得使用实例扩展添加到API的物理设备级功能或行为。
* 除非满足扩展物理设备核心功能中描述的条件，否则不得使用设备扩展添加到API的物理设备级功能或行为。
* 不得使用从`VkDevice`或`VkDevice`的子对象调度的设备扩展添加的设备级功能，除非`vkEnumerateDeviceExtensionProperties`确定设备支持该扩展，并且在`VkDeviceCreateInfo`中启用了该扩展。

### 返回码

当命令需要传达成功或状态信息时，返回成功完成代码(这些代码都大于0)，错误代码都是负值。返回代码通过`VkResult`类型定义，这是一个枚举类型

```
成功代码
VK_SUCCESS命令已成功完成
VK_NOT_READY栅栏或查询尚未完成
VK_TIMEOUT等待操作尚未在指定的 时间
VK_EVENT_SET发出事件信号
VK_EVENT_RESET事件未发出信号
VK_INCOMPLETE返回数组对于结果来说太小
VK_SUBOPTIMAL_KHR交换链不再与表面匹配 完全是属性，但仍可用于呈现到表面 成功。
VK_THREAD_IDLE_KHR延迟的操作未完成，但存在 在此调用时，此线程当前没有工作要做。
VK_THREAD_DONE_KHR延迟的操作未完成，但存在 没有剩余的工作分配给其他线程。
VK_OPERATION_DEFERRED_KHR请求推迟操作，并且 至少有一些工作被推迟了。
VK_OPERATION_NOT_DEFERRED_KHR请求延迟操作 并且没有推迟任何操作。
VK_PIPELINE_COMPILE_REQUIRED请求的管道创建将 需要编译，但应用程序请求编译为 不执行。

错误代码
VK_ERROR_OUT_OF_HOST_MEMORY主机内存分配失败。
VK_ERROR_OUT_OF_DEVICE_MEMORY设备内存分配具有 失败。
VK_ERROR_INITIALIZATION_FAILED对象的初始化可以 由于特定于实现的原因而未完成。
VK_ERROR_DEVICE_LOST逻辑或物理设备已丢失。 查看丢失的设备
VK_ERROR_MEMORY_MAP_FAILED内存对象的映射失败。
VK_ERROR_LAYER_NOT_PRESENT请求的图层不存在或 无法加载。
VK_ERROR_EXTENSION_NOT_PRESENT请求的扩展不是 支持。
VK_ERROR_FEATURE_NOT_PRESENT不支持请求的功能。
VK_ERROR_INCOMPATIBLE_DRIVER请求的 Vulkan 版本是 驱动程序不支持或与 特定于实现的原因。
VK_ERROR_TOO_MANY_OBJECTS该类型的对象过多 已创建。
VK_ERROR_FORMAT_NOT_SUPPORTED不支持请求的格式 在此设备上。
VK_ERROR_FRAGMENTED_POOL池分配由于以下原因而失败 池内存碎片。 仅当未尝试分配主机或设备时，才必须返回此信息 已创建内存以适应新的分配。 这应该优先返回 ，但前提是实现 确定池分配失败是由于碎片造成的。
VK_ERROR_OUT_OF_POOL_MEMORY 超出池内存
VK_ERROR_SURFACE_LOST_KHR曲面不再可用。
VK_ERROR_NATIVE_WINDOW_IN_USE_KHR请求的窗口已存在 被 Vulkan 或其他 API 以阻止其 再次使用。
VK_ERROR_OUT_OF_DATE_KHR表面发生了变化，使得 它不再与交换链兼容，并进一步呈现 使用交换链的请求将失败。 应用程序必须查询新的图面属性并重新创建其 交换链，如果他们希望继续向表面展示。
VK_ERROR_INCOMPATIBLE_DISPLAY_KHR交换链使用的显示 不使用相同的可呈现图像布局，或者在 阻止共享图像的方式。
VK_ERROR_INVALID_SHADER_NV一个或多个着色器编译失败 或链接。 如果启用，更多详细信息将报告回应用程序。VK_EXT_debug_report
VK_ERROR_OUT_OF_POOL_MEMORY池内存分配失败。 仅当未尝试分配主机或设备时，才必须返回此信息 已创建内存以适应新的分配。 如果失败肯定是由于池碎片造成的，则应改为返回。VK_ERROR_FRAGMENTED_POOL
VK_ERROR_INVALID_EXTERNAL_HANDLE外部句柄无效 指定类型的句柄。
VK_ERROR_FRAGMENTATION描述符池创建失败，原因 到碎片化。
VK_ERROR_INVALID_DEVICE_ADDRESS_EXT缓冲区创建失败 因为请求的地址不可用。
VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS缓冲区创建 或内存分配 失败，因为请求的地址不可用。 着色器组句柄分配失败，因为请求的着色器 组句柄信息不再有效。
VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT对 创建时出现故障的交换链 没有独占全屏访问权限。 这可能是由于依赖于实现的原因而发生的，在 应用程序的控件。VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT
VK_ERROR_COMPRESSION_EXHAUSTED_EXT映像创建失败 因为压缩所需的内部资源已耗尽。 仅当请求固定速率压缩时，才必须返回此值。
VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR请求的 VkImageUsageFlags 不受支持。
VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR请求的 不支持视频图片布局。
VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR视频配置文件 不支持通过 VkVideoProfileInfoKHR：： 指定的操作。videoCodecOperation
VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR设置参数格式 在请求的 VkVideoProfileInfoKHR 链中不受支持。
VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR特定于编解码器 请求的 VkVideoProfileInfoKHR 链中的参数不是 支持。
VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR指定的视频 不支持标准标头版本。
VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR指定的视频标准 参数不符合 的句法或语义要求 使用的视频压缩标准或从参数派生的值 根据使用的视频压缩标准定义的规则做 不遵守视频压缩标准或 实现。
VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT提供的二进制着色器 代码与此设备不兼容。
VK_ERROR_UNKNOWN发生未知错误;要么 应用程序提供了无效的输入，或者实现失败 发生。
如果命令返回运行时错误，除非另有指定，否则任何输出 参数将具有未定义的内容，除非输出 参数是一个结构，带有和字段，那些 字段将不被修改。 任何链接的结构也将具有未定义的内容， 除此之外，并且将不被修改。sTypepNextpNextsTypepNext
VK_ERROR_OUT_OF_*_MEMORY错误不会修改任何当前存在的 火神对象。 已成功创建的对象仍可由 应用程序。
```



### 数值表示和计算

实现通常执行**浮点计算**。

大多数浮点计算是在`SPIR-V`着色器模块中进行的，在该着色器中计算性能受到`SPIR-V`指令的精度和操作部分所定义的约束，在着色器执行之外的Vulkan操作中执行的**浮点计算**通常要满足以下范围和精度要求：

* 对于任何非无穷和非Nan，`x*0=0*x=0`|`1*x=x*1=x`|`0^0=1`
* 当一个值被转化为定义的浮点表示时，位于两个可表示的有限值之间的有限值被四舍五入为一个或另一个，其大小大于任何可表示的有限值可以四舍五入到最接近的可表示有限值，如四舍五入到适当的有符号无穷大或者最接近的可表示有限值。

#### 定点和浮点数据转换

**首先将无符号或者有符号标准化，标准化需要根据该数值类型的位数决定。**

无符号规范化定点正数表示范围[0,1]内的数字，从无符号规范化定点数*c*转化为浮点数*f*
$$
f=\frac{c}{2^b-1}
$$
有符号规范化定点正数表示范围[-1,1]内的数字，从有符号规范化定点数*c*转化为浮点数*f*


$$
f=max(\frac{c}{2^{b-1}-1},-1.0)
$$

> <br>
>
> ​		对于有符号中有一个值需要特殊处理，如：位数为8中的-128超出可表示范围，在该值返回到着色器之前必须将其限定为-1.0对结果进行钳制。
>
> 

---

**浮点数到无符号归一化定点数的转换**：首先将浮点数钳制到范围[0,1]，然后计算`c = convertFloatToUint(f*(2^b-1),b)`其中b表示无符号数的位数，

**浮点数到有符号归一化定点数的转换**：首先将浮点数钳制到范围[-1,1]，然后计算`c = convertFloatToint(f*(2^(b-1)-1),b)`其中b表示有符号数的位数，



### 常见对象类型

#### Offsets

用于描述对象或帧缓冲区内的像素位置，如二维图像的(x,y)，三维图形的(x,y,z)

* `VkOffset2D`
* `VkOffset3D`

#### 范围

用于描述图像或帧缓冲区内像素的矩形区域的大小，如二维图像：宽、高

* `VkExtent2D`
* `VkExtent3D`

#### 矩形

`VkRect2D`其中定义了`VkOffset2D`和`VkExtent2D`属性来定义矩形

#### SType

`VkStructureType`是一个枚举类型，其中定义类每种内置类型的SType值，每种类型对应的该值为：该类型去掉前导`Vk`，在每个大写字母前加`_`，将整个结果字符串大写，并在其前加`Vk_structure_TYPE_`。再将该类型对象传递给API前要先设置SType值



## 初始化

一个` VkInstance `可以有多个` VkPhysicalDevice`。

一个` VkPhysicalDevice` (对应物理设备)可以有多个 `VkDevice`(对应逻辑设备)。

### 类型查询网站

[Index of /vulkan/specs/1.3-extensions/man/html (khronos.org)](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/)

一些扩展名和返回码都可以在其中查询

### 初始化配置

在使用Vulkan前，应用程序必须通过加载Vulkan命令并创建`	VkInstance`对象初始化它，一个进程只能有一个`VkInstance`。

`Instance instance;`最终需要调用`vkCreateInstance`创建，并通过`vkDestroyInstance(instance,nullptr)`销毁

可以使用`VkApplicationInfo`为驱动程序提供有用的信息

在创建`VkInstance`时可以为其提供足够的信息，可以告知驱动程序我们需要使用什么全局扩展：

* `vKcreateInstance`第二个参数为一个内存分配器

* `vkDestroyInstance(instance,nullptr)`第二个参数是内存分配器，如果创建时使用了分配器，那么删除的时候也需要提供一个与之兼容的 `VkAllocationCallbacks`。第一个输入参数 可以是NULL，或者一个合法的` VkInstance`句柄

* `vkEnumerateInstanceExtensionProperties`枚举**实例**扩展

* `vkEnumerateDeviceExtensionProperties()`枚举**物理设备**扩展

* `vkEnumerateInstanceVersion`获取Vulkan版本，为NULL时版本为1.0，否则为其返回值。**正确用法**：

  ```c++
      count_ version;
      vkEnumerateInstanceVersion(&version);
      std::cout << "Supported Vulkan Version is "
                << VK_VERSION_MAJOR(version) << '.'
                << VK_VERSION_MINOR(version) << '.'
                << VK_VERSION_PATCH(version) << '\n';
  ```

  

* `VK_MAKE_VERSION(1, 3, 0);`创建版本1.3.0应用版本和引擎版本

* `VK_MAKE_API_VERSION(0, 1,3, 0)`API版本

* `VkDebugReportCallbackCreateInfoEXT` 或`VkDebugUtilsMessengerCreateInfoEXT` 结构链接到给予 `vkCreateInstance 函数中的`的` VkInstanceCreateInfo` 结构的 pNext 元素。可以捕获创建或销毁实例时发生的事件，其中会**传入一个回调函数**。

```C++

typedef struct VkInstanceCreateInfo {
	//当前结构体的类型，必须是 VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO
	VkStructureType sType;
	//NULL，或者扩展该结构体的另外一个结构体，必须是NULL
	const void* pNext; 如果需要捕获创建或销毁Instances时发生的事件，可以在VkInstanceCreateInfo的pNext填加VkDebugReportCallbackCreateInfoEXT或VkDebugUtilsMessengerCreateInfoEXT
	//reserved for future，必须是0
	VkInstanceCreateFlags flags;
	//NULL，或者一个包含应用程序信息的结构体，用于告诉instance应用程序信息。
	//如果使用NULL，或者使用一个0版本的apiVersion，则相当于使用了VK_MAKE_API_VERSION(0,1,0,0) 的apiVersion
	const VkApplicationInfo* pApplicationInfo;
	//启用的global layer的数量
	uint32_t enabledLayerCount;
	//启用的global layer的名字，第一个是最靠近应用程序的layer，最后一个是最靠近驱动的layer
	const char* const* ppEnabledLayerNames;
	//启用的global extension的数量
	uint32_t enabledExtensionCount;
	//启用的extension的名字，这里包含了所有的extension
	const char* const* ppEnabledExtensionNames;
} VkInstanceCreateInfo;

typedef struct VkApplicationInfo {
	//当前结构体的类型，必须是 VK_STRUCTURE_TYPE_APPLICATION_INFO
	VkStructureType sType;
	//NULL，或者扩展该结构体的另外一个结构体，必须是NULL
	const void* pNext;
	//NULL，或者应用程序名字
	const char* pApplicationName;
	//应用程序版本
	uint32_t applicationVersion;
	//NULL，或者创建该应用程序的引擎名字
	const char* pEngineName;
	//引擎版本，设置当前所有物理设备最高支持的版本，若物理设备实际版本小于该逻辑版本，启用物理设备版本，否则启用逻辑版本
	uint32_t engineVersion;
	//应用程序所支持的Vulkan的最高版本。当使用vulkan1.0的时候，这里如果写超过1.0的数字，会出现 
	//VK_ERROR_INCOMPATIBLE_DRIVER 的错误，因此，在创建之前，需要通过 vkGetInstanceProcAddr 获取 
	//vkEnumerateInstanceVersion 的信息，如果 vkEnumerateInstanceVersion 为 NULL，则 为vulkan 1.0，否则 
	//vkEnumerateInstanceVersion 即为 Vulkan版本。而vulkan1.1及以上版本永远不会出现这个错误。需要注意的是：validation layer
	//会根据这个版本，来判断，如果使用了高版本的特性，则会报validation error。比如，如果instance支持1.1，3个physical devices
	//支持1.0、1.1、1.2，如果应用程序将该值设置为1.2。则应用程序中，instance和所有的physical devices都可以使用1.0，
	//instance和1.1和1.2的physical devices可以使用1.1，1.2的physical device可以使用1.2。如果应用程序设置为1.1，则应
	//用程序即使在支持1.2的physical deevice上，也无法使用1.2。这个版本影响了layer的使用。除非是0，否则必须大于等于VK_API_VERSION_1_0
	uint32_t apiVersion;
} VkApplicationInfo;

```



```c++
VkApplicationInfo appInfo = {}; 
appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
appInfo.pNext = nullptr; 
appInfo.pApplicationName = "Hello Triangle"; 
appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0); 
appInfo.pEngineName = "No Engine"; 
appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0); 
appInfo.apiVersion = VK_API_VERSION_1_0; 
// VkInstanceCreateInfo
VkInstanceCreateInfo createInfo = {}; 
createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO; 
createInfo.pApplicationInfo = &appInfo; 
unsigned int glfwExtensionCount = 0; 
const char** glfwExtensions;  
glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount); createInfo.enabledExtensionCount = glfwExtensionCount;  // 需要扩展提供平台信息，这里使用Glfw提供扩展信息
createInfo.ppEnabledExtensionNames = glfwExtensions;  // 需要扩展提供平台信息，这里使用Glfw提供扩展信息
createInfo.enabledLayerCount = 0; 

////////////////////////创建实例
VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);  // 真正的创建
```

在创建instance之前检索支持的扩展列表，通过vkEnumerateInstanceExtensionProperties函数。它指向一个变量，该变量存储扩展数量和一个VkExtensionProperties数组来存储扩展的详细信息。它也接受一个可选择的参数，允许我们通过特定的validation layers过滤扩展

```c++
uint32_t extensionCount = 0; 
vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
std::vector<VkExtensionProperties> extensions(extensionCount); 
vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data()); 
std::cout << "available extensions:" << std::endl;  
for (const auto& extension : extensions) {     
    std::cout << "\t" << extension.extensionName << std::endl; 
} 

// 上述代码 等价于
 uint32_t glfwExtensionCount = 0;
const char **glfwExtensions;
glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

```

##### 命令获取

Vulkan已经内置了各种类型的命令指针，**格式为**：`PFN_命令名`可以强制转化返回的指针为该类型

所有Vulkan命令的函数指针可以通过以下获取，**返回的指针必须强制转化为要查询的实际的指针函数**：

* `vkGetInstanceProcAddr`实例层面的函数指针**对这个实例所拥有的所有对象都有效**
* `vkGetDeviceProcAddr`设备层面的函数指针，**只能在查询这个函数指针的逻辑设备上使用该指针。**

```c++
vkGetInstanceProcAddr(instance,pName);
1. instance是一个VkInstance，是函数指针将与之兼容的实例
2. pName是要获取的命令的名称    
返回的指针类型为：PFN_vkVoidFunction，在使用前必须强制转化为要查询的命令的类型 
// 返回的函数指针只能用VkInstance创建的instance或者instance的子对象(作为第一个参数)来调用（如：VkDevice、VkQueue、VkCommandBuffer、VkInstance、VkPhysicalDevice)
注意：其中instance支持设置为NULL    
    
vkGetDeviceProcAddr(vkDevice,pName); // 返回的函数指针可能指向调用不同vkDevice对象或其子对象的不同实际实现的代码。获取特定于设备的函数指针  
```

例子：

该类型是扩展，可以在Instance实例化期间，可以捕获创建或销毁实例时发生的事件，其中会**传入一个回调函数**。

```c++
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger)
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr)
    {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    }
    else
    {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks *pAllocator)
{
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr)
    {
        func(instance, debugMessenger, pAllocator);
    }
}
void setupDebugMessenger()
{
    if (!enableValidationLayers)
        return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    populateDebugMessengerCreateInfo(createInfo);

    if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to set up debug messenger!");
    }
}
void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo)
{
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
}
{
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
  	populateDebugMessengerCreateInfo(debugCreateInfo);
    createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *)&debugCreateInfo;
}
```

##### Vulkan自定义函数

但凡要定义可以被Vulkan使用的函数，如回调函数，必须要使用一些宏：

* `VKAPI_ATTR`
* `VKAPI_CALL`

```c++
VKAPI_ATTR 返回类型 VKAPI_CALL 函数名() {
	...
}
```

##### Instance附加扩展

扩展可以分为两类：实例扩展和设备扩展。实例扩展用于在某个平台上整体增强Vulkan系统。这种扩展或者通过设备无关的层提供，或者只是每个设备都暴露出来并提升进实例的扩展。设备扩展用于扩展系统里一个或者多个设备的能力，但是这种能力没必要每个设备都具备。

通过向`VkInstanceCreateInfo`类型的`pNext`添加，**要开启对应的扩展时，必须在VkInstanceCreateInfo的扩展列表的扩展名中插入对应的支持扩展名来开启对应的扩展。**扩展名的结构为：`VK_EXT_XXX_XXX_EXTENSION_NAME`，扩展名可以在类型查询网站找到，在类型定义上有一条注释，将其全部大写，后添加后缀`_EXTENSION_NAME`。**一般首先枚举可用扩展，获得扩展列表后向其中push我们想要添加的新扩展名即可**

* `VkDirectDriverLoadingListLUNARG `可以添加其它驱动程序，允许应用程序自己发布驱动，不应该使用任何需要安装的驱动（如硬件驱动）。
* `VkDebugReportCallbackCreateInfoEXT` 或`VkDebugUtilsMessengerCreateInfoEXT` 结构链接到给予 `vkCreateInstance 函数中的`的` VkInstanceCreateInfo` 结构的 pNext 元素。可以捕获创建或销毁实例时发生的事件，其中会**传入一个回调函数**。
* `VkValidationFlagsEXT`可以选择希望实例希望将要禁用验证检查
* `VkValidationFeaturesEXT`指定要启用或要禁用的验证特性

### 选择物理设备

空句柄：`VK_NULL_HANDLE`

通过VkInstance初始化Vulkan后，我们需要在系统中查找并选择一个支持我们所需功能的显卡。实际上，我们可以选择任意数量的显卡并同时使用他们



**获得显卡列表**：

评估合适的设备我们可以通过遍历一些细节来完成。基本的设备属性像name, type以及`Vulkan`版本都可以通过**`vkGetPhysicalDeviceProperties`**来遍历得到。

`VkPhysicalDevice physicalDevice = VK_NULL_HANDLE; `会在`VkInstance`销毁时自动销毁，**这就是一个GPU**

* `vkGetPhysicalDeviceProperties`查询物理设备等基本的设备属性像name, type以及`Vulkan`版本

  ```c++
  typedef struct VkPhysicalDeviceProperties {
  	//当前device支持的Vulkan版本，需要注意的是，这里的apiVersion可能会和 vkEnumerateInstanceVersion 获取到的不同，可能高或者低。
  	//这种情况，应用程序不能使用超过given object相关的vulkan 版本的特性。
  	//vkEnumerateInstanceVersion 返回的 pApiVersion ，为instance及其children相关的版本，
  	//而非 VkPhysicalDevice 以及其 children。 
  	//VkPhysicalDeviceProperties::apiVersion 为 VkPhysicalDevice 及其 children 相关的版本。
  	uint32_t apiVersion;
  	//vendor公司设定的驱动版本，driverVersion 的编码格式为 implementation-defined，可能与apiVersion的编码格式不同。
  	//应用程序需要根据vendor提供的信息，来从driverVersion 获取版本信息
  	uint32_t driverVersion;
  	//当前physical device对应的vendor公司的标识
  	uint32_t vendorID;
  	//当前physical device的标识符
  	uint32_t deviceID;
  	//当前device的类型 
  	VkPhysicalDeviceType deviceType;
  	//一个包含 VK_MAX_PHYSICAL_DEVICE_NAME_SIZE 元素的数组，包含了physical device的name
  	char deviceName[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE];
  	//一个包含 VK_UUID_SIZE 元素的数组，表示当前设备中的一个唯一标识符 
  	uint8_t pipelineCacheUUID[VK_UUID_SIZE];
  	//当前physical device的限制
  	VkPhysicalDeviceLimits limits; 
  	//当前physical device的various sparse 相关属性
  	VkPhysicalDeviceSparseProperties sparseProperties; 
  } VkPhysicalDeviceProperties;
  
  ////////////////// 设备类型
  typedef enum VkPhysicalDeviceType {
  	VK_PHYSICAL_DEVICE_TYPE_OTHER = 0, //设备与任何其它可用类型不匹配
  	VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU = 1, //当前设备通常嵌入主机或与主机紧密连接
  	VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU = 2, //当前设备通常是通过互连连接到主机的独立处理器
  	VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU = 3, //当前device为虚拟环境中的虚拟节点
  	VK_PHYSICAL_DEVICE_TYPE_CPU = 4, //当前device运行在与主机相同的处理器上
  } VkPhysicalDeviceType;
  //vendorID 的枚举值，这个枚举随时可能更新，只有vk.xml和vulkan_core.h才包含了所有reserved Khronos vendor IDs。
  //只有在Khronos注册的vendor IDs才会返回名字，根据 implementation 返回的PCI vendor IDs可以通过PCI-SIG database 进行查询。
  typedef enum VkVendorId {
  	VK_VENDOR_ID_VIV = 0x10001,
  	VK_VENDOR_ID_VSI = 0x10002,
  	VK_VENDOR_ID_KAZAN = 0x10003,
  	VK_VENDOR_ID_CODEPLAY = 0x10004,
  	VK_VENDOR_ID_MESA = 0x10005,
  	VK_VENDOR_ID_POCL = 0x10006,
  } VkVendorId;
  
  ```

* `VkGetPhysicalDeviceProperties2`用于获取通过` vkEnumeratePhysicalDevices` 得到的物理设备常规属性

* `vkGetPhysicalDeviceFeatures`查询对纹理压缩，64位浮点数和多视图渲染(VR非常有用)等可选功能的支持:

* `VkPhysicalDeviceFeatures`物理设备特性类，**可以判断设备具体的支持某种特性否**

* `vkEnumeratePhysicalDevices`枚举所有物理设备

* `vkGetInstanceProcAddr`可以从设备扩展获得物理设备级命令的函数指针，**为不同的VkPhysicalDevice**对象调用不同的实际实现。

```c++
VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
uint32_t deviceCount = 0;
vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
if (deviceCount == 0) {    
    throw std::runtime_error("failed to find GPUs with Vulkan support!"); }
bool isDeviceSuitable(VkPhysicalDevice device) {
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
           deviceFeatures.geometryShader;
}

std::vector<VkPhysicalDevice> devices(deviceCount); 
vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());  // 分配所有显卡句柄给Instance
for (const auto& device : devices) {
    if (isDeviceSuitable(device)) {
        physicalDevice = device;
        break;
    }
}

if (physicalDevice == VK_NULL_HANDLE) {
    throw std::runtime_error("failed to find a suitable GPU!");
}


```

为了避免纯粹的单一的判断一个设备是否合适，尤其是当你发现多个设备都合适的条件下，你也可以给每一个设备做权值，选择最高的一个。这样，可以通过给予更高权值获取定制化的图形设备，但如果没有一个可用的设备，可以回滚到集成图形设备。你可以按照如下方式实现:

```c++
#include <map>

...

void pickPhysicalDevice() {
    ...

    // Use an ordered map to automatically sort candidates by increasing score
    std::multimap<int, VkPhysicalDevice> candidates;

    for (const auto& device : devices) {
        int score = rateDeviceSuitability(device);
        candidates.insert(std::make_pair(score, device));
    }

    // Check if the best candidate is suitable at all
    if (candidates.rbegin()->first > 0) {
        physicalDevice = candidates.rbegin()->second;
    } else {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

int rateDeviceSuitability(VkPhysicalDevice device) {
    ...

    int score = 0;

    // Discrete GPUs have a significant performance advantage
    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
        score += 1000;
    }

    // Maximum possible size of textures affects graphics quality
    score += deviceProperties.limits.maxImageDimension2D;

    // Application can't function without geometry shaders
    if (!deviceFeatures.geometryShader) {
        return 0;
    }

    return score;
}

```

#### 适合的队列族

我们需要对我们的命令操作选择适合的队列族来提交我们的操作命令。

* `vkGetPhysicalDeviceQueueFamilyProperties`获取某个物理设备GPU的可用队列族特性

  ```c++
  typedef struct VkQueueFamilyProperties {
  	//用于表示 VkQueueFlagBits , 是用于该queue family中queue的功能
  	VkQueueFlags queueFlags;
  	//为该queue family中 queue的数量。每个 queue family 至少包含一个 queue
  	uint32_t queueCount; 
  	//是通过 vkCmdWriteTimestamp 这个API输入的 timestamps 中有意义的位。该数值的有效位是36-64位（其他为应该为0），或者为0（代表不支持timestamps）
  	uint32_t timestampValidBits; 
  	//是该 queue family的queue中支持的image transfer 操作中的最小粒度，针对压缩纹理其单位为压缩的纹理block，否则为纹素。指定了队列传输图像时支持多少单位
  	//可能的值为：（0，0，0）：必须以整个mip level为单位进行transfer。这种情况下，有如下限制：1.VkOffset3D的参数x,y,z必须为0，2.VkExtent3D的参数width、height、depth必须匹配图片的w、h、d。
  	//或者(Ax, Ay, Az)，其中三个值均为POT。这种情况下，有如下限制：1.VkOffset3D的参数x,y,z必须为(Ax, Ay, Az)的整数倍，2.VkExtent3D的参数width、height、depth必须是(Ax, Ay, Az)的整数倍，或者x+width、y+height、z+depth等于图片尺寸。3.如果图片为压缩格式，则需要通过压缩texel block尺寸来放大粒度。因此，如果该值为8x8x8，则对于该队列上的所有图像复制操作，像素矩形副本的位置和大小必须在8-pixel边界上对齐。
  	VkExtent3D minImageTransferGranularity;  
  } VkQueueFamilyProperties;
  
  typedef enum VkQueueFlagBits {
  	VK_QUEUE_GRAPHICS_BIT = 0x00000001, //说明这个queue支持graphics 操作 ，如绘制点、线、三角形
  	VK_QUEUE_COMPUTE_BIT = 0x00000002, //说明这个queue支持compute 操作 ，如发送计算着色器
  	VK_QUEUE_TRANSFER_BIT = 0x00000004, //说明这个queue支持 transfer操作 ，如复制缓冲区和图像内容
  	VK_QUEUE_SPARSE_BINDING_BIT = 0x00000008, //说明这个queue支持 sparse memory management操作(内存绑定)，如：更新稀疏资源。如果开启了sparse resource feature，那么至少一个queue family支持这个bit // Provided by VK_VERSION_1_1 
  	VK_QUEUE_PROTECTED_BIT = 0x00000010, //说明这个queue支持 VK_DEVICE_QUEUE_CREATE_PROTECTED_BIT。如果physical device支持potectedMemory特性，则至少一个queue family支持这个bit
  } VkQueueFlagBits;
  
  ```

* `vkGetPhysicalDeviceQueueFamilyProperties2`获取物理设备支持的队列族

* `vkEnumerateDeviceExtensionProperties`在创建设备之前，**查询物理设备支持的扩展**

* `vkEnumeratePhysicalDeviceGroups`用于获取支持的device groups。如果若干个physical devices属于同一个的device group，则可以将一个device与它们同时关联。一个device group的意思是若干个physical devices，互相可以访问内存，以及录制一个single command buffer，可以执行在所有的physical devices上。Device group是通过 `vkEnumeratePhysicalDeviceGroups` 查询，对应的device是通过device group中physical device的子集，将其传入 `VkDeviceGroupDeviceCreateInfo` 来创建。同一个device group中的两个physical devices，必须支持相同的extension、feature和属性，通过 `vkGetPhysicalDevice*` 获取的属性也基本相同（允许因为连接了不同的display、compositor等导致一些特定的query不同，这里就不列出来了）。

  ```c++
  typedef struct VkPhysicalDeviceGroupProperties {
  	//当前结构体的类型，必须是 VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GROUP_PROPERTIES
  	VkStructureType sType; 
  	//NULL，或者扩展该结构体的另外一个结构体，必须是NULL 
  	void* pNext; 
  	//当前device group中physical devices的数量 
  	uint32_t physicalDeviceCount; 
  	//一个包含 VK_MAX_DEVICE_GROUP_SIZE 个 VkPhysicalDevice 元素的数组，其中包含了当前device group中所有的physical devices，所以，前 physicalDeviceCount 个元素是合法的。 
  	VkPhysicalDevice physicalDevices[VK_MAX_DEVICE_GROUP_SIZE]; 
  	//指定根据group创建的device，所分配的device memory的方式，通过 VkMemoryAllocateFlagsInfo 的 deviceMask 设置。
  	//如果为 VK_FALSE ，那么所有的device memory都可以被 group中的所有physical devices共享。
  	//如果 physicalDeviceCount 为 1，那么 subsetAllocation 必须是 VK_FALSE 。
  	VkBool32 subsetAllocation;  
  } VkPhysicalDeviceGroupProperties;
  
  ```

  

队列族结构体：`VkQueueFamilyProperties`包括支持的操作类型和基于当前队列簇可以创建的有效队列数，判断支持某个队列操作类型：`xxx.queueFlags & VK_QUEUE_...`

#### 物理设备内存

Vulkan里的设备内存是指，设备能够访问到并且用作纹理和其他数据的后备存储器的内存。内存可以分为几类，每一类都有一套属性，例如缓存标志位以及主机和设备之间的一致性行为。每种类型的内存都由设备的某个堆（可能会有多个堆）进行支持。

* `vkGetPhysicalDeviceMemoryProperties`得到物理设备支持的内存类型

  ```c++
  typedef struct VkPhysicalDeviceMemoryProperties {
      uint32_t        memoryTypeCount;
      VkMemoryType    memoryTypes[VK_MAX_MEMORY_TYPES]; 
      uint32_t        memoryHeapCount;
      VkMemoryHeap    memoryHeaps[VK_MAX_MEMORY_HEAPS];
  } VkPhysicalDeviceMemoryProperties;
  内存类型数量包含在字段memoryTypeCount里。可能报告的内存类型的最大数量是VK_MAX_MEMORY_TYPES定义的值，这个宏定义为32。数组memoryTypes包含memoryTypeCount个结构体VkMemoryType对象，每个对象都描述了一种内存类型。VkMemoryType的定义如下。
  typedef struct VkMemoryType {
      VkMemoryPropertyFlags    propertyFlags;
      uint32_t                 heapIndex;
  } VkMemoryType;
  
  // 这是个简单的结构体，只包含了一套标志位以及内存类型的堆栈索引。每种内存类型都指定了从哪个堆上使用空间，这由结构体VkMemoryType里的字段heapIndex来标识。这个字段是数组memoryHeaps （在调用vkGetPhysicalDeviceMemoryProperties()返回的结构体VkPhysicalDeviceMemoryProperties里面）的索引。数组memoryHeaps里面的每一个元素描述了设备的一个内存堆。字段flags描述了内存的类型，并由VkMemoryPropertyFlagBits类型的标志位组合而成。标志位的含义如下。
  
  VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT意味着内存对于设备来说是本地的（也就是说，物理上是和设备连接的）。如果没有设置这个标志位，可以认为该内存对于主机来说是本地的。
  VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT意味着以这种方式分配的内存可以被主机映射以及读写。如果没有设置这个标志位，那么内存不能被主机直接访问，只能由设备使用。
  VK_MEMORY_PROPERTY_HOST_COHERENT_BIT意味着当这种内存同时被主机和设备访问时，这两个客户之间的访问保持一致。如果没有设置这个标志位，设备或者主机不能看到对方执行的写操作，直到显式地刷新缓存。
  VK_MEMORY_PROPERTY_HOST_CACHED_BIT意味着这种内存里的数据在主机里面进行缓存。对这种内存的读取操作比不设置这个标志位通常要快。然而，设备的访问延迟稍微高一些，尤其当内存也保持一致时。
  VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT意味着这种内存分配类型不一定立即使用关联的堆的空间，驱动可能延迟分配物理内存，直到内存对象用来支持某个资源。
  ```

* 

#### 扩展物理设备核心功能

当物理设备版本大于或等于添加了新功能的 Vulkan 版本时，可以使用新的核心物理设备级功能。物理设备支持的 Vulkan 版本可以通过调用，物理设备支持的 Vulkan 版本可以通过调用 `vkGetPhysicalDeviceProperties` 获得。

### 逻辑设备

逻辑设备独立于其他逻辑设备的状态和资源。

Device将被用于：1.创建queue，2.创建和跟踪各种各样的synchronization constructs，3.分配、释放、管理内存，4.创建和破坏 command buffer和command buffer pool，5.创建、破环和管理graphics state（pipeline、resource descriptor等）

* `VkResultDevice`

* `VkDeviceCreateInfo`

  ```c++
  typedef struct VkDeviceCreateInfo {
      VkStructureType                    sType;
      const void*                        pNext;
      VkDeviceCreateFlags                flags;
      uint32_t                           queueCreateInfoCount;
      	//为 pQueueCreateInfos 数组的尺寸，必须大于0
      const VkDeviceQueueCreateInfo*     pQueueCreateInfos;
      	//一个指向 queueCreateInfoCount 个 VkDeviceQueueCreateInfo 数组的指针，创建logical device的时候同步创建这些queues
  
      uint32_t                           enabledLayerCount;
      const char* const*                 ppEnabledLayerNames;
      	//当前device开启的extension数量
  
      uint32_t                           enabledExtensionCount;
      // 扩展名必须是通过vkEnumerateDeviceExtensionProperties获取的其中之一
      const char* const*                 ppEnabledExtensionNames;
      	//NULL，或者一个指针指向 VkPhysicalDeviceFeatures 结构体，其中用bool值指出需要开启的feature。
      const VkPhysicalDeviceFeatures*    pEnabledFeatures;
  } VkDeviceCreateInfo;
  ```

  ```
  针对VkDeviceCreateInfo的pNext
  pNext 必须是 NULL，或者VkDeviceGroupDeviceCreateInfo,VkPhysicalDevice16BitStorageFeatures,VkPhysicalDevice8BitStorageFeatures,VkPhysicalDeviceBufferDeviceAddressFeatures,VkPhysicalDeviceDescriptorIndexingFeatures,VkPhysicalDeviceFeatures2,VkPhysicalDeviceHostQueryResetFeatures,VkPhysicalDeviceImagelessFramebufferFeatures,VkPhysicalDeviceMultiviewFeatures,VkPhysicalDeviceProtectedMemoryFeatures,VkPhysicalDeviceSamplerYcbcrConversionFeatures,VkPhysicalDeviceScalarBlockLayoutFeatures,VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures,VkPhysicalDeviceShaderAtomicInt64Features,VkPhysicalDeviceShaderDrawParametersFeatures,VkPhysicalDeviceShaderFloat16Int8Features,VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures,VkPhysicalDeviceTimelineSemaphoreFeatures,VkPhysicalDeviceUniformBufferStandardLayoutFeatures,VkPhysicalDeviceVariablePointersFeatures,VkPhysicalDeviceVulkan11Features,VkPhysicalDeviceVulkan12Features, or VkPhysicalDeviceVulkanMemoryModelFeatures。
  
  如果 pNext 包含 VkPhysicalDeviceVulkan11Features ，那么它必须不能包含：
  VkPhysicalDevice16BitStorageFeatures,VkPhysicalDeviceMultiviewFeatures, VkPhysicalDeviceVariablePointersFeatures,VkPhysicalDeviceProtectedMemoryFeatures,VkPhysicalDeviceSamplerYcbcrConversionFeatures, or VkPhysicalDeviceShaderDrawParametersFeatures。
  
  如果 pNext 包含 VkPhysicalDeviceVulkan12Features ，那么它必须不能包含 ：
  VkPhysicalDevice8BitStorageFeatures,VkPhysicalDeviceShaderAtomicInt64Features,VkPhysicalDeviceShaderFloat16Int8Features,VkPhysicalDeviceDescriptorIndexingFeatures,VkPhysicalDeviceScalarBlockLayoutFeatures,VkPhysicalDeviceImagelessFramebufferFeatures,VkPhysicalDeviceUniformBufferStandardLayoutFeatures,VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures,VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures,VkPhysicalDeviceHostQueryResetFeatures,VkPhysicalDeviceTimelineSemaphoreFeatures,VkPhysicalDeviceBufferDeviceAddressFeatures, or VkPhysicalDeviceVulkanMemoryModelFeatures。
  ```

  

* `VkDeviceQueueCreateInfo`

  ```c++
  typedef struct VkDeviceQueueCreateInfo {
      VkStructureType             sType;
      const void*                 pNext;
      VkDeviceQueueCreateFlags    flags;
      uint32_t                    queueFamilyIndex; // 字段queueFamilyIndex指定了你希望创建的队列所属的族，这是个索引值，与调用vkGetPhysicalDeviceQueueFamilyProperties()返回的队列族的数组对应
      uint32_t                    queueCount; // 为了在这个族里创建队列，将queueCount设置为你希望创建的队列个数。当然，设备在你选择的族中支持的队列数量必须不小于这个值。
      const float*                pQueuePriorities; // 指向浮点数数组，表示提交给每个队列的工作的相对优先级，取值范围：0.0~1.0
  } VkDeviceQueueCreateInfo;
  typedef enum VkDeviceQueueCreateFlagBits {
  	// Provided by VK_VERSION_1_1 
  	//指定 device queue 是一个 protected-capable 的queue
  	VK_DEVICE_QUEUE_CREATE_PROTECTED_BIT = 0x00000001, 
  } VkDeviceQueueCreateFlagBits;
  
  ```

* `VkDeviceGroupDeviceCreateInfo`要关联的一组物理设备

  ```c++
  typedef struct VkDeviceGroupDeviceCreateInfo {
  	//当前结构体的类型，必须是 VK_STRUCTURE_TYPE_DEVICE_GROUP_DEVICE_CREATE_INFO
  	VkStructureType sType; 
  	//NULL，或者扩展该结构体的另外一个结构体
  	const void* pNext; 
  	//pPhysicalDevices 数组的元素数量，如果这个数字不为0， vkCreateDevice 的 physicalDevice 参数必须是 pPhysicalDevices 中的一个元素
  	uint32_t physicalDeviceCount; 
  	//一个 physicalDeviceCount 个 physical device 的数组，其中的元素都属于同一个device group（从 vkEnumeratePhysicalDeviceGroups 获取）。
  	//是logical device关联的一个有序list，必须是一个device group的子集，可以与被get出来的时候的顺序不同。
  	//该顺序决定了每个physical device 的device index。
  	//一些命令和结构体用于若干个physical device会用到device index或者通过device index组成的device mask。数组中的每个元素必须独一无二。
  	const VkPhysicalDevice* pPhysicalDevices;
  } VkDeviceGroupDeviceCreateInfo;
  
  ```

  

* `vkDestroyDevice(device, nullptr); `删除逻辑设备，删除前要显式删除逻辑设备创建的对象。第二个参数对应创建时的内存分配器。为了确保device上没有活动的工作，可以使用 `vkDeviceWaitIdle` 来确保。在销毁 device之前，应用程序负责销毁/释放 device 通过`vkCreate*` 或者`vkAllocate*` 这些API 创建的Vulkan对象。

* `vkDeviceWaitIdle`在销毁设备之前，需要保证它没有正在执行来自应用程序的任何工作。为了达到这个目的，调用vkDeviceWaitIdle()

* `vkGetDeviceQueue(device, queue_index, 0, &queueHandle); `获取逻辑设备中某个queue的handle。第二个参数必须是创建logical device的时候，包含在 `VkDeviceQueueCreateInfo` 中的queue family index。第三个参数为队列数量必须小于创建时对应队列信息的数量。

* `vkGetDeviceQueue2`：`vkGetDeviceQueue` 只能获取 `VkDeviceQueueCreateInfo` 的flag为0的queue，如果想获取flag不为0的queue，需要用 `vkGetDeviceQueue2`。第二个参数：

  ```c++
  typedef struct VkDeviceQueueInfo2 {
  	//当前结构体的类型，必须是 VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2
  	VkStructureType sType; 
  	//NULL，或者扩展该结构体的另外一个结构体，必须是NULL
  	const void* pNext; 
  	//是创建该queue时候的 VkDeviceQueueCreateFlags flag，必须是 VkDeviceQueueCreateFlagBits 的合法组合。
  	//如果在创建device的时候，没有创建对应flag的queue，则返回NULL
  	VkDeviceQueueCreateFlags flags; 
  	//queue 所在的 queue family 的 index，必须是创建logical device的时候，包含在 VkDeviceQueueCreateInfo 中的queue family index
  	uint32_t queueFamilyIndex; 
  	//queue 在 queue family 中的 index，必须小于创建logical device的时候，包含在 VkDeviceQueueCreateInfo 中的 queueCount
  	uint32_t queueIndex; 
  } VkDeviceQueueInfo2;
  
  ```

  



>
>
>`vkGetPhysicalDeviceQueueFamilyProperties` 获取到的 pQueueFamilyProperties 中的 index 都是独一无二的，这些index被用于创建 queue，与 `vkCreateDevice` 中的 `VkDeviceQueueCreateInfo` 中的 queueFamilyIndex 相对应。
>
>queue family index在很多地方会使用到，除了这里之外，还有，在创建 `VkCommandPool` 的时候，需要在 `VkCommandPoolCreateInfo` 中设置一个 queue family index。 这个Pool中的Command buffer 只能 submit到该 queue family 中的queue中。
>
>在创建`VkImage` 和 `VkBuffer`的时候，也需要通过 `VkImageCreateInfo` 和 `VkBufferCreateInfo` 指定 queue families，指定只有这些 queue familyies可以访问这些资源。
>
>当插入一个 `VkBufferMemoryBarrier` 或者 `VkImageMemoryBarrier` 的时候，需要设置一个source和一个desination queue family来指定，将buffer或者image的ownership从一个queue family转移到另外一个queue family。
>
>



#### 	关联多个物理设备

一个逻辑设备可以关联同属于一个设备组的多个物理设备，方法：在pNext中加入 `VkDeviceGroupDeviceCreateInfo` 结构体