#include<stdio.h>
#include<stdlib.h>

typedef char elemtype;

typedef struct treenode
{
    elemtype data;
    treenode *lchild;
    treenode *rchild;
}treenode;

typedef treenode* bitree;

char str[] = "abdh#k###e##cfi###g#j##";
int idx = 0;

void createtree(bitree* t)
{
    elemtype ch;
    ch = str[idx++];
    if(ch == '#')
    {
        *t = NULL;
    }
    else{
        *t = (bitree)malloc(sizeof(treenode));
        (*t)->data = ch;
        createtree(&(*t)->lchild);
        createtree(&(*t)->rchild);
    }
}

void preorder(bitree t)
{
    if(t == NULL)
    {
        return;
    }
    printf("%c",t->data);
    preorder(t->lchild);
    preorder(t->rchild);
}

int main()
{
    bitree t;
    createtree(&t);

    preorder(t);
    printf("\n");

    return 0;
}