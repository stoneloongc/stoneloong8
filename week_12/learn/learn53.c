#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int cash=100;
void play(int bet)
{
    char *c=(char*)malloc(3*sizeof(char));
    c[0]='q',c[1]='k',c[2]='j';
    srand(time(NULL));
    for(int i=0;i<5;i++)
    {
        int x=rand()%3;
        int y=rand()%3;
        int t;
        t=c[x];
        c[x]=c[y];
        c[y]=t;
    }
        int queen;
        printf("where q(1,2,3)\n");
        scanf("%d",&queen);
        if (c[queen-1]=='q')
        {
            cash+=3*bet;
            printf("position%c %c %c\n",c[0],c[1],c[2]);
        }
        else 
        {
            cash-=bet;
            printf("position%c %c %c\n",c[0],c[1],c[2]);
        }
        free(c);
    }
int main()
{
    int bet;
    while(cash>0)
    {
        printf("开始");
        scanf("%d",&bet);
        if(cash<=0 || cash<bet)
        break;
        play(bet);
    }
     
     return 0;
}
