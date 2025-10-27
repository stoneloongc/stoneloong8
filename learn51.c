#include<stdio.h>
#include <stdlib.h> 
void merge(int *nums1,int m,int *nums2,int n)
{
    int p1=0,p2=0,cur;
    //int sorted[m+n]
    int *sorted = malloc((m + n) * sizeof(int));
    while(p1<m || p2<n)
    {
        if(p1==m)
        cur=nums2[p2++];
        else if(p2==n)
        cur=nums1[p1++];
        else if(nums1[p1]<=nums2[p2])//稳定性
        cur=nums1[p1++];
        else
        cur=nums2[p2++];
        sorted[p1+p2-1]=cur;
    }
    for(int i=0;i<m+n;i++)
    nums1[i]=sorted[i];
    free(sorted);
}
int main()
{
    int nums1[100]={2,6,7},nums2[]={1,2,5};
    int m=3,n=3;
    merge(nums1,m,nums2,n);
    for(int i=0;i<m+n;i++)
    printf("%d\n",nums1[i]);
    return 0;
}