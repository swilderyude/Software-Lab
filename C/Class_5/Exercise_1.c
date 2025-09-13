// 单向链表的建立、插入和删除操作。
// 建立一个单向链表，输入一串随机指定位数的整数并排序（升序或者降序），同时可以实现插入节点、删除节点、节点显示等操作，编写一个菜单，由用户选择执行哪一种操作（插入/删除/按值查询），并输出链表。
// 查询
// 开始输入数字用空格分开
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int score;
    struct node *next;
} LinkList;

LinkList *init();
void insert(int score);
void del(int score);
void prints();
void find(int score);
void menu();

LinkList *head;

LinkList *init()
{
    LinkList *node = (LinkList *)malloc(sizeof(LinkList));
    node->next = NULL;
    return node;
}
// 插入（升序）
void insert(int score)
{
    LinkList *newNode = init();
    newNode->score = score;

    if (head->next == NULL)
    {
        head->next = newNode;
        return;
    }

    LinkList *current = head->next;
    LinkList *prev = head;

    while (current != NULL && current->score < score)
    {
        prev = current;
        current = current->next;
    }

    prev->next = newNode;
    newNode->next = current;
}
// 删除
void del(int score)
{
    if (head->next == NULL)
    {
        printf("链表为空，无法删除\n");
        return;
    }

    LinkList *current = head->next;
    LinkList *prev = head;
    int found = 0;

    while (current != NULL)
    {
        if (current->score == score)
        {
            found = 1;
            prev->next = current->next;
            free(current);
            current = prev->next;
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }

    if (found)
        printf("已删除所有值为 %d 的节点\n", score);
    else
        printf("未找到值为 %d 的节点\n", score);
}
// 显示链表
void prints()
{
    if (head->next == NULL)
    {
        printf("链表为空\n");
        return;
    }

    printf("链表：");
    LinkList *current = head->next;
    while (current != NULL)
    {
        printf("%d", current->score);
        if (current->next != NULL)
            printf(" -> ");
        current = current->next;
    }
    printf("\n");
}
// 按值查询
void find(int score)
{
    if (head->next == NULL)
    {
        printf("链表为空\n");
        return;
    }

    LinkList *current = head->next;
    int position = 1;
    int found = 0;
    int firstPos = -1, lastPos = -1;

    while (current != NULL)
    {
        if (current->score == score)
        {
            if (!found)
            {
                firstPos = position;
                found = 1;
            }
            lastPos = position;
        }
        current = current->next;
        position++;
    }

    if (found)
    {
        if (firstPos == lastPos)
            printf("%d 位于链表第 %d 位\n", score, firstPos);
        else
            printf("%d 位于链表第 %d 到第 %d 位\n", score, firstPos, lastPos);
    }
    else
    {
        printf("%d 不存在于链表中\n", score);
    }
}
// 显示菜单
void menu()
{
    printf("\n请选择操作：\n");
    printf("1: 插入节点\n");
    printf("2: 删除节点\n");
    printf("3: 按值查询\n");
    printf("4: 显示链表\n");
    printf("0: 退出\n");
    printf("请输入选择: ");
}

int main()
{
    head = init();
    int n, value, choice;

    printf("=== 单向链表 ===\n");
    printf("输入整数的个数：");
    scanf("%d", &n);
    printf("输入 %d 个整数：", n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &value);
        insert(value);
    }

    prints();

    while (1)
    {
        menu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("请输入要插入的值: ");
            scanf("%d", &value);
            insert(value);
            prints();
            break;

        case 2:
            printf("请输入要删除的值: ");
            scanf("%d", &value);
            del(value);
            prints();
            break;

        case 3:
            printf("请输入要查询的值: ");
            scanf("%d", &value);
            find(value);
            break;

        case 4:
            prints();
            break;

        case 0:
            printf("程序退出\n");
            return 0;

        default:
            printf("无效选择，请重新输入\n");
        }
    }

    return 0;
}