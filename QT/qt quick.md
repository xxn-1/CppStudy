---
QT Quick是Qml的一个类库
---

[TOC]

使用`qmlscene`可以测试QML应用

#### 槽和信号

当声明一个信号后会自动生成一个on<SignalName>这个槽函数（这种是JavaScript代码）

```c
Component.onCompleted:{
 
    rectangleId.greet.connect(rectangleId.myGreeting)
}
// 方法2
signal greet(string message)
 
 
        onGreet: {
 
            console.log("onGreet: greet signal emited, parameter is : " + increment)
            increment += 50
        }
 
        MouseArea{
 
            anchors.fill: parent
            onClicked: {
 
                rectangleId.greet("Hello there")
            }
        }

————————————————


```



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

###### 读写文件

```js
            /* 如需要读取某个路径文件则可以这样写：file:///C:/Users/My/Demo.qml */
---
function readFile(url){
	var request = new XMLHttpRequest();
	request.open("GET",url,false);
	request.send(null);
	return request.responseText;
}
```



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

##### Qt

`Qt.函数()`定义了许多全局函数

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

**附加属性：**

* `KeyNavigation`导航，可以设置按下方向键后的跳转，如：`KeyNavigation.right:对象id`按下右方向会跳转到对象id
* `activeFocus`：bool值，返回其是否是焦点

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

##### TabBar

