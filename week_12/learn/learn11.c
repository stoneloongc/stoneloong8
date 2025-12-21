/*#include<stdio.h>
int main()
{
    int i,j;
    for(i=101;i<=200;i++)
    {
        for(j=2;j<i;j++)
        {
            if(i%j==0){
                printf("%d\n",i);
                {
                    break;
                }
            }
        }
    }
    return 0;
}*/
#include<stdio.h>
int main()
{
    int count=0,i,j;
    for(i=101;i<=200;i++)
    {
        for(j=2;j<i;j++)
        {
            if(i%j==0)
            break;
        }
    if(j>=i)
    {
        count++;
        printf("%d\n",i);
        if(count%5==0)
        {
            printf("\n");
        }
    }
    }
    return 0;
}