#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define HIGH 20
#define WIDE  60

typedef struct BODY
{
    int X;
    int Y;
}BODY;

//定义蛇
struct SNAKE                      //注意如果加上typedefsnake变成类型名，不再是变量名
{
    BODY body[HIGH*WIDE];
    int size;
}snake;

//食物
struct FOOD
{
    int X;
    int Y;
}food;


int score = 0;

//定义初始化蛇
void initSNAKE(void)
{
    snake.size = 2;
    snake.body[0].X = WIDE/2;
    snake.body[0].Y = HIGH/2;
    snake.body[1].X = WIDE/2-1;
    snake.body[1].Y = HIGH/2;
    return ;
}
//食物初始化
void initFOOD(void)
{
    food.X = rand()%WIDE;
    food.Y = rand()%HIGH;
    return;
}



int main(void)
{
    srand(time(NULL));
}
