//选择排序（选择排序比较相邻的）
#include<stdio.h>
int main()
{
    int i,j,t,a[5],m;
    printf("请输入五个整数\n");
    for(i=0;i<5;i++)
        scanf("%d",&a[i]);
    printf("\n");
    printf("未排序时当前数组顺序");
    for(i=0;i<5;i++)
        printf("%d\t",a[i]);
    for(i=0;i<4;i++)
    {
        for(j=i+1;j<5;j++)
        {
            if(a[i]<a[j])
            {
                t=a[i];
                a[i]=a[j];
                a[j]=t;
            }
        }
    }
    printf("排序后数组\n");
    for(i=0;i<5;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
    printf("插入一个整数\n");
    scanf("%d",&m);
    for(i=0;i<5;i++)
    {
        if(a[i]<m)
        {
            for(j=4;j>i;j--)
            {
               a[j-1]=a[j];
            }
            a[i]=m;
            break;
        }
    }
     printf("最新排序数组\n");
    for(i=0;i<5;i++)
    {
        printf("%d ",a[i]);
    }
return 0;
    
}