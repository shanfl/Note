### VIII. 进程控制

##### 1. 引言

创建新进程

执行程序

进程终止

进程属性: 实际 , 有效  保存的用户Id ,组ID

解释器文件,system函数

进程会计机制



##### 2 进程标识

```c
#include <unistd.h>
pid_t getpid();
pdi_t getppid();
uid_t getuid();
uid_T geteuid();
gid_t getgid();
gid_t getegid();
```



##### 3. fork

```c
#include <unistd.h>
pid_t fork();		// 子进程返回0 ,父进程返回子进程id
```

