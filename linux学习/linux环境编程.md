[TOC]

# linux服务器编程

## 简介

```
一，环境编程
1.进程相关概念
	并发
	单道程序设计
	多道程序设计
	cpu/mmu
	进程控制块
	进程状态
2.环境变量
	常用环境变量/作用
	函数
3.进程控制原语
	fock函数
		创建子进程的架构
	exec函数族
		各个函数的参数使用方法/作用
	wait/waitpid
		回收子进程的一般方式
```

## 1.环境变量

### ①环境变量是什么

```c++
指操作系统中用来指定操作系统运行环境的一些参数，通常：
1）字符串(本质)
2）有统一格式:名=值[:值]
3)用来描述进程环境信息
存储形式:与命令行参数类似。char*[],数组名environ，内部存储字符串，NULL作为哨兵结尾
使用形式：与命令行参数类似。
加载位置：与命令行参数类似。位于用户区，高于stack的起始位置。
引入环境变量表：须声明环境变量。
extern char** environ;
```

### ②常用环境变量

```shell
查看$PATH:echo $PATH
查看$SHELL:echo $SHELL
查看$HOME:echo $HOME
查看$LANG:echo $LANG
查看$TERM:echo $TERM(终端类型)
```

### ③环境变量函数

```c++
//getenv       
#include <stdlib.h>
char *getenv(const char *name);
//setenv，成功0失败-1 on error
#include <stdlib.h>
int setenv(const char *name, const char *value, int overwrite);
//unsetenv，成功0失败-1 on error
#include <stdlib.h>
int unsetenv(const char *name);
```

## 2.进程控制

### fork函数

```c++
//创建一个子进程
#include <unistd.h>
pid_t fork(void);
//失败返回-1；成功返回：
//①父进程返回子进程的id（非负）
//②子返回0
pid_t
//表示进程id，为了表示-1，它是有符号整形
//0不是有效进程
//init进程最小，为1
```

### getpid

```C++
       #include <sys/types.h>
       #include <unistd.h>

       pid_t getpid(void);
       pid_t getppid(void);

DESCRIPTION
       getpid() returns the process ID of the calling process.  (This is often used by routines that generate unique temporary filenames.)

       getppid() returns the process ID of the parent of the calling process.
```



### getuid/getgid

```c++
       #include <unistd.h>
       #include <sys/types.h>
       uid_t getuid(void);
       uid_t geteuid(void);
DESCRIPTION
       getuid() returns the real user ID of the calling process.
       geteuid() returns the effective user ID of the calling process.

       #include <unistd.h>
       #include <sys/types.h>
       gid_t getgid(void);
       gid_t getegid(void);
DESCRIPTION
       getgid() returns the real group ID of the calling process.
       getegid() returns the effective group ID of the calling process.
```

### 进程共享

```c++
父子进程相同处：
全局变量、data、.text、栈、堆、环境变量、用户id、宿主id、进程工作目录、信号处理方式
父子进程不同处：
1.进程id
2.fock返回值
3.父进程id
4.程序运行时间
4.闹钟（定时器）
5.未决信号集
```

- 父子进程遵循实时共享写时复制的原则

- 进程共享：

  （1）文件描述符

  （2）mmap建立的映射区gdb调试


### gdb调试

```C++
使用gdb调试时，gdb只能跟踪一个进程
set follow-fork-mode child命令设置gdb在fork之后跟踪子进程
set follow-fork-mode parent命令设置gdb在fork之后跟踪父进程
```

### exec函数族

```c++
	fork创建子进程后执行的是和父进程相同的程序（可能执行不同的代码分支），子进程往往要掉用一种exec函数以执行另一个程序。当进程调用一种exec函数时，该进程的用户空间代码和数据完全被新程序替换，从新程序的启动例程开始执行。/*调用exec并不创建新进程，所以调用exec前后盖进程id未改变。*/
	将当前进程的.text、.data替换为所要加载程序的.text、.data，然后让进程从新的.text的第一条指令开始执行，但进程id不变，换核不换壳。
    exec函数：
int execl(const char *path, const char *arg, ...);
int execlp(const char *file, const char *arg, ...);

int execle(const char *path, const char *arg, ..., char *const envp[]);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execvpe(const char *file, char *const argv[], char *const envp[]);
```

#### execlp函数*

```c++
//加载一个进程，借助PATH环境变量
int execlp(const char *file, const char *arg, ...);
//成功无返回，失败返回-1
//参数1：要加载的程序的名字。该函数需要配合PATH环境变量来用，当PATH中所有目录搜索后没有参数1则出错返回。
//该函数通常用来调用系统程序,如ls\date\cp\cat等
```

