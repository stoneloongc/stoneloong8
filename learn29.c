/*#include<stdio.h>
int main(void)
{
    //int a[4];
    //printf("%p\n",&a);
    //printf("%p\n",a);
    return 0;
}*/


/*#include <stdio.h>

void f(int *p);  

int main(void)
{
    int i = 123;               // 先给 i 赋个值，方便观察
    printf("&i = %p\n", (void *)&i);   // 打印 i 的地址
    f(&i);                     // 把 i 的地址传给函数 f

    int *p = &i;   
    return 0;
}

void f(int *p)                 // 形参 p 接收的是地址，。
{
    printf("p = %p\n", (void *)p);   // 打印收到的地址，(void *)，把这个指针当成纯地址，别管它原来指向什么类型
}*/


#include <stdio.h>

void f(int *p);
void g(int k);

int main(void)
{
    int i = 6;
    printf("&i=%p\n", &i);
    f(&i);
    g(i);
    int a=5;
    int *m=&a;
    printf("%d\n",*m);
    printf("%p\n",(void*)m);

    return 0;
}

void f(int *p)
/*| 场景           | 写法        | 含义                            | 例子                    |
| ------------ | --------- | ----------------------------- | --------------------- |
| **定义**（声明变量） | `int *p;` | `p` 是一个**指针变量**，里面将来存地址       | `int *p;` // p 是指针    |
| **使用**（访问数据） | `*p`      | 把指针 `p` **解引用**，拿到它指向的那块内存里的值 | `printf("%d\n", *p);` |
*/
{
    printf(" p=%p\n", p);
    printf("*p=%d\n", *p);
}

void g(int k)
{
    printf("k=%d\n", k);
}