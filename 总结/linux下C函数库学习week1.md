[TOC]

# **linux下C函数库学习**

##  第一章 字符测试函数

### isalnum 

是否为英文字母或数字，入参为int，返回**int型**TRUE/NULL（0）

测试代码

> ```c
> #include <ctype.h>
> main()
> {
>     char str[]="123c@#FDsp[e?";
>     int i;
>     for(i; str[i] != 0; i++)
>     {
>         if(isalnum(str[i]))
>         {
>             printf("%c is an alphanumeric character\n",str[i]);
>         }
>     }
> }
> ```
>



编译结果

> ```c
> ./test.c: In function ‘main’:
> ./test.c:10: warning: incompatible implicit declaration of built-in function ‘printf’
> ```
>



测试结果

> ```c
> 1 is an alphanumeric character
> 2 is an alphanumeric character
> 3 is an alphanumeric character
> c is an alphanumeric character
> F is an alphanumeric character
> D is an alphanumeric character
> s is an alphanumeric character
> p is an alphanumeric character
> e is an alphanumeric character
> ```

**注意事项**

**1.**最开始判断语句写为if(true == isalnum(str[i]))编译失败（`true' undeclared (first use in this function) or `false' undeclared (first use in this function) ），因为c和早期的c++里没有关键字bool，使用BOOL可以，但BOOL不是内置类型了，都是通过typedef或者宏来定义的，通常都会被定义成int类型。**isalnum返回值为int。**

**2.**gcc不支持for（int i(0); ；i++）的语法，i需要在外部定义。

### isalpha

测试是否为英文字母，同isalnum，入参int，返回**int型**TRUE/NULL（0）

### isascii

测试是否为ASCII码字符，即ASCII码是否在0~127之间，使用方式同上

### 补充

**isdigit**		  是否数字

**isxdigit** 	    是否为16进制数字

**islower**		是否小写

**isupper**	    是否大写

**isspace** 		是否是空格

**iscntrl** 		是否是ASCII控制字符

**isprint**		 是否可打印

**punct**  	     是否为标点或特殊符号

**注** 以上均为宏定义，入参int，返回int型TRUE/NULL（0），使用时须包含头文件<ctype.h>

## 第二章 数据转换函数

### atof

字符串转换为浮点型数，入参const char *，返回double，从字符串第一个数字起到第一个非数字或字符串结尾结束

测试代码

> ```c
> #include <stdlib.h>
> main()
> {
>     char *a = " 367.9";
>     char *b = "  -344.1";
>     float aa = atof(a);
>     float bb = atof(b);
>     printf("a:%.3f\n", aa);
>     printf("b:%.3f\n", bb);
> }
> ```
>

测试结果

a:367.900
b:-344.100

**注意事项：**

1.须包含头文件<stdlib.h>

2.若入参形式错误，例如“s12.3",将会返回0

### 其它

**atoi** 转整形数char*转int

**atol** 转长整形数char*转long

### ecvt fcvt gcvt

char\* ecvt（double，int, int\*，int\*）浮点型转char*，入参（原数，**显示位数**，小数点地址，正负）

char\* fcvt（double，int, int\*，int\*）浮点型转char*，入参（原数，**小数点后位数**，小数点地址，正负）

fcvt与ecvt第二个入参不同，gcvt转换结果包含十进制小数点

char\* **gcvt**(double, size_t, char*)入参（原数，显示位数，返回的指针的地址）

测试代码

> ```c
> #include <stdlib.h>
> main()
> {
>     double a = 123.456;
>     double b = -1234.567;
>     double c = -123456.78;
>     int decpt;    		// position of "."
>     int sign;     		  //+-
>     char* ret;    		//result
>     ret = ecvt(a, 6, &decpt, &sign);
>     printf("123.456 ecvt = %s\n",ret);
>     ret = fcvt(b, 3, &decpt, &sign);
>     printf("-1234.567 fcvt = %s\n",ret);
>     gcvt(c, 8, ret);
>     printf("-123456.78 gcvt = %s\n",ret);
> }
> ```
>

