/*#include <stdio.h>

int main()
 {
    int i, j, sum;
    printf("找出一千以内的完数：\n");
    for (i = 1; i < 1000; i++) {
        sum = 0;
        for (j = 1; j < i; j++) {
            if (i % j == 0) {
                sum += j;
            }
        }
        if (i == sum) {
            printf("%d = 1", i);
            for (j = 2; j < i; j++) {
                if (i % j == 0) {
                    printf(" + %d", j);
                }
            }
            printf("\n"); 
        }
    }
    return 0; 
}*/
#include<stdio.h>
int main()
{
    int i,j,sum;
    printf("请找出一千以内的完数\n");
    for(i=1;i<=1000;i++)
    {
        sum=0;
        for(j=1;j<i;j++)
        {
            if(i%j==0)
            {
                sum+=j;
            }
        }
            if(sum==i)
            {
                printf("%d=1",i);
            for(j=2;j<i;j++)
            {
                if(i%j==0)
                {
                    printf("+%d",j);
                }
            }
             printf("\n");
        }
        
    }
    return 0;
}