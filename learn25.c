#include<stdio.h>
int main ()
{
    int num=0;
    int a,b,c,d,e;
    printf("请输入一个五位数并判断是不是回文数");
    scanf("%d",&num);
    a=num/10000;
    b=num/1000%10;
    c=num/100%10;
    d=num/10%10;
    e=num%10;
    if(a==e && b==d)
    {
        printf("%d是回文数\n",num);
    }
    else
        printf("不是回文数\n");
    return 0;
}