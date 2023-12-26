### III. 文件I/O

##### 1.引言

1. `open read write iseek close`
2. unbuffered I/O 
3. dup  fcntl  sync  fsync  ioctl

##### 2. 文件描述符

0 1 2 ------> *STDIN_FILENO STDOUT_FILENO STDERR_FILENO*    <<< UNISTD.H

##### 3 open  & open_at

```c++
#include <fcntl.h>
int open(const char*path,int oflags,.../*mode_t mode*/);
int open_at(int fd,const char*path,int oflag,... /**mode_t mode/);

：open_at
如果path 是相对路径，则根据fd的当前目录为根目录，再打开
如果fd = AT_FDCWD 则表示在当前目录中获取
```

oflags: 这5个必须要有且唯有一个

    1. O_RDONLY
    2. O_WRONLY
    3. O_RDWR
    4. O_EXEC
    5. O_SEARCH

---------------------

    1. O_APPEND
    2. O_CLOEXEC      --打开的文件描述符在执行exec调用新程序前自动被关闭 https://stackoverflow.com/questions/39848203/difference-between-o-cloexec-and-tiocexcl
    3. O_CREAT
    4. O_DIRECTORY
    5. O_EXCL
    6. O_NOCTTY
    7. O_NOFOLLOW
    8. O_NONBLOCK
    9. O_SYNC
    10. O_TRUNC
    11. O_TTY_INIT
    12. O_DSYNC
    13. O_RSYNC

```
OCLOEXEC is a flag that can be set when opening a file in Linux. 
It enables the close-on-exec flag for the new file descriptor, 
which means that the file descriptor will be automatically closed 
when the process calls exec(). 
This flag can be useful when spawning a new process using fork()/exec()
 and you want to know if exec() worked. An old trick for this is to 
create a pipe and mark the writer end O_CLOEXEC. 
The reader end will read EOF (due to the close of the writer) once exec() has succeeded
```

##### 3.4 create

```c
create(const char*path,mode_t mode)
==
open(path,O_WRNOLY | O_CREAT | O_TRUNC,mode)

// apue代码里的定义
#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define	DIR_MODE	(FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

```

##### 3.5 close

##### 3.6 lseak

```c
#include <sys/types.h>
#include <unistd.h>
off_t lseek(int fd, off_t offset, int whence);
                                        - SEEK_SET
                                        - SEEK_CUR
                                        - SEEK_END
若lseek执行成功，则返回新的文件偏移量
```



##### 3.7 read

```c
#include <unistd.h>
ssize_t read(int fd,void *buf,size_t nbytes);
```

##### 3.8 write

```c
#include <unistd.h>
ssize_t write(int fd,const void *buf,size_t nbytes);
```

##### 3.10 文件共享

内核使用3中数据结构表示打开文件

1）每个进程在进程表中都有一个记录项，记录项中包含一张打开文件描述符表，每个描述符占用一项。与每个文件描述符相关联的是

>  a.文件描述符标志(CLOSE_ON_EXEC)
> 
>  b.指向一个文件表项的指针

2）内核为所有打开文件维持一张文件表。每个表项包含：

> a.文件状态标志（读，写，添写，同步和非阻塞
> 
> b.当前文件偏移量
> 
> c. 指向该文件 v节点表项的指针

3)每个打开文件（或设备）都有一个v节点（v-node)结构。v节点包含了文件类型和对此文件进行各种操作函数的指针



<img title="" src="file:///media/shanfl/KINGSTON/Note/apue/images/3-7.png" alt="" data-align="inline">

![](/media/shanfl/KINGSTON/Note/apue/images/3-8.png)

##### 3.11 原子操作

##### 3.12 dup dup2

```
// dup返回的新文件描述符一定是当前可用文件描述符的最小数值
int dup(int fd);  
int dup2(int fd,int fd2);
```

```
dup(fd) => fcntl(fd,F_DUPFD,0)
dup2(fd1,fd2) => close(fd2) ; fcntl(fd,F_DUPFD,fd2)
```

##### 3.13 sync fsync fdatasync

unix在内核中设有缓冲区高速缓存或页高速缓存，大多数磁盘I/O都通过缓冲区进行。当向文件写入数据时，内核通常先将数据复制到缓冲区中，然后排入队列，晚些时候再写入磁盘，成为延迟写（delayed write）。



```c
#include <unistd.h>
int fsync(int fd);  // 等待写磁盘操作结束才返回
int fdatasync(int fd);    // 完成fsync的操作，还刷新文件属性
void sync(void);   // 将所有修改过的块缓冲器排入写队列,并不等待写磁盘操作
```

##### 3.14 fcntl

```
#include <unistd.h>
int fcntl(int fd,int cmd ... /*int arg*/);
```

| cmd | flags                           | MEANING       |
| --- | ------------------------------- | ------------- |
|     | F_DUPFD \| F_DUPFD_CLOEXEC      | 复制一个已有的文件描述符  |
|     | F_GETFD \| F_SETFD              | 获取/设置文件描述符标志  |
|     | F_GETFL \| F_SETFL              | 获取/设置文件状态标志   |
|     | F_GETOWN \| F_SETOWN            | 获取/设置异步I/O所有权 |
|     | F_GETLK \| F_SETLK \|  F_SETLKW | 获取/设置记录锁      |

```

#include <unistd.h>
...
int value = fcntl(atoi(argv[1]),F_GETFL,0);
switch(value & O_ACCMODE)
{
    case O_RDONLY:
    CASE O_WRONLY:
    CASE O_RDWR:
    default:
}
if (val & O_APPEND)
if(val & O_NONBLOCK)
if (val & O_SYNC)
if(val& O_FSYNC)
...
```

fcntl 的必要性: 有时候应用只能接收到 fd,不能提前设置文件flag



![](/media/shanfl/KINGSTON/Note/apue/images/3-10.PNG)

```c
void set_fl(int fd,int flags){
    int val;
    if((val=fcntl(fd,F_GETFL,0))<0){
        perror("fcntl F_GETFL error);
    }
    val |= flags;   // !!!
    if(fcntl(fd,F_SETFL,val) < 0) {
        perror("fcntl F_SETFL error);
    }
}

set_fl(STDOUT_FILENO,O_SYNC);
```







##### 3.15 ioctl

```c++
#include <unistd.h>
int ioctl(int fd,int request, ...);
```

##### 3.16 /dev/fd

`f = open("/dev/fd/0",mode)`

linux 的实现与unix不同... Linux将文件描述符映射成指向底层物理文件的符号链接

/dev/fd 主要被shell使用