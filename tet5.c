







#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20

int main() {
    initscr(); // 初始化curses库
    cbreak(); // 禁用行缓冲
    noecho(); // 不显示输入字符
    keypad(stdscr, TRUE); // 启用键盘功能键
    curs_set(0); // 隐藏光标

    int snake_x[WIDTH * HEIGHT];
    int snake_y[WIDTH * HEIGHT];
    int snake_length = 1;

    // 初始化蛇的位置
    snake_x[0] = WIDTH / 2;
    snake_y[0] = HEIGHT / 2;

    // 初始化食物位置
    int food_x = rand() % WIDTH;
    int food_y = rand() % HEIGHT;

    // 初始方向
    int direction = 0; // 0: 向右, 1: 向下, 2: 向左, 3: 向上

    int game_over = 0;

    // 游戏主循环
    while (!game_over) {
        clear();
        refresh();

        // 绘制边界
        for (int i = 0; i < WIDTH; i++) {
            mvprintw(0, i, "#");
            mvprintw(HEIGHT - 1, i, "#");
        }
        for (int i = 1; i < HEIGHT - 1; i++) {
            mvprintw(i, 0, "#");
            mvprintw(i, WIDTH - 1, "#");
        }

        // 绘制食物
        mvprintw(food_y, food_x, "O");

        // 绘制蛇
        for (int i = 0; i < snake_length; i++) {
            mvprintw(snake_y[i], snake_x[i], "X");
        }

        // 接收用户输入
        int key = getch();
        if (key == KEY_UP && direction != 1) direction = 3;
        else if (key == KEY_DOWN && direction != 3) direction = 1;
        else if (key == KEY_LEFT && direction != 0) direction = 2;
        else if (key == KEY_RIGHT && direction != 2) direction = 0;

        // 更新蛇的位置
        int new_x = snake_x[0];
        int new_y = snake_y[0];

        switch (direction) {
            case 0: new_x++; break;
            case 1: new_y++; break;
            case 2: new_x--; break;
            case 3: new_y--; break;
        }

        // 检查碰撞
        if (new_x < 0 || new_x >= WIDTH || new_y < 0 || new_y >= HEIGHT) {
            game_over = 1;
        }

        for (int i = 0; i < snake_length; i++) {
            if (snake_x[i] == new_x && snake_y[i] == new_y) {
                game_over = 1;
            }
        }

        // 添加新头部
        for (int i = snake_length; i > 0; i--) {
            snake_x[i] = snake_x[i - 1];
            snake_y[i] = snake_y[i - 1];
        }

        snake_x[0] = new_x;
        snake_y[0] = new_y;

        // 检查是否吃到食物
        if (new_x == food_x && new_y == food_y) {
            snake_length++;
            food_x = rand() % WIDTH;
            food_y = rand() % HEIGHT;
        }

        usleep(100000); // 控制游戏速度
    }

    // 清理
    endwin();
    printf("Game Over!\n");
    return 0;
}