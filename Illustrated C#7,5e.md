# C#图解教程 第5版


## 第 1 章 C#和.NET 框架

###  1.1　在.NET 之前　1

#### 1.1.1　20 世纪90 年代末的Windows编程　1

#### 1.1.2　下一代平台服务的目标　2

#### 1.2　.NET 时代　2

#### 1.2.1　.NET 框架的组成　2

#### 1.2.2　大大改进的编程环境　3

### 1.3　编译成CIL　5

### 1.4　编译成本机代码并执行　6

### 1.5　CLR　7

### 1.6　CLI　8

### 1.7　各种缩写　9

### 1.8　C#的演化　9

| 版本 | 焦点特性 |
| :--: | :------: |
| 7.0  | 值元组  模式匹配  |
| 6.0 | 语言增强 Roslny开源编译器 |
| 5.0 | 异步 |
| 4.0 | 命名参数 / 可选参数 |
| 3.0 | LINQ |
| 2.0 | 泛型 |
| 1.0 | C# |



### 1.9　C#和Windows 的演化　10

## 第 2 章 C#和.NET Core　11

#### 2.1　.NET 框架的背景　11

### 2.2　为什么选择.NET Core（和Xamarin）　11

#### 2.3　.NET Core 的目标　12

### 2.4　多平台支持　13

### 2.5　快速发展和升级　13

### 2.6　程序占用空间小、部署简单、版本问题少　13

### 2.7　开源社区支持　14

### 2.8　改进的应用程序性能　14

### 2.9　全新的开始　14

### 2.10　.NET Core 的发展　15

### 2.11　.NET 框架的未来　15

### 2.12　Xamarin 的适用之处　15

## 第3　章 C#编程概述　16

### 3.1　一个简单的C#程序　16

```c#
using System;

namespace C_5E
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }
}
```



### 3.2　标识符

> 变量名



### 3.3　关键字　18

> c#关键字:

| abstract | const | extern | int  | out  | short | typeof |
| :------: | :---: | :----: | :--: | :--: | :---: | :----: |
|          |       |        |      |      |       |        |
|          |       |        |      |      |       |        |
|          |       |        |      |      |       |        |
|          |       |        |      |      |       |        |
|          |       |        |      |      |       |        |

> 上下文关键字

| add    | ascending | async | await   | by      | descrending | dynamic |
| ------ | --------- | ----- | ------- | ------- | ----------- | ------- |
| equals | from      | get   | global  | group   | in          | into    |
| join   | let       | on    | orderby | partial | remove      | select  |
| set    | value     | var   | where   | yield   |             |         |





### 3.4　Main：程序的起始点　19

### 3.5　空白　19

### 3.6　语句　20

- 语句

- 简单语句

- 块

  ```c#
  {
  	int var1 = 5;
  	System.Console.WriteLine("The value of var1 is {0}",var1)
  }
  ```

  

### 3.7　从程序中输出文本　21

```
System.Console.Write("Hello world")
```



#### 3.7.1　Write　21

#### 3.7.2　WriteLine　21

#### 3.7.3　格式字符串　22

`System.Console.WriteLine("Hello {0}, {1}","Lisa","Lili");`

#### 3.7.4　多重标记和值

`System.Console.WriteLine("Hello {0},{1},{1},{0}","Lisa","Lili");`

#### 3.7.5　格式化数字字符串

`{index,alignment:format}`

- 对齐使用逗号

- 格式使用冒号

  

### 3.8　注释：为代码添加注解　28

#### 3.8.1　关于注释的更多内容　28

#### 3.8.2　文档注释　29

#### 3.8.3　注释类型总结　29

## 第4　章 类型、存储和变量　30

### 4.1　C#程序是一组类型声明

### 4.2　类型是一种模板

### 4.3　实例化类型

### 4.4　数据成员和函数成员

### 4.5　预定义类型

- 预定义简单类型

| 名称    | 含义 | 范围 | .Net框架类型 | 默认值       |
| ------- | ---- | ---- | ------------ | ------------ |
| sbyte   | 8    |      |              | System.Sbyte |
| byte    | 8    |      |              |              |
| short   | 16   |      |              |              |
| ushort  | 16   |      |              |              |
| int     | 32   |      |              |              |
| uint    | 32   |      |              |              |
| long    | 64   |      |              |              |
|         |      |      |              |              |
| float   |      |      |              |              |
| double  |      |      |              |              |
| bool    |      |      |              |              |
| char    |      |      |              |              |
| decimal |      |      |              |              |



- 预定义非简单类型

  | 名称    | 含义 | .Net框架类型  |
  | ------- | ---- | ------------- |
  | object  |      | System.Object |
  | string  |      | System.String |
  | dynamic |      |               |

  

### 4.6　用户定义类型

- class
- struct
- array
- enum
- delegate
- interface

### 4.7　栈和堆　35

#### 4.7.1　栈	LIFO (last-in  first-out)

#### 4.7.2　堆 

### 4.8　值类型和引用类型

#### 4.8.1　存储引用类型对象的成员

> ! 对于引用类型的任何对象,它所有的数据成员都存放在堆中,不管它是值类型还是引用类型

#### 4.8.2　C#类型的分类

- 预定义类型
- 用户定义类型

### 4.9　变量

- 局部变量
- 字段
- 参数
- 数组元素

#### 4.9.1　变量声明　39

#### 4.9.2　多变量声明

`int  v = 3,v2= 4,v3 =3;`

#### 4.9.3　使用变量的值

