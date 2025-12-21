#include <stdio.h>
#include <unistd.h> // 用于 sleep 函数

int main() {
    int target_speed;
    printf("--- 模拟电机控制台 ---\n");
    printf("请输入目标 PWM 速度 (0-100): ");
    scanf("%d", &target_speed);

    // 安全校验
    if (target_speed < 0 || target_speed > 100) {
        printf("参数非法。\n");
        return 1;
    }

    printf(">>> 开始软启动 (Soft Start) >>>\n");

    // 软启动逻辑
    for (int current_speed = 0; current_speed <= target_speed; current_speed += 5) {
        printf("[Motor] Current PWM: %d%%\n", current_speed);
        sleep(1); // 模拟一小段时间
    }

    printf(">>> 加速完成，定速巡航中 ... <<<\n");
    printf("请按任意键继续...\n");
    getchar(); // 等待用户输入
    return 0;
}