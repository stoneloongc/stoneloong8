#include <stdio.h>

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for(int i = 1; i <= n; i++)
     {
        result *= i;
    }
    return result;
}
 
int main() {
    unsigned long long sum = 0;
    
    for(int i = 1; i <= 20; i++)
     {
        sum += factorial(i);
    }
    
    printf("1 + 2! + 3! + ... + 20!的和是: %llu\n", sum);
    int a=0;
    a+=factorial(3);
    printf("%d\n",a);
    return 0;
}