### 4.10　静态类型和dynamic 关键字　41

### 4.11　可空类型

## 第5　章 类的基本概念　43

### 5.1　类的概述

### 5.2　程序和类：一个简单的示例　44

### 5.3　声明类　45

### 5.4　类成员　45

#### 5.4.1　字段　45

#### 5.4.2　方法　47

### 5.5　创建变量和类的实例

```c#
new ClassName();

MyClass = new MyClass();
```



### 5.6　为数据分配内存　48

### 5.7　实例成员

- 实例成员
- 静态成员

### 5.8　访问修饰符

```c#
private
public
protected
internal
protected internal
```

- 不带访问修饰符 即为私有成员
- 私有成员只能从声明它的类的内部使用,其他类看不到

### 5.9　从类的内部访问成员　52

### 5.10　从类的外部访问成员　53

### 5.11　综合应用　54

## 第6　章 方法　56

### 6.1　方法的结构　56

### 6.2　方法体内部的代码执行　57

### 6.3　局部变量　58

#### 6.3.1　类型推断和var 关键字

> - 用于局部变量,不能用于成员变量(字段)
> - 必须有初始化值

#### 6.3.2　嵌套块中的局部变量

> 与c/c++ 不同,更深层级块中,不能再声明上层块已经有的变量名了.

### 6.4　局部常量

`const Type Name = Value`

### 6.5　控制流

```c#
if if ... else
switch
for while do  foreach
break continue goto return
```



### 6.6　方法调用

### 6.7　返回值

### 6.8　返回语句和void 方法

### 6.9　局部函数

### 6.10　参数

> 

#### 6.10.1　形参　67

> 形参是局部变量,它声明在方法的参数列表中,而不是在方法体中

#### 6.10.2　实参

### 6.11　值参数

### 6.12　引用参数

```
            void myMethod(ref int a)
            {
                
            }
```

> 引用参数的几个特征:
>
> - 不会在栈上为形参分配内存
> - 形参的参数名 将作为实参变量的别名,指向相同的内存地址
> - 使用引用参数时,必须在方法的声明和调用中 使用 `ref` 修饰符
> - 实参必须是变量

### 6.13　引用类型作为值参数和引用参数



### 6.14　输出参数

```C#
            MyOutMethod(out int a ,out MyClass aclass);
            aclass.val = 10000;
```

> C#7开始,无须提前声明out变量,可以直接在调用函数中直接声明变量

### 6.15　参数数组

> 一个参数列表里,只能有一个,而且排在最后



```c#
        static void ParamsFunc(params int[] inVals)
        {

        }
		ParamsFunc(1,3,4,5,6,7)
```



#### 6.15.1　方法调用

#### 6.15.2　将数组作为实参

### 6.16　参数类型总结

| 参数类型 | 修饰符 | 是否在声明时使用 | 是否在调用时使用 | 执行 |
| -------- | ------ | ---------------- | ---------------- | ---- |
| 值       |        |                  |                  |      |
| 引用     | ref    | 是               | 是               |      |
| 输出     | out    | 是               | 是               |      |
| 数组     | params | 是               | 是               |      |



### 6.17　ref 局部变量和ref 返回

- 创建别名

  ```c#
  ref int y  = ref x;
  ```

- ref 返回

  ```C#
  
          class Simple
          {
              private int score = 10;
  
  
              public ref int retvalue()
              {
                  return ref score;
              }
          }
          
          ...
  		ref int mf = ref sim.retvalue();
          mf = 1000;
  ```

  > ref return 只能指向原先就在调用域内的位置或者字段,不能指向方法内的局部变量
  >
  > ```c#
  > class B
  > {
  > 	long addValue(long a ,long b);
  > 	int addValue(long a ,long b);	// error 相同的签名
  > }
  > ```
  >
  > 

  

### 6.18　方法重载

> 方法名相同,但是签名不同

>  签名:
>
> - 方法的名称
> - 参数的数目
> - 参数的数据类型和顺序
> - 参数修饰符

返回类型不是签名的一部分

### 6.19　命名参数

```c#
        static void Fnc(int a, int b,int c)
        {
            Console.WriteLine($"{a} , {b},  {c}");
        }
        
        Fnc(b:1,c:10,a:3300);
```



### 6.20　可选参数

```C#
static void Func(int a,int b,int c = 1)
{
	...
}
```



### 6.21　栈帧

### 6.22　递归

## 第7　章 深入理解类

### 7.1　类成员

| 数据成员 | 函数成员          |
| -------- | ----------------- |
| 字段     | 方法              |
| 常量     | 属性              |
|          | 构造函数/析构函数 |
|          | 运算符            |
|          | 索引              |
|          | 事件              |



### 7.2　成员修饰符的顺序 

> ```c
> [特性] [修饰符] 核心声明
> ```



| 声明类型 | 特性 | 修饰符                      | 核心声明                    |
| -------- | ---- | --------------------------- | --------------------------- |
| 字段声明 |      | public/private/static/const | type fieldname              |
|          |      |                             |                             |
|          |      |                             |                             |
| 方法声明 |      | public/private/static       | [returntype] fun(paramlist) |





### 7.3　实例类成员

### 7.4　静态字段

### 7.5　从类的外部访问静态成员

#### 7.5.1　静态字段示例　99

#### 7.5.2　静态成员的生存期

### 7.6　静态函数成员

### 7.7　其他静态类成员类型

### 7.8　成员常量

```
        class X
        {
            public const int cv = 100;
        }
```



### 7.9　常量与静态量　103

