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
        createtree(&(*t)->rchild);
        (*t)->data = ch;
    }
}

void postorder(bitree t)
{
    if(t == NULL)
    {
        return;
    }
    postorder(t->lchild);
    postorder(t->rchild);
    printf("%c",t->data);
}

int main()
{
    bitree t;
    createtree(&t);

    postorder(t);
    printf("\n");

    return 0;
}