#include<stdio.h>
int main()
{
    int arr1[] = {1,2,3};
    int arr2[] = {4,5,6};
    int arr3[] = {7,8,9};
    int *parr[3] = {arr1,arr2,arr3};
    int i=0,j=0;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            printf("%d ",parr[i][j]);
        }
        printf("\n");
       
    }
   
    return 0;
}