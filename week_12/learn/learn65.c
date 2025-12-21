//数组实现一个栈
#include<stdio.h>
#define MAX_SIZE 101
int A[MAX_SIZE];
int top=-1;
void push(int x)
{
    if(top==MAX_SIZE-1)
    {
        printf("stack overflow\n");
        return;
    }
    A[++top] = x;
}

void pop()
{
    if(top==-1)
    {
        printf("no element to pop\n");
        return;
    }
    top--;
}

void print()
{
    int i;
    printf("stack\n");
    for(i=0;i<=top;i++)
        printf("%d\t",A[i]);
    printf("\n");
}

int top1()
{
    return A[top];
}

int main()
{
    push(2);
    push(5);
    push(10);
    print();
    pop();
    push(12);
    print();
}