例：

```c++
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork();
    if(pid == -1)
    {
        perror("fork error!");
        exit(1);
    }else if(pid > 0)
    {
        printf("parent!\n");
    }else
    {
        execlp("ls", "ls", "-a", "-l", NULL);
    }
    return 0;
}
```

#### execl函数*

```c++
//加载一个进程，通过路径+程序名来加载
int execl(const char *path, const char *arg, ...);
//成功无返回，失败返回-1
//对比execlp
execlp("ls", "ls", "-l", "-F", NULL);		//使用程序名在PATH中搜索
execl("/bin/ls", "ls", "-l", "-F", NULL);	//使用参数1给出的路径搜索
```

#### execle函数?

```c++
int execle(const char *path, const char *arg, ..., char *const envp[]);
```

例：

#### execv函数

```c++
int execv(const char *path, char *const argv[]);
```

例：

```c++
char * argv[] = {(char *)"ls", (char *)"-l", (char *)"-a", (char *)"-h", (char *)NULL};
execv("/bin/ls", argv);
```

#### execvp函数

```c++
//加载一个进程，使用自定义环境变量env
int execvp(const char *file, char *const argv[]);
```

例：

```c++
char * argv[] = {(char *)"ls", (char *)"-l", (char *)"-a", (char *)"-h", (char *)NULL};
execvp("ls", argv);
```

#### execvpe函数？

```c++
int execvpe(const char *file, char *const argv[], char *const envp[]);
```

例：

```c++

```

## 3.进程回收

### 1.孤儿进程

```c++
父进程结束，子进程被称为孤儿进程，孤儿被init领养，init进程变为孤儿进程的父亲
为了释放子进程所占用的系统资源
//进程结束后，能够释放用户区空间
//释放不了pcb，必须由父进程释放
```

### 2.僵尸进程

```c++
子进程结束，父进程不释放子进程的pcb，该子进程被称为僵尸进程
僵尸进程不是一个活着的进程
```

### 3.进程回收

#### （1）wait 阻塞函数

```c++
#include <sys/types.h>  
#include <sys/wait.h>
pid_t wait (int * status);
/*函数说明：wait()会暂时停止目前进程的执行, 直到有信号来到或子进程结束. 如果在调用wait()时子进程已经结束, 则wait()会立即返回子进程结束状态值. 子进程的结束状态值会由参数status 返回, 而子进程的进程识别码也会一快返回. 如果不在意结束状态值, 则参数 status 可以设成NULL.*/
//被调用一次只能回收一个子进程
//返回值：
如果执行成功则返回子进程识别码(PID), 如果有错误发生则返回-1. 失败原因存于errno 中.
//参数status:
进程一旦调用了wait，就立即阻塞自己，由wait自动分析是否当前进程的某个子进程已经退出。如果让它找到了这样一个已经变成僵尸的子进程，wait就会收集这个子进程的信息，并把它彻底销毁后返回；如果没有找到这样一个子进程，wait就会一直阻塞在这里，直到有一个出现为止。

参数status用来保存被收集进程退出时的一些状态，它是一个指向int类型的指针。但如果我们对这个子进程是如何死掉的毫不在意，只想把这个僵尸进程消灭掉，（事实上绝大多数情况下，我们都会这样想），我们就可以设定这个参数为NULL，就象下面这样：
pid = wait(NULL); 
如果成功，wait会返回被收集的子进程的进程ID，如果调用进程没有子进程，调用就会失败，此时wait返回-1，同时errno被置为ECHILD。

WIFEXITED(status) 这个宏用来指出子进程是否为正常退出的，如果是，它会返回一个非零值。

WEXITSTATUS(status) 当WIFEXITED返回非零值时，我们可以用这个宏来提取子进程的返回值，如果子进程调用exit(5)退出，WEXITSTATUS(status)就会返回5；如果子进程调用exit(7)，WEXITSTATUS(status)就会返回7。请注意，如果进程不是正常退出的，也就是说，WIFEXITED返回0，这个值就毫无意义

WIFSIGNALED(status):非0时说明进程异常终止
若上宏为真，此时可通过
    WTERMSIG(status)
获取使得进程退出的信号编号
    
if(WIFSIGNALED(status))
{
    printf("使得进程终止的信号编号： %d\n",WTERMSIG(status));   
}
```

#### （2）waitpid





