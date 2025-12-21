#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<termios.h>
#include<stdlib.h>

#define WIDE 50
#define HIGH 20

struct BODY
{
    int x;
    int y;
};
struct SNAKE{
    int size;
    struct BODY body[WIDE*HIGH];
}snake;
struct FOOD{
    int x;
    int y;
}food;

int move_x = 1;  // 初始向右
int move_y = 0;

int game_over = 0;

void position(void)
{
    snake.size = 2;
    snake.body[0].x = WIDE/2;
    snake.body[0].y = HIGH/2;
    snake.body[1].x = WIDE/2-1;
    snake.body[1].y = HIGH/2;
    food.x = rand()%(WIDE-3);
    food.y = rand()%(HIGH-3);
}

void draw(void)
{
    system("clear");
    int x=0,y=0;
    for(y=0;y<HIGH;y++)
    {
        for(x=0;x<WIDE;x++)
        {
            int judge = 0;
            if(y==0 || y==HIGH-1)
            {
                putchar('-');
                judge = 1;
            }
            else if(x==0 || x==WIDE-1)
            {
                putchar('|');
                judge = 1;
            }
            else if(food.x == x && food.y == y)
            {
                putchar('*');
                judge = 1;
            }
            else
            {
                for(int i=0;i<snake.size;i++)
                {
                    if(x==snake.body[i].x && y==snake.body[i].y)
                    {
                        putchar(i == 0 ? 'O' : 'o');
                        judge = 1;
                        break;
                    }
                }
            }
            if(!judge)
            {
                putchar(' ');
            }
        }
        printf("\n");
    }
     printf("Score: %d | Use WASD to move, Q to quit\n", snake.size - 2);
}


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



void key(void)
{
    char intput = getInput();
    switch(intput)
    {
        case 'w': case 'W':if(move_y != 1){move_x = 0;move_y = -1;}break;
        case 's': case 'S':if(move_y != -1){move_x = 0;move_y = 1;}break;
        case 'a': case 'A':if(move_x != 1){move_x = -1;move_y = 0;;}break;
        case 'd': case 'D':if(move_x != -1){move_x = 1;move_y = 0;}break;
        case 'q': case 'Q':game_over = 1;return;
        default:break;
    }
}

void mv(void)
{
    int new_x = snake.body[0].x + move_x,new_y = snake.body[0].y + move_y;
    if(new_x<0 || new_x>WIDE-1 || new_y<0 || new_y>HIGH-1)
    {
            game_over = 1;
            return;
    }
    for(int i =1;i<snake.size;i++)
    {
        if(new_x==snake.body[i].x && new_y == snake.body[i].y)
        {
            game_over = 1;
            return;
        }
        
    }

        if(new_x == food.x && new_y == food.y)
        {
                snake.size++;
                food.x = rand()%(WIDE-3);
                food.y = rand()%(HIGH-3);
        }
        for(int i =snake.size-1;i>0;i--)
        {
            snake.body[i].x = snake.body[i-1].x ;
            snake.body[i].y = snake.body[i-1].y ;
        }
        snake.body[0].x = new_x ;
        snake.body[0].y = new_y ;
}




int main()
{
    srand(time(NULL));
    
    setNonBlockingInput();
    
    atexit(resetTerminal);
    position();
    while(!game_over)
    {
        
        draw();
        key();
        mv();
        usleep(100000);
    }
    printf("游戏结束\n");
    return 0;
}
