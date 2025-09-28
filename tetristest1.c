#include <ncurses.h>

int main()
{
    initscr();               // 启动 ncurses
    printw("Hello, ncurses! Press any key to quit.");
    refresh();               // 把内容画到屏幕
    getch();                 // 等按键
    endwin();                // 恢复终端
    return 0;
}