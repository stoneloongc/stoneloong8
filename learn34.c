/*#include<stdio.h>//存储变量理解
void zeng(int a)
{
    a++;
    printf("%d\n",a);
}
int main()
{
    int a=10;
    zeng(a);//产生新的副本
    printf("%d\n",a);
    return 0;
}*/
/*#include<stdio.h>
void add(int *p)
{
    *p=*p+1;
}
int main()
{
    int a=10;
    add(&a);//去原地址改变里面的值
    printf("%d\n",a);
    return 0;
}*/


//指针与数组
/*#include<stdio.h>
int main()
{
    char c1[6]="hello";
    char *c2=c1;
    c2[0]='a';
    printf("%c\n",c2[0]);
    return 0;
}*/

#include<stdio.h>
void print(char *c)
{
    int i=0;
    while(*(c+i)!='\0')
    {
        printf("%c",c[i]);
        i++;
    }
    printf("\n");
}
int main()
{
    char c[20]="hello";
    print(c);
    return 0;
}