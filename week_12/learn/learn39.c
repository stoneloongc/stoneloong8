#include<stdio.h>
void print(char *c)
{
    c[0]='a';
    while(*c!='\0')
    {
        printf("%c",*c);
        c++;
    }
    printf("\n");
}
int main()
{
    char c[20] ="hello";
    print(c);
    return 0;
}