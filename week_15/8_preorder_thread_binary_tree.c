#include <stdio.h>
#include <stdlib.h>

// 定义最大树节点数（与原代码一致）
#define MAX_TREE_SIZE 256
// 定义节点数据类型
typedef int ElemType;

// 1. 线索二叉树节点结构
typedef struct ThreadTreeNode {
    ElemType value;               // 数据域
    struct ThreadTreeNode *left;  // 左指针（孩子/前驱线索）
    struct ThreadTreeNode *right; // 右指针（孩子/后继线索）
    int lTag;                     // 左标记：0=左孩子，1=前驱线索
    int rTag;                     // 右标记：0=右孩子，1=后继线索
} ThreadTreeNode;

// 全局前驱节点指针（线索化时记录上一个节点）
ThreadTreeNode *preNode = NULL;

// 2. 前序线索化核心函数（修正后继线索条件）
void PreOrderThread(ThreadTreeNode *node) {
    if (node != NULL) {
        // a. 为当前节点设置前驱线索
        if (node->left == NULL) {
            node->left = preNode;
            node->lTag = 1;
        }

        // b. 为前驱节点设置后继线索（修正：判断preNode->right是否为空）
        if (preNode != NULL && preNode->right == NULL) {
            preNode->right = node;
            preNode->rTag = 1;
        }

        // c. 更新前驱节点为当前节点
        preNode = node;

        // 递归左子树（仅左孩子时递归）
        if (node->lTag == 0) {
            PreOrderThread(node->left);
        }

        // 递归右子树（仅右孩子时递归）
        if (node->rTag == 0) {
            PreOrderThread(node->right);
        }
    }
}

// 3. 创建前序线索二叉树（初始化前驱+处理最后一个节点）
void CreatePreOrderThread(ThreadTreeNode *root) {
    // 重置全局前驱节点
    preNode = NULL;
    if (root != NULL) {
        // 执行线索化
        PreOrderThread(root);
        // 处理最后一个节点的右线索
        if (preNode != NULL) {
            preNode->right = NULL;
            preNode->rTag = 1;
        }
    }
}

// 4. 前序递归遍历线索二叉树
void PreOrder(ThreadTreeNode *node) {
    if (node != NULL) {
        // 访问节点（输出数据）
        printf("%d->", node->value);

        // 左孩子存在则递归
        if (node->lTag == 0) {
            PreOrder(node->left);
        }
        // 右孩子存在则递归
        if (node->rTag == 0) {
            PreOrder(node->right);
        }
    }
}

// 5. 前序非递归遍历线索二叉树
void PreOrderByFor(ThreadTreeNode *node) {
    ThreadTreeNode *cursor = node;
    while (cursor != NULL) {
        // 访问节点
        printf("%d->", cursor->value);
        // 左孩子存在则走左孩子，否则走后继线索
        if (cursor->lTag == 0) {
            cursor = cursor->left;
        } else {
            cursor = cursor->right;
        }
    }
}

// 辅助：创建节点（用于测试）
ThreadTreeNode* createNode(ElemType val) {
    ThreadTreeNode *node = (ThreadTreeNode*)malloc(sizeof(ThreadTreeNode));
    node->value = val;
    node->left = NULL;
    node->right = NULL;
    node->lTag = 0;
    node->rTag = 0;
    return node;
}

// 主函数测试
int main() {
    // 构建测试二叉树：根(1)→左(2)→右(3)
    ThreadTreeNode *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);

    // 构建前序线索二叉树
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