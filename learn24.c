#include <stdio.h>
#include <stdbool.h>

bool is_prime(int num) {
    if (num <= 1) {
        return false;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    printf("请输入一个正整数：");
    scanf("%d", &n);

    int primes[n]; // 用于存储素数的数组
    int count = 0;

    printf("1 到 %d 之间的素数有：", n);
    for (int i = 2; i <= n; i++) {
        if (is_prime(i)) {
            primes[count] = i;
            count++;
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}