测试结果

> ```c
> #include<string.h>
> main()
> {
>     char s1[] = "abcde";
>     char s2[] = "12345";
>     bcopy(&s1, &s2, 3);
>     printf("%s %s\n", s1, s2);
>     bcopy(&s1, &s2, 5);
>     printf("%s %s\n", s1, s2);
>     bcopy(&s1, &s2, 7);
>     printf("%s %s\n", s1, s2);
> }
> ```



123.456 ecvt = 123456
-1234.567 fcvt = 1234567
-123456.78 gcvt = -123456.78

### 字符串转为数

浮点型 strtod 

长整型 strtol

无符号长整型 strtoul

测试代码

> ```c
> #include <stdlib.h>
> main()
> {
>    char a[] = "100000";
>    printf("100000,10:%d\n", strtol( a, NULL, 0));
>    printf("100000,16:%d\n", strtol( a, NULL, 16));
>    printf("100000, 2:%d\n", strtol( a, NULL, 2));
> }
> ```
>



测试结果

> ```c
> 100000,10:100000
> 100000,16:1048576
> 100000, 2:32
> ```
>

### 大小写转换

tolower/toupper

> ```c
> //实现字符串大小写互换
> #include<stdlib.h>
> #include<ctype.h>
> main()
> {
>     char a[] = "AbCdEfGhIjKlMn";
>     int i;
>     for(i = 0; i < sizeof(a); i++)
>     {
>         if(isupper(a[i]))
>         {
>             a[i] = tolower(a[i]);
>         }else if(islower(a[i]))
>         {
>             a[i] = toupper(a[i]);
>         }
>     }
>     printf("AbCdEfGhIjKlMn:%s\n",a);
> }
> 
> ```
>

测试结果

> ```c
> AbCdEfGhIjKlMn:aBcDeFgHiJkLmN
> ```
>

## 第三章字符串处理

### bcmp

bcmp(const void\*s1, const void \*s2, int n)

比较s1s2所指空间前n个字节，相同则返回0

测试代码

> ```c
> #include<string.h>
> main()
> {
>     char s1[] = "asdfg";
>     char s2[] = "asert";
>     printf("%d\n", bcmp(&s1, &s2, 2));
>     printf("%d\n", bcmp(&s1, &s2,  4));
> }
> 
> ```

测试结果

> ```c
> 0
> -1
> ```

**注：**须包含头文件<string.h>

### bcopy

bcopy(const void\*src, const void\*des, int n)

把第一个指针的内容复制给第二个，n过界自动中断

测试代码

> ```c
> #include<string.h>
> main()
> {
>     char s1[] = "abcde";
>     char s2[] = "12345";
>     bcopy(&s1, &s2, 3);
>     printf("%s %s\n", s1, s2);
>     bcopy(&s1, &s2, 5);
>     printf("%s %s\n", s1, s2);
>     bcopy(&s1, &s2, 7);
>     printf("%s %s\n", s1, s2);
> }
> 
> ```

测试结果

> ```c
> abcde abc45
> abcde abcde
> abcde abcde
> ```

### memcpy

与bcopy类似，前两入参顺序相反

> ```c
> #include<string.h>
> main()
> {
>     char s1[] = "abcde";
>     char s2[] = "12345";
>     memcpy(&s1, &s2, 3);
>     printf("%s %s\n", s1, s2);
>     memcpy(&s1, &s2, 5);
>     printf("%s %s\n", s1, s2);
>     memcpy(&s1, &s2, 7);
>     printf("%s %s\n", s1, s2);
> }        
> ```



> ```c
> 123de 12345
> 12345 12345
> 12345 12345
> ```

### bzero

将指针所指前n个字节置0

bzero(void *s, int n)

返回值为void

测试代码

