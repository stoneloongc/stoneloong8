/*#include<stdio.h>//判断水仙数
int main()
{
    int hundreds,tens,ones,a;
    printf("请输入一个三位数");
    scanf("%d",&a);
    hundreds=a/100;
    tens=a/10%10;
    ones=a%10;
    if (a == hundreds*hundreds*hundreds + tens*tens*tens + ones*ones*ones)
    {
        printf("%d是一个水仙数\n",a);
    }
    return 0;
}*/
//找出三位数水仙数  共用时30min
#include<stdio.h>
int main()
{
    int a,h,t,o;
    for(a=100;a<=1000;a++)
    {
        h=a/100;
        t=a/10%10;
        o=a%10;
        if(a==h*h*h+t*t*t+o*o*o)
        {
            printf("%d\n",a);
        }
        else
        printf("这不是水仙数");
    }
    return 0;
}