### 7.10　属性

> - 类成员
> - 有类型
> - 可以赋值和取值
> - 不是字段,是成员函数
> - 不一定有他的内存空间
> - 执行代码
> - 访问器 set get

#### 7.10.1　属性声明和访问器

```C#
        class X
        {
            public const int cv = 100;

            public int v
            {
                set{
                   // v = value;
                }

                get {
                    return v + 100;  // stack overflow!!!!!!!!!!!!!!!!!!!!!
                }
            }
        }
```



#### 7.10.2　属性示例

#### 7.10.3　使用属性

#### 7.10.4　属性和关联字段

#### 7.10.5　执行其他计算

#### 7.10.6　只读和只写属性

> 访问器只有一种,

#### 7.10.7　属性与公有字段　109

#### 7.10.8　计算只读属性示例　109

#### 7.10.9　自动实现属性

```C#
        class X
        {
            public const int cv = 100;

            private int v_private;
            public int v
            {
                set{
                   v_private = value;
                }

                get {
                    return v_private + 100;
                }
            }

            public int xx{get; set;}
        }
```



#### 7.10.10　静态属性　111

- 不能访问实例成员,但是可以被实例成员访问
- 在类内部,可以仅使用名称来引用静态属性
- 类的外部,可以通过类名或者使用 using static 结构来引用静态属性

### 7.11　实例构造函数　112

#### 7.11.1　带参数的构造函数　113

#### 7.11.2　默认构造函数　114

- 如果类没有显示提供构造函数,则自动提供默认构造函数
- 没有参数,方法体为空
- 一旦提供了任何构造函数,将不会为其定义默认构造函数

### 7.12　静态构造函数　114

- 系统自动调用静态构造函数
  - 类实例创建之前
  - 类的任何静态成员被引用之前

### 7.13　对象初始化语句　116

### 7.14　析构函数　117

### 7.15　readonly 修饰符　117

```C#
        class Class1{
            static Class1()
            {
                Console.WriteLine("static constructor");
                static_int = 1;     // static readonly 只能在这里赋值
            }

             public Class1()
             {
                 Console.WriteLine("normal constructor");
                 NumOfSliders = 333;
                 
             }

             public int mem1;
             public int mem2;

             readonly double PI = 3.141593;
             readonly int NumOfSliders; 

             static readonly int static_int;
        }
```

- readonly vs const
  - const 字段在声明时,就需要初始化,设定之后就不能更改
  - readonly 可以在
    - 字段声明中
    - 类的任意构造函数中,但是 static readonly 的成员 必须在静态构造函数中完成
  - const 行为总是静态的,
    - readonly 可以是静态字段,也可以是 实例字段
    - readonly在内存中有存储位置

### 7.16　this 关键字　118

### 7.17　索引器　119

```

        class Class1{
            static Class1()
            {
                Console.WriteLine("static constructor");
                static_int = 1;     // static readonly 只能在这里赋值
            }

             public Class1()
             {
                 Console.WriteLine("normal constructor");
                 NumOfSliders = 333;
                 
             }

             public int mem1;
             public int mem2;

             readonly double PI = 3.141593;
             readonly int NumOfSliders; 

             static readonly int static_int;

             public const String Name = "zzfff";


             public int this[int index]
             {
                 get {return 1;}
                 //set{}
             }

             public String this[String index]
             {
                 get { return "";}
             }
        }
```



#### 7.17.1　什么是索引器　120

#### 7.17.2　索引器和属性　120

#### 7.17.3　声明索引器　121

#### 7.17.4　索引器的set 访问器　122

#### 7.17.5　索引器的get 访问器　122

#### 7.17.6　关于索引器的更多内容　123

#### 7.17.7　为Employee 示例声明索引器　123

#### 7.17.8　另一个索引器示例　124

#### 7.17.9　索引器重载　125

### 7.18　访问器的访问修饰符　126

### 7.19　分部类和分部类型　127

### 7.20　分部方法　128  TODO

partial

## 第8　章 类和继承　130

### 8.1　类继承　130

### 8.2　访问继承的成员　131

### 8.3　所有类都派生自object 类　132

### 8.4　屏蔽基类的成员　133

### 8.5　基类访问　135

### 8.6　使用基类的引用　135

#### 8.6.1　虚方法和覆写方法　137

#### 8.6.2　覆写标记为override 的方法　139

#### 8.6.3　覆盖其他成员类型　142

### 8.7　构造函数的执行　142

#### 8.7.1　构造函数初始化语句　144

#### 8.7.2　类访问修饰符　145

### 8.8　程序集间的继承　146

### 8.9　成员访问修饰符　148

#### 8.9.1　访问成员的区域　149

#### 8.9.2　公有成员的可访问性　150

#### 8.9.3　私有成员的可访问性　150

#### 8.9.4　受保护成员的可访问性　150

#### 8.9.5　内部成员的可访问性　151

#### 8.9.6　受保护内部成员的可访问性　151

#### 8.9.7　成员访问修饰符小结　152

### 8.10　抽象成员　153

### 8.11　抽象类　154

#### 8.11.1　抽象类和抽象方法的示例　154

#### 8.11.2　抽象类的另一个例子　155

### 8.12　密封类　156

### 8.13　静态类　156

- 类本身 标记 为 **static**
- 所有的成员必须是 静态的
- 可以有静态构造函数
- 隐式**密封**,不能被继承

### 8.14　扩展方法　157

