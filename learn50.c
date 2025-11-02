#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
int main()
{
    srand(time(NULL));
    int x=rand()%10;
    int a;
    scanf("%d",&a);
    if(a==x)
    printf("对");
    else
    printf("错");

    return 0;
}