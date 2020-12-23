### VII. 进程环境

##### 7.1 引言

##### 7.2 main函数

##### 7.3 进程终止

1. main返回
2. 调用exit
3. 调用_exit / _Exit
4. 最后一个线程从其启动例程返回
5. 从最后一个线程调用 pthrea_exit
6. abort
7. 接收到一个信号
8. 最后一个线程对取消请求做出响应



###### 1. 退出函数

```c
#include <stdlib.h>
void exit(int staus);
void _Exit(int status);

#include <unistd.h>
void _exit(int status);
```



###### 2. aexit

```c
#include <stdlib.h>
int aexit(void (*func)(void));
```



##### 7.4 命令行参数

```c
int main(int argc,char*argv[])
```



##### 7.5 环境表

每个程序都会接收到一张环境表

extern char**environ;



```c
getenv
putenv
```



##### 7.6 C程序的存储空间布局

##### 7.7 共享库

##### 7.8 存储空间分配

```c
void*malloc(size_t size);
void*calloc(size_t nobj,size_t size);
void realloc(void*ptr,size_t newsize);

void free(void*ptr);
```



##### 7.9 环境变量

```c
#include<stdlib.h>

char*getenv(char*name);

int putenv(char*str);
int setenv(char*name,char*value,int rewrite);   // rewrite = 0 如果存在则不覆盖
int unsetenv(char*name);
```





##### 7.10 setjmp longjmp

自动变量  寄存器变量  易逝变量



##### 7.11 getrlimit  setrlimit