[(56条消息) QML_TabBar和ToolBar_qml tabbar_HX科技的博客-CSDN博客](https://blog.csdn.net/weixin_50183638/article/details/125261288)

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
  
  ----
  
  循环时有一个`modelData`可以调用当前model索引的值。

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

  

##### 键盘事件

**键盘事件会传递给当前具有`focus:true`的对象，当前文档树中只能有一个对象获得焦点**

```c
focus:true
Keys.onPreessed:{
	event.accepted = true // 表示该焦点接受该键盘事件，注意，只有接受后，事件的传播才会停止 
}
```

**焦点作用域：**为了解决导入组件是否请求了焦点这种未知情况下使用。

在自定义组件中，要把`FocusScope`放在组件外

```c
FocusScope{ // 不可见组件，因此要使用子对象真正的组件属性来绑定
    x:rectangle.x;
    y:rectangle.y;
    width:rectangle.width;
    height:rectangle.height;
    
    Rectangle{
        id:rectangle
        anchors.centerIn:parent
    }
}
```

##### 定时器

```c
Timer{
	interval:间隔ms
	repeat:true // 设置是否重复触发
	running:true // 开启
	onTriggered:{触发}
}
```

##### Loader动态加载组件

可以设置直到真正需要的时候才被创建，通过其item属性可以获得加载的对象。

```c
Loader{id:load}
// 
需要加载时：修改load.source="xxx.qml"就可以加载xxx组件。将source设置为空字符串，就可以释放并销毁组件。
```

**从加载的项目中发射的信号可以使用Connections接收**

```c
main.qml
---------------------------------------
import QtQuick 1.0
 
Item {
    property bool isFirst : false;
    width: 200
    height: 200
 
    Loader {
        id: pageLoader
        source: "Page1.qml"
    }
 
 
    Connections {
        target: pageLoader.item
        onMessage: console.log(msg);
    }
 
}
 
Page1.qml
----------------------------------------------
import QtQuick 1.0
 
Rectangle {
    id: myItem
    signal message(string msg)
    width: 100; height: 100
 
    MouseArea {
        anchors.fill: parent
        onClicked: myItem.message("clicked!");
    }
}
```

#### QT控件和对话框

放置在模块`Qt Quick Controls`和`Qt Quick Dialogs`

**ApplicationWindow类似QMainWindow，具有菜单栏、工具栏、状态栏，该类型包含一个`contentItem`属性，可以进行窗口大小的设置**

```c
ApplicationWindow{
	...
	Action{
		id:
		text:qsTr("显示文字") // 
		shortcut:"ctrl+q" // 快捷键
         iconSource:"image/xxx.png"
         onTriggered:Qt.quit()
	}
    Action{ // 支持使用"&"定义快捷键
        // 仅仅定义Action，Action可以使用在按钮中，或者MenuItem中，仅仅需要定义action:actionid即可。
    }
    // 菜单栏
    menuBar:MenuBar{ // 
        Menu{ // 在其title属性文字中添加--&快捷键
            // 一个菜单项
            MenuItem{
              // 菜单项中一个组件   
            }
            MenuItem{
                
            }
            MenuSeparator{} // 分割线
        }
        Menu{}
    }
    header: ToolBar{
        width:parent.width
        Row{
            anchors.fill:parent
            ToolButton{
                action:quitAction
                ToolTip:hovered
                ToolTip.text:
            }
            ToolSeparator{}
        }
    }
    
    StackView:作用，类似于一个页面很多子页面，每打开一个子页面将先前的子页面压入用于返回句柄
}

```

**注意：目前Action内取消了tooltip，我们需要在要使用的按钮中定义Tooltip类来使用**

##### 对话框

在`Window`组件中设置`Window.flags`为`Qt.Dialog`，实际要弹出对话框通过`id.show()`

`modality`模态属性，枚举值，包含在`Qt.`中

* `NonModal`非模态
* `WindowModal`窗口模特
* `ApplicationModal`应用程序模态

```c
// 有的情况下单击❌并不真的希望关闭，而是希望在后台运行
我们可以在ApplicationWindow对象的onClosing:{
    // 处理信号设置false就可实现
    close.accepted = false; 
}
```

##### 按钮类

* `Button`
* `CheckBox`
* `RadioButton`
* `Switch`
* `ToolButton`
* `DelayButton`
* `RoundButton`
* `TabButton`

```c
// 渐变
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15  // 导入QtGraphicalEffects才能正常使用LinearGradient

Button {
    id: btn
    width: 160
    height: 44
    property color lightColor: "#FF66B8FF"  // 起始颜色
    property color darkColor: "#FF338BFF"   // 终止颜色
    contentItem: Label {
        font.pixelSize: 14
        font.weight: Font.Black
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "#FFFFFF"
        text: "横向渐变色按钮"
    }
    background: Rectangle {
        anchors.fill: parent
        radius: 8
        layer.enabled: true
        layer.effect: LinearGradient {
            start: Qt.point(0, 0)
            end: Qt.point(width, 0)
            gradient: Gradient {
                GradientStop {
                    position: 0.0
                    color: btn.pressed ? btn.darkColor : btn.lightColor
                }
                GradientStop {
                    position: 1.0
                    color: btn.pressed || !btn.hovered ? btn.darkColor : btn.lightColor
                }
            }
        }
    }
}

```



##### 数据选择类

* `comboBox`：`model`属性中定义选择的数据模型。还可以使用`model:ListModel{}`其中定义
* `spinBox`

##### 文本类：

* `TextField`
* `TextArea`
* `label`

##### 导航类

* `ScrollView`
* `SplitView`对应`QSplitter`，在其中定义的各组件会被垂直或水平的分割。
* `StackView`

##### 等待

* `BusyIndicator`

#### 颜色

* `Qt`全局对象中定义了一系列有关取颜色的函数

---

**渐变：**

```c
gradient:Gradient{
	GradientStop
}
```

#### 图表

`import QtCharts`

在`ChartView`组件中画图

修改`main.cpp`中`QGuiApplication app(argc, argv);`为`QApplication app(argc, argv);`

#### 图片

使用`Imagebiao`

```c
Image{

	source:"..."
}
```

* `width`、`height`和`sourceSize.width`、`sourceSize.height`的区别，**前者仅在绘制时放缩，内存中保存的还是原始大小，后者直接设置内存中大小，可以节省资源，图片默认从宽高的中心来向四周平铺，可以设置**

  ```c
  horizontalAlignment:Image.AlignLeft
  verticalAlignment:Image.AlignTop
  // 从左上角向右下平铺
  ```

  

---

* `BorderImage`：利用图片创建边框。将图片分成九宫格，从上到下从左到右数字为1~9.

  ```
  当图片进行缩放时，源图片的各个区域使用下面的方式进行缩放或者平铺来创建要显示的边界图片：
  ●4个角(1、3、7、9区域)不进行缩放：
  ●区域2和8通过horizontalTileMode属性设置的模式进行缩放；
  ●区域4和6通过verticalTileMode属性设置的模式进行缩放；
  ●区域5结合horizontalTileMode和verticalTileMode属性设置的模式进行缩放。
  ```

  ---

* `AnimatedImage`：动态图片，可以用来播放一系列帧的图片动图，如`gif`文件

#### 缩放、旋转和平移变换

* 使用属性实现简单变换：

  * `scale`缩放，大于1放大，小于1缩小。负值为镜像效果
  * `rotation`旋转，

* 使用Transform实现高级变换。其包含三个具体的实现类

  * `Rotation`可以支持三维旋转
  * `Scale`可以支持单个方向缩放
  * `Translate`平移

  如：`transform:Rotation{}`

#### 状态

**不是Item派生来的组件，可以通过`StateGroup`来使用状态，默认状态为空字符：`""`**

向`states`设置多个状态，通过改变`state`指向的状态ID改变当前状态

状态中支持：

* `StateChangeScript`运行脚本
* `PropertyChanges`重写对象的已有的信号处理器
* `ParentChange`重定义其父对象
* `AnchorChanges`修改锚的值

搭配`transitions`属性设置过渡效果

```c
transitions:[
    Transition:{
        from:"状态名"
        to:"state1"
        动画类型{...;target:}   
    }
]
```



##### 状态改变时动画和过渡

类型：

* `PauseAnimation`：动画执行时暂停
* `ScriptAction`：动画过程中执行js脚本
* `PropertyAction`：动画中立刻修改一个属性的值，属性改变时不使用动画
* `SmoothedAnimation`平滑的过渡效果
* `SpringAnimation`：类似弹簧的动画
* `ParentAnimation`：在父项目改变时产生动画效果
* `PropertyAnimation`：属性改变时触发
* `AnchorAnimation`：在锚改变时产生动画
* `PauseAnimation`：暂停
* `PathAnimation`路径动画
* `RotationAnimation`
* `ColorAnimation`
* `Vector3dAnimation`
* `SequenceAnimation`
* `ParallelAnimation`

**动画的触发：**

1. 使用属性动画：针对属性值应用

   ```
   直接定义动画对象，通过内部的target和property:"属性名"搭配设置针对目标
   ```

   

2. 使用预定义的目标和属性：在某个属性上：`<Animation类型> on <属性>{定义动画属性}`

3. 作为一个`transition`对象

4. 作为一个信号触发器的对象：`onClicked:动画类型{}`

5. 使用默认的行为(Behavior)动画

   ```
   Behavior on 属性{
   动画{
   }
   }
   ```

   ---

###### **组动画：并行或顺序播放**

```
SequentialAnimation:顺序
ParallelAnimation:并行
SequentialAnimation{
	id:
	running:false
	动画类型{
	
	}
	动画类型{
	
	}
	...
}
```

###### 动画控制

* `start`开始
* `stop`停止，属性值只获得停止时的值
* `resume`恢复
* `pause`暂停
* `restart`重新开始
* `complete`完毕，属性获得结束的值

###### 缓和曲线

用来定义动画如何在开始值和结束值之间进行插值。

###### SpriteAnimation

```c
SpriteSequence{
    id:image;width:256;height:256
    anchors.horizontalCenter:parent.horizontalCenter
    interpolate:false;goalSprite:"
    Sprite(
    name:"still";source:"BearSheet.png"
    frameCount:1;framewidth:256;frameHeight:256
    frameDuration:100
    to:("still":1,"blink":0.1,"floating":0)
    Sprite(
    name:"blink":source:"BearSheet.png"
    frameCount:3:framex:256:frameY:1536
    frameWidth:256;frameHeight:256
    frameDuration:100
    to:{"sti11":1)
    }
    Sprite(
    name:"floating";source:"BearSheet.png"
    frameCount:9;framex:0;frameY:0
    frameWidth:256;frameHeight:256
    frameDuration:160
    to:("still":0,"flailing":1)
    Sprite(
    name:"flailing":source:"BearSheet.png"
    frameCount:8;framex:0;frameY:768
    frameWidth:256;frameHeight:256
    frameDuration:160
    to:("falling":1)
    Sprite(
    name:"falling":source:"BearSheet.png"
    frameCount:5;frameY:1280
    framewidth:256;frameHeight:256
    frameDuration:160
    to:("falling":1)}
}
```



```c
精灵引擎中的精灵动画可以使用Sprite类型定义。它是一个纯数据类型，不会进行谊染。该类型可以使用source属性为动画指定图片。如果使用frame Width和frameHeight属性指定了每个帧的大小，那么图片可以分为多个连续的行或者矩形顿：当一行的帧使用完了，会自动使用下一行的帧。如果使用frameX和frameY指定开始帧的位置，那么会从图片的(x,y)坐标的位置开始获取帧。使用name属性可以设置精灵的名称。使用0属性可以设置要过渡到的精灵的名称和权重，该属性的值是QVariantMap类型的键值对。例如{"a":l,"b":2,"c":0},这样会指定当前动画结束后，有1/3的几率过渡到名称为“a”的Sprite动画，有2/3的几率过渡到名称为“b”的Sprite动画，不会过渡到“c”动画。但是如果将目标动画设置为“c”,也可以过渡到“c”
Sprite动画。可以使用frameRate或者frameDuration属性来设置动画的速度，前者通过设置每秒显示的顿数来指定速度，后者通过设置每帧的显示时长来指定速度。如果将frameSync属性设置为true,那么动画顿将没有持续时间，当一个帧渲染到屏幕后会马上渲染下一帧。要反向执行动画，可以将reverse属性设置为true。SpriteSequence类型可以使用精灵引擎绘制定义在它里面的Sprite类型。该类型是一个独立的自给式精灵引擎，因而不能与其他精灵引擎进行交互。可以通过设置sprites属性指定要绘制的Sprite类型。各帧会被缩放为该引擎的大小。sprites属性是默认属性，所以直接在SpriteSequence中定义Sprite。goalSprite属性可以指定目标Sprite类型。指定该属性后，会无视过渡权重，以最短的路径到达目标动画。该类型还有一个jumpTo()函数，可以立即跳转到指定的动画。
```

`AnimatedSprite`：不在动画之间进行过渡

###### Flickable和Flipable

弹动效果：`Flickable`。可以用很小的视图显示很大的图片，通过视图的滚动显示更多内容

**翻转效果：`Flipable`**可以明显在其正面和反面之间进行反转的项目

#### 图形效果

导入：`import QtGraphicalEffects 版本`。包含20多种特效

##### Blend混合效果

混合两个对象

##### 颜色效果

###### BrightnessContrast

亮度对比度

###### ColorOverlay

颜色叠加

###### Colorize

着色

###### Desaturate

饱和度

###### GammaAdjust

伽马调整

###### LevelAdjust

色阶调整

###### HueSaturation

色相饱和度

##### 渐变

###### ConicalGradient

锥形渐变。从对象中间，在边缘结束渐变

###### LinearGradient

线性渐变，从起始点到终止点

###### RadialGradient

辐射渐变，与锥形渐变类似

##### Distortion变形效果

提供了一种可以移动像素的位移效果。

##### 阴影效果

###### DropShadow

投影。

###### InnerShadow

内阴影。

##### 模糊效果

###### FastBlur

快速模糊

###### GaussionBlur

高斯模糊

###### RecursiveBlur

递归模糊

###### MaskedBlue

遮罩模糊

##### 动态模糊

###### DirectionalBlur

方向模糊

###### RadialBlur

径向模糊

###### ZoomBlur

缩放模糊

##### 发光效果

###### Glow

发光

###### RectangularGlow

矩形发光

##### 遮罩效果

###### OpacityMask

不透明遮罩

###### ThresholdMash

阙值遮罩

#### 粒子系统

`import QtQuick.Particles 2.0`

是三维计算机图形学中模拟一些特定的模糊现象的技术。如火、爆炸、烟、云、雾、雪、流星尾迹等等。

**渲染器：设置绘制粒子的方式，其中的delegate可以使用任意QtQuick项目类型作为委托绘制单个粒子的样式形状**

* `CustomParticle`使用自定义的Shader着色器渲染
* `ImageParticle`
* `ItemParticle`

**发射器：指定发射的方式，如指定发射的坐标，宽高`x|y|width|height`设置坐标宽高。其velocity属性设置发射速度，需要指定一个发射方向的类型：**

* `TrailEmitter`
* `Emitter`
* `ParticlePainter`

发射方向类型：

* `AngleDirection`指的是朝着某个角度的方向，以右侧水平为0°，
* `CumulativeDirection`各分量的和的方向作为方向
* `PointDirection`其中的X和Y指的是向量的方向，而不是坐标
* `TargetDirection`

Shape形状类型：这些形状只是在这些形状中选择一个随机点作为指定的点包含：

* `EllipseShape`
* `LineShape`
* `MaskShape3`

##### ParticleSystem

将其他粒子系统中的类型关联在一起，管理他们共享的时间线。渲染器、发射器、影响器必须使用相同的粒子系统。该类型用来对整个粒子系统进行整体控制

`ParticleSystem{id:ss;running:false}`

##### Emitter

发射器

```c
Emitter {
    system:particles
    x:100;
    width:200;
    velocity:PointDirection{y:300;yVariation:100}
}
```



##### ItemParticle

渲染器

```c
ItemParticle{
    system:ss;
    delegate:Rectangle {
        id:rect;
        width:10;
        height:10;
        color:"red"
        radius:10
            
    }
}
```



##### ParticlePainters

渲染器，使粒子可视化

##### TrailEmitter

能以其它逻辑粒子作为起点发射粒子，使用`follow`属性指定要跟随的粒子的类型，`emitShape`设置要发射的粒子的区域，`emitWidth`和`emitHeight`设置区域的大小，以要跟随的粒子的位置为中心

`emitRatePerParticle`每个其它逻辑粒子后跟随的当前粒子数量。

##### 粒子组：ParticleGroup

默认粒子都处在一个空字串的组中。对于同一个组的粒子，图像粒子会隐式共享粒子的数据。可以在粒子中通过组名字设置。**如果一个图像粒子通过定义数据使用特定功能来渲染粒子，但是其它图像粒子没有定义，那么所有图像粒子都会自动使用该特定功能进行绘制，如果两个粒子都定义了数据，那么会分别使用各自定义的方式进行显示**

一个粒子可以属于多个组，粒子可以动态的改变组来改变状态。

`ParticleGroup`可以在组间定时转换，可以直接将发射器、影响器、渲染器作为一个组类型的子对象。通过`duration`设置粒子组发射多长时间后进行组间过渡，`to`**属性设置过渡到的其他组，因为支持过渡到多个组，所以需要设置权重`to:{"group1":1,"group2":10}`**

##### 随机参数

粒子系统通过几个辅助类型来实现随机参数

* `Direction`用于方向控制
  * `AngleDirection`角度
  * `CumulativeDirection`和向量
  * `PointDirection`
  * `TargetDirection`指定目标点作为方向
* `Shape`从一个形状中选取一个随机的点，矩形
  * `EllipseShape`椭圆
  * `LineShape`线
  * `MaskShape3`

##### 影响器Affector

影响器重要的属性：

```c
1. shape 只会对屏幕上该范围内的粒子起作用
2. enabled设置是否启用影响器。
3. groups指定对哪个组粒子起作用，否则全部粒子;
4. once设置只对每个粒子作用一次;
5. system指定要影响的粒子系统
6. whenCollidingWith指定一些粒子组，只有检测到和这些粒子组中的粒子相交时才会触发影响器，可以实现碰撞检测
```



可以在模拟时改变粒子的运行轨迹，提前结束粒子生命,**一下都是可以使用的类型，指定其system即可**

1. 控制器影响粒子的参数包含如下：

   1.生命周期(Age)-修改粒子的生命周期

   2.吸引(Attrator)-吸引粒子朝向指定点

   3.摩擦(Friction)-按照粒子速度成正比减慢速度

   4.重力(Gravity)-设置一个角度的加速度

   5.紊流(Turbulence)-强制基于噪声图像方向的流动，为粒子提供一个气流的效果

   7.漂流(Wander)-随机变化的轨迹

   8.组目标(GroupGoal)-让一个组中的粒子立即过渡到另一个组中，goalState指定要过渡到的目标组的名称，设置jump属性为true，可以使受影响的粒子直接跳入目标组中。可以通过`whenCollidingWith:["group名"]`设置碰撞到某组时生效。

   9.子粒子(SpriteGoal)-改变一个子粒子的状态

   > Gravity用于模拟一个巨大的物体，当其重心在很远的地方时的重力作用效果，如果要模拟一个对象的重心在场景里面或者附近的情形，可以使用Attractor类型
   >
   > 可以设置Width、Height来改变其作用的影响范围

#### Canvas

使用的是JS中的Canvas

##### Shape

用来实现一些自定义的图形，只设置某条边的边框，或者某个角变圆角。

```c
import QtQuick.Shapes 1.13

Shape {
    id: shape
    property var cornersRadius
    property color color
    property color borderColor:"transparent"
    property var borderWidth
    layer.enabled: true
    layer.samples: 4
    layer.smooth: true


    ShapePath {
        startX: 0
        startY: cornersRadius[0]
        fillColor: color
        strokeColor: borderColor
        strokeWidth: borderWidth
        PathQuad { x: cornersRadius[0]; y: 0; controlX: 0; controlY: 0 }
        PathLine { x: shape.width - cornersRadius[1]; y: 0 }
        
        PathQuad { x: shape.width; y: cornersRadius[1]; controlX: shape.width; controlY: 0 }
        PathLine { x: shape.width; y: shape.height - cornersRadius[2] }
        PathQuad { x: shape.width - cornersRadius[2]; y: shape.height; controlX: shape.width; controlY: shape.height }
        PathLine { x: cornersRadius[3]; y: shape.height }
        PathQuad { x: 0; y: shape.height - cornersRadius[3]; controlX: 0; controlY: shape.height }
        PathLine { x: 0; y: cornersRadius[0] }
    }
}
------------------------
     CurvedRectangle{
            width: 160
            height: 160
            color: "cyan"
            cornersRadius: [20,0,20,0]
            borderWidth:[1,2,3,1] // 上下右左
            borderColor:"grey"
        }
```



一个可绘图的画布。

**渲染的目标**：

* `Canvas.Image`：默认值。支持后台渲染
* `Canvas.FramebufferObject`：渲染目标使用OpenGL硬件加速，而不是直接渲染到系统内存

**渲染的策略：**通过`renderStrategy`属性设置

* `Canvas.Immediate`立即执行图形命令
* `Canvas.Threaded`延迟到另一个线程
* `Canvas.Cooperative`将图形命令延迟到应用程序的全局渲染进程

**平铺Canvas**

---

**绘制操作：**一般格式

```c
Canvas{
    width:200;
   	height:
    onPaint:{
        var ctx = getContext("2d"); // 创建Context2D对象，提供一个笛卡尔坐标系统，0,0坐标在左上，x轴向右
        // todo:设置路径
        ...
        // todo:描边或填充
        ...
    }
}
```

两种绘制方式：

* 描边：相关属性
  * `strokeStyle`：描边样式。可以是一个合法的CSS颜色，也可以是一个CanvasGradient或CanvasPattern对象
* 填充：相关的属性
  * `fillStyle`保存当前填充样式，可以是一个合法的CSS颜色，也可以是一个CanvasGradient或CanvasPattern对象

> strokeStyle和fillStyle除了使用颜色外，还可以使用纹理。通过`ctx.createPattern(color,枚举值Qt.xxxPattern)`或使用照片平铺：`ctx.createPattern(image,repeat/repeat-x/repeat-y/no-repeat)`

* 通用属性：
  * `lineWidth`

  * `lineJoin`线条交界处的样式

    * miter [ˈmaitə] 直角 默认
    * round 圆角
    * bevel [ˈbevl] 斜切角

  * `lineCap` 线条转折样式

    ```
    1. butt 默认值
    2. square 方形
    3. round　
    ```

  * `globalAlpha`

* 函数
  * `fillRect`绘制矩形
  * `strokeRect`描边方式绘制矩形
  * `clearRect`清空矩形区域
  * `save()`将当前绘制样式的状态压入栈
  * `restore()`栈顶的样式弹出设置

​	例子：

```js
var ctx = getContext("2d")
ctx.fillStyle = ctx.createPattern("red",DenselPattern) // 或使用照片平铺ctx.createPatten(照片类型,repeat/repeat-x/repeat-y/no-repeat)
```

---

其他绘制

* `fillText`|`strokeText`绘制文本，通过`ctx.font`设置文本样式

  ```c
  ctx.font = "30px Arial"
  ctx.textAlign = "start" // 文字对齐方式，包括：
      1. start
      2. end
      3. center
      4. left
      5. right
      
  textBaseline ：表示文本的基线。可能的值有 "top" 、 "hanging" 、 "middle" 、 "alphabetic" 、"ideographic" 和 "bottom" 。
  ```

  

---

**绘制路径：**

绘制前要使用`beginPath()`，然后设置具体路径，如：`ctx.rect(...)，最后调用`ctx.stroke()`真正绘制。

**注意路径绘制会自动调用`closePath()`将绘制的路径尾和首进行闭合连接直线**

* `moveTo(x,y)`当前坐标移动到x,y不会进行绘制
* `lineTo(x,y)`当前坐标移动到x,y会进行绘制一条直线。
* `strokeRect(x,y,width,height)`||`fillRect(x,y,width,height)`
* `rect(x,y,width,height)`无填充无边框的矩形
* `clearRect(x,y,width,height)`清除矩形
* `arc(圆心x,圆心y,半径,开始弧度,结束弧度,顺or逆时针)`添加一条圆弧。Math.PI / 180 * 角度 -- 弧度和角度转换
* `arcTo(x1,y1,x2,y2,...)`当前点为起点，添加一条与两条线段相切的弧线。
* `quadraticCurveTo`二次贝塞尔曲线
* `bezierCurveTo`贝塞尔曲线
* `rect`
* `ellipse`椭圆
* `roundedRect`圆角矩形
* `text`

##### 渐变填充

* `createLinearGradient`线性渐变，创建渐变后，使用`CanvasGradient.addColorStop()`添加渐变点。最后`ctx.fillStyle(渐变对象)`
* `createRadialGradient`辐射渐变
* `createConicalGradient`锥形渐变

##### 阴影

有四个属性控制

* `shadowBlur`阴影的像素模糊值，即阴影宽度
* `shadowColor`
* `shadowOffsetX`
* `shadowOffsetY`阴影在Y方向的偏移。

##### 图像

* `drawImage(image,x,y)`绘制图像
* `drawImage(image,x,y,w,h)`在矩形区域内绘制
* `drawImage(image,sx,sy,sw,sh,x,y,w,h)`将图像的矩形绘制到矩形
* `getImageData(x,y,width,height)`取得ctx.getImageData可以取得该区域的图像数据，返回的对象包含三个属性`width、height、data`，data是一个数组，保存图像中每一个像素的数据，数组大小为4，从0~3坐标分别保存红、绿、蓝、透明度

##### 坐标变换

* `setTransform()`仅设置当前变换矩阵
* `transform()`将当前矩阵乘以变换矩阵

##### 平移

* `translate(x,y)`实现图形平移，移动的是画布而不是图形

##### 缩放

* `scale()`

##### 旋转

`rotate(弧度)`

##### 扭曲

`shear()`

##### 透明度

`ctx.globalAlpha`设置全局透明度

`ctx.globalCompositionOperation`表示后绘制的图形怎样与先绘制的图形结合：

```c
source-over （默认值）：后绘制的图形位于先绘制的图形上方。
source-in ：后绘制的图形与先绘制的图形重叠的部分可见，两者其他部分完全透明。
source-out ：后绘制的图形与先绘制的图形不重叠的部分可见，先绘制的图形完全透明。
source-atop ：后绘制的图形与先绘制的图形重叠的部分可见，先绘制图形不受影响。
destination-over ：后绘制的图形位于先绘制的图形下方，只有之前透明像素下的部分才可见。
destination-in ：后绘制的图形位于先绘制的图形下方，两者不重叠的部分完全透明。
destination-out ：后绘制的图形擦除与先绘制的图形重叠的部分。
destination-atop ：后绘制的图形位于先绘制的图形下方，在两者不重叠的地方，先绘制的图形会变透明。
lighter ：后绘制的图形与先绘制的图形重叠部分的值相加，使该部分变亮。
copy ：后绘制的图形完全替代与之重叠的先绘制图形。
xor ：后绘制的图形与先绘制的图形重叠的部分执行“异或”操作。
```



##### 阴影

```
shadowColor ：用 CSS 颜色格式表示的阴影颜色，默认为黑色。
shadowOffsetX ：形状或路径 x 轴方向的阴影偏移量，默认为 0。
shadowOffsetY ：形状或路径 y 轴方向的阴影偏移量，默认为 0。
shadowBlur ：模糊的像素数，默认 0，即不模糊
```



#### 模型和视图

模型、视图、委托（控制数据应该如何在视图中显示）

**一般要导入：`QtQml.model`**

一般结构：将视图的model属性绑定到一个模型类型，然后将delegate属性绑定到一个组件**(`Component`)**或者其他兼容的类型

**提供的模型**

`import QtQml.Models 版本`

* `DelegateModel`封装模型和委托

* `DelegateModelGroup`封装经过过滤的可视数据项集合

* `ListModel`定义格式自由的列表式数据项，**通过model.setProperty()可以修改某个值**。特别的，其中可以这样

  ```
  ListElement{
  	name:"xx"
  	attributes:{
  		ListElement{
  			a:"xx"
  		}
  		ListElement{
  			
  		}
  	}
  }
  ...
  可以通过
  Repeater{
  	model:attribute
  	Text{
  		text:a
  	}
  }
  ```

  **在委托组件作用域中可以使用一个特殊的属性表示当前索引：`index`**还有一个表示当前数据`modelData`如

  ```c
  Component{
  	model.setProperty(index,属性名,值);
  } // index可以直接使用
  ```

  **当其他线程修改另外线程的model后，需要使用`model.sync()`**

* `ObjectModel`

`import QtQuick.XmlListModel 版本`

* `XmlListModel`使用XPath指定模型

也可使用C++自定义模型

##### WorkerScript

该类型可以在新线程中进行一些操作，使用该类型时，新线程和父线程之间可以使用`sendMessage()`函数和`onMessage()`处理器传递消息,如：

```c
WorkerScript{
	id:worker;
	source:"dataloader.js"
	onMessage:function(msg){
		msg.reply
	}
}
// js文件
WorkerScript.onMessage = function(message) 
{
    WorkerScript.sendMessage({ 'reply': '鼠标位置：' + message.x + ',' + message.y })
        // 若是在这里修改了模型的值，还需要调用model.sync()
}
```

##### ObjectModel

其中可以定义一系列可视化的组件，将组件显示到ListView中，不需要`delegate`

##### DelegateModel

它能用来访问模特索引。另外，DelegateModel和Package一起使用，可提供多种显示，还可以使用DelegateModelGroup来排序和过滤。**DelegateModel用于封装[model](https://so.csdn.net/so/search?q=model&spm=1001.2101.3001.7020)和delegate**

- 当model为QAbstractItemModel的子类，获取和操作modelIndex
- 和Package一起使用，提供multiple views。
- 和DelegateModelGroup一起使用，为delegate item 提供排序和过滤

DelegateModelGroup提供了访问DelegateModel的delegate items的方法，同时能够排序和过滤这些items

DelegateModel的model属性用来设置Model对象，而delagate属性用来设置委托视图对象

```
DelegateModel每在groups属性中定义一个DelegateModelGroup，则delegate后面定义的委托项的根对象中就会多对应的附加属性，假设委托项根对象id为item：
1. item.DelegateModel.in组名
2. item.DelegateModel.组名Index
我们在其它view显示时，如果设置delegateModel.filterOnGroup = 某个组名，则model中的实际对象会被过滤为该组选中的对象
```

`DelegateModel`的items方法获取当前所有model对象

##### Package

使得多个View可以使用同一个Delegate，结合DelegateModel

```c
ListModel{
     id: delegatemodel
     ListElement{name1:"dog"; name2:"cat"}
     ListElement{name1:"man"; name2:"girl"}
}
ListView{
    model:delegatemodel.parts.list
}
GridView{
    model:delegatemodel.parts.grid
}
DelegateModel{
     id: delegatemodel
     model: listmodel
     delegate: Package{
           Text{text:name1;Package.name:"list"}
           Text{text:name2;Package.name:"grid"}
     }
}

```

**使用附属的属性[Package](https://so.csdn.net/so/search?q=Package&spm=1001.2101.3001.7020).name为两个Text声明不同的名字：list, grid。**

##### XmlListModel

##### LocalStorage

是一个读取和写入SQLite数据库的单例类型

##### 使用C++定义模型再使用

该方法定义的模型，在模型变化时无法通知view更新，需要重新调用context->setContextProperty。[(54条消息) 在QML中使用SQL Model_qml sqlquerymodel_喵喵叫的猴的博客-CSDN博客](https://blog.csdn.net/zjgo007/article/details/112673115)绑定自动更新

**定义QStringList为模型：**

可以在`main.cpp`中

```c
app下方，engine上方添加，以QStringList为例子
只写要添加的部分 
QStringList datalist;
// 添加自己的数据
接着到engine下
QQmlContext *context = engine.rootContext();
context->setContextProperty("stringListModel",QVariant::fromValue(datalist));
// 接下来就可以直接使用了，名字已经定为stringListModel
```

如果是自定义类型：已经有了自己的pojo类，然后创建`model`类继承`QAbstractItemModel`，通过重新实现其中`roleNames()`方法来暴露角色名称：

```c
public: // pojo类有两个变量，type和size
	enum myPojoRoles{
		TypeRole = Qt:UserRole+1,
		SizeRole
	}
	QHash<int,QByteArray>myPojoModel::roleNames()const{
		QHash<int,QByteArray>roles;
		roles[TypeRole] = "type"
		roles[SizeRole] = "size"
		return roles;
	}
	
	
///////////////////////////////
QStringList MyModel::userRoleNames() // Return ordered List of user-defined roles
{
    QMap<int, QString> res;
    QHashIterator<int, QByteArray> i(roleNames());
    while (i.hasNext()) {
        i.next();
        if(i.key() > Qt::UserRole)
            res[i.key()] = i.value();
    }
    return res.values();
}

// 自定义插入对象函数的参数可以使用：`const QVariantMap map`

    QString type = map["type"].toString();
    QString size = map["size"].toString();
 
    MyType data(type, size);
 
    insert(count(), data);
// 注意把插入和删除代码块放在发送和结束的信号内。

void DataModel::insert(int index, const Data &data)
{
    if(index < 0 || index > dataList_.count()) {
        return;
    }
 
    emit beginInsertRows(QModelIndex(), index, index);
    dataList_.insert(index, data);
    emit endInsertRows();
//    emit countChanged(m_data.count());
}
 
void DataModel::remove(int index)
{
    if(index < 0 || index >= dataList_.count()) {
        return;
    }
 
    beginRemoveRows(QModelIndex(), index, index);
    dataList_.removeAt(index);
    endRemoveRows();
}
 
 
void DataModel::append(const QString &title,const QString &color)
{
    insert(count(), Data(title,color));
}
 
 
int DataModel::count() const
{
    return rowCount(QModelIndex());

————————————————
版权声明：本文为CSDN博主「风斜夜」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/fxy0325/article/details/81434762
```

##### 视图类型：

* `ListView`，可以设置头部和脚部，snapMode可以设置其滚动行为
* `GridView`
* `WebView`可以在QML应用中渲染Web网页内容。需要导入`QtWebKit`模块
* `PathView`使模型按一定的路径显示，需**要定义一个委托和一个路径**。可以使用高亮，不过需要设置`visible`属性为`PathView.onPath`，在该view中，`preferedHighlightBegin`和`preferedHighlightEnd`属性很重要，取值范围均为`0~1`，如果需要当前项始终在路径中央，可以将两个属性都设置为0.5，并且将`highlightRangeMode`设置为`PathView.Strictly`。要处理导航按键，需要先设置`focus`为`true`，然后调用`decrementCurrentIndex()`或另一个函数。可以被添加到`pathElements`的路径元素：
  * `PathLine`
  * `PathQuad`二次贝塞尔曲线
  * `PathCubic`二次贝塞尔曲线
  * `PathArc`一段弧
  * `PathSvg`由Svg路径数据字符串定义的一段路
  * `PathCurve`Catmull-Rom曲线上一点
  * `PathAttribute`路径上给定位置的特性，用于调整已有的路径
  * `PathPercent`：定义在路径上项目的分布方式用于调整已有的路径
* `Path`配合`PathView`使用，定义路径

> 若想为模型中单个对象定义不同的动画，需要使用`ViewTransition`包含了许多附加属性

##### View类型性能问题

推荐使用`Loader`



##### View过渡

View中有一些属性，可以定义View统一的过渡

当然也可以针对单个数据项定制动画，需要使用以下附加属性：

* `ViewTransition.item`过渡中的项目
* `ViewTransition.index`过渡中的索引
* `ViewTransition.destination`该项目要移动到的目标位置(x,y)
* `ViewTransition.targetIndexes`目标项目的索引，目标项目可能不止一个
* `ViewTransition.targetItems`目标项目本身

样例：如在displaced属性中：

```c
displaced:Transition{
    id:dispTrans
    SequentialAnimation{
        PauseAnimation{
            duration:(dispTrans.ViewTransition.index-disoTrans.ViewTransition.targetIndexes[0])*100
        }
    }
}
```



##### 注意

关于拖拽，参考https://blog.csdn.net/zhengtianzuo06/article/details/78631977，由于设置交互事件，会影响鼠标滚动和拖拽，所以进行了修改

`interactive: !isClicked`

#### 多媒体

|      功能      | 示例 |              类型               |
| :------------: | :--: | :-----------------------------: |
|    播放音频    |      |       Audio、MediaPlayer        |
|    播放视频    |      | MediaPlayer、VideoOutput、Video |
|    处理视频    |      |    MedioPlayer、VideoOutput     |
|   播放收音机   |      |        Radio、RadioData         |
| 访问相机取景器 |      |       Camera、VideoOutput       |
|   处理取景器   |      |       Camera、VideoOutput       |
|    拍摄照片    |      |             Camera              |
|    拍摄视频    |      |             Camera              |
|     3D声源     |      |          Audio Engine           |

##### 播放压缩音源

```
Audio{
	id:
	source:
}
```

##### 播放未压缩音频

```
SoundEffect{
	id:
	source:
}
```

##### 播放视频

`Video`类型

* `fillMode`属性，定义视频如何缩放来适应窗口

```
VideoOutput.Stretch 视频进行缩放适应窗口大小
VideoOutput.PreserveAspectFit:默认，视频按比例缩放，不会进行裁剪
VideoOutput.PreserveAspectCrop:视频按比例缩放，会进行裁剪
```

`Video{id:xx;source:xx}`

##### 播放音视频

`MediaPlayer`，即可以设置视频资源也可以设置音频资源。

```c
MediaPlayer{id:media;source:xxx}
VideoOutput{source:media;}使用该类型对平台后端进行视频的渲染
```



##### 图形效果作用于视频

在上述笔记中的图形效果类也可以作用于视频，**注意需要设置Video中的`visible`属性为false，否则原视频和图形效果处理后的视频是同时播放的**

#### QT和C++

##### 父对象

一般自定义的类型构造函数参数中要添加：

```
myPojo(QObject *parent = 0)
```



##### QQmlEngine

该C++类提供了一个QML引擎，用于管理QML文档定义的对象层次结构，提供了根上下文

获得该上下文：

```c
QStringListModel modelData;
QQmlContext *context = engine.rootContext();
context->setContextProperty("stringModel",&modelData);
```

##### QQmlComponent

使用该类可以在运行时创建组件。

```c
QQmlComponent component(&engine,QUrl::fromLocalFile("./自定义组件.qml"))
QObject *myObject = component.create();
QQuickItem *item = qobject_cast<QQuickItem *>(myObject) // 由此就创建了一个该组件。
```

##### QQmlExpression

动态执行表达式。

```c
QQmlComponent component(&engine,QUrl::fromLocalFile("./自定义组件.qml"))
QObject *myObject = component.create();
QQmlExpression *expr = new QQmlExpression(engine.rootContext(),myObject,"width*2")
int resule = expr->evaluate().toInt();
// 该表达式求组件的宽*2的值
```

##### QML使用C++

###### 通过宏添加属性和枚举

当有一个变量时，一定要有一个`NOTIFY`信号`xxxChange()`信号，qml会自动创建对应的`onXXXChange()`处理

---

###### 使用函数和槽



QML可以有条件的访问QObject子类的函数。**如果C++函数的参数是`QObject*`类型，可以在qml直接使用`id`或者`js`的`var`类型引用**

条件是：

1. 使用`Q_INVOKABLE`宏标记的`public`函数
2. `public`槽函数

```
public:
Q_INVOKABLE bool postMessage(const &QString &msg);


```



---



**C++自定义组件通过`qmlRegisterType<Test>("在qml import后要写的内容",主版本号, 次版本号, "qml使用时的名字");`导入**

```c
#ifndef XIMAGEVIEW_H
#define XIMAGEVIEW_H

#include <QObject>
#include <QImage>
#include <QQuickPaintedItem>

class QPainter;
class XImageView : public QQuickPaintedItem
{
    Q_OBJECT
	Q_EMNUS(枚举类型名) // 为了使用枚举必须暴露
    Q_PROPERTY(QImage mImage READ getImage WRITE setImage)
    Q_PROPERTY(QString fileUrl READ getFileUrl WRITE setFileUrl)
    Q_PROPERTY(int mWidth READ getWidth WRITE setWidth)
    Q_PROPERTY(int mHeight READ getHeight WRITE setHeight)

public:
    XImageView(QQuickItem *parent = 0);
    virtual ~XImageView();

    virtual void paint(QPainter *painter);

    QImage getImage() const;
    void setImage(QImage img);

    QString getFileUrl() const;
    void setFileUrl(QString url);

    int getWidth() const;
    void setWidth(int w);

    int getHeight() const;
    void setHeight(int h);

    Q_INVOKABLE void zoomDraw(float z = 1.0f);

private:
   QImage mImage;
   QString fileUrl;
   int mWidth;
   int mHeight;
   float mZoom;
};

#endif // XIMAGEVIEW_H

```

**为了在QML访问QObject子类的列表属性，不能使用QList<T>，要使用QQmlListProperty<T>，如：`QQmlListProperty<myPojo>**

###### 注册不可实例化：

```
为了应对这些情况，QML提供了一些用于注册不可实例化对象类型的方法：
1. 使用无参数的qmlRegister Type()函数。由于qmlRegisterType()没有提供命名空间和版本号，也就不能在QML中引用，这限制了QML引擎对该类型实例化的能力。
2. 使用qmlRegisterInterface()注册指定QML类型名称的Qt接口类型。这种类型不能实例化，但是可以使用其类型名称进行引用。
3. 使用qmlRegisterUncreatableType()注册不可被实例化的具有名称的C+十类型，但是这样的类型依然可以作为QML类型系统可识别的一种类型。如果该类型的枚举或者附加特性需要在QML中使用，但是类型本身不应被实例化，就需要使用这种方式进行注册。
4. 使用qmlRegisterSingleton Type()注册不能从QML导人的单例类型，下一节将详细介绍这种方法。
```

##### 类型的修订和版本

使用`Q_REVISION(修订版本号)`标记新增的部分

```
Q_PROPERTY(int root READ root WRITE setRoot NOTIFY rootChanged REVISION 1)
signals:
	Q_REVISION(1) void rootChanged()
然后注册修订后的类型：
qmlRegisterType<MyType,1>("mytype",1,1,"mytype"); 现在root只能在1.1版本使用
```

##### C++实现附加属性对象

**首先需要一个附加对象的类型：**同样继承qObject

**对需要添加附加对象的类型必须添加：**

* 在类结尾后

  ```
  myPojo:public QObject{
  
  };
  QML_DECLARE_TYPEINFO(myPojo,QML_HAS_ATTACHED_PROPERTIES)
  ```

* 在类型中必须添加：

  ```c
  static 自己的附加类型 * qmlAttachedProperties(QObject *object){
      return new 自己的附加类型(object);
  }
  ```

  

**C++可以通过`qmlAttachedPropertiesObject()`函数访问任意附加对象实例**

##### 属性修饰符

包含两种类型：

* 属性值设置拦截器
* 属性值源

如：

```c
NumberAnimation on x{} // 自定义属性值源

```

**方法：**

```
1. 需要继承`QQmlPropertyValueSource`
2. Q_INTERFACE(QQmlPropertyValueSource)
3. 定义一个策略。以定时更新举例：
	需要一个QTimer定时器，需要一个QQmlProperty p变量
	在构造函数初始化时，将QTimer定时器和一个处理槽函数链接，
```

##### 默认赋值属性

```c
// 使用Q_CLASSINFO("DefaultProperty","自己定义的变量名")
Q_CLASSINFO("DefaultProperty","messages")
private:
QList<Message*>messages;
// 没有为子对象指定赋值的属性时，默认赋值给messages
MessageBoard{
    Message{}
    Message{}
}
```

##### 接受对象初始化通知

有些QML对象需要在对象创建完成之后进行数据的延迟初始化

**必须同时继承`QObject`和`QQmlParserStatus`，并且定义`Q_INTERFACES(QQmlParserStatus)`**

##### C++加载QML

* 使用`QQmlComponent`加载

  `Qobject *object=component.create();delete object`

* 使用`QQuickView`加载

  `view.setSource(QUrl(QStringLiteral("url")))`

  `view.show()`

  `QQuickItem* obj = view.rootObject()`获取根对象

  `obj.findChild<QObject*>("objectName属性名")`获取子对象

**qml属性property也可以访问：**

`QObject *obj = component.create()`

`QQmlProperty::read(obj,"属性名")`

属性值设置时应当使用：`obj.setProperty("属性名",value)`

**QML中function在C++调用：**

`obj = component.create()`

`QMetaObject::invokeMethod(obj,"函数名",Q_RETURN_ARG(QVariant，本地定义一个变量来接收返回值),Q_ARG(QVariant,向函数传递的变量参数))`

**C++中关联和QML信号**

`QQuickItem *item = view.rootObject()`

`Object obj`

`QObject::connect(item,SIGNAL(qml中发射的信号名(参数类型)),&obj,SLOT(c++中定义的槽函数))`

> 注意，在C++中定义的槽函数参数中变量类型必须为：`QVariant`，在QML定义的信号的参数类型必须为`var`

#### 网络

* `xmlListModel`
* `XmlHttpRequest`组件
* `WebSocket`与服务器进行HTTP请求  
