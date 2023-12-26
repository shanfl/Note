#### VI. 文件&目录

##### 4.1 引言

`stat`

更改所有者 权限

unix文件系统结构 符号链接

目录操作函数

降序遍历目录函数编写

##### 4.2 stat  fstat fstatat lstat

```c
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <unistd.h>

   int stat(const char *pathname, struct stat *statbuf);
   int fstat(int fd, struct stat *statbuf);
   int lstat(const char *pathname, struct stat *statbuf);  //连接符号信息

   #include <fcntl.h>           /* Definition of AT_* constants */
   #include <sys/stat.h>

   int fstatat(int dirfd, const char *pathname, struct stat *statbuf,
               int flags);      
   fd 是 AT_FDCWD ,且pathname是相对文件路径，则根据当前目录开始计算绝对路径
   flags: AT_SYMLIK_NOFOLLOW 不会跟随连接追溯到实际文件，而是连接本身的信息
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

```c
           struct stat {
               dev_t     st_dev;         /* ID of device containing file */
               ino_t     st_ino;         /* Inode number */
               mode_t    st_mode;        /* File type and mode */
               nlink_t   st_nlink;       /* Number of hard links */
               uid_t     st_uid;         /* User ID of owner */
               gid_t     st_gid;         /* Group ID of owner */
               dev_t     st_rdev;        /* Device ID (if special file) */
               off_t     st_size;        /* Total size, in bytes */
               blksize_t st_blksize;     /* Block size for filesystem I/O */
               blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */

               /* Since Linux 2.6, the kernel supports nanosecond
                  precision for the following timestamp fields.
                  For the details before Linux 2.6, see NOTES. */

               struct timespec st_atim;  /* Time of last access */
               struct timespec st_mtim;  /* Time of last modification */
               struct timespec st_ctim;  /* Time of last status change */

           #define st_atime st_atim.tv_sec      /* Backward compatibility */
           #define st_mtime st_mtim.tv_sec
           #define st_ctime st_ctim.tv_sec
           };
```

##### 4.3 文件类型   信息位于  `struct stat.st_mode`

1. 普通文件 regular file
2. 目录文件 directory file
3. 块文件 block special file 
4. 字符特殊文件 character special file
5. FIFO ,这种类型的文件用于进程间通信，有时也称为 命名管道（named pipe）
6. socket
7. symbolic link

| 宏          | -         |
| ---------- | --------- |
| S_ISREG()  | 普通文件      |
| S_ISDIR()  | 目录        |
| S_ISCHR()  | 字符特殊文件    |
| S_ISBLK()  | 块文件       |
| S_ISFIFO() | 管道or fifo |
| S_ISLNK()  | 符号链接      |
| S_ISSOCK() | 套接字       |

| - 宏                | - 对象的类型 |
| ------------------ | ------- |
| S_TYPEISMQ(stat*)  | 消息队列    |
| S_TYPEISSEM(stat*) | 信号量     |
| S_TYPEISSHM(stat*) | 共享存储对象  |

##### 4.4 设置 用户ID & 组ID

与一个进程相关联的id有6个或更多。

| -         |            |                 |
| --------- | ---------- | --------------- |
| 实际用户id    | 我们实际是谁     | 登录时取自口令文件的登录项   |
| 实际用户组     | 我们实际是谁     | 登录时取自口令文件的登录项   |
| 有效用户id    | 用于文件访问权限检查 |                 |
| 有效组id     | 用于文件访问权限检查 |                 |
| 附属组id     | 用于文件访问权限检查 |                 |
| 保存的设置用户ID | 由exec函数保存  | 保存了有效用户id和有效组id |
| 保存的设置组ID  | 由exec函数保存  |                 |

| -                     | -   |
| --------------------- | --- |
| S_ISUID(stat.st_mode) |     |
| S_ISGID(stat.st_mode) |     |

##### 4.5 文件访问权限   stat.mode

| -                     | -    |
| --------------------- | ---- |
| S_IRUSR(STAT.ST_MODE) | 用户读  |
| S_IWUSR()             | 用户写  |
| S_IXUSR()             | 用户执行 |
| ---                   |      |
| S_IRGRP()             | 组读   |
| S_IWGRP()             | 组写   |
| S_IXGRP()             | 组执行  |
| ---                   |      |
| S_IROTH()             | 其他读  |
| S_IWOTH()             | 其他写  |
| S_IXOTH()             | 其他执行 |

```
chmod
```

| -   | -   |
| --- | --- |
| u   | 所有者 |
| g   | 组   |
| o   | 其他  |

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

##### 4.6 新文件&目录所有权

新文件的用户ID设置为进程的有效用户ID. 

关于组ID

1. 新文件的组ID可以是进程的有效组ID
2. 新文件的组ID可以是它所在目录的组ID

##### 4.7 函数 access & faccessat

如上所说,open 时,内核以进程的<b>有效用户ID</b>和<b>有效组ID</b>为基础执行其访问权限**测试**. 但是,有时候进程也希望按其 <b>实际用户ID</b>和<b>实际组ID</b>来测试访问能力.

access & faccessat 是按照实际用户ID和实际组ID进行访问权限检测的.

```c
#include <unistd.h>
int access(const char* pathname,int mode);
int faccessat(int fd,const char* pathname,int mode,int flag); 
/*
    flags = AT_EACCESS 则采用有效用户/组ID,而不是实际.
*/

