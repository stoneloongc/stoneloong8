#include<stdio.h>
#include<stdlib.h>
    void print()
    {
        printf("hello\n");
    }
    int *add(int *a,int *b)
    {
        int *c=(int*)malloc(sizeof(int));//将指针c内存放在堆内,f如果无该代码内存将被存在栈上执行时被释放影响输出，涉及压栈的知识
        *c=(*a)+(*b);
        return c;
    }
int main()
{
    int a=2,b=4;
    int *ptr=add(&a,&b);
    print();
    printf("%d\n",*ptr);//该指针存的地址在堆内；
    return 0;
    
}