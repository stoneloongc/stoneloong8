#include <stdio.h>

int main() {
    int a, b,i, n;
    printf("Friendly-number pairs smaller than 3000:\n");
    for (a = 1; a < 3000; a++) {
        for (b = 0,i=1; b <= a/2; b++) // Avoid duplicate pairs and a == b case
            if(!(a%i))b+=i;
        for (n=0,i = 1; i < b/2; i++)
            if(!(b%i))n+=i;
            if(n==a && a<b)//a<b可以避免亲和数被打印两次a>b一样
            printf("%4d%4d\n",a,b);
        }
      
    
    return 0;
}