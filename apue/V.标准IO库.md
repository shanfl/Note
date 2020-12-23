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
| r+ / r+b rb+ |        | O_RDWR                          |
| w+  w+b  wb+ |        | O_RDRW \| O_CREAT \| O_TRUNC    |
| a+ a+b ab+   |        | O_RDRW \| O_CREAT \| O_APPEND   |

```c
#include <stdio.h>
int fclose(FILE*fp);
```



##### 5.6 读 & 写 流

```c
#include <stdio.h>
int getc(FILE*fp);
int fgetc(FILE*fp);
int getchar(void);


int ferror(FILE*fp);
int feof(FILE*fp);


void clearerr(FILE*fp);

int ugetc(int c,FILE*fp);
```





```c
int putc(int c,FILE*fp);
int fputc(int c,FILE*fp);
int putchar(int c);
```





##### 5.7 行I/O

```c
char* fgets(char*buf,int n ,FILE*fp);
char* gets(char*buf);

int fputs(char*str,FILE*fp);
int puts(char*str);
```



##### 5.8 标准I/O效率



##### 5. 9  二进制I/O

```c
size_t fread(void * ptr,size_t size ,size_t nobj,FILE*fp);
size_t fwrite(const void *Ptr,size_t size size_t nobj,FILE*fp);
```



##### 5.10 定位流



```c
long ftell(FILE*fp);
int fseek(FILE*fp,long offset,int whence);
void rewind(FILE*fp);
```



```c
off_t ftello(FILE*fp);
int fseeko(FILE*fp,off_t offset,int whence);
```



```c
int fgetpos(FILE*fp,fpos_t *pos);
int fsetpos(FILE*fp,fpos_t *pos);
```



##### 5.11 格式化 i/o

1. 格式化输出

   ```c
   printf
   fprintf
   dprintf
   sprintf
   snprintf
   ```

   ```c
   vprintf
   vfprintf
   vdprintf
   vsprintf
   vsnprintf
   ```



2. 格式化输入

   ```c
   [v]scanf
   [v]fscanf
   [v]sscanf
   
   ```

   

##### 5.12 

```c
int fileno(FILE*fp);  //posix.1
```





##### 5.13 临时文件



```c
char*tmpnam(char*ptr);
FILE*tmpfile(void);



#include <stdlib.h>
char*mkdtemp(char*tmplate);
int mkstemp(char*template);
```



##### 5.14 内存流

```c
#include <stdio.h>
FILE*fmemopen(void*buf,size_t size,char*type);
```





| type          |      |
| ------------- | ---- |
| r    /    rb  |      |
| w  wb         | -    |
| a   / ab      |      |
| r+   r+b  rb+ |      |
| w+  w+b  wb+  |      |
| a+  a+b ab+   |      |

```c
#include <stdio.h>
FILE* open_memstream(char**bufp,size_t*sizep);


#include <wchar.h>
FILE*open_wmemstream(wchar_t ** bufp,size_t sizep);
```

