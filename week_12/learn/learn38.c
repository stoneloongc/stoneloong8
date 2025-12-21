#include<stdio.h>

int sequence(int *arr,int size)
{
    int sum=0;
    for(int i=0;i<size;i++)
    {
        printf("%d ",arr[i]);
        sum+= arr[i];
    }
    printf("\n");
    return sum;
}
int main()
{
    int arr1[5]={1,2,3,4,5};
    sequence(arr1,5);
    int t=sequence(arr1,5);
    //printf("%d\n",t);
    return 0;

}