```
static class ExtendData
{
	public static double Average(this DataCalss md, parameters...)
	{
		...
	}
}

md.Average()
```



### 8.15　命名约定　160

## 第9　章 表达式和运算符　162

### 9.1　表达式　162

### 9.2　字面量　163

#### 9.2.1　整数字面量　164

#### 9.2.2　实数字面量　165

#### 9.2.3　字符字面量　166

#### 9.2.4　字符串字面量　167

### 9.3　求值顺序　168

#### 9.3.1　优先级　168

#### 9.3.2　结合性　169

### 9.4　简单算术运算符　170

### 9.5　求余运算符　170

### 9.6　关系比较运算符和相等比较运算符　171

### 9.7　递增运算符和递减运算符　173

### 9.8　条件逻辑运算符　174

### 9.9　逻辑运算符　175

### 9.10　移位运算符　176

### 9.11　赋值运算符　178

### 9.12　条件运算符　179

### 9.13　一元算术运算符　181

### 9.14　用户定义的类型转换　181

### 9.15　运算符重载　184

#### 9.15.1　运算符重载的示例　185

#### 9.15.2　运算符重载的限制　186

### 9.16　typeof 运算符　189

### 9.17　nameof 运算符　190

### 9.18　其他运算符　191

## 第　10 章 语句　192

### 10.1　什么是语句　192

### 10.2　表达式语句　193

### 10.3　控制流语句　194

### 10.4　if 语句　194

### 10.5　if else 语句　195

### 10.6　while 循环　196

### 10.7　do 循环　197

### 10.8　for 循环　198

#### 10.8.1　for 语句中变量的作用域　200

#### 10.8.2　初始化和迭代表达式中的多表达式　200

### 10.9　switch 语句　201

#### 10.9.1　分支示例　203

#### 10.9.2　其他类型的模式表达式　203

#### 10.9.3　switch 语句的补充　205

#### 10.9.4　分支标签　206

### 10.10　跳转语句　207

### 10.11　break 语句　207

### 10.12　continue 语句　208

### 10.13　标签语句　209

#### 10.13.1　标签　209

#### 10.13.2　标签语句的作用域　209

### 10.14　goto 语句　210

### 10.15　using 语句　211

> 资源: 指实现了 System.IDisposable 接口的类或者结构

#### 10.15.1　包装资源的使用　212

|       | 分配资源                               | 使用资源 |
| ----- | -------------------------------------- | -------- |
| using | (ResourceType Identifier = Expression) | statment |



#### 10.15.2　using 语句的示例　212

```C#
    using (Restype resouce = new ResType(...)) statement 
	= 
    Restype resouce = new ResType(...);
    {

        try 
        {
            statement 
        }
        finnaly
        {
            // 
            // 处理资源
        }
    }
```



#### 10.15.3　多个资源和嵌套　213

```
            using (TextWriter tw1 = File.CreateText("a.txt"), tw2 = File.CreateText("b.txt"))
            {
                tw1.WriteLine("1");
                tw2.WriteLine("2");
            }


            TextWriter tw = File.CreateText("c.txt");
            using(tw)
            {
                ...
            }
```



#### 10.15.4　using 语句的另一种形式　214

### 10.16　其他语句　215

## 第　11 章 结构　216

### 11.1　什么是结构　216

- 类是引用类型 结构是值类型
- 结构是隐式密封的,不能派生其他结构
- 隐式为结构生成 无参数的默认构造函数,而且不能删除或者重定义
- new  为其调用默认/定义的 构造函数
- 如果不用new 创建实例,则对所有数据成员赋值之后,才能 调用结构里的成员函数
- 不允许声明析构函数

### 11.2　结构是值类型　217

### 11.3　对结构赋值　218

### 11.4　构造函数和析构函数　219

#### 11.4.1　实例构造函数　219

#### 11.4.2　静态构造函数　220

#### 11.4.3　构造函数和析构函数小结　221

### 11.5　属性和字段初始化语句　221

```
    struct SimpleStru
    {
        public int a = 0;       // error 
        static int s_a = 0;     // static right

        public int a_t {get;set;} 

        public int b_t {get;set;} = 1;  //error


    }
```



### 11.6　结构是密封的　221

> - 不可以用下面的修饰符
> - protected
> - protected internal
> - abstract
> - sealed
> - virtual

### 11.7　装箱和拆箱　222

> - 将结构实例作为引用类型对象 必须创建装箱(boxing)副本装箱的过程就是制作值类型变量的引用类型副本

### 11.8　结构作为返回值和参数　222

> - 返回值: 创建结构的副本 并返回
> - 值参数: 创建实参结构的副本,用于方法
> - ref / out 如果把一个结构作为 ref/out参数 传入方法的是该结构的一个引用,这样就可以修改其数据成员

### 11.9　关于结构的更多内容　222

## 第　12 章 枚举　223

### 12.1　枚举　223

#### 12.1.1　设置底层类型和显式值　225

#### 12.1.2　隐式成员编号　225

### 12.2　位标志　226

#### 12.2.1　Flags 特性　229

#### 12.2.2　使用位标志的示例　230

### 12.3　关于枚举的更多内容　231

## 第　13 章 数组　234

### 13.1　数组　234

#### 13.1.1　定义　234

`int [] a = new int[4];`

`int[] a = new int[]{1,2,3,4,5}`

#### 13.1.2　重要细节　235

### 13.2　数组的类型　235

### 13.3　数组是对象　236

### 13.4　一维数组和矩形数组　237

### 13.5　实例化一维数组或矩形数组　238

