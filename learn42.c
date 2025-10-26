//动态内存分配储存在堆里，栈储存通往堆指定位置的地址
#include<stdio.h>
#include <stdlib.h>
int main ()
{
    int *p = (int*)malloc(4*sizeof(int));
    p[0]=1;
    for (int i=0;i<4;i++)
    {
        printf("%d \n",p[i]);
    }
    printf("\n");
    free(p);



    int n;
    scanf("%d",&n);
    int *p1 = (int*)malloc(n*sizeof(int));//malloc未赋值内存是未知值
    for(int i=0;i<n;i++)
    {
        p1[i]=i+1;
        printf("%d\n",p1[i]);
    }
    int *p2 = (int*)realloc(p1,2*n*sizeof(int));//字节为0相当于free释放；大于原来内存复制原来的变量在扩展，小于则释放超出内存变量
       for(int i=0;i<2*n;i++)
    {
        printf("%d\n",p2[i]);
    }

    int *p3 = (int*)realloc(NULL,2*n*sizeof(int));//null空的，相当于malloc建立新内存
       for(int i=0;i<2*n;i++)
    {
        printf("%d\n",p3[i]);
    }
    printf("\n");



    int *pc = (int*)calloc(4,sizeof(int));//未赋值的内存值均未0
    pc[0]=2;
    for (int i=0;i<4;i++)
    {
        printf("%d \n",pc[i]);
    }
    free(pc);

    
    return 0;
}