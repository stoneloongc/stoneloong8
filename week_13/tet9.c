#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>

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

// 移动增量（替代枚举）
int move_x = 1;  // 初始向右
int move_y = 0;

int game_over = 0;

// 保存原始终端属性
struct termios original_termios;

// 设置非阻塞输入
void setNonBlockingInput() {
    struct termios new_termios;
    
    // 获取当前终端设置
    tcgetattr(STDIN_FILENO, &original_termios);
    
    // 复制原始设置
    new_termios = original_termios;
    
    // 关闭规范模式和回显
    new_termios.c_lflag &= ~(ICANON | ECHO);
    
    // 设置最小字符数和超时（非阻塞）
    new_termios.c_cc[VMIN] = 0;
    new_termios.c_cc[VTIME] = 0;
    
    // 应用新的终端属性
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

// 恢复终端设置
void resetTerminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
}

// 读取输入（非阻塞）
int getInput() {
    char c = 0;
    if (read(STDIN_FILENO, &c, 1) == 1) {
        return c;
    }
    return 0;
}

// 处理输入（简化版）
void processInput() {
    int input = getInput();
    
    switch (input) {
        case 'w': case 'W':
            if (move_y != 1) { move_x = 0; move_y = -1; }  // 上
            break;
        case 's': case 'S':
            if (move_y != -1) { move_x = 0; move_y = 1; }   // 下
            break;
        case 'a': case 'A':
            if (move_x != 1) { move_x = -1; move_y = 0; }   // 左
            break;
        case 'd': case 'D':
            if (move_x != -1) { move_x = 1; move_y = 0; }   // 右
            break;
        case 'q': case 'Q':
            game_over = 1;
            break;
    }
}

// 初始化蛇和食物
void initGame() {
    // 初始化随机种子
    srand(time(NULL));
    
    // 初始化蛇
    snake.size = 2;
    snake.body[0].x = WIDE / 2;
    snake.body[0].y = HIGH / 2;
    snake.body[1].x = WIDE / 2 - 1;
    snake.body[1].y = HIGH / 2;

    // 初始化食物
    food.x = rand() % (WIDE - 2) + 1;
    food.y = rand() % (HIGH - 2) + 1;
}

// 绘制游戏界面
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

// 蛇移动（简化版，去掉了switch）
void mv(void) {

    int next_head_x = snake.body[0].x + move_x;
    int next_head_y = snake.body[0].y + move_y;
    // 检查碰撞边界
    if (next_head_x  <= 0 || next_head_x  >= WIDE - 1 || 
        next_head_y <= 0 || next_head_y >= HIGH - 1) {
        game_over = 1;
        return;
    }
    
    // 检查自我碰撞
    for (int i = 1; i < snake.size; i++) {
        if (next_head_x == snake.body[i].x && next_head_y == snake.body[i].y) {
            game_over = 1;
            return;
        }
    }
    
        // 检查是否吃到食物
    if (next_head_x == food.x && next_head_y == food.y) {
        // 增加蛇长度（在尾部添加新节点）
        snake.size++;
        
        // 生成新食物
        food.x = rand() % (WIDE - 2) + 1;
        food.y = rand() % (HIGH - 2) + 1;
    }
    
    // 移动蛇身：从尾部向前，每个节点继承前一个节点的位置
    for (int i = snake.size - 1; i > 0; i--) {
        snake.body[i].x = snake.body[i - 1].x;
        snake.body[i].y = snake.body[i - 1].y;
    }
    
    // 移动蛇头（直接使用增量，没有switch！）
    snake.body[0].x = next_head_x;
    snake.body[0].y = next_head_y;
}

// 延时函数
void delay(int milliseconds) {
    usleep(milliseconds * 1000);
}

// 主函数
int main() {
    // 设置非阻塞输入
    setNonBlockingInput();
    
    // 确保程序退出时恢复终端
    atexit(resetTerminal);
    
    // 初始化游戏
    initGame();
    
    // 游戏主循环
    while(!game_over) {
        processInput();   // 处理输入
        mv();            // 移动蛇
        draw();          // 绘制界面
        delay(200);      // 控制游戏速度
    }
    
    // 显示游戏结束信息
    printf("\nGame Over! Final Score: %d\n", snake.size - 2);
    
    return 0;
}