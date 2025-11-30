#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <curses.h>

#define WIDE 50
#define HIGH 20
//定义蛇
struct BODY{
    int x;
    int y;
};

struct SNAKE{
    int size;
    struct BODY body[HIGH*WIDE];
}snake;
//定义食物
struct FOOD{
    int x;
    int y;
}food;
//画墙
void initwall(void){
    for(int i=0;i<HIGH;i++)
    {
        for(int j=0;j<WIDE;j++)
        {
            if(i == 0 || i == HIGH-1)
            {
                printf("—");
            }
            else if(j == 0 || j == WIDE-1)
            {
                printf("|");
            }
            else
                printf(" ");
        }
        printf("\n");
    }
    return;
}
//初始化蛇位置
void initsnake(void)
{
    snake.body[0].x = WIDE/2;
    snake.body[0].y = HIGH/2;
    snake.body[1].x = WIDE/2-1;
    snake.body[1].y = HIGH/2;
}
void drawsnake(char chx,char chy,int x,int y)
{
    
}
//初始化食物位置
void initfood(void)
{
    food.x = rand()%WIDE;
    food.y = rand()%HIGH;
}

//移动


int main()
{
    int score = 0;
    int kx=0,ky=0;
    char key = 'd';
    srand(time(NULL));
    initwall();
    
    //游戏主循环
    while(snake.body[0].x>0 && snake.body[0].x<WIDE 
        && snake.body[0].y>0 && snake.body[0].y<HIGH)
        {
            //移动操作
             if(kbhit()){
                key = getch();
             }
            switch(key)
            {
                case 'w':kx = 0;ky = -1;break;
                case 's':kx = 0;ky = 1;break;
                case 'a':kx = -1;ky = 0;break;
                case 'd':kx = 1;ky = 0;break;
                default: break;
            }

            

            //蛇自撞
            for(int i=0;i<snake.size;i++)
            {
                if(snake.body[0].x == snake.body[i].x 
                    && snake.body[0].y ==snake.body[i].y)
                    {
                        printf("game over!");
                        return 0;
                    }
            }

            //蛇吃食物
            for(int i = 0;i<snake.size;i++)
            {
                if(snake.body[i].x == food.x &&snake.body[i].y == food.y)
                {
                    snake.size++;
                    score++;
                }
            }

            //蛇移动
            for(int i = snake.size-1;i>0;i--)
            {
                snake.body[i].x = snake.body[i-1].x ;
                snake.body[i].y = snake.body[i-1].y ;
            }
            snake.body[0].x +=kx;
            snake.body[0].y +=ky;
            
        }

        return 0;
    }
    
