#include<stdio.h>
int main()
{
    int m,n,t,b;
    scanf("%d%d",&m,&n);
    if(m<n)
    {
        t=m,m=n,n=t;
    }
    if(m%n==0)
    {
        b=m;
    }
    b=m*n;
    printf("最小公倍数%d\n",b);
    return 0;
}