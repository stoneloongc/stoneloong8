//rand与srand用法
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // 用于获取当前时间

int main() {
    // 设置随机数种子
    srand(time(NULL)); // 使用当前时间作为种子

    // 生成一个随机数
    int random_number = rand();
    printf("随机数: %d\n", random_number);

    // 生成一个范围在 0 到 99 之间的随机数
    int random_number_range = rand() % 100; // rand() % 100 会生成 0 到 99 的随机数
    printf("范围在 0 到 99 的随机数: %d\n", random_number_range);

    return 0;
}