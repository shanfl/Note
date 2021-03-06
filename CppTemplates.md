###  第1章 关于本章
#### 1.1 阅读本书所需具备的知识
#### 1.2 本书的整体结构
#### 1.3 如何阅读本书
#### 1.4 关于编程风格的一些说明
#### 1.5 标准和现实
#### 1.6 代码例子和更多信息
#### 1.7 反馈

## 第1部分 基础
###  第2章 函数模板
#### 2.1 初探函数模板
##### 2.1.1 定义模板
##### 2.1.2 使用模板
#### 2.2 实参的演绎(deduction)
#### 2.3 模板参数
#### 2.4 重载函数模板
#### 2.5 小结

###  第3章 类模板
#### 3.1 类模板Stack的实现
#### 3.1.1 类模板的声明
#### 3.1.2 成员函数的实现
#### 3.2 类模板Stack的使用
#### 3.3 类模板的特化
#### 3.4 局部特化
#### 3.5 缺省模板实参
#### 3.6 小结

###  第4章 非类型模板参数
#### 4.1 非类型的类模板参数
#### 4.2 非类型的函数模板参数
#### 4.3 非类型模板参数的限制
#### 4.4 小结

###  第5章 技巧性基础知识
#### 5.1 关键字 typename
#### 5.2 使用this->
#### 5.3 成员模板
#### 5.4 模板的模板参数
#### 5.5 零初始化
#### 5.6 使用字符串作为函数模板的实参
#### 5.7 小结

###  第6章 模板实战
#### 6.1 包含模型
#### 6.1.1 链接器错误
#### 6.1.2 头文件中的模板
#### 6.2 显式实例化
#### 6.2.1 显式实例化的例子
#### 6.2.2 整合包含模型和显式实例化
#### 6.3 分离模型
#### 6.3.1 关键字export
#### 6.3.2 分离模型的限制
#### 6.3.3 为分离模型做好准备
#### 6.4 模板和内联
#### 6.5 预编译头文件
#### 6.6 调试模板
#### 6.6.1 理解长段的错误信息
#### 6.6.2 浅式实例化
#### 6.6.3 长符号串
#### 6.6.4 跟踪程序
#### 6.6.5 oracles
#### 6.6.6 archetypes
#### 6.7 本章后记
#### 6.8 小结

###  第7章 模板术语
#### 7.1 "类模板"还是"模板类"
#### 7.2 实例化和特化
#### 7.3 声明和定义
#### 7.4 一处定义原则
#### 7.5 模板实参和模板参数

## 第2部分 深入模板
###  第8章 深入模板基础
#### 8.1 参数化声明
#### 8.1.1 虚成员函数
#### 8.1.2 模板的链接
#### 8.1.3 基本模板
#### 8.2 模板参数
#### 8.2.1 类型参数
#### 8.2.2 非类型参数
#### 8.2.3 模板的模板参数
#### 8.2.4 缺省模板实参
#### 8.3 模板实参
#### 8.3.1 函数模板实参
#### 8.3.2 类型实参
#### 8.3.3 非类型实参
#### 8.3.4 模板的模板实参
#### 8.3.5 实参的等价性
#### 8.4 友元
#### 8.4.1 友元函数
#### 8.4.2 友元模板
#### 8.5 本章后记

###  第9章 模板中的名称
#### 9.1 名称的分类
#### 9.2 名称查找
#### 9.2.1 Argument-Dependent Lookup(ADL)
#### 9.2.2 友元名称插入
#### 9.2.3 插入式类名称
#### 9.3 解析模板
#### 9.3.1 非模板中的上下文相关性
#### 9.3.2 依赖型类型名称
#### 9.3.3 依赖型模板名称
#### 9.3.4 using-declaration中的依赖型名称
#### 9.3.5 ADL和显式模板实参
#### 9.4 派生和类模板
#### 9.4.1 非依赖型基类
#### 9.4.2 依赖型基类
#### 9.5 本章后记

