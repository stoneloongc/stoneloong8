#include<stdio.h>
int main()
{
    int a;
    printf("请输入一个数");
    scanf("%d",&a);
    for(int i=2;i<a;i++)
    {
        while(a%i==0)
        {
            printf("%d",i);
            a/=i;
            if(a!=1)
            {
                printf("*");
            }
        }
    }
    printf("\n");
    return 0;
}