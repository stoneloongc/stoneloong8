#include<stdio.h>
/*unsigned long long example(int n)
{
    int a=0;
    for(int i=1;i<=n;i++)
    {
        a+=i;
    }
    return a;
}
    int main()
    {
        int sum=0;
        for(int i=1;i<=3;i++)
        {
            sum+=example(i);
        }
        printf("%d\n",sum);
        return 0;
    }*/
   #include<stdio.h>
   int main()
   {
    int n;
    scanf("%d",&n);
    switch(n)
    {
    case 1:printf("1");break;
    case 2:printf("2");break;
    }
    return 0;
   }