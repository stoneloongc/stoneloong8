#include <stdio.h>

int main() {
    // 定义字符图形
    const char *c_pattern[] = {
        " ****",
        " *",
        " *",
        " ****"
    };//一个字符串对应一个指针

    // 输出字符图形
    printf("用 * 号输出字母 C!\n");
    for (int i = 0; i < sizeof(c_pattern) / sizeof(c_pattern[0]); i++) {
        printf("%s\n", c_pattern[i]);
    }

    return 0;
}