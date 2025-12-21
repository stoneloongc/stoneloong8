#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<termios.h>
#include<stdlib.h>

#define WIDE 50
#define HIGH 20

struct BODY
{
    int x;
    int y;
};
struct SNAKE{
    int size;
    struct BODY body[WIDE*HIGH];
}snake;
struct FOOD{
    int x;
    int y;
}food;

int move_x = 1;  // 初始向右
int move_y = 0;

int game_over = 0;

void position(void)
{
    snake.size = 2;
    snake.body[0].x = WIDE/2;
    snake.body[0].y = HIGH/2;
    snake.body[1].x = WIDE/2-1;
    snake.body[1].y = HIGH/2;
    food.x = rand()%(WIDE-3);
    food.y = rand()%(HIGH-3);
}


char image[WIDE][HIGH];

void draw(void)
{
   
    int x=0,y=0;
    for(y=0;y<HIGH;y++)
    {
        for (x = 0; x < WIDE; x++)
        {
            int judge = 0;
            if (y == 0 || y == HIGH - 1)
            {
                image[x][y] = '-';
            }
            else if (x == 0 || x == WIDE - 1)
            {
                image[x][y] = '|';
            }

            else
            {
                image[x][y] = ' ';
            }
        }
    }

    for (int i = 0; i < snake.size; i++)
    {

        image[snake.body[i].x][snake.body[i].y];
    }

    image[food.x][food.y] = '*';

    system("clear");
    
    for(y=0;y<HIGH;y++)
    {
        for(x=0;x<WIDE;x++)
        {
            printf("%c",image[x][y]);
        }
        printf("\n");
    }
     printf("Score: %d | Use WASD to move, Q to quit\n", snake.size - 2);
}

int main()
{
    position();
    draw();
    return 0;
}