###  第10章 实例化
#### 10.1 On-Demand实例化
#### 10.2 延迟实例化
#### 10.3 C++的实例化模型
#### 10.3.1 两阶段查找
#### 10.3.2 POI
#### 10.3.3 包含模型与分离模型
#### 10.3.4 跨翻译单元查找
#### 10.3.5 例子
#### 10.4 几种实现方案
#### 10.4.1 贪婪实例化
#### 10.4.2 询问实例化
#### 10.4.3 迭代实例化
#### 10.5 显式实例化
#### 10.6 本章后记

###  第11章 模板实参演译
#### 11.1 演绎的过程
#### 11.2 演绎的上下文
#### 11.3 特殊的演绎情况
#### 11.4 可接受的实参转型
#### 11.5 类模板参数
#### 11.6 缺省调用实参
#### 11.7 Barton-Nackman方法
#### 11.8 本章后记

###  第12章 特化与重载
#### 12.1 当泛型代码不再适用的时候
#### 12.1.1 透明自定义
#### 12.1.2 语义的透明性
#### 12.2 重载函数模板
#### 12.2.1 签名
#### 12.2.2 重载的函数模板的局部排序
#### 12.2.3 正式的排序原则
#### 12.2.4 模板和非模板
#### 12.3 显式特化
#### 12.3.1 全局的类模板特化
#### 12.3.2 全局的函数模板特化
#### 12.3.3 全局成员特化
#### 12.4 局部的类模板特化
#### 12.5 本章后记

###  第13章 未来的方向
#### 13.1 尖括号Hack
#### 13.2 放松typename的原则
#### 13.3 缺省函数模板实参
#### 13.4 字符串文字和浮点型模板实参
#### 13.5 放松模板的模板参数的匹配
#### 13.6 typedef模板
#### 13.7 函数模板的局部特化
#### 13.8 typeof运算符
#### 13.9 命名模板实参
#### 13.10 静态属性
#### 13.11 客户端的实例化诊断信息
#### 13.12 重载类模板
#### 13.13 List参数
#### 13.14 布局控制
#### 13.15 初始化器的演绎
#### 13.16 函数表达式
#### 13.17 本章后记

## 第3部分 模板与设计
###  第14章 模板的多态威力
#### 14.1 动多态
#### 14.2 静多态
#### 14.3 动多态和静多态
#### 14.3.1 术语
#### 14.3.2 优点和缺点
#### 14.3.3 组合这两种多态
#### 14.4 新形式的设计模板
#### 14.5 泛型程序设计
#### 14.6 本章后记

###  第15章 trait与policy类
#### 15.1 一个实例：累加一个序列
#### 15.1.1 fixed traits
#### 15.1.2 value trait
#### 15.1.3 参数化trait
#### 15.1.4 policy和policy类
#### 15.1.5 trait和policy：区别在何处
#### 15.1.6 成员模板和模板的模板参数
#### 15.1.7 组合多个policie和/或trait
#### 15.1.8 运用普通的迭代器进行累积
#### 15.2 类型函数
#### 15.2.1 确定元素的类型
#### 15.2.2 确定class类型
#### 15.2.3 引用和限定符
#### 15.2.4 promotion trait
#### 15.3 policy trait
#### 15.3.1 只读的参数类型
#### 15.3.2 拷贝、交换和移动
#### 15.4 本章后记

###  第16章 模板与继承
#### 16.1 命名模板参数
#### 16.2 空基类优化
#### 16.2.1 布局原则
#### 16.2.2 成员作基类
#### 16.3 奇特的递归模板模式
#### 16.4 参数化虚拟性
#### 16.5 本章后记

