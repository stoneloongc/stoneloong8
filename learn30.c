#include<stdio.h>
#define N 10
int main()
{
    int a[N]={0,1,2,3,4,5,6,7,8,9};
        printf("原始数组为");
    for(int i=0;i<N;i++)
    {
    printf("%d ",a[i]);
    }
    printf("\n");
    for(int i=0;i<N/2;i++)
    {
        int t;
        t=a[i];
        a[i]=a[N-i-1];
        a[N-i-1]=t;
    }
    printf("倒序数组为");
     for(int i=0;i<N;i++)
    {
    printf("%d ",a[i]);
    }
    printf("\n");
    return 0;
}