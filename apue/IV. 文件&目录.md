#### VI. 文件&目录

##### 4.1 引言

`stat`

更改所有者 权限

unix文件系统结构 符号链接

目录操作函数

降序遍历目录函数编写



##### 4.2 stat  fstat fstatat lstat

```C
#include <sys/stat.h>
int stat(const char*restrict pathname,struct stat * restrict buf);
int fstat(int fd struct stat *buf);
int lstat(const char* pathname ,struct stat*buf);
int fstatat(int fd,const char*pathname,struct stat*buf,int flag);		
```



| struct stat     |            |                                   |
| --------------- | ---------- | --------------------------------- |
| mode_t          | st_mode    | file type & mode (permissions)    |
| ino_t           | st_ino     | i-node number(serial number)      |
| dev_t           | st_dev     | device number (file system)       |
| dev_t           | st_rdev    | device number for special files   |
| nlink_t         | st_nlink   | number of links                   |
| uid_t           | st_uid     | user id of owner                  |
| gid_t           | st_gid     | group id of owner                 |
| off_t           | st_size    | size in bytes , for regular files |
| struct timespec | st_atime   | time of last access               |
| struct timespec | st_mtime   | time of last modification         |
| struct timespec | st_ctime   | time of last file status change   |
| blksize_t       | st_blksize | best i/o block size               |
| blkcnt_t        | st_blocks  | numnber of disk blocks allocated  |

##### 4.3 文件类型   信息位于  `struct stat.st_mode`

1. 普通文件 regular file
2. 目录文件 directory file
3. 块文件 block special file
4. 字符特殊文件 character special file
5. FIFO
6. socket
7. symbolic link



| 宏         | -            |
| ---------- | ------------ |
| S_ISREG()  | 普通文件     |
| S_ISDIR()  | 目录         |
| S_ISCHR()  | 字符特殊文件 |
| S_ISBLK()  | 块文件       |
| S_ISFIFO() | 管道or fifo  |
| S_ISLNK()  | 符号链接     |
| S_ISSOCK() | 套接字       |

| -                  | -            |
| ------------------ | ------------ |
| S_TYPEISMQ(stat*)  | 消息队列     |
| S_TYPEISSEM(stat*) | 信号量       |
| S_TYPEISSHM(stat*) | 共享存储对象 |

##### 4.4 设置 用户ID & 组ID

| -                |                      |                            |
| ---------------- | -------------------- | -------------------------- |
| 实际用户id       | 我们实际是谁         | 登录时取自口令文件的登录项 |
| 实际用户组       | 我们实际是谁         |                            |
| 有效用户id       | 用于文件访问权限检查 |                            |
| 有效组id         | 用于文件访问权限检查 |                            |
| 附属组id         | 用于文件访问权限检查 |                            |
| 保存的设置用户ID | 由exec函数保存       | 保存了有效用户id和有效组id |
| 保存的设置组ID   | 由exec函数保存       |                            |

| -                     | -    |
| --------------------- | ---- |
| S_ISUID(stat.st_mode) |      |
| S_ISGID(stat.st_mode) |      |

##### 4.5 文件访问权限   stat.mode

| -                     | -        |
| --------------------- | -------- |
| S_IRUSR(STAT.ST_MODE) | 用户读   |
| S_IWUSR()             | 用户写   |
| S_IXUSR()             | 用户执行 |
| ---                   |          |
| S_IRGRP()             | 组读     |
| S_IWGRP()             | 组写     |
| S_IXGRP()             | 组执行   |
| ---                   |          |
| S_IROTH()             | 其他读   |
| S_IWOTH()             | 其他写   |
| S_IXOTH()             | 其他执行 |


```
chmod
```


| -    | -      |
| ---- | ------ |
| u    | 所有者 |
| g    | 组     |
| o    | 其他   |



-----

1. 3类(读,写,执行)访问权限:
   1. 用名字打开任意一个文件,其包含该文件的每个目录都要有**执行**权限
   2. 文件的读权限决定我们是否能打开现有文件进行读操作  这 与open 函数的 O_RDONLY O_RDWR
   3. 写权限  O_RDONLY O_RDWR
   4. open函数指定 O_TRUNC 必须对该文件有写权限
   5. 想在目录创建文件,对该目录必须有**写**权限和**执行**权限
   6. 删除一个文件,对该目录有**写**和**执行**权限,对文件**不需要**有读,写权限
   7. exec执行文件,则对该文件必须有**执行**权限

2. 进程打开,创建 ,删除文件 ,内核对其进行**文件访问权限测试**,涉及到 文件的所有者(st_uid, st_gid),进程的 有效ID(有效用户ID,有效组ID),以及进程的附属ID(如果有的话). 所有者ID是文件性质,有效id,附属id是进程性质
   1. 如果进程的有效ID是0(超级用户)
   2. 如果进程的有效用户ID == 文件的所有者ID,则检查文件的访问相应权限是否被设置了,设置了,则允许,否则拒绝.
   3. 若进程组有效组ID == 文件的组ID,那么组的相应权限被设置,则允许访问,否则拒绝
   4. 若其他用户的相应权限被设置,则允许,否则拒绝