faccessat(AT_FDCWD,pathname,...) = access(pathname,mode,...)
```

| mode | intro  |
| ---- | ------ |
| R_OK | 测试读权限  |
| W_OK | 测试写权限  |
| X_OK | 测试执行权限 |

##### 4.8 umask

```c
#include <sys/stat.h>
mode_t umask(mode_t cmask);
/*
S_IRUSR
S_IWUSR
S_IXUSR
S_IRGRP
S_IWGRP
S_IXGRP
S_IROTH
S_IWOTH
S_IXOTH
*/
```

```
umask
umask -S
umask 027
```

##### 4.9 chmod fchmod fchmodat

```c
#include <sys/stat.h>
int chmod(const char*pathname,mode_t mode);
int fchmod(int fd,mode_t mode);

// AT_FDCWD
int fchmodat(int fd,const char*pathname,mode_t ,int flag);        
```

| mode    | intro |
| ------- | ----- |
| S_ISUID |       |
| S_ISGID |       |
| S_ISVTX |       |
| ---     |       |
| S_IRWXU |       |
| S_IRUSR |       |
| S_IWUSR |       |
| S_IXUSR |       |
| ---     |       |
| S_IRWXG |       |
| S_IRGRP |       |
| S_IWGRP |       |
| S_IXGRP |       |
| ---     |       |
| S_IRWXO |       |
| S_IROTH |       |
| S_IWOTH |       |
| S_IXOTH |       |

##### 4.10 粘着位

/tmp  /var/tmp

##### 4.11 chown fchown fchownat lchown

```c++
#include <unistd.h>
int chown(const char*pathname,uid_t owner,gid_t group);
int fchown(int fd,uid_t owner,gid_t group,int flag);
int fchownat(int fd,const *pathname,uid_t owner,gid_t group,int flag);
int lchown(const char*pathname,uid_t owner,gid_t group,)
```

flag 设置 AT_SYMLINK_NOFOLLOW    更改符号链接本身的所有者  fchownat == lchown

##### 4.12 文件长度

stat.st_size  字节为单位的长度只对普通文件，目录文件，和符号连接有意义

```c
st_blksize
st_blocks
```

##### 4.13 文件截断

```c++
#include <unistd.h>
int truncate(const char*pathname,off_t length);
int ftruncate(int fd,off_t length);
```

##### 4.14 文件系统

##### 4.15 link  linkat  unlink  unlinkat  & remove  硬链接

```c++
#include <unistd.h>
int link(const char*existingpath,const char*newpath);
int linkat(const int efd,const char*existingpath,int nfd,const char*newpath,int flag);

int unlink(const char* pathname);
int unlinkat(int fd,const char*pathname,int flag);


#include <stdio.h>
int remove(const char*pathname);
```

##### 4.16 rename & renameat

```
#include<stdio.h>
int rename(const char*oldname,const char*newname);
int renameat(int oldfd,const char*oldname,int newfd,const char*newname);
```

##### 4.17 符号链接

硬链接 直接指向文件的i节点

##### 4.18 创建 & 读取符号链接

```c++
#include <unistd.h>
int symlink(const char* actualpath,const char*sympath);
int symlinkat(const char*actualpath,int fd,const char*sympath);
```

因为open函数跟随符号链接直达链接所指向的文件,而符号链接本身的读取需要其他函数提供

```c++
#include <unistd.h>
ssize_t readlink(constchar*restrict pathname,char* buf,size_t bufsize);
ssize_t readlinkat(int fd,char*pathname,char*buf,size_t bufsize);

/*
    如果 fd = AT_FDCWD readlinkat = readlink
*/
```

##### 4.19 文件时间

| -字段     | -说明         | -例子         | -ls 选项  |
| ------- | ----------- | ----------- | ------- |
| st_atim | 文件数据最后访问时间  | read        | -u      |
| st_mtim | 文件数据最后更改时间  | write       | default |
| st_ctim | i节点状态最后更改时间 | chmod chown | -c      |

`i节点的信息 与 文件的实际内容是分开的`

##### 4.20 futimens  utimensat  utimes

```c++
#include <sys/stat.h>
int futimens(int fd,const struct timespec times[2]);
int utimensat(int fd,const char*path,const struct timespec times[2],int flag);

#include <sys/time.h>
int utimes(const char*pathname,const struct timeval times[2]);
```

```
struct timeval{
    time_t tv_sec;
    time_t tv_usec;
}
```

##### 4.21 mkdir mkdirat rmdir

```c++
#include <sys/stat.h>
int mkdir(const char*pathname,mode_t mode);
int mkdirat(int fd,const char*pathname,mode_t mode);

#include <unistd.h>
int rmdir(const char*dirname);
```

##### 4.22 读目录

```c++
#include <dirent.h>
DIR*opendir(const char* pathname);
DIR*fdopendir(int fd);

struct dirent *readdir(DIR*dp);
void rewinddir(DIR*dp);
int closedir(DIR*dp);

long telldir(DIR*dp);

void seekdir(DIR*dp,long loc);
```

```
struct dirent{
...
    ino_t d_ino;
    char d_name[];
}
```

##### 4.23 chdir fchdir  getcwd

```c++
// 更改当前工作目录
#include <unistd.h>
int chdir(const char*pathname);
int fchdir(int fd);

char* getcwd(char*buf,size_t size);
```

##### 4.24 设备特殊文件 st_dev  st_rdev

##### 4.25 文件访问权小结