### 13.6　访问数组元素　238

### 13.7　初始化数组　239

#### 13.7.1　显式初始化一维数组　240

#### 13.7.2　显式初始化矩形数组　240

#### 13.7.3　初始化矩形数组的语法点　241

#### 13.7.4　快捷语法　241

#### 13.7.5　隐式类型数组　241

#### 13.7.6　综合内容　242

### 13.8　交错数组　242

#### 13.8.1　声明交错数组　243

#### 13.8.2　快捷实例化　243

#### 13.8.3　实例化交错数组　244

#### 13.8.4　交错数组中的子数组　245

### 13.9　比较矩形数组和交错数组　246

### 13.10　foreach 语句　247

#### 13.10.1　迭代变量是只读的　248

#### 13.10.2　foreach 语句和多维数组　249

### 13.11　数组协变　250

### 13.12　数组继承的有用成员　251

### 13.13　比较数组类型　254

### 13.14　数组与ref 返回和ref 局部变量　255

## 第　14 章 委托　256



> - 声明委托类型  `delegate void mydel(int x);`
> - 声明委托变量
> - 创建委托实例,并把他的引用赋值给变量,然后增加第一个方法
> - 调用委托对象

### 14.1　什么是委托　256

### 14.2　委托概述　258

### 14.3　声明委托类型　259

### 14.4　创建委托对象　260

### 14.5　给委托赋值　261

### 14.6　组合委托　262

### 14.7　为委托添加方法　262

### 14.8　从委托移除方法　263

### 14.9　调用委托　263

### 14.10　委托的示例　264

### 14.11　调用带返回值的委托　265

### 14.12　调用带引用参数的委托　266

### 14.13　匿名方法　267

#### 14.13.1　使用匿名方法　268

```C#
            MyDel thDel;
            Program pargram = new Program();
            thDel = new MyDel(pargram.printf);
            
            thDel += delegate(int v)   // 如果 v 没有用到过,可以 '(int v)' 也可以省略
            {
                Console.Write($"+= {v},");
                return v+1;
            };
```



#### 14.13.2　匿名方法的语法　268

```C#
delegate (params) { ... statment }
```



#### 14.13.3　变量和参数的作用域　270

- 捕获的变量的生命周期延长了

  

### 14.14　Lambda 表达式　271

> `=>`

- 删除 delegate 关键字
- 参数列表和匿名方法主题放置 `'=>'`

```C#

            MyDel thDel;
            Program pargram = new Program();
            thDel = new MyDel(pargram.printf);
            
            thDel += delegate(int v)                //  匿名方法
            {
                Console.Write($"+= {v},");
                return v+1;
            };

			thDel += (int v) => {return v + 1;};    // lambda
            thDel += (v) =>{return v + 1;};
            thDel += v =>{return v+1;};
            thDel += v => v+1;

            thDel(1);
```



## 第　15 章 事件　274

### 15.1　发布者和订阅者　274

### 15.2　源代码组件概览　276

### 15.3　声明事件　276

> 事件声明在一个类中
>
> - 事件是成员
> - 必须声明在类或者 结构体中
> - 事件声明需要委托类型的名称
> - 事件对外部只暴露了 += / -=

### 15.4　订阅事件　277

### 15.5　触发事件　278

### 15.6　标准事件的用法　280

#### 15.6.1　通过扩展EventArgs 来传递数据　281

#### 15.6.2　移除事件处理程序　283

```
    delegate void EventHandler<IncrementEventArgs>(object sender,IncrementEventArgs e);

    public class IncrementEventArgs : EventArgs
    {
        public int IterationCount{get;set;}
    }

    class Incrementer
    {
        public event EventHandler<IncrementEventArgs> CountedAdozen
        {
            add
            {
                // 执行 += 运算符的代码
            }

            remove
            {
                // 执行 -= 运算符的代码
            }
        }

        public void DoCount()
        {
            
            IncrementEventArgs args = new IncrementEventArgs();
            
            for(int i = 0;i < 100 ;i++)
                if(i%2 == 0 && CountedAdozen != null)
                {
                    args.IterationCount = i;
                    CountedAdozen(this,args);
                }
                    
        }
    }

    class Dozens
    {
        public int DozensCount{get;private set;}

        public Dozens(Incrementer incrementer)
        {
            DozensCount = 0;
            incrementer.CountedAdozen += this.IncrementDozensCount;
        }

        void IncrementDozensCount(object sender,IncrementEventArgs e)
        {
            Console.WriteLine($"Incremented at iteration :{e.IterationCount} in {sender.ToString()}");
            DozensCount  ++ ;
        }
    }
```



### 15.7　事件访问器　284

```C#
        public event EventHandler<IncrementEventArgs> CountedAdozen
        {
            add
            {
                // 执行 += 运算符的代码
            }

            remove
            {
                // 执行 -= 运算符的代码
            }
        }
```



## 第　16 章 接口　286

### 16.1　什么是接口　286

### 16.2　声明接口　291

- 接口不能包含一下成员
  - 数据成员
  - 静态成员
  - 接口成员不能有访问修饰符,但是接口类本身可以有
- 可以包含 一下非静态成员
  - 方法
  - 属性
  - 事件
  - 索引器

### 16.3　实现接口　292

### 16.4　接口是引用类型　294

```C#
IIface if = (IIface) object;
```



### 16.5　接口和as 运算符　295

```C#
IIface if = object as IIface;
```



### 16.6　实现多个接口　295

### 16.7　实现具有重复成员的接口　296

