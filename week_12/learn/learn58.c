#include<stdio.h>
typedef struct Node{
    int date;
    Node *link;
}Node;
int main()
{
    Node *A=NULL;
    Node *t=(Node*)malloc(sizeof(Node));
    Node *t1=(Node*)malloc(sizeof(Node));
    (*t).date=2;
    (*t).link=t1;
    A=t;
    t1 ->date =4;
    t1 ->link =NULL;
}
/*#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int date;
    struct Node *link;
} Node;

int main(void)
{
    //1. 手动建 3 节: 10→20→30 
    Node n1 = {10, NULL};
    Node n2 = {20, NULL};
    Node n3 = {30, NULL};
    n1.link = &n2;
    n2.link = &n3;          // n3.link 保持 NULL

    Node *A = &n1;          // 头指针

    //2. 遍历找尾（核心
    Node *temp = A;         // temp 从头开始
    while (temp->link != NULL)
        temp = temp->link;  // 往后跳
    // 现在 temp 指向第 3 节（30

    //3. 在尾巴后面插入 40
    Node newNode = {40, NULL};
    temp->link = &newNode;  // 旧尾→新节点

    // 4. 打印验证: 10 20 30 40
    for (Node *p = A; p; p = p->link)
        printf("%d ", p->date);
}*/