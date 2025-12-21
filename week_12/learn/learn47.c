#include <stdio.h>
int unique(int *a,int size)
{
    if(size==0)
    {
        return 0;
    }
    int i=1,j=1;
    while(j<size)
    {
        if(a[j]!=a[j-1])
        {
            a[i]=a[j];
            i++;
        }
        j++;
        
    }    
    return i;
}
int main()
{
    int num[]={1,2,3,3,4,4};
    int size =sizeof(num)/sizeof(num[0]);
    int new=unique(num,size);
    printf("当前数组长度:%d\n",new);
    printf("去重后数组元素：");
    for(int i=0;i<new;i++)
    {
        printf("%d ",num[i]);
    }
    return 0;
}