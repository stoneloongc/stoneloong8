#include<stdio.h>
#include<string.h>
void print(char *c)
{
    while(*c!='\0')
    {
        printf("%c",*c);
        c++;
    }
}
int main()
{
    char *c ="hello";
    c[0]='a';
    print(c);
    return 0;
}