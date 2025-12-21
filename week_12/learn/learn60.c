//删除链表中任意值
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
void print(){
    Node*temp = head;
    while(temp!=NULL){
        printf("%d",temp->data);
        temp = temp ->next;
    }
    printf("\n");
}
void delete(int n)
{
    Node *temp1 =head;
    if(n==1)
    {
        head=temp1->next;
        free(temp1);
        return ;
    }
    int i;
    for(i=0;i<n-2;i++){
        temp1=temp1->next;
        Node *temp2=temp1->next;
        temp1->next=temp2->next;
        free(temp2);
    }
}
int main(){
    head = NULL;
    Insert(2,1);
    Insert(3,2);
    Insert(4,3);
    Insert(5,4);
    print();
    delete(3);
    print();
    return 0;
}
