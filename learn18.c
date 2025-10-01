/*#include<stdio.h>
int main()
{
    float n,t,a=2,b=1;
    float m,sum=0.0;
    for(n=1;n<=20;n++)
    {
        m=a/b;
        sum+=m;
        t=b;
        b=a;
        a=t+b;
    }
    printf("前二十项和是%f\n",sum);
    return 0;
}*/


#include<stdio.h>
int main()
{
    int n;
    float a=2,b=1,t,m,sum;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        m=a/b;
        t=b;
        b=a;
        a=t+b;
        sum+=m;
    }
    printf("m的前n项和为%f\n",sum);
    return 0;
}