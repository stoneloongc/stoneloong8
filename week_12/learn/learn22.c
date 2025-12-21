#include<stdio.h>
int age(int n)
{
    return n==1?10:age(n-1)+2;
}
int main()
{
    printf("%d\n",age(5));
    return 0;
}