> ```c
> main()
> {
>     int n[]= {1,2,3};
>     bzero(n, 4);
>     printf("%d\n", n[0]);
> }
> ```

测试

```c
0
```

当n不足int长度时，int清0

> ```c
> main()
> {
>     int n[]= {1,2,3};
>     bzero(n, 1);
>     printf("%d\n", n[0]);
> }
> ```

测试结果

> ```c
> 0
> ```

n不足char长度时，char为空

> ```c
> main()
> {
>     char str[]= {'a','b','c'};
>     bzero(str, 1);
>     printf("%c\n", str[0]);
> }
> ```

测试结果

> ```c
> 
> ```

### ffs

查找第一个值为真的位置，由低位到高位

返回int（0~32）

测试代码

> ```c
> main()
> {
>     int i[] = {0, 3, 5, 6, 9};
>     int j;
>     for(j = 0; j < 5; j++)
>     {
>         printf("%d:%d\n", i[j],ffs(i[j]));
>     }
> }
> ```

测试结果

> ```c
> 0:0
> 3:1
> 5:1
> 6:2
> 9:1
> ```

### index

查找字符串中指定字符

返回值为查找元素的地址，若没有找到则返回空

测试代码

> ```c
> main()
> {
>     char* s = "abcdefg";
>     int j;
>     char* p = index(s, 'd');
>     printf("%p\n", p);
>     printf("%s\n", p);
>     p = index(s, 'z');
>     printf("%p\n", p);
>     printf("%s\n", p);
> }
> ```

测试结果

> ```c
> 0x4006db
> defg
> (nil)
> Segmentation fault (core dumped)
> ```

**注：**strchr同index用法相同，区别在于index查找范围包括结尾'\0'

### memchr

在一定范围内查找指定字符，规定查找范围，其余同index

void \*memchar(const void*s, int c, size_t n)

### memcmp

在指定范围按位比较两字符串字符大小（ASCII顺序先后）

返回第一对不同字符ASCII码差值，int类型

int memcmp(const void\* s1, const void\* s2, size_t n);

测试代码

> ```c
> main()
> {
>     char* a = "abcdefg";
>     char* b = "abcdxyz";
>     char* c = "abcdefg";
>     printf("%d\n", memcmp(a, b, 28));
>     printf("%d\n", memcmp(a, c, 28));
> }
> ```

测试结果

> ```c
> -19
> 0
> ```

经测试，若不限制size_t,会造成操作越界

> ```c
> main()
> {
>     char* a = "abcdefg";
>     char* b = "abcdxyz";
>     printf("%d\n", memcmp(a, b));
> }   
> ```

> ```c
> Segmentation fault (core dumped)
> ```

### memfrob

制定内存前n个字符与42做异或，目的为隐藏内容，再次调用即可还原

返回值void

linux特有

测试代码

> ```c
> #include<stdio.h>
> #include<string.h>
> main()
> {
>     char a[] = "This_is_memfrob";
>     memfrob(a, strlen(a));
>     printf("%s\n", a);
>     memfrob(a, strlen(a));
>     printf("%s\n", a);
> }
> ```
>

测试结果

> ```c
> ~BCYuCYuGOGLXEH
> This_is_memfrob
> ```

经测试，该函数只接受char数组，不接受char*

### memmove

拷贝内容，src到dest

void\* memmove(void\* dest, const void\* src, size_t n)

与memcpy不同的是，当目的与源内存重叠时，memcpy仍可正常处理，但效率低于memcpy

返回目的地址

测试代码

> ```c
> #include<stdio.h>
> #include<string.h>
> main()
> {
>     char a[] = "123456789";
>     memmove(&a[5], &a[0], 3*sizeof(char));
>     printf("%s\n", a);
> }
> ```
>

测试结果

> ```c
> 123451239
> ```
>

### memset

将参数填入内存

返回值为被填入内存的指针

void\* (void\* s, int c, size_t n)

测试代码

