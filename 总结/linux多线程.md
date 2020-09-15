linux多线程学习

### 线程的概念

又称轻量级进程，是程序执行的最小单位，系统独立调度和分派cpu的基本单位，它是进程的一个实体，一个进程可以有多个实体，这些线程共享进程的所有资源，线程本身只包含一点必不可少的资源。

进程出现了许多弊端，一是由于进程是资源拥有者，创建、取消和切换存在较大的时空开销，因此需要引入轻型进程；二是由于对称多处理机（SMP）的出现，可以满足多个运行单位，而多个进程并行开销过大。

### 线程创建

|            |       线程       |   进程   |
| :--------: | :--------------: | :------: |
| 标识符类型 |    pthread_t     |  pid_t   |
|   获取id   |  pthread_self()  | getpid() |
|    创建    | pthread_create() |  fork()  |

线程id在linux中为unsigned long int，可打印

```
`int` `pthread_create(pthread_t *tidp,``const` `pthread_attr_t *attr,``void` `*(*start_rtn)(``void``*),``void` `*arg);`
```

创建线程并打印主附线程id

```c
#include <pthread.h>
#include <stdio.h>

void print_id(char *s)
{
        pid_t pid;
        pthread_t tid;

        pid = getpid();
        tid = pthread_self();
        printf("%s pid is %u, tid is 0x%x\n", s, pid, tid);
}

void *thread_fun(void *arg)
{
        print_id(arg);
        return (void *)0;
}

int main()
{
        pthread_t ntid;
        int err;

        err = pthread_create(&ntid, NULL, thread_fun, "new thread");
        if(0 != err)
        {
                printf("new thread failed\n");
                return 0;
        }
        print_id("main_thread:");
        sleep (2);

        return 0;
}                                  
```



### 主副线程

1.当c程序运行，首先运行main函数，该执行流被称作主线程/初始线程；

2.主线程main函数返回，会导致进程结束，关闭所有线程，可以在主线程调用pthread_exit()函数，这样主进程会等待所有线程结束再终止；

3.主线程接收参数通过argc和argv,普通线程只有参数void*;

4.绝大多数情况下，主线程在默认堆栈上运行，该堆栈可以增长到足够长度，而普通线程的堆栈是受限制的，一旦溢出就会产生错误；

5.主线程随着进程创建而创建；

6.其它线程可以通过调用函数来创建，主要调用pthread_create;

7.新线程可能在当前线程从函数pthread_create返回之前就已经运行了，甚至新线程可能在当前线程从函数pthread_create返回至前就已经运行完毕了。