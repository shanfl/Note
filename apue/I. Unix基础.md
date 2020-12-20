### 1.unix基础

##### 1.1 引言

##### 1.2 unix 体系结构



##### 1.3  登录 

​	/etc/passwd

​    shell

##### 1.4 文件&目录

```c++
#include <dirent.h>
...
DIR *dp;
struct dirent *dirp;
dp = opendir(argv[1])
while((dirp = readdir(dp)) != nullptr)
{
	std::cout<<dirp->d_name;
}
...
closedir(dp);
```



##### 1.5 i/o

1. 文件描述符
2. stdio stdout stderr
3. 无缓冲的 I/O
   1. open read write lseek close
4. unistd.h  `open read write lseek close`
   1. STDIN_FILENO(0) STDOUT_FILENO(1) 
5. 标准io

##### 1.6 程序和进程

 `fork exec waitpid getpid` 

1. 程序
2. 进程 & 进程id `getpid()`
3. 进程控制
   1. fork
   2. exec
   3. waitpid
4. 线程 线程id  thread

##### 1.7 出错处理

1. ```c++
   #include <string.h>
   char*strerror(int no);
   ```

2. ```c++
   #include <stdio.h>
   perror(const char*msg); // perror 基于当前的errno的当前值,输出 msg + ':'' +  errno对应的字符串
   ```

##### 1.8 用户标识

1. user id
2. group id   
   1. getuid()
   2. getgid()
3. 附属组 `/etc/group`

##### 1.9 信号 signal

```C++
static void sig_int(int)
{...}

...
signal(SIGINT,sig_int);
```

##### 1.10  时间值

1. 日历时间   clock_t sysconf
2. 进程时间
   1. 时钟时间
   2. 用户cpu时间
   3. 系统cpu时间

3. `time -P  grep POSIX_SOURCE */*.h > /dev/null `

##### 1.11 系统调用 & 库函数'

'