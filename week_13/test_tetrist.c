#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20

char game_view[HEIGHT][WIDTH] = {' '};
typedef struct s_point
{
    int x;
    int y;
} point_t;
typedef point_t food_t;

typedef struct s_snake
{
    point_t head;
    point_t tail;

    int len;
} snake_t;
snake_t snake;
food_t food;

int init_snake(){
    snake.head.x = 1+ rand()%(HEIGHT-2);
    snake.head.y = 1+ rand()%(WIDTH-2);
    snake.tail = snake.head;
    snake.len =1;
    return 0;
}
bool check_is_ok(food_t food){
    if(game_view[food.x][food.y] != ' ')
        return false;
    return true;
}
int create_food(){
    while (1)
    {
        // 可能死循环
        food.x = 1+ rand()%(HEIGHT-2);
        food.y = 1+ rand()%(WIDTH-2);
        if(check_is_ok(food))
            return 0;
    }
    return 0;
}

int init_game_view(){
    for (int j = 0; j < HEIGHT; j++)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            
            game_view[j][i]=' ';
        }
    }
    // 绘制边界
    for (int i = 0; i < WIDTH; i++) {
        game_view[0][i]='#';
        game_view[HEIGHT-1][i]='#';
    }
    for (int j = 0; j < HEIGHT; j++) {
        game_view[j][0]='#';
        game_view[j][WIDTH-1]='#';
    }
}

int print_game_view(){
    system("clear");
    for (int j = 0; j < HEIGHT; j++)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            printf("%c", game_view[j][i]);
        }
        if(j==2) 
            printf("    score : %d", snake.len);
        printf("\n");
    }
}

int redraw_game_view(){
    game_view[snake.head.x][snake.head.y]='o';
    game_view[snake.tail.x][snake.tail.y]='o';
    game_view[food.x][food.y]='*';
}
int is_eat_food(){
    return 0;
}

int main(){
    srand((unsigned int)time(NULL)); // 用当前时间设置种子
    init_game_view();
    init_snake();
    create_food();
    // game_view[snake_x][snake_y]='o';
    while(1){

        // snake_run_step();//蛇跑一步
        // if(is_eat_food()){
        //     // snake_grow();
        //     create_food();
        // }
        redraw_game_view();
        print_game_view();
      
    }
    return  0;
}