#include <stdio.h>
 
int main() {
   int i,j,result;
   for(i=1;i<=9;i++){
        for(j=1;j<=i;j++){
            result=i*j;
            printf("%d*%d=%d\n",i,j,result);
        }printf("\n");
   }
    return 0;
}