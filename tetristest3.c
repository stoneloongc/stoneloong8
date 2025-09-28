#include<ncurses.h>
#define INT_X 50
#define INT_Y 15
#define BLOCK_BLOCK 2
#define BLOCK_HEIGHT 2
int main()
{
    int x=INT_X  ;
    int y=INT_Y  ;
    int ch;
    initscr();
    cbreak();
    noecho();
    keypad(stdscr,TRUE);
    clear();
    box(stdscr,0,0);
    mvprintw(y,x,"hello");
    refresh();
    while(1)
    {
        ch=getch();
        switch(ch)
        {
        case KEY_UP:
        if (y>1)
        {
            y--;
        }
        break;
        case KEY_DOWN:
        if (y< LINES-1)
        {
            y++;
        }
        break;
        case KEY_LEFT:
        if(x>1)
        {
            x--;
        }
        break;
        case KEY_RIGHT:
        if (x<COLS-5)
        {
            x++;
        }
        break;
        case 'q':
        endwin();
        return 0;
    }
        //clear();
        box(stdscr, 0, 0);
        mvprintw(y, x, "hello");
        refresh();
    }

    return 0;
}