> ```C
> #include<stdio.h>
> #include<string.h>
> main()
> {
>     char a[] = "123456789";
>     memset(&a[2], 'X', 5*sizeof(char));
>     printf("%s\n", a);
> }
> ```
>

测试结果

> ```c
> 12XXXXX89
> ```
>

### reindex

查找字符串中最后一次出现的参数地址

返回该字符地址，没找到返回0

测试代码

> ```c
> #include<stdio.h>
> #include<string.h>
> main()
> {
>     char a[] = "123456789";
>     printf("%p\n", rindex(a, '3'));
>     printf("%p\n", rindex(a, 'a'));
> }
> ```



测试结果

> ```c
> 0x7ffca8370582
> (nil)
> ```

### strcasecmp

忽略大小写比较字符串，类似bcmp

测试代码

> ```c
> #include<stdio.h>
> #include<string.h>
> main()
> {
>     char a[] = "aBcDeF";
>     char b[] = "AbCdEf";
>     char c[] = "abc";
>     char d[] = "abcdefg";
>     printf("%d\n", strcasecmp(a, b));
>     printf("%d\n", strcasecmp(a, c));
>     printf("%d\n", strcasecmp(a, d));
> }
> ```

测试结果

> ```c
> 0
> 100
> -103
> ```

### strcat

将第二个字符串拼接在第一个末尾，第一个字符串须保留足够空间

返回第一个字符串地址

测试代码

> ```测试结果
> #include<stdio.h>
> #include<string.h>
> main()
> {
>     char a[] = "aBcDeF";
>     char b[] = "123456";
>     printf("%s\n", strcat(a, b));
> }
> ```

测试结果

> ```c
> aBcDeF123456
> ```

### strcspn

返回不含指定字符串内容的长度

测试代码

> ```c
> #include<stdio.h>
> #include<string.h>
> main()
> {
>     char a[] = "aBcDeF";
>     char b[] = "ce";
>     printf("%d\n", strcspn(a, b));
> }
> ```

测试结果

> ```c
> 2
> ```

### strdup

复制字符串

返回新字符串地址

测试代码

> ```c
> #include<stdio.h>
> #include<string.h>
> main()
> {
>     char a[] = "aBcDeF";
>     char* b = strdup(a);
>     printf("%s\n", b);
> }
> ```

测试结果

> ```c
> aBcDeF
> ```

# 第二周

### strpbrk

char\* strpbrk(const char\* accept, const char\* s)

查找s字符串中最先出现在accept字符串中的任意字符

返回值：找到指定字符，返回其地址，否则返回0

**注：**可以用来截取字符串，但要注意未找到返回0

### strrchr

查找目标字符串中指定元素最后一次出现的地址，类似index

char*strrchr(const char\*, const char\* s)

**注：**同样注意未找到返回0

### strspn

size_t strspn(const char *s, const char * accept);

从s开头开始查找，知道s中某字符不属于accept，返回长度

**注：**返回值为字符数

### strstr（字符串查找）

char* strstr(const char \*haystack, const char \*needle);

在haystack中查找needle

**注：**只返回第一次出现的位置，同样注意未找到返回0



### strtok

char *strtok(char *s, const char *delim);

字符串分割，将s中出现在delim中的字符替换为\0

**注：**第一次调用必须给与参数s字符串，往后s须为NULL

例：拆分字符串并依次打印

> ~~~~~~
> #include<stdio.h>
> #include<string.h>
> main()
> {
>     char s[] = "aBcD.edg?jslgznv;djln.s?F"; 
>     char *delim = ".;?";
>     char *p;
>     printf("%s ", strtok(s, delim)); 
>     while((p = strtok(NULL, delim)))
>     { 
>         printf("%s ",p);
>     } 
>     printf("\n");
> }   
> ~~~

> ~~~c
> aBcD edg jslgznv djln s F
> ~~~

**注：**被分割字符串应当为char[]，不可使用char*  