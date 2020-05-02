### GDB 

#### 1.  -g    添加调试信息 

- O0 O1 ：优化等级
- ulimit -c unlimited :  开启崩溃转储

#### 2 .   加载进程　

- gdb file
- gdb attach pid
- gdb file core  然后 `bt`打印堆栈

####   3. 常用命令
> 命令名称  |	命令缩写  |	命令说明
-|-|-|
run    |	r |	运行一个程序
continue |	c	| 让暂停的程序继续运行
next	|  n	|  运行到下一行
step	| s	 | 如果有调用函数，进入调用的函数内部，相当于 step into
until	| u	| 运行到指定行停下来
finish	| fi	| 结束当前调用函数，到上一层函数调用处
return	| return	| 结束当前调用函数并返回指定值，到上一层函数调用处
jump	| j	| 将当前程序执行流跳转到指定行或地址
print	| p | 	打印变量或寄存器值
backtrace	| bt | 	查看当前线程的调用堆栈
frame	| f	|切换到当前调用线程的指定堆栈，具体堆栈通过堆栈序号指定
thread	|thread	|切换到指定线程
break	|b	|添加断点
tbreak	|tb	|添加临时断点
delete	|del| 	删除断点
enable	|enable|	启用某个断点
disable	|disable|	禁用某个断点
watch	|watch|	监视某一个变量或内存地址的值是否发生变化
list	| l	| 显示源码
info	|info	|查看断点 / 线程等信息
ptype	|ptype|	查看变量类型
disassemble	|dis|	查看汇编代码
set | args	|	设置程序启动命令行参数
show | args	| 	查看设置的命令行参数

#### 4. 实例
- b
  - b anet.c:441
  - b main
  - b 441  // 当前文件的441行
  - break [lineNo] if [condition]  //条件断点
- bt
- frame (f):  bt  & f 1
- info 
  - info break  , disable b-num, enable b-num , delete num 
  - enable / disable /delete 如果不加number 表示全部断点
- list  查看断点出代码
  - bt，f 1, list
- print / p 查看(也能`修改`)变量
  - p server.port 
  - p server.port = 1000  // 修改变量
  - p & server.port
  - p this
  - p *  解引用
- ptype  查看变量类型
- info thread
- thread 1
- info args

- cotrol flow
  - step 
  - next
  - until
  - finish
    - 正常执行当前函数返回
  - return
    - 立即返回，当前函数没有正常走完
    - return 111 // 可以指定返回值
  - until： untile linenum

  - jump ： 直接略过之间的代码，执行执行的代码，并 继续执行
    - jump file:line
    - jump line-num

- disassemble

  - show disassembly-flavor
  - set disassembly-flavor intel
  - set disassembly-flavor att

- args : 指的是启动的参数 ， 与 info args 不同

  - show args
  - set args

- tbreak ( temporarily break)

  - tbreak main

- watch *p  watch p 硬件断点，如果watch的变量有变化，自动断下

- display

  - show display
  - delete display  [num]

- stricks 

  - set print element 0   // 完整打印字符串
  - signal SIGINT
  - handle SIGINT nostop print
  - 如果 b fnName 失效，可采用 b file:line 方式
  - set scheduler-locking on/off  // 防止调试多线程被其他线程打断
  - 