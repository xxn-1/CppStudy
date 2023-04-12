---
QT Quick是Qml的一个类库
---

[TOC]

使用`qmlscene`可以测试QML应用

#### 基本语法

* `import 模块名 版本号 [as Qualifier]`Qualifier表示一个文档内部的命名空间，如果不给出该限定符，那麽导入的对象类型和js资源会导入全局命名空间。如：

  ```c
  import QtQuick 2.2 as Quick
  原本是
  Rectangle{
  
  }
  现在是：
  Quick.Rectangle{
  
  }
  // 也支持直接导入js文件
  ```
  
  **也可以直接导入目录，需要包含qml文档：**
  
  * 本地目录
  
  * 远程目录：该目录必须定义包含一个`qmldir`文件，**没有后缀该文件。**该文件中罗列了目录中的文件列表。
  
    ~~~
    qmldir格式：
    1. 对象类型声明指定对象的类型名
    类型名 文件名
    2. 内部对象类型声明
    internal 类型名 文件名
    3. JavaScript资源声明，将资源通过给定的标识符暴露
    标识符 文件名
    ~~~
  
    

---

QML文档就是一个QML对象树，对象由他们的类型指定，以大写字母开头，后面跟随一对大括号。括号中包含了对象的特性定义，比如这个对象的属性值或者其子对象。

```qml
Rectangle{
	width:100;
	height:100;
	color:"yellow";
	
}
```

##### 注释

* `//`单行
* `/* */`多行

##### 表达式

属性的值可为表达式：`width:3*2`、`width:parent.width == 3?1:2`

##### 布局

* `anchors`

##### 调试输出

可以输出在qml中

* `console.log("ddd"+msg)`

* `console.debug(msg)`

如：

```
Rectangle{
	MouseArea{
		
	}
}
```

##### 数据类型

**每个基本类型都有自身的属性改变信号**

qml默认支持的数据类型

* `int`
* `bool`
* `real`
* `double`
* `string`
* `url`
* `list`
* `var`通用类型属性
* `enumration`枚举值

QtQuick提供的基本类型

* `color`
* `font`
* `matrix4x4`4行4列矩阵
* `quaternion`一个4元数，包含一个标量以及x,y,z属性
* `vector2d`二维向量
* `vector3d`
* `vector4d`
* `date`
* `point`点值，包含x和y
* `size`包含width和height
* `rect`包含x,y,width,height

##### 对象特性

* ###### `id`：定义id使得其可以被引用，必须使用小写字母或者下划线开头

* ###### 属性特性：**定义方法**

  * C++通过注册一个类的`Q_PROPERTY`宏，再注册到QML系统

  * `属性名:{js代码块}`

  * 可以在QML文档中使用语法自定义一个属性：

    `[default][readonly]property <数据类型/对象类型><propertyName>`**声明一个属性，会隐式的为其创建一个值改变信号，和一个信号处理器**。**属性可以在JS和QML中使用。另外，若定义默认属性，一个对象最多允许存在一个默认属性，默认属性类似于C++默认值一般。**可以初始化，`peoperty int height:50`。代码中使用`=`赋值，初始化使用`:`赋值。

    **特别的列表属性的处理方法：**

    ```c
    语法格式：
    列表声明：
    property list<类型> 属性名
    属性名:[
        类型如Rectangle{id:n1},
        Rectangle{id:n2}
    ]
    // 定义的属性可以作为值被使用
    ```

  * **别名：**

    `[default]property alias 已存在的属性名:别名`如：`property alias 别名 : window.color`将window.color定义了别名

* ###### 信号特性：可以在C++中定义，也可以在QML中直接定义，语法：

  `signal 信号名[(类型 参数名,...)]`定义信号后会自动在对象定义中添加信号处理器。如信号名为：`activated`

  使用信号时直接调用信号就等于发射：不再需要`emit`关键字。**可在同目录其他qml文件接收，其他文件定义槽函数接收`onActivated:`**	

  ---

  其他方法：

  ```c
  id:name
  Component.onCompleted:{
      name.信号名.connect(函数名/或者其他信号名)
  }
  function func(参数){
      // 处理
  }
  
  // 再发射信号就会调用该函数处理
  ```

  

* ###### 信号处理器

* ###### 方法特性：

  `function func`。

  ~~~c
  Rectangle{
      id:name
      function func(newx){
          name.x=newx
      }
      onClicked:name.func(2)
  }
  // 可以通过id引用
  ~~~

  

* ###### 附加属性

  允许对象访问与个别对象相关的属性和信号。

  如一个列表ListView，`ListView.isCurrentItem`判断对象是不是当前选中

* ###### 附加信号处理器

  如：`Component.onCompleted:{}`就是一个附加信号处理器，在组件创建完成时进行。

  **注意：附加属性和附加信号处理器都必须在这些子对象的父对象中使用**

##### JS

可以在qml中直接进行JS操作，**两者可以混合进行，或直接调用JS的函数**。

###### 属性绑定

`height:parent.height`当父对象height改变，子对象height自动改变

