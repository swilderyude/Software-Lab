// 搜索二叉树的建立、插入、删除以及遍历
// 搜索二叉树： 左<根<右
// 打印默认中序：从小到大
// 不一定平衡
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node
{
    struct node *left;
    int val;
    struct node *right;
} TreeNode;

typedef struct list
{
    struct list *next;
    TreeNode *val;
} LinkList;

TreeNode *init(int x);
LinkList *listInit(TreeNode *n);
void insert(int value);
TreeNode *deleteNode(TreeNode *root, int key);
void preorder(TreeNode *n);
void inorder(TreeNode *n);
void postorder(TreeNode *n);
void dfsorder(TreeNode *n);
void bfsorder(TreeNode *n);
void menu();
TreeNode *findMin(TreeNode *node);

TreeNode *root = NULL;

TreeNode *init(int x)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->left = NULL;
    node->right = NULL;
    node->val = x;
    return node;
}

LinkList *listInit(TreeNode *n)
{
    LinkList *list = (LinkList *)malloc(sizeof(LinkList));
    list->next = NULL;
    list->val = n;
    return list;
}
// 查找最小节点（用于删除操作）
TreeNode *findMin(TreeNode *node)
{
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}
// 插入节点
void insert(int value)
{
    TreeNode *newNode = init(value);
    if (root == NULL)
    {
        root = newNode;
        return;
    }
    TreeNode *current = root;
    TreeNode *parent = NULL;

    while (current != NULL)
    {
        parent = current;
        if (value < current->val)
        {
            current = current->left;
        }
        else if (value > current->val)
        {
            current = current->right;
        }
        else
        {
            free(newNode);
            return;
        }
    }

    if (value < parent->val)
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }
}
// 删除节点
TreeNode *deleteNode(TreeNode *root, int key)
{
    if (root == NULL)
    {
        printf("值 %d 不存在于树中\n", key);
        return root;
    }

    if (key < root->val)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->val)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        // 找到要删除的节点
        // 情况1：没有左子节点（可能有右子节点，也可能没有）
        if (root->left == NULL)
        {
            TreeNode *temp = root->right; // 用右子节点替代当前节点
            free(root);
            return temp;
        }
        // 情况2：没有右子节点（但有左子节点）
        else if (root->right == NULL)
        {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }

        // 情况3：有两个子节点
        TreeNode *temp = findMin(root->right);
        root->val = temp->val;
        root->right = deleteNode(root->right, temp->val);
    }
    return root;
}
// 前序遍历
void preorder(TreeNode *n)
{
    if (!n)
        return;
    printf("%d ", n->val);
    preorder(n->left);
    preorder(n->right);
}
// 中序遍历
void inorder(TreeNode *n)
{
    if (!n)
        return;
    inorder(n->left);
    printf("%d ", n->val);
    inorder(n->right);
}
// 后序遍历
void postorder(TreeNode *n)
{
    if (!n)
        return;
    postorder(n->left);
    postorder(n->right);
    printf("%d ", n->val);
}
// 深度优先遍历（与前序遍历相同）
void dfsorder(TreeNode *n)
{
    preorder(n);
}
// 广度优先遍历
void bfsorder(TreeNode *n)
{
    if (n == NULL)
        return;
    LinkList *queue = listInit(n);
    LinkList *tail = queue;

    while (queue != NULL)
    {
        TreeNode *current = queue->val;
        printf("%d ", current->val);

        if (current->left != NULL)
        {
            tail->next = listInit(current->left);
            tail = tail->next;
        }

        if (current->right != NULL)
        {
            tail->next = listInit(current->right);
            tail = tail->next;
        }

        LinkList *temp = queue;
        queue = queue->next;
        free(temp);
    }
}
// 显示菜单
void menu()
{
    printf("\n=== 二叉搜索树操作菜单 ===\n");
    printf("1: 插入节点\n");
    printf("2: 删除节点\n");
    printf("3: 前序遍历\n");
    printf("4: 中序遍历\n");
    printf("5: 后序遍历\n");
    printf("6: 深度优先遍历\n");
    printf("7: 广度优先遍历\n");
    printf("0: 退出\n");
    printf("请输入选择: ");
}
// 打印树的信息
void printTreeInfo()
{
    if (root == NULL)
    {
        printf("树为空\n");
        return;
    }
    printf("根节点: %d\n", root->val);
    printf("中序遍历结果: ");
    inorder(root);
    printf("\n");
}

int main()
{
    int choice, value, count;

    printf("=== 二叉搜索树 ===\n");
    printf("输入整数的个数：");
    scanf("%d", &count);
    printf("输入 %d 个整数：", count);
    for (int i = 0; i < count; i++)
    {
        scanf("%d", &value);
        insert(value);
    }

    printf("生成的二叉搜索树：\n");
    printTreeInfo();

    while (1)
    {
        menu();

        if (scanf("%d", &choice) != 1)
        {
            printf("输入无效，请输入数字\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("请输入要插入的值: ");
            if (scanf("%d", &value) == 1)
            {
                insert(value);
                printf("插入后的树：\n");
                printTreeInfo();
            }
            else
            {
                printf("输入无效\n");
            }
            break;

        case 2:
            printf("请输入要删除的值: ");
            if (scanf("%d", &value) == 1)
            {
                root = deleteNode(root, value);
                printf("删除后的树：\n");
                printTreeInfo();
            }
            else
            {
                printf("输入无效\n");
            }
            break;

        case 3:
            printf("前序遍历: ");
            preorder(root);
            printf("\n");
            break;

        case 4:
            printf("中序遍历: ");
            inorder(root);
            printf("\n");
            break;

        case 5:
            printf("后序遍历: ");
            postorder(root);
            printf("\n");
            break;

        case 6:
            printf("深度优先遍历: ");
            dfsorder(root);
            printf("\n");
            break;

        case 7:
            printf("广度优先遍历: ");
            bfsorder(root);
            printf("\n");
            break;

        case 0:
            printf("程序退出\n");
            while (root != NULL)
            {
                root = deleteNode(root, root->val);
            }
            return 0;

        default:
            printf("无效选择，请重新输入\n");
        }
    }

    return 0;
}