### 16.8　多个接口的引用　298

### 16.9　派生成员作为实现　299

```C#
        class Base : ISomeDoing
        {
            public void PrintOut()
            {

            }
        }

        class Derived:Base,ISomeDoing
        {

        }
```



### 16.10　显式接口成员实现　300

```
class MyCalss : IFace1,IFace2
{
	// 限定接口名称
	void IFace1.PrintOut(){}
	void IFace2.PrintOut(){}
}

MyCalss my = new MyCalss();
((IFace1)my).PrintOut();
```



### 16.11　接口可以继承接口　302

### 16.12　不同类实现一个接口的示例　303

## 第　17 章 转换　305

### 17.1　什么是转换　305

### 17.2　隐式转换　306

### 17.3　显式转换和强制转换　307

### 17.4　转换的类型　308

### 17.5　数字的转换　309

#### 17.5.1　隐式数字转换　309

#### 17.5.2　溢出检测上下文　310

#### 17.5.3　显式数字转换　311

### 17.6　引用转换　315

#### 17.6.1　隐式引用转换　316

#### 17.6.2　显式引用转换　317

#### 17.6.3　有效显式引用转换　318

### 17.7　装箱转换　318

#### 17.7.1　装箱是创建副本　319

#### 17.7.2　装箱转换　320

### 17.8　拆箱转换　320

> **装箱** 是一种隐式转换 它接受值类型的值,根据这个值在堆上创建一个完整的引用类型对象,并返回对象引用

### 17.9　用户自定义转换　321

```C#
        class Derived:Base,ISomeDoing
        {
            public static implicit/explicit operator int(Derived p)
            {
                return 1;
            }

            public static implicit/explicit operator Derived(int i)
            {
                return new Derived();
            }
        }
```



#### 17.9.1　用户自定义转换的约束　322

#### 17.9.2　用户自定义转换的示例　322

#### 17.9.3　评估用户自定义转换　323

#### 17.9.4　多步用户自定义转换的示例　324

### 17.10　is 运算符　325

> 转换之前可以用**is** 判断是否能够转换成功

### 17.11　as 运算符　326

> **as 与强制转换符不同,as 不抛出异常,转换失败时,返回null**

## 第　18 章 泛型　327

### 18.1　什么是泛型　327

- 非泛型类型
  - 委托
  - 数组
  - 枚举
  - 结构
  - 类
  - 接口
- 泛型类型
  - 类
  - 结构
  - 接口
  - 委托

### 18.2　C#中的泛型　329

- 泛型类
- 泛型方法
- 泛型扩展方法
- 泛型结构
- 泛型委托
- 泛型接口
- 协变/逆变

### 18.3　泛型类　330

```C#
    // T1,T2 ==> 类型参数(type parameter)
	class SomeClass<T1,T2>
    {

    }

    // 类型实参 (type argument)
    SomeClass<int,float> mm;
```



#### 18.3.1　声明泛型类　331

#### 18.3.2　创建构造类型　331

#### 18.3.3　创建变量和实例　332

#### 18.3.4　使用泛型的栈的示例　333

#### 18.3.5　比较泛型和非泛型栈　334

### 18.4　类型参数的约束　335

#### 18.4.1　Where 子句　336

#### 18.4.2　约束类型和次序　337

> 约束类型
>
> | 约束类型 | 描述                                                         |
> | :------: | :----------------------------------------------------------- |
> |   类名   | 只有这个类或是派生类才能作为类型实参                         |
> |  class   | 任何引用类型,包括类,数组,委托,接口 都可以作为类型实参        |
> |  struct  | 任何值类型 都可以作为类型实参                                |
> |  接口名  | 只有这个接口,或者实现了这个接口的类型才能作为类型实参        |
> |  new()   | 任何带无参公共构造函数的类型可以作为类型实参,这叫做 **构造函数约束** |
>
> - 最多一个主约束
> - 接口约束可以任意多个
> - 构造函数约束必须放到最后

### 18.5　泛型方法　337

#### 18.5.1　声明泛型方法　338

#### 18.5.2　调用泛型方法　338

#### 18.5.3　泛型方法的示例　339

```
        //                  类型参数列表  方法参数列表  约束字句
        public void PrintData<S,T>(S s, T t) where S:MyStack
        {

        }
```



### 18.6　扩展方法和泛型类　340

### 18.7　泛型结构　341

### 18.8　泛型委托　342

```
 delegate R th_del<T,R>(T t);

```



### 18.9　泛型接口　344

```
interface IInfo<T>
{
	...
}

class My<T> : IInfo<T>
{
}
class MyS<S,T>:Info<T>
{

}
```



#### 18.9.1　使用泛型接口的示例　345

#### 18.9.2　泛型接口的实现必须唯一　345

### 18.10　协变和逆变　346

> 可变性(variance)
>
> - 协变 convariance
> - 逆变 contravariance
> - 不变 invariance

#### 18.10.1　协变　346

#### 18.10.2　逆变　349

#### 18.10.3　协变和逆变的不同　350

#### 18.10.4　接口的协变和逆变　351

#### 18.10.5　关于可变性的更多内容　352

## 第　19 章 枚举器和迭代器　354

### 19.1　枚举器和可枚举类型　354

```C#
foreach(Type varName in EnumerableObject)
{ ... }
```

- 实现** GetEnumerator**方法的类型 叫作 **可枚举类型(enumerable type / enumerable)**
- 

### 19.2　IEnumerator 接口　356

- Current
- MoveNext
- Reset

