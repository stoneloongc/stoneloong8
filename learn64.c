#include<stdio.h>
#include<stdlib.h>
typedef struct Node {
    int data;
    Node *next;
    Node *prev;
}Node;

Node* head;


Node *getnewnode(int x)
{
    Node *newnode=(Node*)malloc(sizeof(Node));
    newnode->data = x;
    newnode->next = NULL;
    newnode->next = NULL;
    return newnode;
}

void inserthead(int x){
    Node*newnode = getnewnode(x);
    if(head==NULL){
        head = newnode;
        return;
    }
    head->prev = newnode;
    newnode->next = head;
    head = newnode;
}

void print()
{
    Node *temp=head;
    while(temp != NULL){
        printf("%d",temp->data);
        temp=temp->next;
    }
    printf("\n");
}

int main()
{
    head =NULL;
    inserthead(2);print();
}