```c
height:{
	if(parent.height>100)return parent.height/2;
	else return parent.height;
}
// 上面的绑定都是允许的
height:Math.max(parent.width,parent.height)
// 注意区别于 =。=号进行的操作是赋值，不是动态的绑定，仅仅改变一次值。同时只有使用了 = 号原有的绑定就会消除。
如果想改变值时同时不消除绑定，方法例子：
Keys.onSpacePressed:height=Qt.binding(function(){return this.width*3})
```

###### 外部导入

较复杂的程序逻辑，JS内容会放置在单独的文件中，可以使用

`import "js文件路径" as ...`，**对于一个组件中导入js文件，其每个实例都会加载一个该js资源的实例**

<font color="red">若是想要让所有实例共享一个js资源，需要在js文件最上方代码之前添加：`.pragma library`</font>

---

js文件导入js文件：`.import "...js" as...`

js文件导入QML模块：`.import 模块 版本号 as ...`

###### 在启动时运行js代码

在对象的`Component.onCompleted:{}`中使用js

###### js动态创建qml对象

有两种方法：

1. `Qt.createComponent(Item parent,object properties)`

   ```c
   var component;
   var sprite;
   Component.onCompleted:{
       createObject();
   }
   function createObject(){
       component = Qt.createComponent("组件qml相对路径");
       if(component.status==Component.Ready)finishCreation();
   }
   function finishCreation(){
       if(component.status==Component.Ready){
           sprite = component.createObject(父对象id,{"x":100,"y":200});
           if(sprite==null)console.log("Error");
       }else if(component.status==Component.Error){
           console.log("Error"+component.errorString());
       }
   }
   ```

   

2. `Qt.createQmlObject()`从字符串创建，适合连同QML本身都是动态创建的

   ```c
   var newObject = Qt.createQmlObject('import QtQuick 2.2;Rectangle{...}',父对象,新对象文件相关的文件路径)
   ```

   **动态删除对象：**只能删除动态创建的对象。

   通过：`对象.destody()`删除

   ```c
   // myComponent.qml
   Rectangle{
       ...
       id:name;
       ... name.destory();//删除
   }
   ```

   

##### 对象类型

**自定义方式：**

* 通过创建qml文件类定义
* 通过C++定义QML类型后在QML引擎中注册

##### 自定义组件

方法1：需要创建一个`qml`文件，**文件必须大写开始，文件名即是组件名**，**同时属于一个组件的所有根对象的属性都可以在外部访问修改。**

方法2：在一个QML文档内部使用`component`定义：

```c
Item{
    Component{
        id:redSquare // 自定义组件名
        Rectangle{ // 自定义使用的组件类型
            
        }
    }
    Loader{sourceComponent:自定义组件名;...}; // 加载一个自定义组件
}
```

方法3：自定义



##### 国际化

对所有需要在界面上需要显式的字符串使用`qsTr()`

##### qml对象基本结构顺序

```c
id:
属性声明:
信号声明:
JS函数:
对象属性:
子对象:
状态:
states:[
	State{...}, // 状态1
	State{
		name:"name"
		when:触发mouseArea.pressed // 触发方式1，被动定义
            // 其他方式，一般在槽函数中id.state = "name"主动改变
		PropertyChanges{ // 改变属性
			target:目标对象id
			color:"red"
		}
	}
]	
状态切换
transitions:[
    ...Transitions{}
    Transitions{
        from "状态name"
        to:"状态name"
        PropertyAnimation{ // 动画效果
            
        }
    }
]
```

#### QML模块

##### 自定义

一个模块在一个类型命名空间中提供了版本类型和JS资源，能被导入使用

**模块定义通过`qmldir`，需要将该模块的所有QML文档、JS资源和C++插件都放到同一个目录中，然后在该目录中编写一个`qmldir`定义文件**



QT Quick所有可视项目都继承自`Item`。

一般包含属性：

* `opacity`
* `x`
* `y`
* `width`
* `height`
* `visible`
* `enabled`是否接收鼠标和键盘事件
* `z`设置堆叠，大z会放在小z值的对象上面
* `childAt(x,y)`返回点(x,y)处的对象
* `mapFromItem(item,x,y)`将返回item坐标系统中x,y处对象
* `maptoItem(item,x,y)`从当前对象x,y处映射
* `anchors`
* `LayoutMirroring.enabled:true`开启镜像，`.childrenInherit:true`原本对象被锚定在父对象左侧，镜像后会显示在右侧

##### Rectangle

一个矩形区域

* `color`
* `gradient`指定一个渐变填充
* `border.color`|`border.width`
* `radius`:设置边框角弧度

##### Text

* `text`设置文本，支持富文本
* `font`字体，其有很多子属性
* `color`
* `wrapMode`设置换行，枚举值：`Text.xxx`
* `elide`设置宽度的文本并且只想在单行中显示，会使用`...`代替
* `clip`设置是否裁剪
* `horizontalAlignment`水平对齐
* `verticalAlignment`垂直对齐
* `style`设置文本样式
* `textFormat`决定了text属性的显示方式，是否支持富文本
* `onLinkActivated`在文本超链接被调用时启动

