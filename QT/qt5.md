---
QT
---

[TOC]

#### QT概况

##### 乱码

```c
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec); //解决汉字乱码问题
// 在main.cpp中添加即可
```



QT将所有内容分为3部分：

1. QT基本模块：定义了适用于所有平台的基础功能，是QT核心。基本模块的基础是QT Core模块，其他模块都依赖于该模块。基本模块包括：

   ​	![](https://pic.imgdb.cn/item/642e6f41a682492fccbfc495.png)

2. QT扩展模块

   ​	![](https://pic.imgdb.cn/item/642e7036a682492fccc123be.png)

   ​	![](https://pic.imgdb.cn/item/642e7036a682492fccc123f6.png)

3. QT开发工具

#### 项目组成

##### 加载资源

在新建文件或项目中找到文件和类，点击`Qt`，有`Qt Resource File`

##### 项目管理文件

后缀`.pro`是项目的管理文件，文件名就是项目的名称。

```C
QT	+= core gui // 表示项目中加入core gui模块，用于GUI设计的类库模块
// 如果要用sql模块，就要加QT	+= sql
greaterThan(QT_MAJOR_VERSION,4):QT += widgets // 表示QT主版本大于4时才加入widgets模块
TARGET = 文件名 // 表示生成可执行文件为--文件名.exe
RC_ICONS = 图标名.ico // 这个图标要放在源程序exe目录下，设置程序的图标。
```

#### 组件

对需要访问的组件要修改其`objectName`，以便进行区分，不访问的则不用修改。窗体的类`objectName`不要修改，其要去涉及的代码里去定义。

上方有个`edit bubble`编辑伙伴关系，需要使用`Label`组件，将其托向需要被链接的组件即可。然后可以设定快捷键，使得我们使用快捷键后，被聚焦到链接的伙伴。快捷键设定方法，设置`Label`的`Text`属性，如要设立快捷键为`alt+x`只需要添加`&x`即可，如`姓名(&x)`。

#### 信号与槽

信号就是在特定的条件下发射的事件，槽就是对信号响应的函数。使用：`connect([send],SIGNAL(信号事件),[receiver],SLOT(槽事件))`。一个信号可以连接多个槽，当信号和槽带有参数时，在`connect`函数内要写明参数的类型，但可以不写参数名称。如：`connect(send,SIGNAL(valueChanged(int)),this,SLOT(refreshInfo(int)))`。在使用信号与槽的类中，必须在类的定义中加入宏`Q_OBJECT`。

**注意connect函数有一个缺省值，默认为Qt::AutoConnection，其他还有：`Qt::DirectConnection`，信号被发送后立刻执行，槽函数与信号在同一个线程，`Qt::QueuedConnection`在事件循环回到接收者线程后执行槽函数，槽函数和信号在不同线程。`Qt::BlockingQueuedConnection`信号线程会阻塞直到草函数执行完毕，只能用于不同线程的信号和槽函数**

在槽函数中可以使用`QObject::sender()`获取信号发送者指针，若知道类型还可以使用`qobject_cast`进行转换

我们添加信号的方法

* 可以右键组件点击转到槽，来为其添加信号。
* 可以自己在窗体类私有`slots`中添加函数`private slots:`，在函数名上右击，选择`Refactor`->添加定义，然后在窗体类的构造函数中手工进行关联，就是在`ui->setupUi(this);`下一行添加`connect`函数即可。这里的this代表窗体类，表示调用了其中的槽函数`connect(send,SIGNAL(valueChanged(int)),this,SLOT(refreshInfo(int)))`
* 可视化方法，`UI`设计器上面有个`Edit Signals/Slots`，将鼠标移动到某个组件上，或者移动到一个空白区域释放。

---



* `click()`
* `click(bool)`这个版本会传递当前组件的选择状态，同时会增加一函数。

##### 自定义信号

```c++
class QPerson: public QObject
{
    Q_OBJECT
private:
    int m_age = 10;
public:
    void incAge();
signals: // 定义信号量，要写这个
    void ageChanged(int value); // 信号本身是一个函数，必须是无返回值的函数
}
// 发射时：
void QPerson::incAge()
{
    // 发射信号：
    emit ageChanged(m_age); // 发射函数就可以
}
```



#### 通常的

使用`ui->组件名`获取某个组件

* `QFont`修改字体
* `QPalette`用于控件的颜色和背景管理，如需要修改文本类颜色`setColor(QPalette::Text,Qt::blue)`
* `QCheckBox`
* `QRadioButtion`
* `QPlainTextEdit`
* `QPushButton`
* `...`

> 使用以上都要包含对应的头文件，头文件就是对应的组件所属的大类别。

#### 代码方式编写

代码方式中是没有默认的`ui`这个对象的。一切对象布局都需要自己创建。`.h`文件。我们需要在`private`中创建需要用到的组件，布局的定义来自于基类中的`setLayout()`函数，布局可以在需要使用的时候在定义，需要在`private slots:`中定义槽函数。需要一个`iniUI`函数，需要一个`initSignalSlots`函数.

> 对比可视化，可视化方法存在一些缺陷，某些组件无法可视化地添加到界面上去，比如在工具栏上设置调节字体大小的选择框，选择字体样式的选择框，而用代码可以。
>
> **推荐使用可视化+代码混合方式**

```c++
#ifndef QWDLGMANUAL_H
#define QWDLGMANUAL_H

#include <QDialog>

#include <QCheckBox>
#include <QRadioButton>
#include <QPlainTextEdit>
#include <QPushButton>


class QWDlgManual : public QDialog
{
    Q_OBJECT

private:
    QCheckBox   *chkBoxUnder;
    QCheckBox   *chkBoxItalic;
    QCheckBox   *chkBoxBold;

    QRadioButton    *rBtnBlack;
    QRadioButton    *rBtnRed;
    QRadioButton    *rBtnBlue;

    QPlainTextEdit  *txtEdit;

    QPushButton     *btnOK;
    QPushButton     *btnCancel;
    QPushButton     *btnClose;

    void    iniUI();//UI 创建与初始化
    void    iniSignalSlots();//初始化信号与槽的链接

private slots:
    void on_chkBoxUnder(bool checked); //Underline 的clicked(bool)信号的槽函数

    void on_chkBoxItalic(bool checked);//Italic 的clicked(bool)信号的槽函数

    void on_chkBoxBold(bool checked); //Bold 的clicked(bool)信号的槽函数

    void setTextFontColor(); //设置字体颜色

public:
    QWDlgManual(QWidget *parent = 0);
    ~QWDlgManual();

};

#endif // QWDLGMANUAL_H

```

```c++
#include "qwdlgmanual.h"
#include    <QHBoxLayout>
#include    <QVBoxLayout>

void QWDlgManual::iniUI()
{
//创建 Underline, Italic, Bold三个CheckBox，并水平布局
    chkBoxUnder=new QCheckBox(tr("Underline"));
    chkBoxItalic=new QCheckBox(tr("Italic"));
    chkBoxBold=new QCheckBox(tr("Bold"));

    QHBoxLayout *HLay1=new QHBoxLayout;
    HLay1->addWidget(chkBoxUnder);
    HLay1->addWidget(chkBoxItalic);
    HLay1->addWidget(chkBoxBold);

//创建 Black, Red, Blue三个RadioButton，并水平布局
    rBtnBlack=new QRadioButton(tr("Black"));
    rBtnBlack->setChecked(true);//缺省被选中
    rBtnRed=new QRadioButton(tr("Red"));
    rBtnBlue=new QRadioButton(tr("Blue"));

    QHBoxLayout *HLay2=new QHBoxLayout;
    HLay2->addWidget(rBtnBlack);
    HLay2->addWidget(rBtnRed);
    HLay2->addWidget(rBtnBlue);

//创建 确定, 取消, 退出 三个 QPushButton, 并水平布局
    btnOK=new QPushButton(tr("确定"));
    btnCancel=new QPushButton(tr("取消"));
    btnClose=new QPushButton(tr("退出"));

    QHBoxLayout *HLay3=new QHBoxLayout;
    HLay3->addStretch();
    HLay3->addWidget(btnOK);
    HLay3->addWidget(btnCancel);
    HLay3->addStretch();
    HLay3->addWidget(btnClose);


//创建 文本框,并设置初始字体
    txtEdit=new QPlainTextEdit;
    txtEdit->setPlainText("Hello world\n\nIt is my demo");

    QFont   font=txtEdit->font(); //获取字体
    font.setPointSize(20);//修改字体大小为20
    txtEdit->setFont(font);//设置字体

//创建 垂直布局，并设置为主布局
    QVBoxLayout *VLay=new QVBoxLayout;
    VLay->addLayout(HLay1); //添加字体类型组
    VLay->addLayout(HLay2);//添加字体颜色组
    VLay->addWidget(txtEdit);//添加PlainTextEdit
    VLay->addLayout(HLay3);//添加按键组

    setLayout(VLay); //设置为窗体的主布局
}

void QWDlgManual::iniSignalSlots()
{
//三个颜色  QRadioButton的clicked()事件与setTextFontColor()槽函数关联
    connect(rBtnBlue,SIGNAL(clicked()),this,SLOT(setTextFontColor()));//
    connect(rBtnRed,SIGNAL(clicked()),this,SLOT(setTextFontColor()));//
    connect(rBtnBlack,SIGNAL(clicked()),this,SLOT(setTextFontColor()));//

//三个字体设置的  QCheckBox 的clicked(bool)事件与 相应的槽函数关联
    connect(chkBoxUnder,SIGNAL(clicked(bool)),this,SLOT(on_chkBoxUnder(bool)));//
    connect(chkBoxItalic,SIGNAL(clicked(bool)),this,SLOT(on_chkBoxItalic(bool)));//
    connect(chkBoxBold,SIGNAL(clicked(bool)),this,SLOT(on_chkBoxBold(bool)));//

//三个按键与窗体的槽函数关联
    connect(btnOK,SIGNAL(clicked()),this,SLOT(accept()));//
    connect(btnCancel,SIGNAL(clicked()),this,SLOT(reject()));//
    connect(btnClose,SIGNAL(clicked()),this,SLOT(close()));//
}

void QWDlgManual::on_chkBoxUnder(bool checked)
{
    QFont   font=txtEdit->font();
    font.setUnderline(checked);
    txtEdit->setFont(font);
}

void QWDlgManual::on_chkBoxItalic(bool checked)
{
    QFont   font=txtEdit->font();
    font.setItalic(checked);
    txtEdit->setFont(font);
}

void QWDlgManual::on_chkBoxBold(bool checked)
{
    QFont   font=txtEdit->font();
    font.setBold(checked);
    txtEdit->setFont(font);
}

void QWDlgManual::setTextFontColor()
{
    QPalette   plet=txtEdit->palette();
    if (rBtnBlue->isChecked())
        plet.setColor(QPalette::Text,Qt::blue);
    else if (rBtnRed->isChecked())
        plet.setColor(QPalette::Text,Qt::red);
    else if (rBtnBlack->isChecked())
        plet.setColor(QPalette::Text,Qt::black);
    else
        plet.setColor(QPalette::Text,Qt::black);

    txtEdit->setPalette(plet);
}

QWDlgManual::QWDlgManual(QWidget *parent)
    : QDialog(parent)
{
    iniUI(); //界面创建与布局
    iniSignalSlots(); //信号与槽的关联
    setWindowTitle("Form created manually");//设置窗体标题
}

QWDlgManual::~QWDlgManual()
{

}

```

#### Action

可以表示菜单项、工具栏按钮、快捷键等用户操作。所有用于菜单和工具栏设计的功能都需要用Action实现，有了Action后，直接将某个Action拉到菜单栏中就完成了。

* 文本：该Action的显示名称
* 对象名称：该Action的objectName。
* `ToolTip`：当鼠标在菜单项或工具项上短暂停留时显示的文字
* `Icon`：设置`Action`的图标
* `Checkable`：设置`Action`是否可以被复选
* `Shortcut`：设置快捷键

工具栏的创建，右键窗口区域就可以`Add Tool Bar`。可以将Action作用于工具栏。其中工具栏显示方式可以通过设置其`toolButtonStyle`属性即可，已有的属性定义在`QT::ToolButtonStyle`作为枚举类型。

##### 状态栏

`setStatusBar(statusbar)`继承的窗口类已经有此函数

##### 工具栏

`setToolBar(toolbar)`继承的窗口类已经有此函数

#### QT快捷键

![](https://pic.imgdb.cn/item/642fb8d2a682492fcc2e2c66.png)

#### QT类库

##### 元对象系统：

<font color="red">注意要继承类`QObject，并且在类中使用宏Q_OBJECT，这样才能使用信号、槽、属性功能`</font>

该系统由以下三个基础组成：

* `QObject`类是所有元对象系统的类的基类
* 在一个类的`private`部分声明`Q_OBJECT`宏，使得类可以使用元对象的特性，如动态属性、信号与槽
* `MOC`（元对象编译器）为每个`QObject`的子类提供必要的代码来实现元对象系统的特性。

该系统还提供：

* `QObject::metaObject()`返回类关联的元对象，包含访问元对象的一些接口函数，`QMetaObject::className()`函数可以支持在运行时返回类的名称字符串。
* `QMetaObject::newInstance()`函数创建类的一个新的实例
* `QObject::inherit(const char* className)`判断一个对象实例是否是名称为`className`的类或`QObject`的子类的实例。
* `QObject::tr()`、`QObject::trUtf8()`两个函数可以翻译字符串，用于多语言设计
* `QObject::setProperty()`和`QObject::property()`用于通过属性名称动态设置和获取属性值

* `qobject_cast<type>()`将一个类动态转换成其父类

##### 属性系统

属性值可以通过`QObject`实例对象的`property`方法获取

![](https://pic.imgdb.cn/item/642fbddda682492fcc370247.png)

![](https://pic.imgdb.cn/item/642fbddea682492fcc37031e.png)

```c++
READ：如果未指定成员变量（通过 MEMBER ），则需要读取访问器函数。用于读取属性值。理想情况下，一个const函数可用于此目的，它必须返回属性的类型或对该类型的const引用。
WRITE：写访问器函数是可选的。用于设置属性值。它必须返回void，并且必须只接受一个参数，要么是属性的类型，要么是指向该类型的指针或引用。
MEMBER：如果未指定读取访问器函数，则需要成员变量关联。这使得给定的成员变量可读写，而无需创建读写访问器函数。如果需要控制变量访问，除了成员变量关联（但不是两者）之外，还可以使用读或写访问器函数。
RESET：复位功能是可选的。它用于将属性设置回其特定于上下文的默认值。
NOTIFY：通知信号是可选的。如果已定义，它应该指定该类中的一个现有信号，该信号在属性值更改时发出。成员变量的通知信号必须采用零个或一个参数，这些参数必须与属性的类型相同。参数将采用属性的新值。仅当属性确实发生更改时才应发出NOTIFY信号，以避免绑定在QML中被不必要地重新计算。
REVISION：修订号是可选的。如果包含，它将定义属性及其通知程序信号，以便在特定版本的API中使用（通常用于暴露于QML）。如果不包含，则默认为0。
DESIGNABLE：表示属性是否应该在GUI设计工具（例如Qt Designer）的属性编辑器中可见。大多数属性是可设计的（默认为true）。可以指定布尔成员函数，而不是true或false。
SCRIPTABLE：表示脚本引擎是否应该访问此属性（默认为true）。可以指定布尔成员函数，而不是true或false。
STORED：表示属性是应该被认为是独立存在还是依赖于其他值。它还指示在存储对象状态时是否必须保存属性值。
USER：表示是将属性指定为类的面向用户属性还是用户可编辑属性。通常，每个类只有一个用户属性（默认值为false）。
CONSTANT：表示属性值是常量。对于给定的对象实例，常量属性的READ方法每次调用时必须返回相同的值。对于对象的不同实例，此常量值可能不同。常量属性不能有写入方法或通知信号。
FINAL：表示派生类不会重写该属性。在某些情况下，这可以用于性能优化，但不是由moc强制执行的。
READ、WRITE、RESET 可以继承。当它们在使用多重继承的类中继承时，它们必须来自第一个继承的类。

```

当我们在Qt中创建自定义的对象时，我们可能需要为对象定义一些属性，以便我们可以在运行时或在Qt Designer中设置和修改这些属性。这些属性可以是任何类型，例如整数、字符串、布尔值等等。在这种情况下，我们可以使用Q_PROPERTY宏来定义属性。

```c++
class Person : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    explicit Person(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

signals:
    void nameChanged();

private:
    QString m_name;
};

Person::Person(QObject *parent) : QObject(parent)
{
}

QString Person::name() const
{
    return m_name;
}

void Person::setName(const QString &name)
{
    if (name != m_name) {
        m_name = name;
        emit nameChanged(); // emit宏，这里表示发送信号到nameChanged()
    }
}
```

###### 属性系统的附加信息

仍然注意要继承`QObject`类

`Q_CLASSINFO()`可以为类定义“名称-值”。

![](https://pic.imgdb.cn/item/642fc51da682492fcc44db60.png)

##### 数据类型定义

![image-20230407164147638](https://pic.imgdb.cn/item/642fdf56a682492fcc7d319a.png)

##### 函数

`<QtGlobal>`头文件包含一些常用函数，多以模板类型为参数。

![image-20230410085221757](https://cdn.jsdelivr.net/gh/xxn-1/image/img/202304100852869.png)

![image-20230410085306409](https://cdn.jsdelivr.net/gh/xxn-1/image/img/202304100853488.png)

##### 常用宏

`<QtGlobal>`头文件包含一些常用宏。

* `QT_VERSION`，表示QT编译器版本，如果版本为QT5.9.1，则值为`0x050901`，可以使用`#if QT_VERSION >= 0x050901`
* `QT_VERSION_CHECK`,表示QT版本号的整数形式。`#if (QT_VERSION>=QT_VERSION_CHECK(5,0,0))`
* `QT_VERSION_STR`版本的字符串形式
* `Q_BYTE_ORDER`表示内存的字节序，值为以下两种，`#if Q_BYTE_ORDER == Q_BIG_ENDIAN`
  * `Q_BIG_ENDIAN`
  * `Q_LITTLE_ENDIAN`
* `Q_DECL_IMPORT`,`Q_DECL_EXPORT`:使用或设计共享库时，用于导入或导出库的内容。
* `Q_DECL_OVERRIDE`:可以代替以前`override`的位置，转而使用该宏代替关键字。
* `Q_DECL_FINAL`:代替原来的`final`关键字，表示不能被继承的类。
* `Q_UNUSED(参数名)`在函数中定义却没有使用的变量可以使用该宏避免警告。
* `foreach(x,容器变量)`代替以前的范围for
* `forever{代码块}`构造一个无限循环
* `qDebug("消息")`在debugger窗体内显示消息，若定义了宏`QT_NO_DEBUG_OUTPUT`则不作输出

##### 容器类

###### 顺序容器

* `QList`
* `QLinkedList`
* `QVector`
* `QStack`
* `QQueue`

###### 关联容器

* `QMap`
* `QMultiMap`
* `QHash`
* `QMultiHash`
* `QSet`

###### 容器类的访问遍历

QT提供了两个版本的迭代器

* `java版本迭代器`：

  ![image-20230410091908417](https://cdn.jsdelivr.net/gh/xxn-1/image/img/202304100919499.png)

  * 只读：`Q容器类型Iterator<T>it(容器变量)`
  * 读写迭代器：`QMutable容器类型Iterator<T>it(容器变量)`

  ```c++
  QList<QString>list;
  QListIterator<QString>i(list);
  while(i.hasNext())qDebug()<<i.next();
  // map
  QMap<QString,QString>map;
  QMutableMapIterator<QString,QString>i(map);
  while(i.hasNext()){
      if(i.next().key().endsWith("City"))i.remove();
  }
  ```

  ![image-20230410092042210](https://cdn.jsdelivr.net/gh/xxn-1/image/img/202304100920291.png)

* `sql版本迭代器`：比java版本更快

  * 只读版本：`Q类型<T>::const_iterator`
  * 读写版本：`Q类型<T>::iterator`


##### 常用：

* `QCoreApplication`提供一些获取文件路径等的静态函数

##### QT类库

###### 基本模块：

```
Qt Core 其他模块都用到的核心非图形类
Qt GUI 设计GUI界面的基础类，包括OpenGL
Qt Multimedia 音频、视频、摄像头和广播功能的类
Qt Multimedia Widgets 实现多媒体功能的界面组件类
Qt Network 使网络编程更简单和轻便的类
Qt QML 用于QML和JavaScript语言的类
Qt Quick 用于构建具有定制用户界面的动态应用程序的声明框架
Qt Quick Controls 创建桌面样式用户界面，基于Qt Quick的用户界面控件
Qt Quick Dialogs 用于Qt Quick的系统对话框类型
Qt Quick Layouts 用于Qt Quick2界面元素的布局项
Qt SQL 使用SQL用于数据库操作的类
Qt Test 用于应用程序和库进行单元测试的类
Qt Widgets 用于构建GUI界面的C++图形组件类
```

###### 附加模块

```
Active Ot
用于开发使用ActiveX和COM的Windows应用程序
Qt 3D
支持2D和3D渲染，提供用于开发近实时仿真系统的功能
Qt Android Extras
提供Android平台相关的API
Qt Bluetooth
提供访问蓝牙硬件的功能
Qt Concurrent
提供一些类，无需使用底层的线程控制就可以编写多线程程序
Qt D-Bus
使进程间通过D-Bus协议通信的一些类
Qt Gamepad
使Q应用程序支持游戏手柄硬件的使用
Qt Image Formats
支持附加图片格式的插件，包括TIFF、MNG、TGA、WBMP
Qt Mac Extras
提供macOS平台相关的API
Qt NFC
提供访问NFC(近场通信)硬件的功能
Qt Positioning
提供一些类，用于通过GPS卫星、WiFi等定位
Qt Print Support
提供一些用于打印控制的类
Qt Purchasing
提供一些类，在Q应用程序内实现应用内购买的功能
Qt Sensors
提供访问传感器硬件的功能，以识别运动和手势
Qt Serial Bus
访问串行工业总线的功能，目前只支持CAN和Modbus协议
Qt SVG
提供显示SVG图片文件的类
用于实现服务器端(QML或C++应用程序)与客户端(HTML/JavaScript或QML应用
Qt WebChannel
程序)之间的P2P通信
Qt WebEngine
提供类和函数，实现在应用程序中嵌入网页内容
提供兼容于RFC6455的WebSocket通信，WebSocket是实现客户端程序与远端主机进行
Qt WebSockets
双向通信的基于Web的协议
Qt Windows Extras
提供Windows平台相关的API
Qt XML
该模块不再维护了，应使用Qt Core中的QXmlStreamReader和QXmlStream Writer
Qt XML Patterns
提供对XPath、XQuery、XSLT和XML等的支持
Qt Charts
用于数据显示的二维图表组件
Qt Data Visualization
用于3D数据可视化显示的界面组件
Qt Virtual Keyboard
实现不同输入法的虚拟键盘框架

```

#### QString

每个字符是一个16位的Qchar。

常用函数：

* `append()`
* `prepend()`在前面追加
* `toUpper`、`toLower`
* `count(),size(),length()`三个等价
* `trimmed`去首尾空格，`simplified`去掉首尾空格，且中间连续的空格用一个空格代替
* `isNull`判断其是否未赋值，`isEmpty()`判断其是否为`\0`或未赋值
* `section(seq,start,end)`提取以seq为分隔符，从start-end的字符串。

#### 界面组件

##### 常用

使用最多的是`QLabel`（用于显示字符串）和`QLineEdit`（用于显示和输入字符串）。

​	四个设置格式的函数：

* `str = QString::number(total,'f',2)`，还支持设置进制
* `str = QString::asprintf("%.2f",total)`
* `str = str.setNum(total,'f',2)`支持设置数值进制
* `str = str.sprintf("%.2f",total)`

---

QSpinBox用于整数的显示和输入，特殊的可以设置进制

QDoubleSpinBox用于浮点数的显示和输入，特殊的可以设置小数位数

---

QSlider：滑动条，滑动设置数值

QScrollBar：卷滚条，与滑动条类似还可以用于卷滚区域

QProgressBar：进度条

QDial：表盘式，通过转动表针获得输入值

QLCDNumber：模仿LCD数字的显示组件，可以显示整数或浮点数

---

###### QLabel显示图片

为其设置一个`QPixmap`显示图片，可进行缩放显示，通过`QLabel`的`setPixmap(pixmap)`函数设置图片。

`qpixmap.load(filename)`加载图片

```c++
需要有一个图片缩放比例的变量
    pixRatio = 1
// 适应高度显示图片
int H = ui->scrollArea->height();
int realH = curPixmap.height(); // 真实高度
pixRatio = float(H)/realH;
Qpixmap pix = curPixmap.scaledToHeight(H-30) // 图片缩放到指定高度;
ui->qlabel->setPixmap(pix);
// 放大显示
pixRatio = pixRatio*1.2;
int w = pixRatio*curPixmap.width();
int h = pixRatio*curPixmap.height();
QPixmap pix = curPixmap.scaled(w,h);
ui->qlabel->setPixmap(pix);

// 实际大小显示
```



##### 时间日期：

* `QTime`仅显示时间
* `QDate`仅显示日期
* `QDateTime`
* `QTimeEdit`
* `QDateEdit`
* `QDateTimeEdit`
* `QCalenderWidget`

---

**定时器**：用来处理周期性事件的一个对象`QTimer`

```c++
QTimer* timer = new QTimer(this);
timer->stop();
timer->setInterval(毫秒); // 设置定时周期
其发出的信号为：timeout();
// 需要编写槽函数接收。
```

---

**计时器**：

```c++
QTime time;
time.start(); // 开始
time.stop(); // 停止
```

##### QComboBox

下拉列表框组件类，提供下拉列表供选择，也可以用作QLineEdit输入，除了显示下拉列表外，每个列表项还可以关联一个`QVariant`类型的变量，存储一些不可见数据

##### QPlainTextEdit

多行普通文本编辑器。其文字内容以`QTextDocument`类型存储，可以使用对象的`document()`获得其指针。其包含函数，支持每次读取一行，读到回车结尾。

**右键菜单设置：**编写槽函数`customContextMenuRequested()`

```c++
// 槽函数内容如下：
QMenu* menu = ui->plainTextEdit->createStandardContextMenu();
menu->exec(pos);
```



##### QTextEdit

带格式多行文本编辑器

##### QScrollArea

子窗口大于其时进行滚动

##### QFileDialog

`QString dir = QFileDialog::getExistingDirectory()`在界面上弹出一个对话框输入文件名，以此返回

`QFileDialog::getOpenFileNames()`获取文件列表

##### QToolButton

关联方式

* 可以使用`setDefaultAction()`与某个action关联。

  

`setMenu()`可以再点击按钮后，出现一个菜单

~~~c++
QMenu *menu = new QMenu(this);
menu.addAction(ui->actSelALL);
ui->btn->setPopupMode(QToolButton::MenuButtonPopup); // 设置样式
ui->btn->setMenu(menu);
~~~



##### QToolBox

组件上右击，可以添加分组。每组都可以包含多个`QToolButton`

##### QSplitter

可以使用该组件分割界面，填充满整个工作区使用

`setCentralWidger(ui->splitter)`;

##### QListWidget

QT中用于项处理组件有两类：

* `Item Views`:基于模型/视图

  * `QListView`
  * `QTreeView`
  * `QTableView`
  * `QColumnView`
  * 等

* `Item Widgets`：直接将数据存储在每一个项中，如`QTreeWidget`存储在每个节点中。**每个从QWidget继承来的类都有信号customContextMenuRequested()，在鼠标右键时发射，我们在槽函数中创建菜单，最后使用exec(pos)执行**

  * `QxxxWidget`

  * `QTabWidget`：一个多页的容器类组件。

  * `QListWidget`：存储多个项的列表组件，比较重要的是其`flags`标记，`item->setFlags(Qt:ItemIsSelectable|Qt:ItemIsEditable)`，一次设置多个标记

    ```c++
    Selectable:项是否可被选择，对应枚举值Qt:ItemIsSelectable.
    Editable:项是否可被编辑，对应枚举值Qt:ItemIsEditable。
    DragEnabled:.项是否可以被拖动，对应枚举值Qt:ItemIsDragEnabled。
    DropEnabled:项是否可以接收拖放的项，对应枚举值Qt:ItemIsDropEnabled。.
    UserCheckable:项是否可以被复选，若为true,项前面出现一个CheckBox,对应枚举值
    Qt:ItemIsUserCheckable.
    Enabled:项是否被使能，对应枚举值Qt:ItemIsEnabled。
    Tristate:是否允许Check的第三种状态，若为false,则只有checked和unChecked两种状
    态，对应枚举值Qt:ItemIsAutoTristate.
    ```

  

  

##### QTreeWidget

**目录树组件**。每个节点设置一个自定义类型。

需要定义两个自定义类型

~~~c++
enum
treeItemType (itTopItem=1001,itGroupItem,itImageItem); // 创建的结点类型，自定义类型必须大于1000
enum
treeColNum{colItem=0,colItemType=l};//每个目录树列的编号，这里创建了两列，可以显示两列内容
// 初始化内容如下
QTreewidgetItem*item=new QTreewidgetItem(MainWindow:itTopItem);
item->setIcon(MainWindow::colItem,icon);//第1列的图标
item->setText(MainWindow::colItem,"图片文件")；//第l列的文字
item->setText (MainWindow:colItemType,"type=itTopItem");//2
item->setFlags (Qt:ItemIsSelectable Qt:ItemIsUserCheckable Qt:ItemIsEnabled
Qt:ItemIsAutoTristate);
item->setCheckstate(colItem,Qt:Checked);
item->setData(Mainwindow:colItem,Qt:UserRole,QVariant (datastr)); // 为某一列设置一个角色数据，
ui->treeFiles->addTopLevelItem(item);//添加顶层节点，每个树中只能添加一个顶层节点
~~~

* `addChild(item)`在目录下新建一个对象

##### QDockWidget

**停靠区域组件，这个停靠区域类似于显示项目的那种**。可以在QMainWindow窗口停靠，或在桌面最上层浮动的界面组件。

`setAllowedAreas(Qt::DockWidgetAreas枚举类型)`设置允许停靠的区域

`setFeatures`，值为`QDockWidget::DockWidgetFeature`的组合值

```c++
QDock Widget:Dock WidgetClosable:停靠区可关闭
QDock Widget:Dock WidgetMovable:停靠区可移动。
QDock Widget:Dock WidgetFloatable:停靠区可浮动。
QDock Widget:Dock Widget VerticalTitleBar:在停靠区左侧显示垂直标题栏。
QDock Widget::AllDock WidgetFeatures:使用以上所有特征。
QDock Widget:NoDock WidgetFeatures::不能停靠、移动和关闭。
```

##### QTableWidget

~~~c++
// 需要两个枚举类自定义
enum CellType{
    // 提供字段列表，需要为每列提供一个字段，初始值一般从1001开始
}

enum FieldColNul{
    // 提供上面对应字段的列号，从0开始。
}
ui->table->setHorizontalHeaderLabels(headerTexts ); // 一次性设置表头，参数是一个列表
// 若还需要精细控制每个头
使用QTableWidgetItem，结合for遍历头列表
// 控制headerItem...代码块 = new QTableWidgetItem(headerTexts.at(i));
ui->table->setHorizontalHeaderItem(i,headerItem);

// 对于每个需要使用的表格都要new QTableWidgetItem对象
ui->table->setItem(行号,类::列字段,item);
~~~

* 自动调节行高和列宽：`resize...()`
* 设置表格内容编辑模式：`ui->table->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked)`双击或获取焦点后单击，进入编辑模式
* 设置行表头、列表头是否显示：`table->horizontalHeader()/verticalHeader()->setVisible(checked)`设置其可见
* `table->setAlternatingRowColors(checked)`设置间隔行底色
* `table->setSelectionBehaver(QAbstractItemView::SelectItems/SelectRows)`设置选择模式为单元格选择还是行选择

#### 角色数据

**对于role角色,常用的值有:**

- **Qt::DisplayRole**        0      以文本方式显示数据(QString)
- **Qt::DecorationRole**    1     将数据作为图标来装饰(QIcon,QPixmap)
- **Qt::EditRole**           2      可编辑的数据信息显示(QString)
- **Qt::ToolTipRole**        3      作为工具提示显示(QString)
- **Qt::StatusTipRole**      4     作为状态栏中显示的数据(QString)
- **Qt::WhatsThisRole**     5     作为帮助信息栏中显示的数据(QString)
- **Qt::FontRole**           6     设置字体(QFont)
- **Qt::TextAlignmentRole**  7    设置模型数据的文本对齐(Qt::AlignmentFlag)
- **Qt::BackgroundRole**   8     设置模型数据的背景色(QBrush)
- **Qt::ForegroundRole**   9     设置模型数据的前景色,比如字体(QBrush)
- **Qt::UserRole 自定义数据**

#### 模型和视图

![image-20230410151627268](https://cdn.jsdelivr.net/gh/xxn-1/image/img/202304101516561.png)

常用的QT已经定义好的模型类：

* `QStringListModel`：处理字符串列表数据的模型类

* `QStandardItemModel`：基于项数据的模型类，类型可以为任何。**搭配`QItemSelectionModel`可以提供单元格的行列等信息**

  ```c++
  theModel = new QStandardItemModel(行数，列数，this);
  theSelection = new QItemSelectionModel(theModel);
  ui->table->setModel(theModel); // 设置模型
  ui->table->setSelectionModel(theSelection) // 设置选择模型
  // setSelectionMode()设置选择模式，支持多选按住ctrl，单选等等。
      // 没写完
  ```

  

* `QFileSystemModel`：文件系统的数据模型类，需要使用`setRootPath()`设置根目录，可以直接设置为`QDir::currentPath()`

* `QSortFilterProxyModel`：与其他数据模型结合，提供排序和过滤功能的模型类

* `QSqlQueryModel`：数据库sql查询结果的模型类

* `QSqlTableModel`：数据库的一个数据表的模型类

* `QSqlRelationalTableModel`：关系型数据库的数据模型类

**自定义模型类：**继承以下类之一

* `QAbstractItemModel`
* `QAbstractListModel`
* `QAstractTableModel`

QT提供的视图组件如下：**组件通过setModel()直接显示数据**

* `QListView`：显示单列的列表数据，适用于一维数据
* `QTreeView`：显示树状结构数据
* `QTableView`表格数据，适用于二维
* `QColumnView`多个QListView显示多维数据
* `QHeaderView`提供行表头或列表头的视图组件

如：`QFileSystemModel`和`QTreeView`结合可以用目录树的形式显示本机的文件系统。

##### 代理

就是在视图组件上为编辑数据提供编辑器。就是为某个表格设置一个组件来编辑数据。支持自定义代理类

推荐继承基类：**`QStyledItemDelegate`**。必须实现以下四个功能

```c++
1. createEditor(); // 创建用于编辑的widget，如一个QSpinBox组件。创建好后返回对象即可
2. setEditorData(); // 从模型数据获取数据，供widget编辑，spinBox->setValue(value -- 从widget获取)，当双击一个单元格时会自动调用该函数
3. setModelData(); // 将widget上数据更新到数据模型，完成编辑时会自动调用
spinBox->interpretText(); // 该函数将字符串计算其表达式。最后使用model->setData(index,value,Qt::EditRole)
4. updateEditorGeometry(); // 给widget组件设置一个合适的大小
editor->setGeometry(option.rect)；直接使用此句即可
// 需要创建新的文件
```

**代理类的使用：**

~~~c++
使用时只需要创建变量即可，不用new。
QWComboBoxDelegate d;
而且只需要初始化时设置，会应用到一整列。
ui->table->setItemDelegateForColumn(0,&d);//为第一列设置
~~~



##### 模型索引

数据模型基本形式是用行和列定义的表格数据，这并不意味底层数据是用二维数组存储，只是方便组件交互。

要使用索引，**需要提供行号、列号、父项的模型索引**，一般**列表和表格**父项的索引模型只需要写`QModelIndex()`即可，即`QModelIndex index = model->index(1,2,QModelIndex())`。若是树型，根节点是`QModelIndex()`，若是下面的节点，假如B索引父节点索引为A，则提供A的。



#### 流

* `QTextStream`

#### 对话框

常常搭配：**`QCoreApplication::applicationDirPath()`**获取应用程序可执行文件所在目录。

QT已经预定义的静态函数形式的对话框：

* `QFileDialog`类

  * `getOpenFileName()`选择打开一个文件
  * `getOpenFileNames()`打开多个文件
  * `getSaveFileName()`选择保存一个文件，可能会覆盖，**覆盖后的删除操作不会实质执行，需要自己编码实现**
  * `getExistingDirectory()`选择一个已有的目录，还应传递一个选项`QFileDialog::ShowDirsOnly`表示对话框中只显示目录
  * `getOpenFileUrl()`选择打开一个文件，可选择远程网络文件

* `QcolorDialog`

  * `getColor()`选择颜色

* `QFontDialog`

  * `getFont()`选择字体

* `QInputDialog`

  * `getText()`输入单行文字，编辑模式是枚举`QLineEdit::Password`
  * `getInt()`输入整数
  * `getDouble()`输入浮点数
  * `getItem()`从下拉列表框中选择
  * `getMultiLineText()`输入多行字符串

* `QMessageBox`

  可以设置按钮：`QMessageBox::Yes|No|Cancel|NoButton`

  * `information()`信息提示对话框
  * `question()`询问并获取是否确认的对话框
  * `warning()`警告对话框
  * `critical()`错误消息提示对话框
  * `about()`设置自定义消息的关于对话框
  * `aboutQt()`关于QT对话框

##### 自定义对话框

创建新文件`->`选择`Qt Designer Form Class`创建可视化设计的对话框类，选择窗口模板为`Dialog without Buttons`。在其中自己放置组件，可视化添加槽函数，**接收者为对话窗本身。如OK按钮，调用对话窗的`accept()`槽函数，会使其对话框本身返回`QDialog::Accept`**

要弹出对话框时使用：`dialog->exec()`**以模态方式显示，即弹出对话框后不能点击原窗口**，`dialog->show()`非模态显示。

```c
dialog->setWindowFlags(dialog->windowFlags|Qt:;MSWindowsFixedSizeDialogHint); // 对话框固定大小

最后对话框需要手动删除：
delete dialog;
dialog->setAttribute(Qt::WA_DeleteOnClose()); // 非模态下要设置此属性，当关闭对话框后自动析构。
```

#### 事件

继承的基类已经定义了一些事件，我们只需要重写即可。

#### 多窗口

常用的可继承窗体类：

* `QWidget`没有父容器可作为独立窗口，否则作为容器内部组件
* `QDialog`设计对话框
* `QMainWindow`设计带菜单栏、工具栏、状态栏的主窗口
* `QSplashScreen`没有边框
* `QMdiSubWindow`用于多文档应用程序
* `QDesktopWidget`具有多显卡、多显示器的系统具有多个桌面，这个类提供用户桌面信息
* `QWindow`通过底层的窗口系统表示一个窗口的类，一般作为一个父容器的嵌入式窗体，不作为独立窗体。

##### 窗口特性

* `setAttribute()`设置显示特性

  ```c++
  Qt:WA AcceptDrops
  允许窗体接收拖放来的组件
  Qt:WA DeleteOnClose
  窗体关闭时删除自己，释放内存
  Qt::WA Hover
  鼠标进入或移出窗体时产生paint事件
  Qt:WA AcceptTouchEvents
  窗体是否接受触屏事件
  ```

  

* `setWindowFlags()`设置运行特性

  ```c++
  这是QWidget类的缺省类型。这种类型的窗体，如果它有父窗体，就作为父窗
  Qt::Widget
  体的子窗体：否则就作为一个独立的窗口
  Qt:Window
  表明这个窗体是一个窗口，通常具有窗口的边框、标题栏，而不管它是否有父窗体
  Qt::Dialog
  表明这个窗体是一个窗口，并且要显示为对话框（例如在标题栏没有最小化、
  最大化按钮)。这是QDialog类的缺省类型
  Qt::Popup
  表明这个窗体是用作弹出式菜单的窗体
  表明这个窗体是工具窗体，具有更小的标题栏和关闭按钮，通常作为工具栏的
  Qt:Tool
  窗体
  Qt:ToolTip
  表明这是用于Tooltip消息提示的窗体
  Qt:SplashScreen
  表明窗体是splash屏幕，是QSplashScreen类的缺省类型
  Qt::Desktop
  表明窗体是桌面，这是QDesktop Widget类的类型
  Qt:Sub Window
  表明窗体是子窗体，例如QMdiSub Window就是这种类型
  控制窗体显示效果的常量
  Qt:MS WindowsFixedSizeDialogHint
  在Windows平台上，使窗口具有更窄的边框，用于固定大小的对话框
  Ot:Frameless WindowHint
  创建无边框窗口
  定制窗体外观的常量，要定义窗体外观，需要先设置Qt:Customize WindowHint
  Qt:Customize WindowHint
  关闭缺省的窗口标题栏
  Qt:WindowTitleHint
  窗口有标题栏
  Qt:WindowSystemMenuHint
  有窗口系统菜单
  Qt:WindowMinimizeButtonHint
  有最小化按钮
  Qt:WindowMaximizeButtonHint
  有最大化按钮
  Qt:WindowMinMaxButtonsHint
  有最小化、最大化按钮
  Qt:WindowCloseButtonHint
  有关闭按钮
  Qt::WindowContextHelpButtonHint
  有上下文帮助按钮
  Qt:WindowStaysOnTopHint
  窗口总是处于最上层
  Qt:WindowStaysOnBottomHint
  窗口总是处于最下层
  Qt:Window TransparentForInput
  窗口只作为输出，不接受输入
  ```

* `setWindowState()`设置窗口处于最大化或最小化等状态

  ```c
  Qt:WindowNoState
  正常状态
  Qt:WindowMinimized
  窗口最小化
  Qt:WindowMaximized
  窗口最大化
  Qt:WindowFullScreen
  窗口填充整个屏幕，而且没有边框
  Ot:WindowActive
  变为活动的窗口，例如可以接收键盘输入
  ```

* `setWindowModality()`设置窗口的模态

  ```c
  Qt:NonModal
  无模态，不会阻止其他窗口的输入
  Qt:WindowModal
  窗口对于其父窗口、所有的上级父窗口都是模态的
  Qt:ApplicationModal
  窗口对整个应用程序是模态的，阻止所有窗口的输入
  ```

* `setWindowOpacity()`设置窗口的透明度

##### TabWidget

要为其两个信号编写槽函数

~~~c
1. tabCloseRequested() // 传入的参数为索引，tabWidget->widget(index)获取widget对象，调用widget.close()关闭。
2. currentChanged()  // 关闭一个对象后，会启用该函数，若count()<0，隐藏tabWidget
~~~



---



**以下是嵌入式窗口**

该组件是带标签的窗口，其中可以存储多个子窗口，没有子窗口时一般使用`tabW->setVisible(false)`隐藏，**`tabW->tabsClosable`设置每个子界面窗口都会出现关闭按钮**，初始化时要设置`setCentralWidget(ui->tabWidget)`

**使用`addTab`添加一个新界面**

---

**以下是独立式窗口**

创建`widget`对象时，**主要不要向其传入父窗口(this)，空对象即可**

并且需要通过`对象.show()`展示

##### MDI多窗口文档

// 没学

#### 文件系统

读写方式

1. 通过`QFile`的`IODevice`读写功能直接进行读写

2. 利用`QFile`和`QTextStream`结合，通过流的方式进行

   ```c
   QTextStream stream(&file);
   stream.setAutoDetectUnicode(true);//自动检测编码
   
   ```

   

##### 二进制文件读写

QFile结合QDataStream

QT有两种二进制文件格式：

1. `.dat`标准二进制文件格式，通用
   * `setByteOrder()`设置大小端
   * `writeRawData()`写入qint,qreal时都使用
   * `writeBytes()`写入qstring，实际写入的字节数为`4+string长度`
2. `.stm`QT预定义编码格式，仅通过QT读写，在用`QDataStream`前，通过其对象的`setVersion(QDataStream::QT_版本)`，设置版本号，我们要写入对象前，需要定义变量类型确认其bit位数如`qint16 x = ....value()`，在将该变量写入。这样方便读入

##### 文件目录操作相关类

* `QCoreApplication`提取应用程序路径，程序名等消息
* `QFile`文件操作
* `QFileInfo`提取文件的信息
* `QDir`操作目录
* `QTemporaryDir`,`QTemporaryFile`创建临时目录和临时文件
* `QFileSystemWatcher`文件和目录监听类，监听器修改变化

#### 绘图

绘图系统基于QPainter、QPaintDevice使用Painter绘图的二维界面、QPaintEngine提供在不同设备绘图的接口 

一般绘图设备包括：`QWidght`、`QPixmap`、`QImage`，这些绘图设备为`QPainter`提供了“画布”。**要进行绘图，方法为：重写父类的paintEvent()事件，创建QPainter对象获取绘图设备接口就可以在画布上绘图了**

~~~c
void 类::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // 绘图
}

~~~

绘图时，**坐标系统为，窗口左上角为(0,0)，向右为x轴，向下为y轴。**

绘图的三大属性：

1. `pen`：QPen，控制线条

2. `brush`：QBrush，控制填充

   渐变填充：`QRadialGradient`继承了`QBrush`

3. `font`：QFont

##### QPainter

画图包含很多样式，如：`QRect`等

最后使用painter.drawRect(rect);

绘制基本图形：

* `drawArc`绘制弧形

  ```c
  QRect rect (W/4,H/4,W/2,H/2);
  int startAngle 90 16;
  //起始90°
  int spanAngle=90*16;//旋转90°
  painter.drawArc(rect,startAngle,spanAngle);
  ```

  

* `drawChord`弦

  ```c
  QRect rect (W/4,H/4,W/2,H/2);
  int startAngle 90 16;
  //起始90°
  int spanAngle=90*16;//旋转90°
  painter.drawArc(rect,startAngle,spanAngle);
  ```

  

* `drawConvexPolygon`凸多边形

  ```c
  OPoint points[4]={
  QPoint (5*W/12,H/4),
  QPoint(3*W/4,5*H/12),
  QPoint(5*W/12,3*H/4),
  QPoint (W/4,5*H/12),
  )
  painter.drawConvexPolygon (points,4);
  ```

  

* `drawEllipse`椭圆

* `drawImage`图片，QImage

* `drawLine`线

  ```c
  QLine Line (W/4,H/4,W/2,H/2)
  painter.drawLine(Line);
  ```

  

* `drawLines`画一批直线

  ```c
  QRect
  rect (W/4,H/4,W/2,H/2);
  OVector<QLine>Lines;
  Lines.append (QLine(rect.topLeft ()rect.bottomRight ()))
  Lines.append (QLine (rect.topRight ()rect.bottomLeft ()))
  Lines.append (QLine(rect.topLeft ()rect.bottomLeft ()))
  Lines.append (QLine (rect.topRight ()rect.bottomRight ()))
  oainter.drawLines(Lines);
  ```

  

* `drawPath`绘制定义的路线

* `drawPie`扇形

* `drawPixmap`绘制pixmap图片，QPixmap

* `drawPoint`画一个点，QPoint

* `drawPoints`

* `drawPolygon`画多边形，最后一个点会和第一个点相连

* `drawPolyline`多点连接的线，最后一个点不和第一个点相连

* `drawRect`

* `drawRounded`圆角矩形

* `drawText`

* `eraseRect`擦除某个矩形区域

* `fillPath`填充某个QPainterPath定义的绘图路径

* `fillRect`填充一个矩形



###### 坐标变换

**坐标变换**

---

**视图和窗口**

##### 基于Graphics View的绘图

与Painter不同的是，此绘图每个图形元件是可选择、可拖放和修改的，架构主要有三部分组成：**场景、视图、图形项**

**场景**：是不可见的。可以管理图形项的容器，场景还有背景层和前景层。

**视图：**用于显示场景中的内容，一个场景可以有几个试图

**图形项**：基类是`QGraphicsItem`，已经定义了一些`QGraphicsXXXItem`

###### 坐标系统

三部分都包含相应的自己的坐标系。

* 图形项坐标：一般其内函数都使用自己的局部坐标，通常以其为原点(0,0)。图形项的位置是其中心在父图形中的坐标。图形项进行坐标变换时，连同其子图形都会进行变换。
* 视图坐标：窗口界面的物理坐标，**单位是像素。**左上角坐标总是(0,0)。
* 场景坐标：

###### 相关的类



#### QtCharts图表

必须先在pro文件添加，Qt+=charts

在需要使用QtCharts的类中添加：

```c
#include <QtCharts>
using namespace QtCharts;
```

...

#### 三维显示Data Visualization



#### 数据库

#### 自定义插件和库

#### 多线程

一个QThread类的对象管理一个线程，重写其run()。

run()函数中调用exit()或quit()可以结束线程事件循环，或在主线程调用terminate()强制结束

线程可以使用信号和槽，包含`started()`和`finished()`信号，前者在线程开始run前进行，后者在线程结束前进行。

##### 线程同步

###### 基于互斥量

`QMutex`、`QMutexLocker`

###### 基于QReadWriteLock

...

###### 基于QWaitCondition的线程同步

和`QMutex`结合，可以在一个线程满足一定条件时同时其他线程

```c++
void othreadProducer::run()
{
m stop=false;
seq=0;
qsrand(Qtime::currentTime().msec());//随机数初始化
    while(!m stop)//循环主体
    {
        mutex.lock ()
        dicevalue=grand();//获取随机数
        dicevalue=(dicevalue号6)+1；
        seq++;
        mutex.unlock();
        newdataAvailable.wakeAl1();//唤醒所有线程，有新数据了
        msleep(500);//线程休眠
    }
}
void othreadConsumer::run()
	m_stop=false;
    while(!m stop){//循环主体
    mutex.lock ();//一定要先锁定
    newdataAvailable,wait(&mutex);//先解锁mutex,使其他线程可以使用mutex,被唤醒后再次锁定mutex
    emit newvalue (seq,dicevalue);
    mutex.unlock();}
}
```

###### 基于信号量

QSemaphore

```c
QSemaphore是实现信号量功能的类，它提供以下几个基本的函数：
acquire(intn)尝试获得n个资源。如果没有这么多资源，线程将阻塞直到有n个资源可用：
release(intn)释放n个资源，如果信号量的资源已全部可用之后再release(),就可以创建更多的资源，增加可用资源的个数
int available()返回当前信号量可用的资源个数，这个数永远不可能为负数，如果为0，就说明当前没有资源可用：
bool tryAcquire(intn=I),尝试获取n个资源，不成功时不阻塞线程。
```

```c
const int BufferSize = 8;
int buffer1[BufferSize];
int buffer2[BufferSize];
int curBuf=1; //当前正在写入的Buffer

int bufNo=0; //采集的缓冲区序号

quint8   counter=0;//数据生成器

QSemaphore emptyBufs(2);//信号量：空的缓冲区个数，初始资源个数为2
QSemaphore fullBufs; //满的缓冲区个数，初始资源为0
void QThreadDAQ::run()
{
    m_stop=false;//启动线程时令m_stop=false
    bufNo=0;//缓冲区序号
    curBuf=1; //当前写入使用的缓冲区
    counter=0;//数据生成器

    int n=emptyBufs.available();
    if (n<2)  //保证 线程启动时emptyBufs.available==2
      emptyBufs.release(2-n);

    while(!m_stop)//循环主体
    {
        emptyBufs.acquire();//获取一个空的缓冲区
        for(int i=0;i<BufferSize;i++) //产生一个缓冲区的数据
        {
            if (curBuf==1)
                buffer1[i]=counter; //向缓冲区写入数据
            else
                buffer2[i]=counter;
            counter++; //模拟数据采集卡产生数据

            msleep(50); //每50ms产生一个数
        }

        bufNo++;//缓冲区序号
        if (curBuf==1) // 切换当前写入缓冲区
          curBuf=2;
        else
          curBuf=1;

        fullBufs.release(); //有了一个满的缓冲区,available==1
    }
    quit();
}

void QThreadShow::run()
{
    m_stop=false;//启动线程时令m_stop=false

    int n=fullBufs.available();
    if (n>0)
       fullBufs.acquire(n); //将fullBufs可用资源个数初始化为0

    while(!m_stop)//循环主体
    {
        fullBufs.acquire(); //等待有缓冲区满,当fullBufs.available==0阻塞

        int bufferData[BufferSize];
        int seq=bufNo;

        if(curBuf==1) //当前在写入的缓冲区是1，那么满的缓冲区是2
            for (int i=0;i<BufferSize;i++)
               bufferData[i]=buffer2[i]; //快速拷贝缓冲区数据
        else
            for (int i=0;i<BufferSize;i++)
               bufferData[i]=buffer1[i];

        emptyBufs.release();//释放一个空缓冲区
        emit    newValue(bufferData,BufferSize,seq);//给主线程传递数据
    }
    quit();
}
```



#### 网络编程

添加`Qt += network`

提供了各种网络类，常见的：

1. TCP通信：`QTcpSocket`和`QTcpServer`
2. UDP通信：`QUdpSocket`
3. 实现HTTP、FTP：`QNetworkRequest`、`QNetworkReply`、`QNetworkAccessManaget`
4. 等

**查询主机MAC以及IP等信息：**

* `QHostInfo`类：

  ```c++
  // 公共函数
  QList<QHostAddress>addresses()
  返回与hostName()主机关联的IP地址列表
  
  HostInfoError error()
  如果主机查找失败，返回失败类型
  
  QString errorStringO
  如果主机查找失败，返回错误描述字符串
  QString hostName()
  返回通过IP查找的主机的名称
  int lookupld()
  返回本次查找的D
  // 静态函数
  void abortHostLookup(int id)
  中断主机查找
  QHostInfo fromName(QString &name)
  返回指定的主机名的P地址
  
  QString localDomainNameO
  返回本机DNS域名
  QString localHostName()
  返回本机主机名
  int lookupHost(QString &name,QObject *receiver.char *member)
  以异步方式根据主机名查找主机的P地址，并返回一个表示本次查找的ID,可用于abortHostLookupO
  ```

  

* `QNetworkInterface`类

  ```c
  // 公共函数
  QList<QNetworkAddressEntry>addressEntries()
  返回该网络接口（包括子网掩码和广播地址）的iP地址列表
  QString hardwareAddress(
  返回该接口的低级硬件地址，以太网里就是MAC地址
  QString humanReadableName()
  返回可以读懂的接口名称，如果名称不确定，得到的就是name()函数的返回值
  bool isValid()如果接口信息有效就返回true
  QString name()返回网络接口名称
  
  // 静态函数
  QList<QHostAddress>allAddresses()
  返回主机上所有IP地址的列表
  QList<QNetworkInterface>allInterfaces()
  返回主机上所有接口的网络列表
  ```

##### TCP通信

服务器端程序首先需要用QTcpServer:listen()开始服务器端监听，初始化时要设置连接时信号，断开时信号的槽函数，可以指定监听的IP地址和端口，一般一个服务程序只监听某个端口的网络连接。当有新的客户端接入时，QTcpServer内部的incomingConnection()函数会创建一个与客户端连接的QTcpSocket对象，然后发射信号newConnection()。**在newConnection(信号的槽函数中，可以用nextPendingConnection()接受客户端的连接**，然后使用QTcpSocket与客户端通信。所以在客户端与服务器建立TCP连接后，具体的数据通信是通过QTcpSocket完成的。QTepSocket类提供了TCP协议的接口，可以用QTcpSocket类实现标准的网络通信协议如POP3、SMTP和NNTP,也可以设计自定义协议。

~~~c
// 一般在槽函数中需要把链接进来的socket添加connect
void MainWindow::onNewConnection()
{
//    ui->plainTextEdit->appendPlainText("有新连接");
    tcpSocket = tcpServer->nextPendingConnection(); //创建socket

    connect(tcpSocket, SIGNAL(connected()),
            this, SLOT(onClientConnected()));
    onClientConnected();//

    connect(tcpSocket, SIGNAL(disconnected()),
            this, SLOT(onClientDisconnected()));

    connect(tcpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this,SLOT(onSocketStateChange(QAbstractSocket::SocketState)));
    onSocketStateChange(tcpSocket->state());

    connect(tcpSocket,SIGNAL(readyRead()),
            }  
~~~



TCPSOCKET继承了`QAstractSocket`，客户端通过socket与服务器连接，信号`readyRead()`缓冲区有数据未读取会发送此信号

![image-20230411145012389](https://cdn.jsdelivr.net/gh/xxn-1/image/img/202304111450980.png)

**SOCKET状态**：包含在`QAbstractSocket`中。

##### UDP通信

以数据报传送，而不是连续的数据流。**接收数据报时，先使用bind()绑定一个端口**

```c
bool bind(quint16 port =0)
为UDP通信绑定一个端口
qint64 writeDatagram(QByteArray &datagram,
向目标地址和端口的UDP客户端发送数据报，返回成功
QHostAddress &host,quint16 port)
发送的字节数
bool hasPendingDatagrams()
当至少有一个数据报需要读取时，返回true
qint64 pendingDatagramSize(
返回第一个待读取的数据报的大小
qint64 readDatagram(char *data,qint64 maxSize)
读取一个数据报，返回成功读取的数据报的字节数
bool joinMulticastGroup(QHostAddress &groupAddress)
加入一个多播组
bool
leaveMulticastGroup(OHostAddress &groupAddress)
离开一个多播组
```



* 单播

* 广播

* 组播：`udpsocket->setSocketOption(QAbstractSocket::MulticastTtlOption,1);`MulticastTtlOption表示路由每跨一个路由减1，后者1表示多播只能在同1路由下局域网内传播。加入组播前，**必须绑定端口，语句为：`if(bind(QHostAddress::AnyIPv4,端口,QUdpSocket::ShareAddress)){joinMulticastGroup(多个地址);}`**

  ```v
  关于组播P地址，有如下的一些约定：
  224.0.0.0~224.0.0.255为预留的组播地址（永久组地址），地址224.0.0.0保留不做分配，
  其他地址供路由协议使用：
  224.0.1.0~224.0.1.255是公用组播地址，可以用于Internet:
  224.0.2.0~238.255.255.255为用户可用的组播地址（临时组地址），全网范围内有效；
  239.0.0.0~239.255.255.255为本地管理组播地址，仅在特定的本地范围内有效。
  所以，若是在家庭或办公室局域网内测试UDP组播功能，可以使用的组播地址范围是239.0.0.0~239.255.255.255。
  ```

##### HTTP网络

需要使用：

* `QNetWorkRequest`：支持HTTP、FTP和局部文件URLs的下载和上传
* `QNetworkAccessManager`上一个类发送网络请求后，由该类负责发送请求并进行创建响应，是一个管理类
* `QNetworkReply`表示网络响应

**可能要借助`QUrl`类，构建URL，`QUrl url = QUrl::fromUserInput(url字符串)`**

```c
// 请求时：
qnetworkReply = qNetworkAccessManager.get(QNetWorkRequest(url));
// 我们需要创建临时的空文件file
// 请求建立后会获得url的流，发送信号readyRead()。
在槽函数中，通过file.write(qnetworkReply.readAll())。这就完成了下载
读取过程会不断触发downloadProgress()信号。参数分别表示已读取字节数和总字节数。
// 下载完成后触发finished信号，在其中删除临时文件，并调用QDesktopServices::openUrl打开。
void MainWindow::on_finished()
{//网络响应结束
    QFileInfo fileInfo;
    fileInfo.setFile(downloadedFile->fileName());

    downloadedFile->close();
    delete downloadedFile;
    downloadedFile = Q_NULLPTR;

    reply->deleteLater(); //
    reply = Q_NULLPTR;

    if (ui->checkOpen->isChecked())//打开下载的文件
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));

    ui->btnDownload->setEnabled(true);
}
```



#### 多媒体

~~~
Qt多媒体模块提供了很多类，可以实现如下的一些功能：
访问原始音频设备进行输入或输出：
低延迟播放音效文件，如WAV文件：
使用播放列表播放压缩的音频和视频文件，如mp3、wmv等：
录制声音并且压制文件：
使用摄像头进行预览、拍照和视频录制：
音频文件解码到内存进行处理：
录制音频或视频时，访问其视频帧或音频缓冲区：
数字广播调谐和收听。
~~~







#### 辅助功能
