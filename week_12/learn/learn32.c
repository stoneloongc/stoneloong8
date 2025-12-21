//定义静态变量
#include<stdio.h>

int sta();
int main(void)
{
    sta();
    sta();
    return 0;
}
int sta(void)
{
    static int a=0;
    a++;
    printf("%d\n",a);
}