##### TextInput

单行可编辑的文本，**更好的选择是使用Qt Quick Controls中的`TextField`项目**

* `validator`验证器
* `echoMode`可以设置如何显示，如密码，不显示，等等
* `selectByMouse`设置文本可选
* `mouseSelectionMode`选中时模式，单词还是单个字符
* `selectedTextcolor`选中时文字颜色
* `selectedcolor`选中时颜色
* `onAccepted`回车时调用

##### TextEdit

推荐使用TextArea代替。

##### Repeater

#### 布局管理

##### 基于定位器

使用定位器，其内的子项目不需要再手动设置x,y以及锚。

定位器包含：Column、Row、Grid、Flow，**每个定位器中都附加一个`Positioner`类型对象包含索引信息，如`id.Positioner.index`**

1. `Column`：列
   * `spacing`设置各组件间距
2. `Row`：行
   * `spacing`间距
3. `Grid`：
   * `rows`行数
   * `columns`列数
   * `spacing`设置子项目间间距
   * `horizontalItemAlignment`水平对齐方式
   * `verticalItemAlignment`垂直对齐方式
4. `Flow`：从前向后，向流一样放置，通过换行排列
   * `flow`可以设置从左到右流，或从上到下流
   * `spacing`间距

**四个定位器添加删除子元素时，都可以使用一个过渡使这些操作具有动画效果，4个定位器都有`add`、`move`、`populate(在定位器第一次创建时，只会应用一次)`，都需要分配一个`Transition`对象**

```c
move:Transition{
	... // 动画效果
}
```

##### Repeater

用来创建大量相似的项目，一个Repeater包含一个模型`model`属性和`delegate`属性。

* `model`:重复次数

  在model下面定义对象，会重复model次

##### 基于锚的布局

如希望自身的左端锚到`id1`对象右端：

`anchors.left:id1.right`

若希望对角分布，可以使用多个锚语句：

`anchors.left:id1.right;anchors.top:id1.bottom`

* `anchors.xxxMargin:`边距
* `anchors.xxxOffset`偏移量

**运行时改变锚：**通过`AnchorChanges`，需要再状态`State`中进行。**该类型不能修改边距，需要时可以通过PropertyChanges改变**

```c
states:State{
	AnchorChanges{
		target:xxx
		anchors.top = ...
		//
	}
    PropertyChanges{
        target:xxx
        anchors.topMargin:10
    }
}
```

##### 布局管理器

布局管理器不仅进行布局，而且也会改变项目的大小，更适合于需要改变用户界面大小的应用。为了将布局管理器与窗口关联，需要添加：`anchors.fill:parent`

需要导入`QtQuick.Layouts`包括：`RowLayout`、`ColumnLayout`、`GridLayout`。

**主要特色：**

* 项目的对齐方式可以使用`Layout.alignment`指定
* 可变大小项目可以使用`Layout.fillWidth`和`Layout.fillHeight`指定
* 大小约束可以通过：`Layout.minimumWidth`、`Layout.preferredWidth`、`Layout.maximumWidth`另外还有类似属性指定
* 网格中坐标可以通过`Layout.row`和`Layout.column`指定
* 自动网格坐标同时使用了`flow`、`rows`、`column`
* 网格行和列的跨度可以通过`Layout.rowSpan`和`Layout.columnSpan`指定

---

**要想自动调整需要进行：**

```c
指定最小宽高
指定最佳宽高
将对应的fillWidth、fillHeight设置为true
```

#### 事件管理

##### MouseArea

默认情况下，该类只报告鼠标单击而不报告鼠标光标的位置改变，可以通过设置`hoverEnabled`属性为true来更改。这样设置后`onPositionChanged()`、`onEntered`、`onExited`等处理函数才能使用。

多个鼠标区域重叠的情况下，可以设置`propagateComposedEvents`为true，同时设置`mouse.accepted=false`才可以使事件继续传播

`mouse`对象中可以通过x,y获取坐标，通过`button`获取按键（左键、中建、右键等等），通过`modifiers`获取按下的键盘修饰符如：`Shift`、`Alt`、`Ctrl`等

**拖放：**

* 简单的拖放：

  ```c
  MouseArea{
      anchors.fill:parent
      drag.target:要拖放的对象id
      drag.axis:Drag.xxAxis // 拖动方向
      drag.minimumX // 水平方向最小拖动距离
          ...
  }
  ```

* 复杂的拖放：`DropArea`

  ```c
  // 自定义qml组件结构如下：
  item类型{
  	id:it
  	Drag.active:dragArea.drag.active // 激活
  	Drag.source:it // 拖放的源对象
      Drag.dragType:Drag.Aut
       Drag.supportedActions:Qt.CopyAction // 拷贝式
  	MouseArea{
  		id:dragArea
  		drag.target:parent // 关键
  		anchors.fill:parent
  	}
  //    Drag.mimeData:{
  //        "text/uri-list":it.source
  ////    } 拖动的实际内容
  }
  // 接收端
  DropArea{
      id:droparea
      anchors.fill:parent
      onDropped:
  }
  ```

  
