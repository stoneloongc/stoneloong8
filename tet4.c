#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<termios.h>
#include<fcntl.h>  // 添加这个头文件

#define WIDE 50
#define HIGH 20

//定义蛇
struct BODY{
    int x;
    int y;
};

struct SNAKE{
    int size;
    struct BODY body[HIGH*WIDE];
}snake;

//定义食物
struct FOOD{
    int x;
    int y;
}food;

// Linux非阻塞输入
int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

//画墙和游戏内容
void initwall(void){
    printf("\033[2J\033[1;1H"); // Linux清屏
    for(int i=0;i<HIGH;i++)
    {
        for(int j=0;j<WIDE;j++)
        {
            int isBody = 0;
            // 检查是否是蛇身
            for(int k=0;k<snake.size;k++){
                if(snake.body[k].x == j && snake.body[k].y == i){
                    printf("@");
                    isBody = 1;
                    break;
                }
            }
            if(isBody) continue;
            
            // 检查是否是食物
            if(food.x == j && food.y == i){
                printf("*");
            }
            else if(i == 0 || i == HIGH-1)
            {
                printf("-");
            }
            else if(j == 0 || j == WIDE-1)
            {
                printf("|");
            }
            else
                printf(" ");
        }
        printf("\n");
    }
    return;
}

//初始化蛇位置
void initsnake(void)
{
    snake.size = 2;
    snake.body[0].x = WIDE/2;
    snake.body[0].y = HIGH/2;
    snake.body[1].x = WIDE/2-1;
    snake.body[1].y = HIGH/2;
}

//初始化食物位置
void initfood(void)
{
    int valid;
    do{
        valid = 1;
        food.x = rand()%(WIDE-2) + 1;
        food.y = rand()%(HIGH-2) + 1;
        
        // 检查食物是否与蛇身重叠
        for(int i=0;i<snake.size;i++){
            if(food.x == snake.body[i].x && food.y == snake.body[i].y){
                valid = 0;
                break;
            }
        }
    }while(!valid);
}

int main()
{
    int score = 0;
    int kx=1,ky=0;
    char key = 'd';
    
    srand(time(NULL));
    initsnake();
    initfood();
    
    //游戏主循环
    while(1)
    {
        initwall();
        printf("Score: %d\n", score);
        
        //移动操作
        if(kbhit()){
            key = getchar();
        }
        
        switch(key)
        {
            case 'w': if(ky != 1) { kx = 0; ky = -1; } break;
            case 's': if(ky != -1) { kx = 0; ky = 1; } break;
            case 'a': if(kx != 1) { kx = -1; ky = 0; } break;
            case 'd': if(kx != -1) { kx = 1; ky = 0; } break;
            case 'q': printf("Game Over!\n"); return 0;
            default: break;
        }

        //边界检查
        if(snake.body[0].x <= 0 || snake.body[0].x >= WIDE-1 || 
           snake.body[0].y <= 0 || snake.body[0].y >= HIGH-1)
        {
            printf("Game Over! Hit the wall.\n");
            break;
        }

        //蛇自撞检查
        for(int i=1;i<snake.size;i++)
        {
            if(snake.body[0].x == snake.body[i].x && 
               snake.body[0].y == snake.body[i].y)
            {
                printf("Game Over! Hit yourself.\n");
                return 0;
            }
        }

        //蛇吃食物
        if(snake.body[0].x == food.x && snake.body[0].y == food.y)
        {
            snake.size++;
            score++;
            initfood();
        }

        //蛇移动
        for(int i = snake.size-1;i>0;i--)
        {
            snake.body[i].x = snake.body[i-1].x;
            snake.body[i].y = snake.body[i-1].y;
        }
        snake.body[0].x += kx;
        snake.body[0].y += ky;
        
        usleep(200000); // 控制游戏速度
    }
    
    return 0;
}