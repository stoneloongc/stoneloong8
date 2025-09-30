/*
 * 简易彩色俄罗斯方块
 * gcc tetris.c -o tetris -lncurses -O2
 */
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define WIDTH  10
#define HEIGHT 20
#define PREVIEW_W 6
#define PREVIEW_H 4

/*---------- 方块定义 ----------*/
typedef enum { I=0, O, S, Z, J, L, T, NO } PieceType;

typedef struct { char b[4][4]; } Mino;

/* 19 种旋转状态（I*2 其余*4） */
static const Mino MINO[7][4] = {
    [I] = { {{{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}}},
            {{{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}}},
            {{{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0}}},
            {{{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}}}} ,
    [O] = { {{{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}}},
            {{{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}}},
            {{{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}}},
            {{{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}}}} ,
    [S] = { {{{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}}},
            {{{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}}},
            {{{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}}},
            {{{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}}} ,
    [Z] = { {{{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}}},
            {{{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}}},
            {{{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}}},
            {{{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}}}} ,
    [J] = { {{{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}}},
            {{{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}}},
            {{{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}}},
            {{{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}}}} ,
    [L] = { {{{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}}},
            {{{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}}},
            {{{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}}},
            {{{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}}}} ,
    [T] = { {{{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}}},
            {{{0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}}},
            {{{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}}},
            {{{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}}} ,
};

/*---------- 游戏状态 ----------*/
typedef struct {
    int x, y, r;
    PieceType t;
} Piece;

static char board[HEIGHT][WIDTH];
static Piece cur, next;
static int score, lines, level;
static const int color_pair[7] = { 1,2,3,4,5,6,7 };

/*---------- 工具函数 ----------*/
static int valid(const Piece *p) {
    const Mino *m = &MINO[p->t][p->r];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            if (!m->b[i][j]) continue;
            int x = p->x + j, y = p->y + i;
            if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return 0;
            if (board[y][x]) return 0;
        }
    return 1;
}

static void place(const Piece *p) {
    const Mino *m = &MINO[p->t][p->r];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (m->b[i][j])
                board[p->y + i][p->x + j] = p->t + 1;
}

static void clear_line(void) {
    int count = 0;
    for (int y = HEIGHT - 1; y >= 0; y--) {
        int full = 1;
        for (int x = 0; x < WIDTH; x++)
            if (!board[y][x]) { full = 0; break; }
        if (full) {
            count++;
            for (int yy = y; yy > 0; yy--)
                memcpy(board[yy], board[yy - 1], WIDTH);
            memset(board[0], 0, WIDTH);
            y++;
        }
    }
    if (count) {
        lines += count;
        score += count * count * 100 * (level + 1);
        level = lines / 10;
    }
}

static void spawn(void) {
    cur = next;
    cur.x = WIDTH / 2 - 2;
    cur.y = 0;
    next.t = rand() % 7;
    next.r = 0;
    if (!valid(&cur)) { /* game over */
        for (int y = 0; y < HEIGHT; y++)
            for (int x = 0; x < WIDTH; x++)
                if (board[y][x]) mvaddch(y, x, '*');
        mvprintw(HEIGHT / 2, WIDTH / 2 - 4, "GAME OVER");
        refresh();
        napms(2000);
        endwin();
        exit(0);
    }
}

/*---------- 绘图 ----------*/
static void draw_box(int sx, int sy, int w, int h) {
    mvhline(sy - 1, sx, '-', w);
    mvhline(sy + h, sx, '-', w);
    mvvline(sy, sx - 1, '|', h);
    mvvline(sy, sx + w, '|', h);
    mvaddch(sy - 1, sx - 1, '+');
    mvaddch(sy - 1, sx + w, '+');
    mvaddch(sy + h, sx - 1, '+');
    mvaddch(sy + h, sx + w, '+');
}

static void redraw(void) {
    clear();
    /*  board  */
    draw_box(0, 0, WIDTH, HEIGHT);
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            if (board[y][x]) {
                attron(COLOR_PAIR(board[y][x]));
                mvaddch(y, x, '#');
                attroff(COLOR_PAIR(board[y][x]));
            }
    /* 当前方块 */
    const Mino *m = &MINO[cur.t][cur.r];
    attron(COLOR_PAIR(color_pair[cur.t]));
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (m->b[i][j])
                mvaddch(cur.y + i, cur.x + j, '#');
    attroff(COLOR_PAIR(color_pair[cur.t]));

    /* 下一方块预览 */
    draw_box(WIDTH + 3, 1, PREVIEW_W, PREVIEW_H);
    const Mino *pn = &MINO[next.t][next.r];
    attron(COLOR_PAIR(color_pair[next.t]));
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (pn->b[i][j])
                mvaddch(2 + i, WIDTH + 4 + j, '#');
    attroff(COLOR_PAIR(color_pair[next.t]));

    mvprintw(1, WIDTH + 3, "Score : %d", score);
    mvprintw(2, WIDTH + 3, "Lines : %d", lines);
    mvprintw(3, WIDTH + 3, "Level : %d", level);
    mvprintw(4, WIDTH + 3, "Keys  :");
    mvprintw(5, WIDTH + 3, "← → ↓ 旋转");
    mvprintw(6, WIDTH + 3, "空格 硬降");
    mvprintw(7, WIDTH + 3, "q 退出");
    refresh();
}

/*---------- 主循环 ----------*/
int main(void) {
    srand(time(NULL));
    initscr(); cbreak(); noecho(); keypad(stdscr, TRUE); nodelay(stdscr, TRUE);
    if (has_colors()) {
        start_color();
        for (int i = 0; i < 7; i++)
            init_pair(i + 1, i + 1, COLOR_BLACK);
    }
    memset(board, 0, sizeof board);
    next.t = rand() % 7;
    next.r = 0;
    spawn();

    int drop_cnt = 0, delay = 20;
    while (1) {
        int c = getch();
        if (c == 'q') break;
        Piece bak = cur;
        switch (c) {
            case KEY_LEFT:  cur.x--; if (!valid(&cur)) cur = bak; break;
            case KEY_RIGHT: cur.x++; if (!valid(&cur)) cur = bak; break;
            case KEY_DOWN:  cur.y++; if (!valid(&cur)) cur = bak; break;
            case KEY_UP:    cur.r = (cur.r + 1) % 4; if (!valid(&cur)) cur = bak; break;
            case ' ': /* 硬降 */
                while (valid(&cur)) { cur.y++; }
                cur.y--;
                break;
        }
        /* 重力下降 */
        drop_cnt++;
        if (drop_cnt >= delay - level * 2) {
            drop_cnt = 0;
            cur.y++;
            if (!valid(&cur)) {
                cur.y--;
                place(&cur);
                clear_line();
                spawn();
            }
        }
        redraw();
        napms(20);
    }
    endwin();
    return 0;
}