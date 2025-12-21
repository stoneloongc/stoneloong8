#include<stdio.h>
int main()
{
    int a[50],i,b,sum=0,s=0;
    float ave;
    printf("请输入整数");
    for(i=0;i<50;i++)
    {
        scanf("%d",&b);
       
        if(b==-1)
        break;
         a[i]=b;
    }
    if(i==0)
    return 0;
    for(int j=0;j<i;j++)
    {
        sum+=a[j];
    }
    ave=sum/(float)i;
    for(int j=0;j<i;j++)
    {
        if(a[j]>ave)
        s++;
        
    }
    printf("%d",s);
    return 0;
}