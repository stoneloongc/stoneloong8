#include<stdio.h>
void a(void)
{
    printf("hello,world\n");
}
void b(void)
{
        for(int i=0;i<3;i++)
        a();
}
int main()
{
    b ();
    return 0;
}