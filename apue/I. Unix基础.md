### 1.unix基础

##### 1.1 引言

##### 1.2 unix 体系结构

##### 1.3  登录

###### 1 登录名

 /etc/passwd

```bash
|登录名|加密口令|用户id|组id|注释字段|其实目录|shell|

root:x:0:0:root:/root:/bin/bash
```



​    shell

##### 1.4 文件&目录

1.文件系统

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
   
   ```cpp
          #include <sys/types.h>
          #include <sys/stat.h>
          #include <fcntl.h>
   
          int open(const char *pathname, int flags);
          int open(const char *pathname, int flags, mode_t mode);
   
          int creat(const char *pathname, mode_t mode);
   
          int openat(int dirfd, const char *pathname, int flags);
          int openat(int dirfd, const char *pathname, int flags, mode_t mode);
   
          /* Documented separately, in openat2(2): */
          int openat2(int dirfd, const char *pathname,
                      const struct open_how *how, size_t size);
   
   ```
   
   ```cpp
   #include <unistd.h>
   ssize_t read(int fd, void *buf, size_t count);
   ```
   
   ```c
   #include <unistd.h>
   ssize_t write(int fd, const void *buf, size_t count);
   ```
   
   ```c
   #include <unistd.h>
   int close(int fd);
   ```
   
   
4. unistd.h  `open read write lseek close`
   1. STDIN_FILENO(0) STDOUT_FILENO(1)  STDERR_FILENO(2)
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

```C
#include <sys/types.h>
#include <unistd.h>
pid_t fork(void);
```

`https://stackoverflow.com/questions/21558937/i-do-not-understand-how-execlp-works-in-linux`

```c
       #include <unistd.h>

       extern char **environ;

       int execl(const char *pathname, const char *arg, ...
                       /* (char  *) NULL */);
       // p- search in ‘PATH’
       int execlp(const char *file, const char *arg, ...
                       /* (char  *) NULL */);
       int execle(const char *pathname, const char *arg, ...
                       /*, (char *) NULL, char *const envp[] */);
       int execv(const char *pathname, char *const argv[]);
       int execvp(const char *file, char *const argv[]);
       int execvpe(const char *file, char *const argv[],
                       char *const envp[]);

```



```c
       #include <sys/types.h>
       #include <sys/wait.h>

       pid_t wait(int *wstatus);

       pid_t waitpid(pid_t pid, int *wstatus, int options);

       int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);
                       /* This is the glibc and POSIX interface; see
                          NOTES for information on the raw system call. */

```

```bash
-----------------------------------------------------------------------
The value of pid can be:

       < -1   meaning  wait  for  any  child process whose process group ID is
              equal to the absolute value of pid.

       -1     meaning wait for any child process.

       0      meaning wait for any child process whose  process  group  ID  is
              equal  to that of the calling process at the time of the call to
              waitpid().

       > 0    meaning wait for the child whose process  ID  is  equal  to  the
              value of pid.
------------------------------------------------------------------------       
 The  value  of  options  is an OR of zero or more of the following con‐
       stants:

       WNOHANG
              return immediately if no child has exited.

       WUNTRACED
              also  return  if  a  child  has  stopped  (but  not  traced  via
              ptrace(2)).   Status  for  traced children which have stopped is
              provided even if this option is not specified.

       WCONTINUED (since Linux 2.6.10)
              also return if a stopped child has been resumed by  delivery  of
              SIGCONT.

```





##### 1.7 出错处理



```c
errno.h
/* The error code set by various library functions.  */
extern int *__errno_location (void) __THROW __attribute_const__;
# define errno (*__errno_location ())
```

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
3. 附属组(supplementary group ID) `/etc/group`
   
   ```ini
   允许一个用户属于多至16个其他组,posix要求至少8个
   ```
   
   ```bash
   shanfl@shanfl:/media/shanfl/KINGSTON1/Note/build$ cat /etc/group | grep shanfl
   adm:x:4:syslog,shanfl
   cdrom:x:24:shanfl
   sudo:x:27:shanfl
   dip:x:30:shanfl
   plugdev:x:46:shanfl
   lpadmin:x:122:shanfl
   lxd:x:134:shanfl
   shanfl:x:1000:
   sambashare:x:135:shanfl
   ```
   
   

##### 1.9 信号 signal

```bash
kill -l
>
 1) SIGHUP	 2) SIGINT	 3) SIGQUIT	 4) SIGILL	 5) SIGTRAP
 6) SIGABRT	 7) SIGBUS	 8) SIGFPE	 9) SIGKILL	10) SIGUSR1
11) SIGSEGV	12) SIGUSR2	13) SIGPIPE	14) SIGALRM	15) SIGTERM
16) SIGSTKFLT	17) SIGCHLD	18) SIGCONT	19) SIGSTOP	20) SIGTSTP
21) SIGTTIN	22) SIGTTOU	23) SIGURG	24) SIGXCPU	25) SIGXFSZ
26) SIGVTALRM	27) SIGPROF	28) SIGWINCH	29) SIGIO	30) SIGPWR
31) SIGSYS	34) SIGRTMIN	35) SIGRTMIN+1	36) SIGRTMIN+2	37) SIGRTMIN+3
38) SIGRTMIN+4	39) SIGRTMIN+5	40) SIGRTMIN+6	41) SIGRTMIN+7	42) SIGRTMIN+8
43) SIGRTMIN+9	44) SIGRTMIN+10	45) SIGRTMIN+11	46) SIGRTMIN+12	47) SIGRTMIN+13
48) SIGRTMIN+14	49) SIGRTMIN+15	50) SIGRTMAX-14	51) SIGRTMAX-13	52) SIGRTMAX-12
53) SIGRTMAX-11	54) SIGRTMAX-10	55) SIGRTMAX-9	56) SIGRTMAX-8	57) SIGRTMAX-7
58) SIGRTMAX-6	59) SIGRTMAX-5	60) SIGRTMAX-4	61) SIGRTMAX-3	62) SIGRTMAX-2
63) SIGRTMAX-1	64) SIGRTMAX
```



```C++
static void sig_int(int)
{...}

...
signal(SIGINT,sig_int);
```

```cpp
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <wait.h>
#include <iostream>

static void sig_int(int);


#define MAXLINE 1024
int main(){
    char buff[MAXLINE];
    pid_t pid;
    int status;

    if(signal(SIGINT,sig_int) == SIG_ERR){
        fprintf(stderr,"signal error\n");
    }

    while(fgets(buff,MAXLINE,stdin)!=nullptr){
        if(buff[strlen(buff)-1] == '\n')
            buff[strlen(buff)-1] = 0;
        
        if((pid=fork()) < 0){
            fprintf(stderr,"fork error\n");
        }else if(pid == 0) // child
        {
            execlp(buff,buff,nullptr);
            fprintf(stderr,"couldn't execute %s error\n",buff);
            return 0;
        }

        if((pid = waitpid(pid,&status,0))<0){
            perror("watipid error");
        }

        printf("%% ");
    }

    return 0;
}

void sig_int(int signo){
    std::cout << "interrupt signo:" << signo << std::endl;
}
```



##### 1.10  时间值

1. 日历时间(time_t)   clock_t sysconf

2. 进程时间 (clock_t)
   
   1. 时钟时间
   2. 用户cpu时间
   3. 系统cpu时间

3. `time -P  grep POSIX_SOURCE */*.h > /dev/null `

##### 1.11 系统调用 & 库函数'

'