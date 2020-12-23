### VI. 系统数据文件 & 信息

##### 6.1 引言







##### 6.9 系统标识

```c
#include<sys/utsname.h>

int uname(struct utsname*name);
```



```c
struct utsname{
	char sysname[];
	char nodename[];
	char release[];
	char version[];
	char machine[];
}
```





```c
#include <unistd.h>
int gethostname(char*name,int namelen);
```





##### 6.10 时间 日期



```
#include <time.h>
time_t time(time_t *calptr);
```





| clockid_t   标识符       | - 选项 | -说明                    |
| ------------------------ | ------ | ------------------------ |
| CLOCK_REALTIME           |        | 系统实时时间             |
| CLOCK_MONOTONIC          |        | 不带负跳数的实时系统时间 |
| CLOCK_PROCESS-CPUTIME_ID |        | 调用进程的cpu时间        |
| CLOCK_THREAD_CPUTIME_ID  |        | 调用线程的cpu时间        |



```c
#include <sys/time.h>
int clock_gettime(clockid_t clock_id,struct timespec *tsp);
int clock_settime(clockid_t clock_id,struct timespec*tsp);

int gettimeofday(struct timeval*tp,void *tzp);  // tzp = nullptr  forever
```



```c
struct tm{
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
}
```

```c
struct tm*gmtime(const time_t *calptr);
struct tm*localtime(const time_t calptr); // 本地时间

time_t mktime(struct tm*tmptr);//本地时间转换为 time_t

size_t strftime(char* buf,size_t maxsize,char*format,tm*tmptr);
strftime_l
    
char* strptime(char*buf,char*format,struct tm* tmptr);
```

