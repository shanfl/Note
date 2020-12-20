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
```



oflags:

	1. O_RDONLY
	2. O_WRONLY
	3. O_RDWR
	4. O_EXEC
	5. O_SEARCH

---------------------

	1. O_APPEND
	2. O_CLOEXEC
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



##### 3.4 create

```
create(const char*path,mode_t mode)
==
open(path,O_WRNOLY | O_CREAT | O_TRUNC,mode)
```

##### 3.5 close

##### 3.6 lseak

1. SEEK_SET
2. SEEK_CUR
3. SEEK_END

##### 3.7 read

```c++
#include <unistd.h>
ssize_t read(int fd,void *buf,size_t nbytes);
```

##### 3.8 write

```
#include <unistd.h>
ssize_t write(int fd,const void *buf,size_t nbytes);
```

##### 3.11 原子操作



##### 3.12 dup dup2

```
int dup(int fd);
int dup2(int fd,int fd2);
```



```
dup(fd) => fcntl(fd,F_DUPFD,0)
dup2(fd1,fd2) => close(fd2) ; fcntl(fd,F_DUPFD,fd2)
```



##### 3.13 sync fsync fdatasync

```c
#include <unistd.h>
int fsync(int fd);
int fdatasync(int fd);
void sync(void);   // 将所有修改过的块缓冲器排入写队列,并不等待写磁盘操作
```

##### 3.14 fcntl

```
#include <unistd.h>
int fcntl(int fd,int cmd ... /*int arg*/);
```

| cmd  | flags                           | MEANING                  |
| ---- | ------------------------------- | ------------------------ |
|      | F_DUPFD \| F_DUPFD_CLOEXEC      | 复制一个已有的文件描述符 |
|      | F_GETFD \| F_SETFD              | 获取/设置文件描述符标志  |
|      | F_GETFL \| F_SETFL              | 获取/设置文件状态标志    |
|      | F_GETOWN \| F_SETOWN            | 获取/设置异步I/O所有权   |
|      | F_GETLK \| F_SETLK \|  F_SETLKW | 获取/设置记录锁          |



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

##### 3.15 ioctl

```c++
#include <unistd.h>
int ioctl(int fd,int request, ...);
```

##### 3.16 /dev/fd

`f = open("/dev/fd/0",mode)`

linux 的实现与unix不同... Linux将文件描述符映射成指向底层物理文件的符号链接



/dev/fd 主要被shell使用