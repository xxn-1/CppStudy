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