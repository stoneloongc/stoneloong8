//指针对数组的解引用
#include<stdio.h>
int main()
{
    int a[2][3]={{1,2,3},{4,5,6}};
    int (*p)[3]=a;
    printf("%d\n",**(a+1));
    printf("%d\n",a[1][0]);
    printf("%d\n",*(a[1]+0));
    printf("%d\n",*(*(a+1)+0));
    printf("%p\n",a);
    printf("%p\n",p);
    printf("%p\n",a[0]);
    printf("%p\n",&a[0][0]);
    int b[3][2][2]={{{2,5},{7,9}},{{3,4},{6,1}},{{0,8},{11,13}}};
    int (*pb)[2][2]=b;
    printf("%d\n",*(*(b[0]+0)+0));
    printf("%d\n",*(b[0][0]+0));
    printf("%d\n",*(*(*(b+0)+0)+0));
    return 0;
}