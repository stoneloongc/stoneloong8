/*#include<stdio.h>
int main()
{
    int month=0;
    int rabbit=1;
    int a=2;
    for(month=0;month+2<=40;month++)
    {
        rabbit*=a;
    }
    printf("此时兔子有%d对\n",rabbit);
    return 0;
}
#include <stdio.h>
int main() {
    int month = 0;
    unsigned long long rabbit = 1;  // 使用更大的整数类型
    int a = 2;
    for (month = 0; month <= 40; month++) {
        month+=2;
        rabbit *= a;
    }
    printf("此时兔子有%llu对\n", rabbit);
    return 0;
}*/
include <stdio.h>
 
int main()
{
    int a = 1, b = 1, temp, i;
    printf("%12d%12d", a, b); // 输出前两项
 
    for (i = 3; i <= 20; i += 2)
    {
        temp = a + b; // 计算下一项
        printf("%12d", temp); // 输出下一项
 
        a = b; // 更新a
        b = temp; // 更新b
 
        temp = a + b; // 再计算下一项
        printf("%12d\n", temp); // 输出并换行
 
        a = b; // 更新a
        b = temp; // 更新b
    }
 
    return 0;
}