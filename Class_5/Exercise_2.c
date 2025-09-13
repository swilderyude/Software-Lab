// 双向链表的建立、插入和删除操作
// 建立一个双向链表，输入一串随机指定位数的整数并排序（升序或者降序），同时可以实现插入节点、删除节点、节点显示等操作，编写一个菜单，由用户选择执行哪一种操作（插入/删除/按值查询），并输出链表。
// 查询
// 开始输入数字用空格分开
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node
{
    struct node *prior;
    int score;
    struct node *next;
} LinkList;

LinkList *init();
void insert(int score);
void del(int score);
void find(int score);
void prints();
void menu();

LinkList *head, *tail;

LinkList *init()
{
    LinkList *node = (LinkList *)malloc(sizeof(LinkList));
    node->prior = NULL;
    node->next = NULL;
    return node;
}
// 插入（升序）
void insert(int score)
{
    LinkList *newNode = init();
    newNode->score = score;

    if (head->next == tail)
    {
        head->next = newNode;
        newNode->prior = head;
        newNode->next = tail;
        tail->prior = newNode;
        return;
    }
    LinkList *current = head->next;

    while (current != tail && current->score < score)
    {
        current = current->next;
    }
    newNode->next = current;
    newNode->prior = current->prior;
    current->prior->next = newNode;
    current->prior = newNode;
}
// 删除
void del(int score)
{
    if (head->next == tail)
    {
        printf("链表为空，无法删除\n");
        return;
    }
    LinkList *current = head->next;
    int found = 0;

    while (current != tail)
    {
        if (current->score == score)
        {
            found = 1;
            // 保存下一个节点
            LinkList *nextNode = current->next;
            // 删除当前节点
            current->prior->next = current->next;
            current->next->prior = current->prior;
            free(current);
            current = nextNode;
        }
        else
        {
            current = current->next;
        }
    }
    if (found)
        printf("已删除所有值为 %d 的节点\n", score);
    else
        printf("未找到值为 %d 的节点\n", score);
}
// 按值查询
void find(int score)
{
    if (head->next == tail)
    {
        printf("链表为空\n");
        return;
    }

    LinkList *current = head->next;
    int forwardPos = 1;
    int found = 0;
    int firstForwardPos = -1, lastForwardPos = -1;
    // 正向查找
    while (current != tail)
    {
        if (current->score == score)
        {
            if (!found)
            {
                firstForwardPos = forwardPos;
                found = 1;
            }
            lastForwardPos = forwardPos;
        }
        current = current->next;
        forwardPos++;
    }
    if (found)
    {
        // 计算反向位置（总数 - 正向位置 + 1）
        int totalNodes = 0;
        current = head->next;
        while (current != tail)
        {
            totalNodes++;
            current = current->next;
        }
        int lastReversePos = totalNodes - firstForwardPos + 1;
        int firstReversePos = totalNodes - lastForwardPos + 1;

        printf("%d位于正向链表第%d", score, firstForwardPos);
        if (firstForwardPos != lastForwardPos)
            printf("到第%d位", lastForwardPos);
        else
            printf("位");

        printf("，位于反向链表第%d", firstReversePos);
        if (firstReversePos != lastReversePos)
            printf("到第%d位", lastReversePos);
        else
            printf("位");
        printf("\n");
    }
    else
    {
        printf("%d不存在于链表中\n", score);
    }
}
// 显示链表
void prints()
{
    if (head->next == tail)
    {
        printf("链表为空\n");
        return;
    }
    // 正向输出
    printf("链表(Next): ");
    LinkList *current = head->next;
    while (current != tail)
    {
        printf("%d", current->score);
        if (current->next != tail)
            printf("->");
        current = current->next;
    }
    printf("\n");
    // 反向输出
    printf("链表(Prior): ");
    current = tail->prior;
    while (current != head)
    {
        printf("%d", current->score);
        if (current->prior != head)
            printf("->");
        current = current->prior;
    }
    printf("\n");
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
    tail = init();
    head->next = tail;
    tail->prior = head;

    int choice, value, count;

    printf("=== 双向链表 ===\n");
    printf("输入整数的个数：");
    scanf("%d", &count);

    printf("输入%d位整数：", count);
    for (int i = 0; i < count; i++)
    {
        scanf("%d", &value);
        insert(value);
    }
    prints();

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
            printf("插入: ");
            if (scanf("%d", &value) == 1)
            {
                insert(value);
                prints();
            }
            else
            {
                printf("输入无效\n");
            }
            break;

        case 2:
            printf("删除: ");
            if (scanf("%d", &value) == 1)
            {
                del(value);
                prints();
            }
            else
            {
                printf("输入无效\n");
            }
            break;

        case 3:
            printf("查询: ");
            if (scanf("%d", &value) == 1)
            {
                find(value);
            }
            else
            {
                printf("输入无效\n");
            }
            break;

        case 4:
            prints();
            break;

        case 0:
            printf("程序退出\n");
            while (head->next != tail)
            {
                LinkList *temp = head->next;
                head->next = temp->next;
                free(temp);
            }
            free(head);
            free(tail);
            return 0;

        default:
            printf("无效选择，请重新输入\n");
        }
    }

    return 0;
}