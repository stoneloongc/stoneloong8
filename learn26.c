#include<stdio.h>
int main()
{
    char i,j;
    printf("请输入字母");
    scanf("%c",&i);
    switch(i){
    case 'm':
        printf("monday\n");
        break;
    case 'w':
        printf("wednesday\n");
        break;
    case 'f':
        printf("friday\n");
        break;
    case 't':
        printf("请继续输入字母");
        scanf("%c",&j);
        if(j=='u')
        {printf("tuesday\n");break;}
        else if(j=='h')
        {printf("thursday\n");break;}
    case 's':
        printf("请继续输入字母");
        scanf("%c",&j);
        if(j=='a')
        {printf("saturday\n");break;}
        else if(j=='u')
        {printf("sunday");break;}
    }

    return 0;
}