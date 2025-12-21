#include <stdio.h>
void fun(char *s, int *t)
{
    int i, n;
    n = 0;
    for (i = 0; s[i] != 0; i++)
        if (s[i] >= '0' && s[i] <= '9')
            n++;
    *t = n;
}

int main()
{
    char s[80] = "abcde35adgh3k]sdf7";
    int t;
    fun(s, &t);
    printf("\nThe original string is: %s\n", s);
    printf("\nThe result 1a: %d\n", t);
    return 0;
}