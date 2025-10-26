#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int str(char *haystack,char *needle)
{
    int n=strlen(haystack);
    int m=strlen(needle);
    int i,flag;
    for(i=0;i+m<=n;i++)
    {
        flag=true;
        for(int j=0;j<m;j++)
        {
            if(haystack[i+j]!=needle[j])
            {
                flag=false;
                break;
            }
        }
        if(flag)
        break;
    }
    if(flag)
    return i;
    else
    return -1;
}
int main()
{
    char haystack[10],needle[5];
    printf("haystcak字符:");
    fgets(haystack,sizeof(haystack),stdin);
    haystack[strcspn(haystack,"\n")]='\0';
    printf("needle字符:");
    fgets(needle,sizeof(needle),stdin);
    needle[strcspn(needle,"\n")]='\0';
    int t=str(haystack,needle);
    if(t!=-1)
    {
        printf("通过\n");
        printf("%d\n",t);
    }
    else
    printf("失败\n");

    return 0;
}