```C#
            int[] a = {1,2,3,4,5,6,7};

            // 
            foreach(int item in a)
            {
                Console.WriteLine($"item: {item}");
            }

            IEnumerator ie = a.GetEnumerator();            
			while(ie.MoveNext())
            {
                Console.WriteLine($"{ie.Current}");
            }
```



### 19.3　IEnumerable 接口　358

```
class MyClass:IEnumerable
{
	IEnumerator GetEnumerator();
}
```

```c#
    class TestEnumerator
    {
        public void test()
        {
            int[] a = {1,2,3,4,5,6,7};

            // 
            foreach(int item in a)
            {
                Console.WriteLine($"item: {item}");
            }

            IEnumerator ie = a.GetEnumerator();

            while(ie.MoveNext())
            {
                Console.WriteLine($"{ie.Current}");
            }

            ie.Reset();


            EnuClass eu = new EnuClass();
            foreach(string color in eu)
            {
                Console.WriteLine($"{color}");
            }

        }


        public class ColorEnumerator:IEnumerator
        {
            public ColorEnumerator(string[] clrAry)
            {
                _colorAry = new string[clrAry.Length];
                for(int i = 0; i <clrAry.Length;i++)
                    _colorAry[i] = clrAry[i];
            }
            public object Current 
            {
                get 
                {
                    if(position == -1)
                        throw new InvalidOperationException();
                    if(position > _colorAry.Length )
                        throw new InvalidOperationException();
                    
                    return _colorAry[position];
                }
            }

            public bool MoveNext()
            {
                if(position < _colorAry.Length - 1)
                {
                    position++;
                    return true;
                }

                return false;
            }

            public void Reset()
            {
                position = -1;
            }

            int position = -1;
            string []_colorAry;
        }
        public class EnuClass : IEnumerable
        {
            string [] _colors  = {"red","blue","yell"};
            public IEnumerator GetEnumerator()
            {
                return new ColorEnumerator(_colors);
            }
        }
```



### 19.4　泛型枚举接口　360

### 19.5　迭代器　362

#### 19.5.1　迭代器块　362

#### 19.5.2　使用迭代器来创建枚举器　363

#### 19.5.3　使用迭代器来创建可枚举类型　365

### 19.6　常见迭代器模式　366

### 19.7　产生多个可枚举类型　367

### 19.8　将迭代器作为属性　368

### 19.9　迭代器的实质　369

## 第　20 章 LINQ　371

### 20.1　什么是LINQ　371

### 20.2　LINQ 提供程序　372

### 20.3　方法语法和查询语法　374

### 20.4　查询变量　375

### 20.5　查询表达式的结构　376

#### 20.5.1　from 子句　377

#### 20.5.2　join 子句　378

#### 20.5.3　什么是联结　379

#### 20.5.4　查询主体中的from let where 片段　381

#### 20.5.5　orderby 子句　384

#### 20.5.6　select group 子句　385

#### 20.5.7　查询中的匿名类型　386

#### 20.5.8　group 子句　387

#### 20.5.9　查询延续：into 子句　388

### 20.6　标准查询运算符　389

#### 20.6.1　标准查询运算符的签名　392

#### 20.6.2　查询表达式和标准查询运算符　393

#### 20.6.3　将委托作为参数　394

#### 20.6.4　LINQ 预定义的委托类型　395

#### 20.6.5　使用委托参数的示例　396

#### 20.6.6　使用Lambda 表达式参数的示例　397

### 20.7　LINQ to XML　398

#### 20.7.1　标记语言　398

#### 20.7.2　XML 基础　398

#### 20.7.3　XML 类　400

#### 20.7.4　使用XML 特性　406

#### 20.7.5　其他类型的节点　408

#### 20.7.6　使用LINQ to XML 的LINQ 查询　409

## 第　21 章 异步编程　412

### 21.1　什么是异步　412

### 21.2　async/await 特性的结构　416

### 21.3　什么是异步方法　417

#### 21.3.1　异步方法的控制流　421

#### 21.3.2　取消一个异步操作　427

#### 21.3.3　在调用方法中同步地等待任务　430

```
task.Wait()
Task.WaitAll()
Task.WaitAny()
```



#### 21.3.4　在异步方法中异步地等待任务　433

```
Task<string> t1 = ...
Task<string> t2 = ...
List<Task<string>> tasks = ...
tasks.add(t1)
tasks.add(t2)
await Task.WhenAll(tasks)
...
```



#### 21.3.5　Task.Delay 方法　435

> 与Thread.Sleep阻塞线程不同，Task.Delay 不会阻塞线程
>
> ```C#
> private async void ShowDelayAsync()
> {
> 	await Task.Delay(1000);
> }
> ```

### 21.4　GUI 程序中的异步操作　436

`Task.Yeild`



### 21.5　使用异步Lambda 表达式　440

```
startWorkButton.Click += async(sender,e)=>
{
	// ... 
}
```



### 21.6　完整的GUI 程序　441

### 21.7　BackgroundWorker 类　443

### 21.8　并行循环　447

### 21.9　其他异步编程模式　450

### 21.10　BeginInvoke 和EndInvoke　451

#### 21.10.1　等待直到完成模式　452

#### 21.10.2　AsyncResult 类　453

#### 21.10.3　轮询模式　454

#### 21.10.4　回调模式　455

### 21.11　计时器　458

## 第　22 章 命名空间和程序集　460

### 22.1　引用其他程序集　460

### 22.2　命名空间　464

