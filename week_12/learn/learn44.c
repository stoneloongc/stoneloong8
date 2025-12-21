//内存泄漏
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int cash=100;
void play(int bet)
{
    //char c[3]={'q','k','j'};
    char *c=(char*)malloc(3*sizeof(char));//相比于局部变量节省栈内存
    c[0]='q',c[1]='k',c[2]='j';
    printf("shuffling...\n");
    srand(time(NULL));
    int i;
    for(i=0;i<5;i++)
    {
        int x = rand()%3;
        int y = rand()%3;
        int t=c[x];
        c[x]=c[y];
        c[y]=t;
    }
    int queen;
    printf("what is the position of queen?(1,2,3)\n");
    scanf("%d",&queen);
    if(c[queen-1]=='q')
    {
        cash+=3*bet;
        printf("win result%c %c %c cash=%d\n",c[0],c[1],c[2],cash);
    }
    else
    {
        cash-=bet;
        printf("loose result%c %c %c cash=%d\n",c[0],c[1],c[2],cash);
    }
    free(c);
}
    
    int main ()
{
    int bet;
    while(cash>0)
    {
        printf("what is your bet?\n");
        scanf("%d",&bet);
        if(cash<=0 || bet>cash)
        break;
        play(bet);
       
    }
    return 0;
}