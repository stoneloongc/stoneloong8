/*#include<stdio.h>
int main()
{
    int x,y,z,t;
    printf("请依次输入值");
    scanf("%d%d%d",&x,&y,&z);
    if(x>y)
    {
        t=x,x=y,y=t;
    }
    if(x>z)
    {
        t=x,x=z,z=t;
    }
    if(y>z)
    {
        t=y,y=z,z=t;
    }
    printf("输出值由小到大%d%d%d\n",x,y,z);
    return 0;
}*/
#include<stdio.h>
void swap(int *a,int *b)//这里指的为空间内的值交换；平时的赋值是赋值一个副本，将值在另一个空间内；void在前指不会返回任何值给试用者
{//隐形显性赋值，void
        int temp=*a;
        *a=*b;
        *b=temp;
}//为什么赋值是可以t=a，a=b，b=t不是产生新的副本吗
int main()
{
    int x,y,z;
    printf("请输入值");
    scanf("%d%d%d",&x,&y,&z);
    if(x>y)
    {
        swap(&x,&y);
    }
    if(x>z)
    {
        swap(&x,&z);
    }
    if(y>z)
    {
        swap(&z,&y);
    }
    printf("请由小到大输出%d%d%d",x,y,z);
    return 0;
}