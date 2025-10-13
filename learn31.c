#include <stdio.h>
#define N 10

// 递归函数：反转数组
void reverse(int a[], int left, int right) {
    if (left >= right) return;  // 递归结束条件
    int t = a[left];
    a[left] = a[right];
    a[right] = t;
    reverse(a, left + 1, right - 1);  // 递归调用
}

int main() {
    int a[N] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    printf("原始数组为：");
    for (int i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    reverse(a, 0, N - 1);  // 调用递归函数

    printf("倒序数组为：");
    for (int i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}