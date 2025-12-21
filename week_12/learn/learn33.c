//多级指针解引用

#include <stdio.h>

int main()
{
    int a = 10;
    int *p;
    int **q;
    int ***r;

    p = &a;
    q = &p;
    r = &q;

    printf("Address of a (p): %p\n", (void *)p);
    printf("Value of a (*p): %d\n", *p);
    printf("Address of p (*q): %p\n", (void *)*q);
    printf("Value of a (*(*q)): %d\n",**q );
    printf("Value(Address) of p *q:%p",*q);
    printf("Address of q (via *r): %p\n", (void*)*r);
    printf("Value of val (via ***r): %d\n", ***r);
    printf("val 的地址: %p\n", (void*)**r); 
    

    return 0;
}