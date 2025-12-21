#include<stdio.h>
void func(int (*b)[2][2])
{

}
int main()
{
    int b[3][2][2]={{{2,5},{7,9}},{{3,4},{6,1}},{{0,8},{11,13}}};
    func(b);
}
