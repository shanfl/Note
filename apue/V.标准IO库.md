### V. 标准I/O库

##### 5.1 引言

标准io处理细节:缓冲区分配,优化块长度执行io ...

##### 5.2 流 & FILE

```c++
#include <stdio.h>
#include <wchar.h>
int fwide(FILE*fp,int mode);

/*
mode >0 设置宽
< 0  字节
= 0 查询
*/
```

##### 5.3 stdin stdout stdout



###### 5.4 缓冲

1. 全缓冲
2. 行缓冲
3. 不缓冲

```c++
#include <stdio.h>
void setbuf(FILE*fp,char*buf);
int setvbuf(FILE*fp,char*buf,int mode,size_t size);

mode
    _IOFBF   全
    _IOLBF   行缓冲
    _IONBF   不缓冲
```



| -函数   | -mode  | -buf | -缓冲区及长度                | -缓冲类型     |
| ------- | ------ | ---- | ---------------------------- | ------------- |
| setbuf  |        | 非空 | 长度位BUFSIZE的用户缓冲区buf | 全缓冲/行缓冲 |
|         |        | null | 无                           | 不带缓冲      |
| setvbuf | _IOFBF | 非空 | 长度为size的用户缓冲区buf    | 全            |
|         |        | null | 合适长度的系统缓冲区buf      | 全            |
|         | _IOLBF | 非空 | 长度为size的用户缓冲区       | 行            |
|         |        | null | 合适长度的系统缓冲区buf      | 行            |
|         | _IONBF |      | 无                           | 不带缓冲      |

```C
#include <stdio.h>
int fflush(FILE*fp);
```

##### 5.5 打开流

```c
#include <stdio.h>
FILE*fopen(char pathname,char*type);
FILE*freopen(char* pathname,type, FILE*fp);
FILE*fdopen(int fd,char*type);
```

| -type        | -intro | -open flag                      |
| ------------ | ------ | ------------------------------- |
| r  / rb      |        | O_RDONLY                        |
| w / wb       |        | O_WRONLY \| O_CREAT \| O_TRUNC  |
| a / ab       |        | O_WRONLY \| O_CREAT \| O_APPEND |
| r+ / r+b rb+ |        |                                 |
| w+  w+b  wb+ |        |                                 |
| a+ a+b ab+   |        |                                 |

