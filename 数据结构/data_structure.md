- [红黑树](#红黑树)
- [stl红黑树](#stl红黑树)
- [set、multiset](#setmultiset)
- [map,multimap](#mapmultimap)
- [hashtable](#hashtable)
- [unorderd容器](#unorderd容器)
# 红黑树
关联容器都有一个key（键）和一个value（值）。当元素被插入到关联式容器中时，内部结构依照其键值的大小，以特定的规则将元素放到合适的位置（实现查找算法吧）。
一般关联时容器内部结构是一个平衡二叉树，用于在恶劣的环境下获得良好的搜寻效率。平衡二叉树的实现有：AVL-tree、RB-tree、AA-tree。用的最广的就是RB-tree，不论是在Nginx还是Linux内核任务调度，都使用广泛，所以在STL中也不例外。

关联式容器分为set(集合)和map（映射）两大类，以及衍生出来的multiset（多键集合）和multimap（多键映射）。这些容器都是通过红黑树实现。所以这节就详细讲讲STL里面各种树的实现。
```
关联式容器：
RB-tree
set
map
multset
,ultmap
hashtable
hash_set
hash_map
hash_multiset
hash_multimap
```
*平衡二叉搜索树（AVL-Tree）：保证任何节点的左右子树高度相差最大1。*

```
1.红黑树是一种特化的AVL树（平衡二叉树），都是在进行插入和删除操作时通过特定操作保持二叉查找树的平衡，从而获得较高的查找性能。它可以在O(log n)时间内做查找，插入和删除。
2.红黑树是一种平衡二叉查找树的变体，它的左右子树高差有可能大于 1，所以红黑树不是严格意义上的平衡二叉树（AVL），但  对之进行平衡的代价较低， 其平均统计性能要强于 AVL 。
3.由于每一棵红黑树都是一颗二叉排序树，因此，在对红黑树进行查找时，可以采用运用于普通二叉排序树上的查找算法，在查找过程中不需要颜色信息。
```

```
红黑树的性质：
性质1. 结点是红色或黑色。 
性质2. 根结点是黑色。 
性质3.所有叶子都是黑色。（叶子是NIL结点） 
性质4. 每个红色结点的两个子结点都是黑色。（从每个叶子到根的所有路径上不能有两个连续的红色结点）
性质5.. 从任一节结点其每个叶子的所有路径都包含相同数目的黑色结点。
```
**红黑树是通过比较key建成的平衡二叉树，所以不允许随意更改key值，但是可以修改节点里面对应的data值，这就是为set和map提供了思路。**


# stl红黑树
1.不应该使用迭代器直接改变元素值
2.rb_tree提供两种插入操作：insert_unique()和insert_equal()
```c++
#include <algorithm>
#include <bits/stl_tree.h>
#include <stdio.h>
using namespace std;

int main()
{
    int nums[] = {3,1,2,5,2,4,6,7,45,4,67,7,8,9,35,36,7,78};
    _Rb_tree<int , int , _Identity<int> , less<int> > itree;
    int N = (int)(sizeof(nums)/sizeof(int));
    for(int i = 0; i < N; i++)
    {
        itree._M_insert_equal(nums[i]);
    }
    for_each(itree.begin(), itree.end(), [](int x){
        printf("%d ", x);
    });
    printf("\ncount 7 = %ld\n", (int)itree.count(7));
    printf("tree's size = %d\n", (int)itree.size());
    return 0;


/*
itree.size();
itree.count(T);
itree.empty();
itree.swap();
itree._M_insert_equal(T);
itree._M_insert_unique(T);
*/
```

# set、multiset
以_RB_tree为底层结构，因此有**元素自动排序**的特点，排序依据就是key，而set/multiset元素的value/key合一:value就是key

无法使用set/multiset的iterator改变元素值，因为key有其严谨排序规则。set/multiset的iteration是其底部RB tree的const-iterator，就是为了禁止user对元素赋值

set的key必须独一无二,因此insert()用的是rb_tree的itree._M_insert_unique(),map则是itree._M_insert_equal();

```c++
#include <algorithm>
#include <set>
#include <stdio.h>
using namespace std;

template<class Key, class Compare = less<Key>, class Alloc = alloc>
class set
{
private:
    typedef rb_tree<key_type, value_type, identity<value_type>, key_compare, Alloc> rep_type;
    rep_type t;
    ···
}

int main()
{
    int nums[] = {3,1,2,5,2,4,6,7,45,4,67,7,8,9,35,36,7,78};
    set<int> iset;
    int N = (int)(sizeof(nums)/sizeof(int));
    for(int i = 0; i < N; i++)
    {
        iset.insert(nums[i]);
    }
    for_each(iset.begin(), iset.end(), [](int x){
        printf("%d ", x);
    });
    printf("\ncount 7 = %d\n", (int)iset.count(7));
    printf("set's size = %d\n", (int)iset.size());
    return 0;
}
```
set的所有操作都会转化为呼叫底层t的操作，从这个意义上来看，set是个container adapter


# map,multimap
底层为rb_tree,依据key自动排序

map提供遍历操作及iterator，无法使用iterator改变元素的key，但可以使用它改变data，因此map/multimap内部自动将user指定的key type设为const，以此禁止user对key赋值,**map元素key独一无二，因此insert()用的是rb_tree的insert_unique(),multimap元素key可以重复，因此insert()用的是rb_tree的insert_equal()**
```c++
template<class Key, class T, class Compare = less<Key>, class Alloc=alloc>
class map
{
public:
    typedef Key key_type;
    typedef T data_type;
    typedef T mapped_type;
    typedef pair<const Key, T> value_type;
    typedef Compare key_compare;
    typedef typename rep_type::iterator iterator;
private:
    typedef rb_tree<key_type, value_type,         select1st<value_type>, key_compare, Alloc>rep_type;
    rep_type t;
    ···
};
```

```c++
#include <algorithm>
#include <map>
#include <stdio.h>
#include <string>
#include <stdexcept>
#include <stdlib.h>
#include <ctime>
using namespace std;

void test_multimap(long value,multimap<long, string> &c)
{
    char buf[10];
    clock_t timeStart = clock();
    printf("start-seconds: %ld\n", timeStart);
    for(long i = 0; i < value; i++)
    {
        try
        {
            snprintf(buf, 10, "%d", (rand() % 100000));
            c.insert(pair<long, string>(atoi(buf), string(buf)));
        }
        catch(exception& p)
        {
            printf("i= %ld %s\n", i, p.what());
            abort();
        }
    }
    printf("milli-seconds: %ld\n", clock() - timeStart);
    printf("c.size = %ld\n", c.size());
}

void test_mapfind(multimap<long, string> &imap, const long x)
{
    clock_t timeStart = clock();
    multimap<long, string>::iterator pItem = imap.find(x);
    printf("time %ld\n", clock() - timeStart);
    if(imap.end() != pItem)
        printf("found \n"); 
    else
        printf("not\n");
}

int main()
{
    multimap<long, string> c;
    test_multimap(1000000, c);
    char buf[10];
    snprintf(buf, 10, "%d", (rand() % 100000));
    printf("target %s\n", buf);
    test_mapfind(c, atoi(buf));
    
    return 0;
}

start-seconds: 0
milli-seconds: 1570000
c.size = 1000000
target 26689
time 0
found 
```
map独有：operator[]

# hashtable 
```c++
template<class Value, class key, class HashFcn, class Extractkey, class EqualKey, class Alloc = alloc>
class hashtable
{
public:
    typedef HashFcn     hasher;
    typedef EqualKey    key_equal;
    typedef size_t      size_type;
private:
    hasher      hash;                       //1
    key_equal   equals;                     //1
    Extractkey  get_key;                    //1

    typedef _hashtable_node<Value> node;
    vector<node *, Alloc>   buckets;        //12
    size_type num_elements;                 //4         19->20  
public:
    size_type bucket_count() const {return buckets.size();}
    ···
}
```

```c++
hash< int>到底是什么样子？看看源码:

struct hash<int> {
        size_t operator()(int __x) const { return __x; }
};
原来是个函数对象。在SGI STL中，提供了以下hash函数：

struct hash<char*>
struct hash<const char*>
struct hash<char> 
struct hash<unsigned char> 
struct hash<signed char>
struct hash<short>
struct hash<unsigned short> 
struct hash<int> 
struct hash<unsigned int>
struct hash<long> 
struct hash<unsigned long>
也就是说，如果你的key使用的是以上类型中的一种，你都可以使用缺省的hash函数。当然你自己也可以定义自己的hash函数。对于自定义变量，你只能如此，例如对于string，就必须自定义hash函数。例如：

struct str_hash{
        size_t operator()(const string& str) const
        {
                unsigned long __h = 0;
                for (size_t i = 0 ; i < str.size() ; i ++)
                __h = 5*__h + str[i];
                return size_t(__h);
        }
};
//如果你希望利用系统定义的字符串hash函数，你可以这样写：
struct str_hash{
        size_t operator()(const string& str) const
        {
                return __stl_hash_string(str.c_str());
        }
};

在声明自己的哈希函数时要注意以下几点：

1.使用struct，然后重载operator().
2.返回是size_t
3.参数是你要hash的key的类型。
4.函数是const类型的。


4.1 hash_map和map的区别在哪里？
构造函数。hash_map需要hash函数，等于函数；map只需要比较函数(小于函数).
存储结构。hash_map采用hash表存储，map一般采用红黑树(RB Tree)实现。因此其memory数据结构是不一样的。
4.2 什么时候需要用hash_map，什么时候需要用map?
总体来说，hash_map 查找速度会比map快，而且查找速度基本和数据数据量大小，属于常数级别;而map的查找速度是log(n)级别。并不一定常数就比log(n)小，hash还有hash函数的耗时，明白了吧，如果你考虑效率，特别是在元素达到一定数量级时，考虑考虑hash_map。但若你对内存使用特别严格，希望程序尽可能少消耗内存，那么一定要小心，hash_map可能会让你陷入尴尬，特别是当你的hash_map对象特别多时，你就更无法控制了，而且hash_map的构造速度较慢。

现在知道如何选择了吗？权衡三个因素: 查找速度, 数据量, 内存使用。
```
```c++
//hashtable使用
int main()
{
    __gnu_cxx::hashtable<int, int, __gnu_cxx::hash<int>,
                         __gnu_cxx::identity<int>, std::equal_to<int> > 
                        iht(50, __gnu_cxx::hash<int>(), std::equal_to<int>());
    std::cout<<"size = "<<iht.size()<<std::endl;
    std::cout<<"bucket size = "<<iht.bucket_count()<<std::endl;
    std::cout<<"max bucket size = "<<iht.max_bucket_count()<<std::endl;
    iht.insert_unique(1);
    iht.insert_unique(54);
    iht.insert_unique(0);
    iht.insert_unique(7);
    std::cout<<"size = "<<iht.size()<<std::endl;
    std::cout<<"bucket size = "<<iht.bucket_count()<<std::endl;
    std::cout<<"max bucket size = "<<iht.max_bucket_count()<<std::endl;
    return 0;
}

/*====================================*/
#include <iostream>
#include <hashtable.h>
#include <bits/stl_function.h>
#include <hash_fun.h>
#include <ext/functional>
#include <string.h>

class equal
{
public:
    bool operator()(const char*s1, const char *s2)
    {
        return (0 == strcmp(s1, s2));
    }
};

int main()
{
    __gnu_cxx::hashtable<const char*, const char*, __gnu_cxx::hash<const char*>,
                        __gnu_cxx::identity<const char*>, equal >
                        iht(50, __gnu_cxx::hash<const char*>(), equal());
    std::cout<<"size is "<<iht.size()<<std::endl;
    std::cout<<"bucket is "<<iht.bucket_count()<<std::endl;
    std::cout<<"max bucket is "<<iht.max_bucket_count()<<std::endl;
    iht.insert_unique("orange");
    iht.insert_unique("pear");
    iht.insert_unique("apple");
    iht.insert_unique("banana");
    std::cout<<"size is "<<iht.size()<<std::endl;
    std::cout<<"bucket is "<<iht.bucket_count()<<std::endl;
    std::cout<<"max bucket is "<<iht.max_bucket_count()<<std::endl;
    for(auto it = iht.begin(); it != iht.end(); it++)
    {
        std::cout<<*it<<std::endl;
    }
} 
```

# unorderd容器
```c++
//before c++11:
hash_set
hash_multiset
hsah_map
hash_multimap
//sice c++11:
unordered_set
unordered_multiset
unordered_map
unordered_multimap
```c++