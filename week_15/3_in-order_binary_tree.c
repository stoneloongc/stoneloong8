#include<stdio.h>
#include<stdlib.h>

typedef char elemtype;

typedef struct treenode
{
    elemtype data;
    struct treenode *lchild;
    struct treenode *rchild;
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
        createtree(&(*t)->lchild);
        (*t)->data = ch;
        createtree(&(*t)->rchild);
    }
}

void inorder(bitree t)
{
    if(t == NULL)
    {
        return;
    }
    inorder(t->lchild);
    printf("%c",t->data);
    inorder(t->rchild);
}

int main()
{
    bitree t;
    createtree(&t);

    inorder(t);
    printf("\n");

    return 0;
}