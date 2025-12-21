//链表实现栈
#include<stdio.h>
#include<stdlib.h>
typedef struct Node
{
    int data;
    Node *link;
}Node;

struct Node *top = NULL;
void push(int x)
{
    Node *temp1 = (Node*)malloc(sizeof(Node*));
    temp1->data=x;
    temp1->link=top;
    top = temp1;
}
void pop()
{
    Node *temp1;
    if(top==NULL)
        return;
    temp1=top;
    top = top->link;
    free(temp1);
}
