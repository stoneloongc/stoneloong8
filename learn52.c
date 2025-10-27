#include<ctype.h>
#include<stdio.h>
#include<stdbool.h>
#include <string.h>
bool seq(char *s)
{
    int i=0,j=strlen(s)-1;
    while(i<j)
    {
        if(!isalnum(s[i]))
        i++;
        else if(!isalnum(s[j]))
        j--;
        else if(tolower(s[i])==tolower(s[j]))
        {
            i++;
            j--;
        }
        else
        return false;
    }
    return true;
}
int main()
{
    char s[100];
    scanf("%s",s);
    bool t=seq(s);
    printf("%d",t);
    return 0;
}