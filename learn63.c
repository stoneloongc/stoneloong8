//递归反序链表
#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int data;
    struct Node *next;
}Node;

Node *head=NULL;

void Insert(int data,int n){
    Node* temp1=(Node*)malloc(sizeof(Node));
    temp1->data=data;
    temp1->next=NULL;
    if(n==1){
        temp1->next=head;
        head=temp1;
        return;
    }
    Node*temp2=head;
    for(int i=0;i<n-2;i++){
        if(temp2==NULL){
            printf("List is too short to insert at position %d\n", n);
            free(temp1);
            return;
        }
        temp2=temp2->next;
    }
    temp1->next=temp2->next;
    temp2->next=temp1;
}

void print(Node*p)
{
    if(p==NULL)
    return;
    printf("%d",p->data);
    print(p->next);
}
void reverse(Node *p){
    if(p->next==NULL)
    {
        head = p;
        return;
    }
    reverse(p->next);
    Node *q=p->next;
    q->next=p;
    p->next=NULL;
    }
int main(){
    head = NULL;
    Insert(2,1);
    Insert(3,2);
    Insert(4,3);
    Insert(5,4);
    print(head);
    reverse(head);
    print(head);
    return 0;
}
