# thread中join和detach的区别

当thread::join()函数被调用后，调用它的线程会被block，直到线程的执行被完成。基本上，这是一种可以用来知道一个线程已结束的机制。当thread::join()返回时，OS的执行的线程已经完成，C++线程对象可以被销毁。

当thread::detach()函数被调用后，执行的线程从线程对象中被分离，已不再被一个线程对象所表达--这是两个独立的事情。C++线程对象可以被销毁，同时OS执行的线程可以继续。如果程序想要知道执行的线程何时结束，就需要一些其它的机制。join()函数在那个thread对象上不能再被调用，因为它已经不再和一个执行的线程相关联。

去销毁一个仍然可以“joinable”的C++线程对象会被认为是一种错误。为了销毁一个C++线程对象，约么join()函数需要被调用（并结束），要么detach()函数被调用。如果一个C++线程对象当销毁时仍然可以被join，异常会被抛出。

C++线程对象不被表达为执行的线程的其它的情况（也就是unjoinable）：



- 默认构造的线程对象不表达为执行的线程，所以是unjoinable。
- 被移开的线程将不表达为执行的线程，所以是unjoinable。

在std::thread的析构函数中，std::terminate会被调用如果：

- 线程没有被Joined（用t.join()）
- 线程也没有被detached（用t.detach()）

因此，你应该在执行流程到析构函数前总是要么join，要么detach一个线程。

当一个程序终止时（比如main返回），剩下的在后台的detached线程执行不会再等待；相反它们的执行会被挂起并且它们的本地线程对象会被销毁。

关键地，这意味着这些线程的栈不是完好无损的，因此一些析构函数不会被执行。~~依赖于这些行为，一些析构函数假象会被承担，这可能是一种坏情形，好像程序已经Crash或者已经被kill。希望OS会释放加在这些文件上的锁。~~Depending on the actions those destructors were supposed to undertake, this might be as bad a situation as if the program had crashed or had been killed. Hopefully the OS will release the locks on files, etc... but you could have corrupted shared memory, half-written files, and the like.

所以，你应该使用join还是detached？

- 使用join
- 除非你需要更灵活并且想要独立地提供一种同步机制来等待线程完成，在这种情况下你应该使用detach