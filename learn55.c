#include <stdio.h>

int main(void)
{
    int a[50];          /* 存输入的数据 */
    int i, j;           /* 循环变量 */
    int sum = 0;        /* 和 */
    int s   = 0;        /* 计数器：>= 平均值的个数 */
    double ave = 0.0;   /* 平均值，用浮点避免整除丢失小数 */

    /* 读入数据，-1 结束 */
    for (i = 0; i < 50; ++i)
    {
        scanf("%d", &a[i]);
        if (a[i] == -1)      /* 遇到结束标志 */
            break;
    }

    /* 计算和 */
    for (j = 0; j < i; ++j)
        sum += a[j];

    /* 计算平均值 */
    if (i > 0)
        ave = (double)sum / i;

    /* 统计 >= 平均值的个数 */
    for (j = 0; j < i; ++j)
        if (a[j] >= ave)
            ++s;

    printf("s=%d\n", s);
    return 0;
}