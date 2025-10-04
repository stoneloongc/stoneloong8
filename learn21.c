/*#include <stdio.h>

void palin(int n);   //现代函数声明，防止报错 

int main(void)
{
    int i = 5;
    printf("请输入5个字符 : ");
    palin(i);
    printf("\n");
    return 0;        
}

//现代函数定义 
void palin(int n)
{
    char next;//明确咯只要一个字符，否则getchar在未知情况需要用int承接和检查eof
    if (n <= 1) {
        next = getchar();
        printf("相反顺序输出结果 : ");
        putchar(next);
    } else {
        next = getchar();
        palin(n - 1);   // 递归 
        putchar(next);
    }
}//函数调用不按座位顺序；递归先问后倒着回答*/

#include<stdio.h>
void plain(int n);
int main(void)
{
    int i=5;
    printf("请输入五个字母");
    plain(i);
    printf("\n");
    return 0;
}
void plain(int n)
{
    char next;
    if(n<=1)
    {
        next=getchar();
        printf("请输入相反结果");
        putchar(next);
    }
    else
    {
        next=getchar();
        plain(n-1);
        putchar(next);
    }
}