#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <termios.h>

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
    point_t body[WIDTH * HEIGHT];
    int len;
    int direction;
} snake_t;

snake_t snake;
food_t food;

struct termios original_termios;

// 保存和恢复终端设置
void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}

void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &original_termios);
    atexit(disable_raw_mode);
    
    struct termios raw = original_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// 初始化蛇
void init_snake(){
    snake.head.x = HEIGHT / 2;
    snake.head.y = WIDTH / 2;
    snake.body[0] = snake.head;
    snake.len = 1;
    snake.direction = 1;
}

// 创建食物
void create_food(){
    int attempts = 0;
    while (attempts < 100) {
        food.x = 1 + rand() % (HEIGHT - 2);
        food.y = 1 + rand() % (WIDTH - 2);
        
        bool overlap = false;
        for (int i = 0; i < snake.len; i++) {
            if (food.x == snake.body[i].x && food.y == snake.body[i].y) {
                overlap = true;
                break;
            }
        }
        
        if(!overlap)
            return;
        attempts++;
    }
    // 如果找不到位置，放在第一个可用位置
    for (int j = 1; j < HEIGHT - 1; j++) {
        for (int i = 1; i < WIDTH - 1; i++) {
            bool overlap = false;
            for (int k = 0; k < snake.len; k++) {
                if (j == snake.body[k].x && i == snake.body[k].y) {
                    overlap = true;
                    break;
                }
            }
            if (!overlap) {
                food.x = j;
                food.y = i;
                return;
            }
        }
    }
}

// 初始化游戏界面
void init_game_view(){
    for (int j = 0; j < HEIGHT; j++) {
        for (int i = 0; i < WIDTH; i++) {
            game_view[j][i] = ' ';
        }
    }
    for (int i = 0; i < WIDTH; i++) {
        game_view[0][i] = '#';
        game_view[HEIGHT-1][i] = '#';
    }
    for (int j = 0; j < HEIGHT; j++) {
        game_view[j][0] = '#';
        game_view[j][WIDTH-1] = '#';
    }
}

// 打印游戏界面
void print_game_view(){
    system("clear");
    for (int j = 0; j < HEIGHT; j++) {
        for (int i = 0; i < WIDTH; i++) {
            printf("%c", game_view[j][i]);
        }
        if(j == 2) 
            printf("    Score: %d", snake.len - 1);
        printf("\n");
    }
    printf("Use WASD to control, Q to quit\n");
}

// 重绘游戏界面
void redraw_game_view(){
    for (int j = 1; j < HEIGHT - 1; j++) {
        for (int i = 1; i < WIDTH - 1; i++) {
            game_view[j][i] = ' ';
        }
    }
    
    for (int i = 0; i < snake.len; i++) {
        game_view[snake.body[i].x][snake.body[i].y] = 'o';
    }
    
    game_view[snake.head.x][snake.head.y] = 'O';
    game_view[food.x][food.y] = '*';
}

// 检查是否吃到食物
bool is_eat_food(){
    return (snake.head.x == food.x && snake.head.y == food.y);
}

// 蛇移动一步
void snake_run_step(){
    point_t old_head = snake.head;
    
    switch(snake.direction){
        case 0: snake.head.x--; break;
        case 1: snake.head.y++; break;
        case 2: snake.head.x++; break;
        case 3: snake.head.y--; break;
    }
    
    // 检查碰撞
    if (snake.head.x <= 0 || snake.head.x >= HEIGHT - 1 || 
        snake.head.y <= 0 || snake.head.y >= WIDTH - 1) {
        system("clear");
        printf("Game Over! Hit the wall! Final Score: %d\n", snake.len - 1);
        disable_raw_mode();
        exit(0);
    }
    
    for (int i = 0; i < snake.len; i++) {
        if (snake.head.x == snake.body[i].x && snake.head.y == snake.body[i].y) {
            system("clear");
            printf("Game Over! Hit yourself! Final Score: %d\n", snake.len - 1);
            disable_raw_mode();
            exit(0);
        }
    }
    
    for (int i = snake.len; i > 0; i--) {
        snake.body[i] = snake.body[i - 1];
    }
    snake.body[0] = old_head;
    
    if (is_eat_food()) {
        snake.body[snake.len] = snake.body[snake.len - 1];
        snake.len++;
        create_food();
    }
}

// 处理键盘输入
void handle_input(){
    char ch;
    if (read(STDIN_FILENO, &ch, 1) > 0) {
        switch(ch){
            case 'w': case 'W': if (snake.direction != 2) snake.direction = 0; break;
            case 'd': case 'D': if (snake.direction != 3) snake.direction = 1; break;
            case 's': case 'S': if (snake.direction != 0) snake.direction = 2; break;
            case 'a': case 'A': if (snake.direction != 1) snake.direction = 3; break;
            case 'q': case 'Q': 
                system("clear");
                printf("Game quit! Final Score: %d\n", snake.len - 1);
                disable_raw_mode();
                exit(0);
        }
    }
}

int main(){
    srand((unsigned int)time(NULL));
    
    // 设置原始模式
    enable_raw_mode();
    
    init_game_view();
    init_snake();
    create_food();
    
    printf("Game starting in 2 seconds...\n");
    sleep(2);
    
    while(1){
        handle_input();
        snake_run_step();
        redraw_game_view();
        print_game_view();
        usleep(200000); // 200ms
    }
    
    return 0;
}