#### 22.2.1　命名空间名称　467

#### 22.2.2　命名空间的补充　467

#### 22.2.3　命名空间跨文件伸展　468

#### 22.2.4　嵌套命名空间　469

### 22.3　using 指令　470

#### 22.3.1　using 命名空间指令　470

#### 22.3.2　using 别名指令　471

#### 22.3.3　using static 指令　471

### 22.4　程序集的结构　472

### 22.5　程序集标识符　473

### 22.6　强命名程序集　474

### 22.7　私有程序集的部署　475

### 22.8　共享程序集和GAC　476

#### 22.8.1　把程序集安装到GAC　476

#### 22.8.2　GAC 内的并肩执行　477

### 22.9　配置文件　477

### 22.10　延迟签名　478

## 第　23 章 异常　480

### 23.1　什么是异常　480

### 23.2　try 语句　481

### 23.3　异常类　482

### 23.4　catch 子句　483

### 23.5　异常过滤器　485

### 23.6　catch 子句段　485

### 23.7　finally 块　486

### 23.8　为异常寻找处理程序　487

### 23.9　进一步搜索　488

#### 23.9.1　一般法则　489

#### 23.9.2　搜索调用栈的示例　489

### 23.10　抛出异常　492

### 23.11　不带异常对象的抛出　493

### 23.12　throw 表达式　494

## 第　24 章 预处理指令　495

### 24.1　什么是预处理指令　495

### 24.2　基本规则　495

### 24.3　#define 和#undef 指令　496

### 24.4　条件编译　497

### 24.5　条件编译结构　498

### 24.6　诊断指令　500

### 24.7　行号指令　501

### 24.8　区域指令　502

### 24.9　#pragma warning 指令　503

## 第　25 章 反射和特性　504

### 25.1　元数据和反射　504

### 25.2　Type 类　505

### 25.3　获取Type 对象　506

### 25.4　什么是特性　508

### 25.5　应用特性　509

### 25.6　预定义的保留特性　509

#### 25.6.1　Obsolete 特性　509

#### 25.6.2　Conditional 特性　510

#### 25.6.3　调用者信息特性　512

#### 25.6.4　DebuggerStepThrough 特性　513

#### 25.6.5　其他预定义特性　514

### 25.7　关于应用特性的更多内容　514

#### 25.7.1　多个特性　514

#### 25.7.2　其他类型的目标　515

#### 25.7.3　全局特性　515

### 25.8　自定义特性　516

#### 25.8.1　声明自定义特性　516

#### 25.8.2　使用特性的构造函数　516

#### 25.8.3　指定构造函数　517

#### 25.8.4　使用构造函数　517

#### 25.8.5　构造函数中的位置参数和命名参数　518

#### 25.8.6　限制特性的使用　518

#### 25.8.7　自定义特性的最佳实践　520

### 25.9　访问特性　520

#### 25.9.1　使用IsDefined 方法　520

#### 25.9.2　使用GetCustomAttributes方法　521

## 第　26 章 C# 6.0 和C# 7.0 新增的内容　523

### 26.1　新增内容概述　524

### 26.2　字符串插值（C# 6.0）　524

### 26.3　自动属性初始化语句　525

### 26.4　只读自动属性（C# 6.0）　526

### 26.5　表达式函数体成员（C# 6.0 和

### C#　7.0）　526

### 26.6　using static（C# 6.0）　527

### 26.7　空条件运算符（C# 6.0）　528

### 26.8　在catch 和finally 块中使用await（C# 6.0）　528

### 26.9　nameof 运算符（C# 6.0）　529

### 26.10　异常过滤器（C# 6.0）　529

### 26.11　索引初始化语句（C# 6.0）　530

### 26.12　集合初始化语句的扩展方法（C# 6.0）　532

### 26.13　改进的重载决策（C# 6.0）　533

### 26.14　值元组（C# 7.0）　534

### 26.15　is 模式匹配（C# 7.0）　534

### 26.16　switch 模式匹配（C# 7.0）　536

### 26.17　自定义析构函数（C# 7.0）　538

### 26.18　二进制字面量和数字分隔符（C# 7.0）　540

### 26.19　out 变量（C# 7.0）　541

### 26.20　局部函数（C# 7.0）　542

### 26.21　ref 局部变量（ref 变量）和 ref　返回（C# 7.0）　544

### 26.22　表达式函数体成员的扩展（C# 7.0）　544

### 26.23　throw 表达式（C# 7.0）　545

### 26.24　扩展的async 返回类型（C# 7.0）　545

## 第　27 章 其他主题　546

### 27.1　概述　546

### 27.2　字符串　546

### 27.3　StringBuilder 类　548

### 27.4　把字符串解析为数据值　549

### 27.5　关于可空类型的更多内容　550

#### 27.5.1　为可空类型赋值　552

#### 27.5.2　使用空接合运算符　552

#### 27.5.3　空条件运算符　553

#### 27.5.4　使用可空用户定义类型　555

### 27.6　Main 方法　556

### 27.7　文档注释　558

#### 27.7.1　插入文档注释　558

#### 27.7.2　使用其他XML 标签　559

### 27.8　嵌套类型　559

#### 27.8.1　嵌套类的示例　560

#### 27.8.2　可见性和嵌套类型　561

### 27.9　析构函数和dispose 模式　563

#### 27.9.1　标准dispose 模式　564

#### 27.9.2　比较构造函数和析构函数　566

### 27.10　Tuple 和ValueTuple　566

### 27.11　和COM 的互操作　568
