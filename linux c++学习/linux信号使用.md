例：计算计算机一秒可以数到几
第一版代码：
```c++
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int i;


int main(void)
{
    i = 0;
    alarm(1);
    while(1)
    {
        printf("%d\n", i);
        i++;
    }
    
    return 0;
}

运行结果：
······
91672
91673
91674
91675
91676
91677Alarm clock
分析：io占用过多，结果误差大
```

第二版
```c++
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int i;

void func(int sig)
{
    if(SIGALRM == sig)
    {
        printf("%d\n", i);
        exit(0);
    }
}

int main(void)
{
    signal(SIGALRM, func);
    i = 0;
    alarm(1);
    while(1)
    {
        i++;
    }
    
    return 0;
}
运行结果：
570494586
分析：
自定义信号处理，避免io，优化效率提升6222倍
```