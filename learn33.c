#include <stdio.h>

int main()
{
    int a = 10;
    int *p;
    int **q;

    p = &a;
    q = &p;

    printf("Address of a (p): %p\n", (void *)p);
    printf("Value of a (*p): %d\n", *p);
    printf("Address of p (*q): %p\n", (void *)*q);
    printf("Value of a (*(*q)): %d\n",**q );
    printf("Value(Address) of p *q:%p",*q);

    return 0;
}