/*#include<stdio.h>    一重for循环
int main ()
{
    int sum =0;
    for (int n=0;n<=100;n++)//for(初始化语句，条件，表达式)..循环体
    {
        sum += n;
    }
    printf ("sum:%d",sum);
    return 0;
}*/


/*#include<stdio.h>   二重for循环
int main()
{
    int i,j;
    for(i=0;i<5;i++)     //外循环一次，内循环一套
    {
        for(j=0;j<5;j++)
        {
        printf("i=%d,j=%d/n",i,j);
        }
    }
    return 0;
}*/


#include <stdio.h>

int main()
{
    /* 三重循环：每层从 1 到 4（不含 5） */
    for (int i = 1; i < 5; ++i)           // 第 1 位
    {
        for (int j = 1; j < 5; ++j)       // 第 2 位
        {
            for (int k = 1; k < 5; ++k)   // 第 3 位
            {
                /* 去重：保证三个数互不相同 */
                if (i != j && i != k && j != k)//&&读法并且  “左右两边表达式都为真（非 0）时，整体结果才是真；否则就是假。”

                {
                    printf("%d,%d,%d\n", i, j, k);
                }
            }
        }
    }
    return 0;
}