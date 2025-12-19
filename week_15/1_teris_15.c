#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

// 游戏区域大小
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define BUFFER_HEIGHT 2  // 顶部缓冲区域

// 方块形状定义
#define TETROMINO_COUNT 7
#define TETROMINO_SIZE 4

// 方块颜色代码
#define COLOR_RESET "\033[0m"
#define COLOR_CYAN "\033[36m"
#define COLOR_BLUE "\033[34m"
#define COLOR_ORANGE "\033[33m"
#define COLOR_YELLOW "\033[93m"
#define COLOR_GREEN "\033[32m"
#define COLOR_PURPLE "\033[35m"
#define COLOR_RED "\033[31m"

// 方块形状定义（俄罗斯方块的标准7种形状）
int tetrominos[TETROMINO_COUNT][TETROMINO_SIZE][TETROMINO_SIZE] = {
    // I型
    {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    },
    // J型
    {
        {0,0,0,0},
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0}
    },
    // L型
    {
        {0,0,0,0},
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0}
    },
    // O型
    {
        {0,0,0,0},
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0}
    },
    // S型
    {
        {0,0,0,0},
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0}
    },
    // T型
    {
        {0,0,0,0},
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0}
    },
    // Z型
    {
        {0,0,0,0},
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0}
    }
};

// 方块颜色
char* tetromino_colors[TETROMINO_COUNT] = {
    COLOR_CYAN,    // I
    COLOR_BLUE,    // J
    COLOR_ORANGE,  // L
    COLOR_YELLOW,  // O
    COLOR_GREEN,   // S
    COLOR_PURPLE,  // T
    COLOR_RED      // Z
};

// 游戏结构体
typedef struct {
    int type;          // 方块类型
    int rotation;      // 旋转状态 (0-3)
    int x;             // 当前x位置
    int y;             // 当前y位置
} Tetromino;

typedef struct {
    int board[BOARD_HEIGHT + BUFFER_HEIGHT][BOARD_WIDTH];  // 游戏板（包含顶部缓冲）
    Tetromino current;       // 当前下落的方块
    Tetromino next;          // 下一个方块
    int score;               // 得分
    int level;               // 等级
    int lines_cleared;       // 消除的行数
    int game_over;           // 游戏结束标志
    int pause;               // 暂停标志
} Game;

// 终端控制相关
struct termios original_termios;

