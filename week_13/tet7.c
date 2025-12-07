#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

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

// 方向枚举
enum DIRECTION {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

int current_direction = RIGHT;
int game_over = 0;

// 设置非阻塞输入
void setNonBlockingInput() {
    struct termios ttystate;
    
    // 获取终端状态
    tcgetattr(STDIN_FILENO, &ttystate);
    
    // 关闭规范模式
    ttystate.c_lflag &= ~(ICANON | ECHO);
    
    // 设置最小字符数和超时
    ttystate.c_cc[VMIN] = 0;
    ttystate.c_cc[VTIME] = 0;
    
    // 设置新的终端属性
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

// 恢复终端设置
void resetTerminal() {
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

// 读取输入（非阻塞）
int getInput() {
    char c = 0;
    if (read(STDIN_FILENO, &c, 1) == 1) {
        return c;
    }
    return 0;
}

// 处理输入
void processInput() {
    int input = getInput();
    
    switch (input) {
        case 'w': case 'W':
            if (current_direction != DOWN) current_direction = UP;
            break;
        case 's': case 'S':
            if (current_direction != UP) current_direction = DOWN;
            break;
        case 'a': case 'A':
            if (current_direction != RIGHT) current_direction = LEFT;
            break;
        case 'd': case 'D':
            if (current_direction != LEFT) current_direction = RIGHT;
            break;
        case 'q': case 'Q':
            game_over = 1;
            break;
    }
}

// 初始化蛇和食物
void initGame() {
    snake.size = 2;
    snake.body[0].x = WIDE / 2;
    snake.body[0].y = HIGH / 2;
    snake.body[1].x = WIDE / 2 - 1;
    snake.body[1].y = HIGH / 2;

    food.x = rand() % (WIDE - 2) + 1;
    food.y = rand() % (HIGH - 2) + 1;
}

void draw(void) {
    system("clear"); // 清屏
    
    for(int y = 0; y < HIGH; y++) {
        for(int x = 0; x < WIDE; x++) {
            int printed = 0;
            
            // 画边界
            if(x == 0 || x == WIDE - 1) {
                putchar('|');
                printed = 1;
            }
            else if(y == 0 || y == HIGH - 1) {
                putchar('-');
                printed = 1;
            }
            // 画食物
            else if(food.x == x && food.y == y) {
                putchar('*');
                printed = 1;
            }
            // 画蛇
            else {
                for(int i = 0; i < snake.size; i++) {
                    if(snake.body[i].x == x && snake.body[i].y == y) {
                        putchar(i == 0 ? 'O' : 'o');
                        printed = 1;
                        break;
                    }
                }
            }
            
            if(!printed) {
                putchar(' ');
            }
        }
        putchar('\n');
    }
    
    // 显示分数和提示
    printf("Score: %d | Use WASD to move, Q to quit\n", snake.size - 2);
}

// 蛇移动
void mv(void) {
    // 保存蛇头位置
    int prev_x = snake.body[0].x;
    int prev_y = snake.body[0].y;
    int temp_x, temp_y;
    
    // 移动蛇头
    switch (current_direction) {
        case UP:
            snake.body[0].y--;
            break;
        case DOWN:
            snake.body[0].y++;
            break;
        case LEFT:
            snake.body[0].x--;
            break;
        case RIGHT:
            snake.body[0].x++;
            break;
    }
    
    // 移动蛇身
    for (int i = 1; i < snake.size; i++) {
        temp_x = snake.body[i].x;
        temp_y = snake.body[i].y;
        snake.body[i].x = prev_x;
        snake.body[i].y = prev_y;
        prev_x = temp_x;
        prev_y = temp_y;
    }
    
    // 检查是否吃到食物
    if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
        // 增加蛇长度
        snake.size++;
        snake.body[snake.size - 1].x = prev_x;
        snake.body[snake.size - 1].y = prev_y;
        
        // 生成新食物
        food.x = rand() % (WIDE - 2) + 1;
        food.y = rand() % (HIGH - 2) + 1;
    }
    
    // 检查碰撞边界
    if (snake.body[0].x <= 0 || snake.body[0].x >= WIDE - 1 || 
        snake.body[0].y <= 0 || snake.body[0].y >= HIGH - 1) {
        game_over = 1;
    }
    
    // 检查自我碰撞
    for (int i = 1; i < snake.size; i++) {
        if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y) {
            game_over = 1;
            break;
        }
    }
}

// 延时函数
void delay(int milliseconds) {
    usleep(milliseconds * 1000);
}

// 主函数测试
int main() {
    setNonBlockingInput();
    
    initGame();
    
    while(!game_over) {
        processInput();
        mv();
        draw();
        delay(200); // 控制游戏速度
    }
    
    resetTerminal();
    printf("Game Over! Final Score: %d\n", snake.size - 2);
    
    return 0;
}