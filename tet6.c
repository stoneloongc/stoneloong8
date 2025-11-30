#include <stdio.h>
#include <stdlib.h>

#define WIDE 50
#define HIGH 20

// 蛇的身体结构
struct BODY {
    int x;
    int y;
};

// 蛇结构
struct SNAKE {
    int size;
    struct BODY body[WIDE * HIGH];
} snake;

// 食物结构
struct FOOD {
    int x;
    int y;
} food;

// 初始化蛇和食物
void initGame() {
    snake.size = 2;
    snake.body[0].x = WIDE / 2;
    snake.body[0].y = HIGH / 2;
    snake.body[1].x = WIDE / 2 - 1;
    snake.body[1].y = HIGH / 2;

    food.x = rand() % WIDE;
    food.y = rand() % HIGH;
}

// 画出地图、蛇和食物
/*void draw(void)
{
    for(int y=0; y<HIGH;y++)
    {
        for(int x=0; x<WIDE;x++)
        {
            if(x==0 || x==WIDE-1)
            {
                putchar('|');
                continue;
            }
            if(y==0 ||y==HIGH-1)
            {
                putchar('-');
                continue;
            }
            if(food.x == x && food.y == y)
            {
                putchar('*');
                continue;
            }
            for(int i=0;i<snake.size;i++)
            {
                if(snake.body[0].x == x && snake.body[0].y == y)
                {
                    putchar('O');
                    continue;
                }
                else if(snake.body[i].x == x && snake.body[i].y == y)
                {
                    putchar('o');
                    continue;
                }
            }
                putchar(' ');
        }
        putchar('\n');
    }
}*/
void draw(void)
{
    for(int y = 0; y < HIGH; y++)
    {
        for(int x = 0; x < WIDE; x++)
        {
            int printed = 0;  // 标志变量
            
            // 画边界
            if(x == 0 || x == WIDE - 1)
            {
                putchar('|');
                printed = 1;
            }
            else if(y == 0 || y == HIGH - 1)
            {
                putchar('-');
                printed = 1;
            }
            // 画食物
            else if(food.x == x && food.y == y)
            {
                putchar('*');
                printed = 1;
            }
            // 画蛇
            else
            {
                for(int i = 0; i < snake.size; i++)
                {
                    if(snake.body[i].x == x && snake.body[i].y == y)
                    {
                        putchar(i == 0 ? 'O' : 'o');  // 蛇头用O，身体用o
                        printed = 1;
                        break;  // 找到蛇身就退出内层循环
                    }
                }
            }
            
            // 如果什么都没画，画空格
            if(!printed)
            {
                putchar(' ');
            }
        }
        putchar('\n');
    }
}
// 主函数测试
int main() {
    initGame();
    draw();
    return 0;
}