// 设置非阻塞输入
void setNonBlockingInput() {
    struct termios new_termios;
    tcgetattr(STDIN_FILENO, &original_termios);
    new_termios = original_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    new_termios.c_cc[VMIN] = 0;
    new_termios.c_cc[VTIME] = 0;
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

// 初始化游戏
void initGame(Game* game) {
    memset(game->board, 0, sizeof(game->board));
    
    // 初始化当前和下一个方块
    srand(time(NULL));
    game->current.type = rand() % TETROMINO_COUNT;
    game->current.rotation = 0;
    game->current.x = BOARD_WIDTH / 2 - TETROMINO_SIZE / 2;
    game->current.y = BUFFER_HEIGHT;  // 从缓冲区域开始
    
    game->next.type = rand() % TETROMINO_COUNT;
    game->next.rotation = 0;
    
    game->score = 0;
    game->level = 1;
    game->lines_cleared = 0;
    game->game_over = 0;
    game->pause = 0;
}

// 检查方块是否可以放置在指定位置
int canPlaceTetromino(Game* game, Tetromino* t, int x, int y, int rotation) {
    for (int i = 0; i < TETROMINO_SIZE; i++) {
        for (int j = 0; j < TETROMINO_SIZE; j++) {
            if (tetrominos[t->type][i][j]) {
                int board_x = x + j;
                int board_y = y + i;
                
                // 检查边界
                if (board_x < 0 || board_x >= BOARD_WIDTH || 
                    board_y >= BOARD_HEIGHT + BUFFER_HEIGHT) {
                    return 0;
                }
                
                // 检查是否与已有方块重叠
                if (board_y >= 0 && game->board[board_y][board_x]) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

// 旋转当前方块
void rotateTetromino(Game* game) {
    int new_rotation = (game->current.rotation + 1) % 4;
    
    // 简单的旋转：转置然后反转行
    if (canPlaceTetromino(game, &game->current, game->current.x, game->current.y, new_rotation)) {
        game->current.rotation = new_rotation;
    }
}

// 移动当前方块
int moveTetromino(Game* game, int dx, int dy) {
    if (canPlaceTetromino(game, &game->current, 
                         game->current.x + dx, 
                         game->current.y + dy, 
                         game->current.rotation)) {
        game->current.x += dx;
        game->current.y += dy;
        return 1;
    }
    return 0;
}

// 将当前方块固定到游戏板
void lockTetromino(Game* game) {
    for (int i = 0; i < TETROMINO_SIZE; i++) {
        for (int j = 0; j < TETROMINO_SIZE; j++) {
            if (tetrominos[game->current.type][i][j]) {
                int board_x = game->current.x + j;
                int board_y = game->current.y + i;
                
                if (board_y >= 0 && board_y < BOARD_HEIGHT + BUFFER_HEIGHT &&
                    board_x >= 0 && board_x < BOARD_WIDTH) {
                    game->board[board_y][board_x] = game->current.type + 1;
                }
            }
        }
    }
    
    // 检查游戏是否结束
    for (int x = 0; x < BOARD_WIDTH; x++) {
        if (game->board[BUFFER_HEIGHT][x]) {
            game->game_over = 1;
            return;
        }
    }
    
    // 生成新的方块
    game->current = game->next;
    game->current.x = BOARD_WIDTH / 2 - TETROMINO_SIZE / 2;
    game->current.y = BUFFER_HEIGHT;
    game->current.rotation = 0;
    
    game->next.type = rand() % TETROMINO_COUNT;
    game->next.rotation = 0;
    
    // 立即检查新方块是否可以放置
    if (!canPlaceTetromino(game, &game->current, game->current.x, game->current.y, 0)) {
        game->game_over = 1;
    }
}

// 检查并清除完整的行
void clearLines(Game* game) {
    int lines_to_clear = 0;
    
    for (int y = BOARD_HEIGHT + BUFFER_HEIGHT - 1; y >= 0; y--) {
        int full = 1;
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (!game->board[y][x]) {
                full = 0;
                break;
            }
        }
        
        if (full) {
            lines_to_clear++;
            // 将上面的行下移
            for (int ny = y; ny > 0; ny--) {
                for (int x = 0; x < BOARD_WIDTH; x++) {
                    game->board[ny][x] = game->board[ny-1][x];
                }
            }
            // 清空最顶部一行
            for (int x = 0; x < BOARD_WIDTH; x++) {
                game->board[0][x] = 0;
            }
            y++;  // 重新检查这一行（因为行下移了）
        }
    }
    
    // 更新分数
    if (lines_to_clear > 0) {
        game->lines_cleared += lines_to_clear;
        game->level = game->lines_cleared / 10 + 1;
        
        // 计分规则：一次消除的行数越多，得分越高
        int points[] = {0, 100, 300, 500, 800};  // 0,1,2,3,4行
        if (lines_to_clear > 4) lines_to_clear = 4;
        game->score += points[lines_to_clear] * game->level;
    }
}

// 绘制游戏界面
void drawGame(Game* game) {
    system("clear");
    
    // 绘制顶部边框和分数信息
    printf("┌");
    for (int i = 0; i < BOARD_WIDTH; i++) printf("──");
    printf("┐  NEXT BLOCK\n");
    
    // 绘制游戏区域和下一个方块区域
    for (int y = BUFFER_HEIGHT; y < BOARD_HEIGHT + BUFFER_HEIGHT; y++) {
        printf("│");
        
        // 绘制主游戏区域
        for (int x = 0; x < BOARD_WIDTH; x++) {
            int drawn = 0;
            
            // 绘制当前下落的方块
            if (y >= game->current.y && y < game->current.y + TETROMINO_SIZE &&
                x >= game->current.x && x < game->current.x + TETROMINO_SIZE) {
                
                int block_x = x - game->current.x;
                int block_y = y - game->current.y;
                
                if (block_x >= 0 && block_x < TETROMINO_SIZE &&
                    block_y >= 0 && block_y < TETROMINO_SIZE &&
                    tetrominos[game->current.type][block_y][block_x]) {
                    
                    printf("%s██%s", tetromino_colors[game->current.type], COLOR_RESET);
                    drawn = 1;
                }
            }
            
            // 绘制已固定的方块
            if (!drawn && game->board[y][x]) {
                int type = game->board[y][x] - 1;
                printf("%s██%s", tetromino_colors[type], COLOR_RESET);
                drawn = 1;
            }
            
            // 绘制空白
            if (!drawn) {
                printf("  ");
            }
        }
        
        // 绘制侧边信息
        printf("│");
        
        if (y == BUFFER_HEIGHT) {
            printf("  ┌────┐");
        } else if (y >= BUFFER_HEIGHT + 1 && y <= BUFFER_HEIGHT + TETROMINO_SIZE) {
            int py = y - (BUFFER_HEIGHT + 1);
            printf("  │");
            
            for (int px = 0; px < TETROMINO_SIZE; px++) {
                if (py < TETROMINO_SIZE && px < TETROMINO_SIZE &&
                    tetrominos[game->next.type][py][px]) {
                    printf("%s██%s", tetromino_colors[game->next.type], COLOR_RESET);
                } else {
                    printf("  ");
                }
            }
            printf("│");
        } else if (y == BUFFER_HEIGHT + TETROMINO_SIZE + 1) {
            printf("  └────┘");
        } else if (y == BUFFER_HEIGHT + 6) {
            printf("  Score: %d", game->score);
        } else if (y == BUFFER_HEIGHT + 7) {
            printf("  Level: %d", game->level);
        } else if (y == BUFFER_HEIGHT + 8) {
            printf("  Lines: %d", game->lines_cleared);
        }
        
        printf("\n");
    }
    
    // 绘制底部边框
    printf("└");
    for (int i = 0; i < BOARD_WIDTH; i++) printf("──");
    printf("┘\n");
    
    // 绘制控制说明
    printf("\nControls:\n");
    printf("  A/D - Move Left/Right\n");
    printf("  S   - Soft Drop\n");
    printf("  W   - Rotate\n");
    printf("  Space - Hard Drop\n");
    printf("  P   - Pause/Resume\n");
    printf("  Q   - Quit\n");
    
    if (game->pause) {
        printf("\n╔══════════════╗\n");
        printf("║   PAUSED     ║\n");
        printf("╚══════════════╝\n");
    }
}

// 处理用户输入
void handleInput(Game* game) {
    int input = getInput();
    
    if (game->pause && input != 'p' && input != 'P' && input != 'q' && input != 'Q') {
        return;
    }
    
    switch (input) {
        case 'a': case 'A':
            moveTetromino(game, -1, 0);
            break;
        case 'd': case 'D':
            moveTetromino(game, 1, 0);
            break;
        case 's': case 'S':
            if (!moveTetromino(game, 0, 1)) {
                lockTetromino(game);
                clearLines(game);
            }
            break;
        case 'w': case 'W':
            rotateTetromino(game);
            break;
        case ' ':
            // 硬降落：一直下落直到不能下落
            while (moveTetromino(game, 0, 1)) {
                game->score += 2;  // 硬降落奖励分数
            }
            lockTetromino(game);
            clearLines(game);
            break;
        case 'p': case 'P':
            game->pause = !game->pause;
            break;
        case 'q': case 'Q':
            game->game_over = 1;
            break;
    }
}

// 更新游戏状态（重力下落）
void updateGame(Game* game) {
    static int frame_counter = 0;
    frame_counter++;
    
    if (game->pause) {
        return;
    }
    
    // 下落速度：等级越高，下落越快
    int drop_interval = 20 - game->level;
    if (drop_interval < 3) drop_interval = 3;
    
    if (frame_counter >= drop_interval) {
        frame_counter = 0;
        
        if (!moveTetromino(game, 0, 1)) {
            lockTetromino(game);
            clearLines(game);
        }
    }
}

// 主函数
int main() {
    Game game;
    
    setNonBlockingInput();
    atexit(resetTerminal);
    
    initGame(&game);
    
    printf("俄罗斯方块 - 按任意键开始...\n");
    getchar();
    
    while (!game.game_over) {
        drawGame(&game);
        handleInput(&game);
        updateGame(&game);
        usleep(50000);  // 20 FPS
    }
    
    drawGame(&game);
    printf("\n╔══════════════════════╗\n");
    printf("║     游戏结束！       ║\n");
    printf("║  最终得分: %-6d   ║\n", game.score);
    printf("╚══════════════════════╝\n");
    printf("按任意键退出...\n");
    
    // 恢复阻塞输入以等待按键
    resetTerminal();
    getchar();
    
    return 0;
}