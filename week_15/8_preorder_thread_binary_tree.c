#include <stdio.h>
#include <stdlib.h>


#define MAX_TREE_SIZE 256

typedef int ElemType;


typedef struct ThreadTreeNode {
    ElemType value;               
    struct ThreadTreeNode *left;  
    struct ThreadTreeNode *right;
    int lTag;                     
    int rTag;                     
} ThreadTreeNode;


ThreadTreeNode *preNode = NULL;


void PreOrderThread(ThreadTreeNode *node) {
    if (node != NULL) {
       
        if (node->left == NULL) {
            node->left = preNode;
            node->lTag = 1;
        }

        
        if (preNode != NULL && preNode->right == NULL) {
            preNode->right = node;
            preNode->rTag = 1;
        }

        
        preNode = node;

       
        if (node->lTag == 0) {
            PreOrderThread(node->left);
        }

        
        if (node->rTag == 0) {
            PreOrderThread(node->right);
        }
    }
}


void CreatePreOrderThread(ThreadTreeNode *root) {
    preNode = NULL;
    if (root != NULL) {
        PreOrderThread(root);
        if (preNode != NULL) {
            preNode->right = NULL;
            preNode->rTag = 1;
        }
    }
}

//前序递归遍历线索二叉树
void PreOrder(ThreadTreeNode *node) {
    if (node != NULL) {
       
        printf("%d->", node->value);

        
        if (node->lTag == 0) {
            PreOrder(node->left);
        }
        
        if (node->rTag == 0) {
            PreOrder(node->right);
        }
    }
}

//前序非递归遍历线索二叉树
void PreOrderByFor(ThreadTreeNode *node) {
    ThreadTreeNode *cursor = node;
    while (cursor != NULL) {
        
        printf("%d->", cursor->value);
       
        if (cursor->lTag == 0) {
            cursor = cursor->left;
        } else {
            cursor = cursor->right;
        }
    }
}


ThreadTreeNode* createNode(ElemType val) {
    ThreadTreeNode *node = (ThreadTreeNode*)malloc(sizeof(ThreadTreeNode));
    node->value = val;
    node->left = NULL;
    node->right = NULL;
    node->lTag = 0;
    node->rTag = 0;
    return node;
}


int main() {
    
    ThreadTreeNode *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);

   
    CreatePreOrderThread(root);

    // 递归遍历
    printf("前序递归遍历：");
    PreOrder(root);
    printf("\n");

    // 非递归遍历
    printf("前序非递归遍历：");
    PreOrderByFor(root);
    printf("\n");

    return 0;
}