###  第17章 metaprogram
#### 17.1 metaprogram的第一个实例
#### 17.2 枚举值和静态常量
#### 17.3 第2个例子：计算平方根
#### 17.4 使用归纳变量
#### 17.5 计算完整性
#### 17.6 递归实例化和递归模板实参
#### 17.7 使用metaprogram来展开循环
#### 17.8 本章后记

###  第18章 表示式模板
#### 18.1 临时变量和分割循环
#### 18.2 在模板实参中编码表达式
#### 18.2.1 表达式模板的操作数
#### 18.2.2 Array类型
#### 18.2.3 运算符
#### 18.2.4 回顾
#### 18.2.5 表达式模板赋值
#### 18.3 表达式模板的性能与约束
#### 18.4 本章后记

## 第4部分 高级应用程序
###  第19章 类型区分
#### 19.1 辨别基本类型
#### 19.2 辨别组合类型
#### 19.3 辨别函数类型
#### 19.4 运用重载解析辨别枚举类型
#### 19.5 辨别class类型
#### 19.6 辨别所有类型的函数模板
#### 19.7 本章后记

###  第20章 智能指针
#### 20.1 holder和trule
#### 20.1.1 安全处理异常
#### 20.1.2 holder
#### 20.1.3 作为成员的holder
#### 20.1.4 资源获取于初始化
#### 20.1.5 holder的局限
#### 20.1.6 复制holder
#### 20.1.7 跨函数调用来复制holder
#### 20.1.8 trule
#### 20.2 引用记数
#### 20.2.1 计数器在什么地方
#### 20.2.2 并发访问计数器
#### 20.2.3 析构和释放
#### 20.2.4 CountingPtr模板
#### 20.2.5 一个简单的非侵入式计数器
#### 20.2.6 一个简单的侵入式计数器模板
#### 20.2.7 常数性
#### 20.2.8 隐式转型
#### 20.2.9 比较
#### 20.3 本章后记

###  第21章 tuple
#### 21.1 duo
#### 21.2 可递归duo
#### 21.2.1 域的个数
#### 21.2.2 域的类型
#### 21.2.3 域的值
#### 21.3 tuple构造
#### 21.4 本章后记

###  第22章 函数对象和回调
#### 22.1 直接调用、间接调用与内联调用
#### 22.2 函数指针与函数引用
#### 22.3 成员函数指针
#### 22.4 class类型的仿函数
#### 22.4.1 class类型仿函数的第1个实例
#### 22.4.2 class类型仿函数的类型
#### 22.5 指定仿函数
#### 22.5.1 作为模板类型实参的仿函数
#### 22.5.2 作为函数调用实参的仿函数
#### 22.5.3 结合函数调用参数和模板类型参数
#### 22.5.4 作为非类型模板实参的仿函数
#### 22.5.5 函数指针的封装
#### 22.6 内省
#### 22.6.1 分析一个仿函数的类型
#### 22.6.2 访问参数的类型
#### 22.6.3 封装函数指针
#### 22.7 函数对象组合
#### 22.7.1 简单的组合
#### 22.7.2 混合类型的组合
#### 22.7.3 减少参数的个数
#### 22.8 值绑定
#### 22.8.1 选择绑定的目标
#### 22.8.2 绑定签名
#### 22.8.3 实参选择
#### 22.8.4 辅助函数
#### 22.9 仿函数操作：一个完整的实现
#### 22.10 本章后记

###  附录A 一处定义原则
A.1 翻译单元
A.2 声明和定义
A.3 一处定义原则的细节
A.3.1 程序的一处定义约束
A.3.2 翻译单元的一处定义约束
A.3.3 跨翻译单元的等价性约束

附录B 重载解析
B.1 何时应用重载解析
B.2 简化过的重载解析
B.2.1 成员函数的隐含实参
B.2.2 细化完美匹配
B.3 重载的细节
B.3.1 非模板优先
B.3.2 转型序列
B.3.3 指针的转型
B.3.4 仿函数和代理函数
B.3.5 其他的重载情况
参考资料
术语表