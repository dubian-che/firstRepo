#include <iostream>

void fun()
{
    std::cout << "fun()" << std::endl;
}

void fun(int)
{
    std::cout << "fun(int)" << std::endl;
}

int main()
{
    fun(1);
    fun();
    return 0;
}